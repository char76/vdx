/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: WidBrowseView.C,v $
 *  $Date: 1999/08/27 15:32:13 $
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
 * $Log: WidBrowseView.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:32:13  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:16  lazy
 * Imported to CVS
 *
 * Revision 1.2  1998/02/10  00:53:48  lazy
 * Added support for enable/disable menu items
 * in createMenu.
 *
 * Revision 1.1  1997/07/25  20:36:03  lazy
 * Initial revision
 *
 */

// ------------------------------ 
// WidBrowseView.C                      
// ------------------------------

#include "WidBrowseView.h"
#include "Lwidget.h"
#include "lic.h"
#include "Lwhere.h"
#include <lac/Controller.h>

#include <ctype.h>
#include <Xm/ToggleB.h>

RefArray<WidBrowseView> WidBrowseView::allViews;
Ref<WidBrowseView> WidBrowseView::automaticLoadView;

// ------------------------------
// WidBrowseView()
// ------------------------------

WidBrowseView::WidBrowseView(Lwidget *lwidget)
:WidBrowseView_base(NULL,NULL,0), createCallback(this), popupCallback(this)
{
  quickHelpLabel = quickHelp;

  treeView = new WidgetTreeView(lwidget, treeFrame);
  XtManageChild(treeView->getTop());
  allViews.add(this);

  setWidget(lwidget);
  setGeometryModel(app);

  controllerImpl.add(editButton, LWIDGET_EDIT);
  controllerImpl.add(browseButton, LWIDGET_BROWSE);
  controllerImpl.add(menuEditButton, LWIDGET_MENUEDIT);
  controllerImpl.add(cutButton, LWIDGET_CUT);
  controllerImpl.add(copyButton, LWIDGET_COPY);
  controllerImpl.add(pasteButton, LWIDGET_PASTE);
  controllerImpl.add(deleteButton, LWIDGET_DELETE);

  XmToggleButtonSetState(automaticLoadButton, 
			 app->getBrowserAutomaticLoad(), TRUE);

  XmToggleButtonSetState(withClassNameButton, TRUE, FALSE);
  XmToggleButtonSetState(withClassNameButton, 
			 app->getBrowserWithClassName(), TRUE);

  XmToggleButtonSetState(smallIconButton, 
			 app->getBrowserSmallIcons(), TRUE);

  XmToggleButtonSetState(withIconButton, TRUE, FALSE);
  XmToggleButtonSetState(withIconButton, 
			 app->getBrowserWithIcons(), TRUE);

  createMenu = new WidClassMenu(&(app->getWidClasses()),
				widBrowseMenuBar, createButton);
  createMenu->setCallback(createCallback);
  createMenu->setCallback(popupCallback);
}

// ----------------------------
//      ~WidBrowseView()
// ----------------------------
WidBrowseView::~WidBrowseView()
{
  if(!treeView.isNil())
    treeView.Delete();
  delete createMenu;
}


// ------------------------------
// createWidget()
// ------------------------------

void 
WidBrowseView::createWidget(Lcreator &creator)
{
  RefArray<Iconable> selection;

  char name[strlen(creator.getShortName())+1];
  strcpy(name, creator.getShortName());
  name[0] = tolower(name[0]);

  treeView->getSelectedObjects(selection);
  for(unsigned int i=0; i<selection.getSize(); i++) {     // for all selected
    Lwidget *lwidget = (Lwidget*)(Iconable*)selection[i]; // cast
    if(lwidget->getClass()->asChildOk(&creator)) {        // is allowed
      Lwhere where;
      where.setparent(lwidget);                           // set the parent
      new Lwidget(&creator, name, where);                 // create
      lwidget->changed(CONTAINER_CHANGED);                // update
    }
  }
}

// ------------------------------
// popupCreateMenu()
// ------------------------------

void 
WidBrowseView::popupCreateMenu()
{
  RefArray<Iconable> selection;
  
  treeView->getSelectedObjects(selection);
  if(selection.getSize() == 1) {    
    Lwidget *lwidget = (Lwidget*)(Iconable*)selection[0]; // cast

    createMenu->enableIfAsChildOk(lwidget->getClass());
    XtSetSensitive(createMenu->getWidget(), TRUE);

  } else {
    XtSetSensitive(createMenu->getWidget(), FALSE);
  }
}

