/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: TemplateView.C,v $
 *  $Date: 1999/08/27 15:31:54 $
 *  $Revision: 1.1.1.1.2.1 $
 *
 *  Copyright 1995, Dirk Laessig
 *  ALL RIGHTS RESERVED
 *  See the file Copyright for more information
 *
 *  Dirk Laessig
 *  Goettingstr. 5
 *  38106 Braunschweig
 *  Germany
 ****************************************************************/
/*
 * $Log: TemplateView.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:31:54  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:17  lazy
 * Imported to CVS
 *
 * Revision 1.2  1998/03/30 19:08:42  lazy
 * *** empty log message ***
 *
 * Revision 1.1  1997/07/25  20:30:37  lazy
 * Initial revision
 *
 */

// ------------------------------ 
// TemplateView.C                      
// ------------------------------

#include "TemplateView.h"
#include "Lpalette.h"
#include "lic.h"
#include "Lwhere.h"
#include <Xm/ToggleB.h>
#include <unistd.h>

#define VD_WITH_SMALLICONS "WithSmallIcons"
#define VD_WITH_ICONS "WithIcons"
#define VD_WITH_CLASSES "WithClasses"
#define VD_CREATE_ON_CLICK "CreateOnClick"

RefArray<TemplateView> TemplateView::allViews;

// ------------------------------
// TemplateView()
// ------------------------------

TemplateView::TemplateView(Lpalette *model)
:TemplateView_base(NULL,NULL,0) 
{
  PaletteIcon *icon;
  Boolean b;

  this->model = model;
  setModel(model);

  controllerImpl.add(editButton, LWIDGET_EDIT);
  controllerImpl.add(browseButton, LWIDGET_BROWSE);
  controllerImpl.add(cutButton, LWIDGET_CUT);
  controllerImpl.add(copyButton, LWIDGET_COPY);
  controllerImpl.add(pasteButton, LWIDGET_PASTE);
  controllerImpl.add(deleteButton, LWIDGET_DELETE);

  icon = new PaletteIcon();
  icon->templateView = this;
  iconView = new WidgetIconView(model, templateFrame, icon);
  iconView->setDragOperations(XmDROP_COPY);
  XtManageChild(iconView->getTop());

  quickHelpLabel = quickHelp;
  
  dropSiteRegister();

  XmToggleButtonSetState(createOnClick, TRUE, TRUE);

  b = FALSE;
  XmToggleButtonSetState(smallIconButton, b, FALSE);
  model->getVDBoolean(this, VD_WITH_SMALLICONS, b);
  XmToggleButtonSetState(smallIconButton, b, TRUE);

  b = TRUE;
  XmToggleButtonSetState(withIconButton, b, FALSE);
  model->getVDBoolean(this, VD_WITH_ICONS, b);
  XmToggleButtonSetState(withIconButton, b, TRUE);

  b = TRUE;
  XmToggleButtonSetState(withClassNameButton, b, FALSE);
  model->getVDBoolean(this, VD_WITH_CLASSES, b);
  XmToggleButtonSetState(withClassNameButton, b, TRUE);
  
  b = TRUE;
  XmToggleButtonSetState(createOnClick, b, FALSE);
  model->getVDBoolean(this, VD_CREATE_ON_CLICK, b);
  XmToggleButtonSetState(createOnClick, b, TRUE);
  
  allViews.add(this);

  update(NAME_CHANGED);
}

// ------------------------------
// ~TemplateView()
// ------------------------------
TemplateView::~TemplateView()
{

}

// ------------------------------
// showView()
// ------------------------------
void TemplateView::showView(Lpalette *model)
{
  ::TemplateView *view = NULL;

  for(unsigned int i=0; i<allViews.getSize(); i++) {
    if(allViews[i]->model == model) {
      view = allViews[i];
      break;
    }
  }

  if(view == NULL)
    view = new ::TemplateView(model);

  view->open();
}

// ---------------------------------
// findPalette()
// ---------------------------------

Lpalette *TemplateView::findPalette( Widget dropOver )
{
  for(unsigned int i=0; i<allViews.getSize(); i++ ) {
    if( dropOver == allViews[i]->iconView->getTop() ) {
      return allViews[i]->model;
    }
    if( XtParent(dropOver) == allViews[i]->iconView->getTop() ) {
      return allViews[i]->model;
    }
    if( XtParent(XtParent(dropOver)) == allViews[i]->iconView->getTop() ) {
      return allViews[i]->model;
    }
  }
  return NULL;
}


// ---------------------------------
// update()
// ---------------------------------

void TemplateView::update(unsigned long flags)
{
  if(flags & NAME_CHANGED) {
    char title[PATH_MAX];
    msgCat->getMsg(title, TEMPLATES_TITLE, model->getFilename());
    XtVaSetValues(popupShell, 
		  XmNtitle, title,
		  XmNiconName, title,
		  NULL);
  }
}

// ---------------------------------
// dropSiteRegister()
// ---------------------------------

