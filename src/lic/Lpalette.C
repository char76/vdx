/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: Lpalette.C,v $
 *  $Date: 1999/08/27 15:31:15 $
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
 * $Log: Lpalette.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:31:15  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:14  lazy
 * Imported to CVS
 *
 * Revision 1.2  1998/03/30 19:08:23  lazy
 * *** empty log message ***
 *
 * Revision 1.1  1997/07/25  20:27:08  lazy
 * Initial revision
 *
 */

// -------------------------------------------------
// Lpalette.C
// Implementation of Lpalette, PaletteView
// (C) Dirk Laessig
// -------------------------------------------------

#include "Lpalette.h"
#include "Lproject.h"
#include "Lwhere.h"
#include "misc.h"
#include "lic.h"
#include "VersionControl.h"

#include <stdlib.h>
#include <Xm/Form.h>
#include <Xm/PushB.h>

#define PALETTE_CLOSE "PaletteClose"



// ##########################################
//              Lpalette
// ##########################################

// ----------------------------------------
// Lpalette()
// ----------------------------------------

Lpalette::Lpalette()
{
  aNew = TRUE;
  setFilename();
}

Lpalette::Lpalette(char *filename)
{
  char f[PATH_MAX];
  YResult *result;
  YWidget *ywg;

  aNew = FALSE;
  strcpy(name,filename);
  //  getBasename(name);
  withSuffix(name, PATH_MAX, "pal");
  
  strcpy(f,filename);
  
  openFileHook(f);
  result = parse(f);
  if(result) {
    if(result->error) {
      app->showSystemError(filename, result->error);
    }
    if(result->root_widget) {
      for( ywg = result->root_widget->first_child; ywg; ywg = ywg->next ) {
	if(Lcreator::getClass(ywg->widget_class)) {
	  add( new Lwidget(ywg) );
	} else {
	  fprintf(stderr, "Error: Widget class '%s' is not available.\n", 
		  ywg->widget_class);
	}
      }
      parseViewData(result->root_widget->viewData);
    }

    free_YResult( result );
  }

}

// ----------------------------------------
// save()
// ----------------------------------------

Boolean Lpalette::save( char *f )
{
  unsigned int i;
  char filename[PATH_MAX];

  if(f==NULL) {
    //  getPath(Lproject::current().getFilename(), filename, sizeof(filename));
    strcpy(filename, name);
  } else {
    if( f[0]==0 ) {
      strcpy(filename, name);
    } else {
      if( f[strlen(f)-1]=='/' ) {
	strcpy(filename, f);
	strcat(filename, name);
      } else {
	strcpy(filename, f);
      }
    }
  }
  withSuffix(filename, sizeof(filename), "pal");
  
  YResult *toWrite = (YResult*)malloc(sizeof(YResult));
  memset( toWrite, 0, sizeof(YResult));
  toWrite->root_widget = (YWidget*)malloc(sizeof(YWidget));
  memset( toWrite->root_widget, 0, sizeof(YWidget));
  
  YWidget *ywg = NULL, *last = NULL;
  for( i=0; i<children.getSize(); i++ ) {
    ywg = children[i]->createYWidget();
    if(last)
      last->next = ywg;
    else 
      toWrite->root_widget->first_child = ywg;

    last = ywg;
  }
  m_strcpy(&toWrite->root_widget->viewData, getViewData());

  if(app->isDemo() && countSubTree() > DEMO_MAX_WIDGETS) {
    char msg[1024];
    
    msgCat->getMsg(msg, DEMO_ERROR, filename);
    fprintf(stderr,"%s\n",msg);

    free_YResult( toWrite );
    return FALSE;
  } else {
    int error;
    if( (error = writeFile( filename, toWrite ))) {
      app->showSystemError(filename, error);
      free_YResult( toWrite );
      return FALSE;
    }
    saveFileHook(filename);
  }
  free_YResult( toWrite );
  resetChangedFlag();
  aNew = FALSE;
  return TRUE;
}


// ----------------------------------------
// myAdd()  
// ----------------------------------------

void Lpalette::myAdd( Lwidget *lw )
{
  YResult *dummy;
  dummy = (YResult*)malloc(sizeof(YResult));
  memset( dummy, 0, sizeof(YResult) );
  dummy->root_widget = lw->createYWidget();
  
  Lwidget *copied = new Lwidget( dummy->root_widget );
  //  copied->getProperties()->fillWithDefaults(copied->getClass()->getDummy());
  add(copied);
  changed(CONTAINER_CHANGED);
  free_YResult(dummy);
}

// ----------------------------------------
// setFilename()
// ----------------------------------------