// ------------------------------
// showView()
// ------------------------------

void
WidBrowseView::showView(Lwidget *lwidget)
{
  ::WidBrowseView *view = NULL;
  if(!automaticLoadView.isNil()) {
    view = automaticLoadView;
    view->setWidget(lwidget);
  } else {
    for(unsigned int i=0; i<allViews.getSize(); i++) {
      if(allViews[i]->model == lwidget) {
	view = allViews[i];
	break;
      }
    }
  }
  if(view == NULL) {
    view = new ::WidBrowseView(lwidget);
  }
  view->open();
}


// ----------------------------
//      update()
// ----------------------------
void WidBrowseView::update( unsigned long flags )
{
  if(flags & NAME_CHANGED) {
    char title[256];
    msgCat->getMsg(title, WIDGET_BROWSE_TITLE, 
		   model->getName(), 
		   model->getClass()->getName() );
    XtVaSetValues(popupShell, 
		  XmNtitle, title,
		  XmNiconName, title,
		  NULL );
  }
}

// ------------------------------
// setWidget()
// ------------------------------

void WidBrowseView::setWidget(Lwidget *m)
{
  this->model = m;
  setModel(m);
  treeView->setModel(m);

  update(NAME_CHANGED);
}

// ------------------------------
// do_load()
// ------------------------------
void WidBrowseView::do_load(Widget, XtPointer)
{
  RefArray<Selectable> selection(Selectable::getSelection());
  
  if(!strcmp(Selectable::getCurrentClass(), "Linterface")
     && selection.getSize() > 0) {
    Linterface *linterface = (Linterface*)(Selectable*)selection[0];
    setWidget(linterface->getShell());
  } else if(!strcmp(Selectable::getCurrentClass(), "Lwidget")
	    && selection.getSize() > 0) {
    Lwidget *lwidget = (Lwidget*)(Selectable*)selection[0];
    setWidget(lwidget);
  }
}


// ------------------------------
// do_loadParent()
// ------------------------------
void WidBrowseView::do_loadParent(Widget, XtPointer)
{
  Lwidget *lwidget;

  lwidget = model->getParent();
  if(lwidget && !strcmp(lwidget->getClassName(), "Lwidget"))
    setWidget(lwidget);
}


// ------------------------------
// do_close()
// ------------------------------
void WidBrowseView::do_close(Widget, XtPointer)
{
  close();
  delete this;
}


// ------------------------------
// do_smallIcon()
// ------------------------------
void WidBrowseView::do_smallIcon(Widget wg, XtPointer)
{
  treeView->setWithSmallIcons(XmToggleButtonGetState(wg));
}


// ------------------------------
// do_withIcon()
// ------------------------------
void WidBrowseView::do_withIcon(Widget wg, XtPointer)
{
  treeView->setWithIcons(XmToggleButtonGetState(wg));
}


// ------------------------------
// do_withClassName()
// ------------------------------
void WidBrowseView::do_withClassName(Widget, XtPointer)
{
  treeView->setWithClasses(XmToggleButtonGetState(withClassNameButton));
}


// ------------------------------
// do_widgetMenuMap()
// ------------------------------
void WidBrowseView::do_widgetMenuMap(Widget, XtPointer)
{
  controllerImpl.process(treeView);
}


// ------------------------------
// do_onHelp()
// ------------------------------
void WidBrowseView::do_onHelp(Widget, XtPointer)
{
  getHelp(HID_USING_HELP);
}


// ------------------------------
// do_onContext()
// ------------------------------
void WidBrowseView::do_onContext(Widget, XtPointer)
{
  contextHelp();
}


// ------------------------------
// do_help()
// ------------------------------
void WidBrowseView::do_help(Widget, XtPointer)
{
  getHelp(HID_WIDGET_BROWSER);
}

// ------------------------------
// do_automaticLoad()
// ------------------------------

void WidBrowseView::do_automaticLoad(Widget,XtPointer)
{
  if(XmToggleButtonGetState(automaticLoadButton)) {
    if(!automaticLoadView.isNil())
      XmToggleButtonSetState(automaticLoadView->automaticLoadButton, FALSE,
			     TRUE);
    automaticLoadView = this;
  } else {
    automaticLoadView = NULL;
  }
}