void TemplateView::dropSiteRegister()
{
  static Atom imports[1];
  Widget wg;
  
  wg = iconView->getTop();
  imports[0] = XmInternAtom(XtDisplay(wg), "Lwidget", False);
  
  Arg args[10];
  Cardinal n = 0;
  XtSetArg(args[n], XmNimportTargets, imports); n++;
  XtSetArg(args[n], XmNnumImportTargets, 1); n++;
  XtSetArg(args[n], XmNdropSiteOperations, XmDROP_COPY); n++;
  XtSetArg(args[n], XmNdropProc, dropProc); n++;
  XtSetArg(args[n], XmNdropSiteType, XmDROP_SITE_COMPOSITE); n++;
  XmDropSiteRegister(wg,args,n);
}

// ---------------------------------
// dropProp
// ---------------------------------

void TemplateView::dropProc(Widget wg, XtPointer, XtPointer callData)
{
  static XmDropTransferEntryRec transList[1];
  XmDropProcCallback dd = (XmDropProcCallback)callData;
  Arg args[10];
  Cardinal n=0;
  ::TemplateView *pv = NULL;

  for(unsigned int i=0; i<allViews.getSize(); i++ ) {
    if( wg == allViews[i]->iconView->getTop() ) {
      pv = allViews[i];
    }
  }

  if(!pv) {
    fprintf(stderr, "Fatal Error: pv==NULL in TemplateView\n");
  }
  transList[0].target = XmInternAtom(XtDisplay(wg), "Lwidget", False);
  transList[0].client_data = (XtPointer)pv;
  XtSetArg(args[n], XmNdropTransfers, transList); n++;
  XtSetArg(args[n], XmNnumDropTransfers, 1); n++;
  XtSetArg(args[n], XmNtransferProc, transferProc); n++;
  XmDropTransferStart(dd->dragContext,args,n);

}

// ---------------------------------
// transferProc()
// ---------------------------------

void TemplateView::transferProc(Widget w, XtPointer closure, 
			       Atom *, Atom *,
			       XtPointer value, unsigned long *, 
			       int *)
{
  if(!value) {
    XtVaSetValues(w, XmNtransferStatus, XmTRANSFER_FAILURE, NULL);
    return;
  }
  ::TemplateView *pv  = (::TemplateView*)closure;
  Lwidget **ptr = (Lwidget**)value;
  Lwidget *lwidget = *ptr;

  Lwidget *copied;
  copied = lwidget->copy();
  if( !copied ) {
    XtVaSetValues(w, XmNtransferStatus, XmTRANSFER_FAILURE, NULL);
    return;
  }
  //  copied->getProperties()->fillWithDefaults(copied->getClass()->getDummy());
  pv->model->add(copied);
  pv->model->changed(CONTAINER_CHANGED);
}
			   
// ------------------------------
// do_save()
// ------------------------------
void TemplateView::do_save(Widget, XtPointer)
{
  char title[256], msg[1024];
  Boolean result;
  Dimension width, height;
  
  XtVaGetValues(popupShell,
		XmNwidth, &width,
		XmNheight, &height,
		NULL);
  model->setVDLong(this,"width", (long)width);
  model->setVDLong(this,"height", (long)height);

  model->setVDBoolean(this, VD_WITH_CLASSES, 
		      XmToggleButtonGetState(withClassNameButton));
  model->setVDBoolean(this, VD_WITH_SMALLICONS, 
		      XmToggleButtonGetState(smallIconButton));
  model->setVDBoolean(this, VD_WITH_ICONS, 
		      XmToggleButtonGetState(withIconButton));
  model->setVDBoolean(this, VD_CREATE_ON_CLICK, 
		      XmToggleButtonGetState(createOnClick));


  if(model->isNew()) {
    XtManageChild(saveAsDialog);
    return;
  }

  setWaitCursor(TRUE);

  result =   model->save();

  setWaitCursor(FALSE);

  if(!result) {
    msgCat->getMsg(title, ERROR_TITLE );
    msgCat->getMsg(msg, ERROR_SEEN);
    LicView::MsgBox(title, msg, MSGBOX_STYLE_OK);
    return;
  }
}


// ------------------------------
// wmDelete()
// ------------------------------
void TemplateView::wmDelete()
{
  do_close(NULL, NULL);
}

// ------------------------------
// do_close()
// ------------------------------
void TemplateView::do_close(Widget, XtPointer)
{
  if(model->getChangedFlag()) {
    char title[256];
    char msg[1024];
    msgCat->getMsg(title, WARNING_TEMPLATE_CHANGED_TITLE);
    msgCat->getMsg(msg, WARNING_TEMPLATE_CHANGED_MSG, model->getFilename());
    
    if(MSGBOX_OK != MsgBox(title, msg, MSGBOX_STYLE_YESNO))
      return;
  }
  close();
  
  Lpalette *theModel = model;
  delete this;
  delete theModel;
}


// ------------------------------
// do_smallIcon()
// ------------------------------
void TemplateView::do_smallIcon(Widget, XtPointer)
{
  iconView->setWithSmallIcons(XmToggleButtonGetState(smallIconButton));
}


// ------------------------------
// do_withIcon()
// ------------------------------
void TemplateView::do_withIcon(Widget, XtPointer)
{
  iconView->setWithIcons(XmToggleButtonGetState(withIconButton));
}