void Lpalette::setFilename(char *n)
{ 
  if(n)
    strcpy(name,n); 
  else
    strcpy(name, PALETTE_DEFAULT_NAME);
}

#if(0)
// ############# PaletteView ##########

RefArray<PaletteView> PaletteView::allViews;

// ----------------------------------------
// PaletteView()
// ----------------------------------------

PaletteView::PaletteView( Lpalette *model )
: LicView(model)
{
  lpalette = model;
  Widget button;

  popupShell = XtVaCreatePopupShell ("PaletteShell", 
				     topLevelShellWidgetClass,
				     topLevel,
				     NULL );
  form = XtVaCreateManagedWidget("PaletteForm",
				 xmFormWidgetClass,
				 popupShell,
				 NULL);
  button = XtVaCreateManagedWidget("Close",
				   xmPushButtonWidgetClass,
				   form,
				   XmNbottomAttachment, XmATTACH_FORM,
				   XmNleftAttachment, XmATTACH_FORM,
				   XmNrightAttachment, XmATTACH_FORM,
				   XmNleftOffset, 5,
				   XmNrightOffset, 5,
				   XmNbottomOffset, 5,
				   NULL );
  addAction( button, PALETTE_CLOSE );

  lwidgets = new WidgetIconView(lpalette, form, new PaletteIcon() );
  lwidgets->setDragOperations(XmDROP_COPY);
  XtManageChild(lwidgets->getTop());

  XtVaSetValues( lwidgets->getTop(),
		XmNleftAttachment, XmATTACH_FORM,
		XmNleftOffset, 5,
		XmNtopAttachment, XmATTACH_FORM,
		XmNtopOffset, 5,
		XmNrightAttachment, XmATTACH_FORM,
		XmNrightOffset, 5,
		XmNbottomAttachment, XmATTACH_WIDGET,
		XmNbottomWidget, button,
		XmNbottomOffset, 5,
		NULL );
  
  allViews.add(this);
  dropSiteRegister();
}

// ---------------------------------
// ~PaletteView()
// ---------------------------------

PaletteView::~PaletteView()
{
  if(!lwidgets.isNil())
    lwidgets.Delete();
//  XtDestroyWidget(popupShell);
}
  
// ---------------------------------
// act()
// ---------------------------------

void PaletteView::act( char *action )
{
  if( !strcmp(action,PALETTE_CLOSE) ) {
    delete this;
  }
}
  
// ---------------------------------
// findPalette()
// ---------------------------------

Lpalette *PaletteView::findPalette( Widget dropOver )
{
  for(unsigned int i=0; i<allViews.getSize(); i++ ) {
    if( dropOver == allViews[i]->lwidgets->getTop() ) {
      return allViews[i]->lpalette;
    }
    if( XtParent(dropOver) == allViews[i]->lwidgets->getTop() ) {
      return allViews[i]->lpalette;
    }
    if( XtParent(XtParent(dropOver)) == allViews[i]->lwidgets->getTop() ) {
      return allViews[i]->lpalette;
    }
  }
  return NULL;
}

// ---------------------------------
// dropSiteRegister()
// ---------------------------------

void PaletteView::dropSiteRegister()
{
  static imports[1];
  Widget wg;
  
  wg = lwidgets->getTop();
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

void PaletteView::dropProc(Widget wg, XtPointer, XtPointer callData)
{
  static XmDropTransferEntryRec transList[1];
  XmDropProcCallback dd = (XmDropProcCallback)callData;
  Arg args[10];
  Cardinal n=0;
  PaletteView *pv = NULL;

  for(unsigned int i=0; i<allViews.getSize(); i++ ) {
    if( wg == allViews[i]->lwidgets->getTop() ) {
      pv = allViews[i];
    }
  }

  if(!pv) {
    fprintf(stderr, "Fatal Error: pv==NULL in PaletteView\n");
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

void PaletteView::transferProc(Widget w, XtPointer closure, 
			       Atom *, Atom *,
			       XtPointer value, unsigned long *, 
			       int *)
{
  if(!value) {
    XtVaSetValues(w, XmNtransferStatus, XmTRANSFER_FAILURE, NULL);
    return;
  }
  PaletteView *pv  = (PaletteView*)closure;
  Lwidget **ptr = (Lwidget**)value;
  Lwidget *lwidget = *ptr;

  Lwidget *copied;
  copied = lwidget->copy();
  if( !copied ) {
    XtVaSetValues(w, XmNtransferStatus, XmTRANSFER_FAILURE, NULL);
    return;
  }
  copied->getProperties()->fillWithDefaults(copied->getClass()->getDummy());
  pv->lpalette->add(copied);
  pv->lpalette->changed(CONTAINER_CHANGED);
}
			   



#endif