// ------------------------------
// do_withClassName()
// ------------------------------
void TemplateView::do_withClassName(Widget, XtPointer)
{
  iconView->setWithClasses(XmToggleButtonGetState(withClassNameButton));
}


// ------------------------------
// do_widgetMenuMap()
// ------------------------------
void TemplateView::do_widgetMenuMap(Widget, XtPointer)
{
  if(Lwidget::clipboard.getSize() > 0) {
    XtSetSensitive(pasteToTemplateButton, TRUE);
  } else {
    XtSetSensitive(pasteToTemplateButton, FALSE);
  }
  controllerImpl.process(iconView);
}


// ------------------------------
// do_pasteToTemplate()
// ------------------------------
void TemplateView::do_pasteToTemplate(Widget, XtPointer)
{
  View::transactionBegin();
  for(unsigned int i=0; i<Lwidget::clipboard.getSize(); i++) {
    model->myAdd(Lwidget::clipboard[i]);
  }
  View::transactionEnd();
}


// ------------------------------
// do_clickOnCreate()
// ------------------------------
void TemplateView::do_clickOnCreate(Widget, XtPointer)
{
  createOnClickMode = XmToggleButtonGetState(createOnClick);
}


// ------------------------------
// do_onHelp()
// ------------------------------
void TemplateView::do_onHelp(Widget, XtPointer)
{
  getHelp(HID_USING_HELP);
}


// ------------------------------
// do_onContext()
// ------------------------------
void TemplateView::do_onContext(Widget, XtPointer)
{
  contextHelp();
}


// ------------------------------
// do_help()
// ------------------------------
void TemplateView::do_help(Widget, XtPointer)
{
  getHelp(HID_TEMPLATES);
}


// ------------------------------
// do_saveAs()
// ------------------------------
void TemplateView::do_saveAs(Widget, XtPointer)
{
  XmString xmstr;
  char *filename;
  char title[256], msg[1024];
  Boolean result;
  Dimension width, height;
  
  XtVaGetValues(popupShell,
		XmNwidth, &width,
		XmNheight, &height,
		NULL);
  model->setVDLong(this,"width", (long)width);
  model->setVDLong(this,"height", (long)height);

  XtVaGetValues(saveAsDialog, 
		XmNtextString, &xmstr,
		NULL );
  XmStringGetLtoR( xmstr, XmSTRING_DEFAULT_CHARSET, &filename );

  setWaitCursor(TRUE);

  result = model->save(filename);

  setWaitCursor(FALSE);

  if(!result) {
    msgCat->getMsg(title, ERROR_TITLE );
    msgCat->getMsg(msg, ERROR_SEEN);
    LicView::MsgBox(title, msg, MSGBOX_STYLE_OK);
    XtFree(filename);
    return;
  } else {
    model->setFilename(filename);
    model->changed(NAME_CHANGED);
  }

  XtFree(filename);
}


// ------------------------------
// do_mapSaveAsDialog()
// ------------------------------

void TemplateView::do_mapSaveAsDialog(Widget,XtPointer)
{
  XmString xmstr;
  char filename[PATH_MAX];

  if(model->isNew()) {
    getcwd(filename, PATH_MAX);
  } else {
    filename[0] = 0;
  }
  if(filename[0] != 0 && filename[strlen(filename)-1] != '/') {
    strcat(filename, "/");
  }
  strcat(filename, model->getFilename());
  xmstr = XmStringCreateLtoR(filename, XmSTRING_DEFAULT_CHARSET);
  XtVaSetValues(saveAsDialog, 
		XmNtextString, xmstr,
		NULL );
  XmStringFree(xmstr);
}



// ######################
//  PaletteIcon
// ######################

// ---------------------------------
// select()
// ---------------------------------

void PaletteIcon::select( Boolean b, Position x, Position y)
{
  YResult *dummy;
  Lwidget *parent;

  if(!templateView->getCreateOnClick()) {
    Icon::select(b, x, y);
    return;
  }

  Lwhere where( Lproject::current(), (Boolean)FALSE );

  if( where.isCanceled() ) {
    pressed = FALSE;
    draw();
    return;
  }

  dummy = (YResult*)malloc(sizeof(YResult));
  memset( dummy, 0, sizeof(YResult) );
  dummy->root_widget = lwidget->createYWidget();

  parent = where.getparent();
  if( parent ) {
    Lwidget *copied = new Lwidget( dummy->root_widget, parent );
    copied->getProperties()->setResource( "x", where.getx() );
    copied->getProperties()->setResource( "y", where.gety() );
    copied->moveTo( parent );
    parent->changed(CONTAINER_CHANGED);
  } else {
    Linterface *interface;
    if(lwidget->getClass()->isShell()) {
      interface = new Linterface(dummy->root_widget);
      app->getProject()->addInterface(interface);
    } else {
      interface = app->getProject()->addInterface();
      Lwidget *copied = new Lwidget(dummy->root_widget, interface->getShell());
      copied->moveTo(interface->getShell());
    }
    interface->show();
  }

  free_YResult(dummy);

  pressed = FALSE;
  draw();
}
