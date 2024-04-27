/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: WidResEditor.C,v $
 *  $Date: 1999/08/27 15:32:20 $
 *  $Revision: 1.3.2.1 $
 *
 *  Copyright 1997, Dirk Laessig
 *  ALL RIGHTS RESERVED
 *  See the file Copyright for more information
 *
 *  Dirk Laessig
 *  Goettingstr. 5
 *  38106 Braunschweig
 *  Germany
 ****************************************************************/
/*
 * $Log: WidResEditor.C,v $
 * Revision 1.3.2.1  1999/08/27 15:32:20  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.3  1998/04/25 00:50:41  lazy
 * Move the ScrolledWindowClient.
 *
 * Revision 1.2  1998/04/25 00:24:14  lazy
 * Uncomment the XtMoveWidget()
 *
 * Revision 1.1.1.1  1998/04/24 23:45:16  lazy
 * Imported to CVS
 *
 * Revision 1.3  1998/03/30 19:08:49  lazy
 * *** empty log message ***
 *
 * Revision 1.2  1997/09/06  13:39:40  lazy
 * Use getEditorDefaultView()
 *
 * Revision 1.1  1997/07/25  20:37:03  lazy
 * Initial revision
 *
 */

// ------------------------------ 
// WidResEditor.C                      
// ------------------------------

#include "WidResEditor.h"
#include "Lwidget.h"
#include "lic.h"
#include "LresEditor.h"
#include "misc.h"

#include <Xm/ToggleB.h>
#include <lwid/CellTable.h>
#include <Xm/ScrolledW.h>
#include <Xm/List.h>
#include <Xm/MessageB.h>

RefArray<WidResEditor> WidResEditor::allViews;
Ref<WidResEditor> WidResEditor::automaticLoadView;

// ------------------------------
// WidResEditor()
// ------------------------------

WidResEditor::WidResEditor(Lwidget *lwidget)
:WidResEditor_base(NULL,NULL,0), selectionCallback(this)
{
  quickHelpLabel = quickHelp;
  model = lwidget;
  coreW = specificW = constraintW = callbacksW = extraW = NULL;
  allViews.add(this);

  Selectable::selectionCallbacks.add(&selectionCallback);

  currentPropertyWin = (enum PropertyWin)app->getEditorDefaultView();
  setWidget(lwidget);
  setGeometryModel(app);

  XtUnmanageChild(XmMessageBoxGetChild(messageDialog, XmDIALOG_HELP_BUTTON));
  XtUnmanageChild(XmMessageBoxGetChild(messageDialog, XmDIALOG_CANCEL_BUTTON));

  XmToggleButtonSetState(automaticLoad, app->getEditorAutomaticLoad(), FALSE);
  do_automaticLoad(NULL, NULL);
}

// ----------------------------
//      ~WidResEditor()
// ----------------------------
WidResEditor::~WidResEditor()
{
  while( core.getSize() )
    core[0].Delete();
  while( specific.getSize() )
    specific[0].Delete();
  while( constraint.getSize() )
    constraint[0].Delete();
  while( callbacks.getSize() )
    callbacks[0].Delete();
  if(!widNameView.isNil())
    widNameView.Delete();
  if(!widManageView.isNil())
    widManageView.Delete();
  if(!widDescriptionView.isNil())
    widDescriptionView.Delete();
  if(!widQuickHelpView.isNil())
    widQuickHelpView.Delete();
  if(!widHelpNodeView.isNil())
    widHelpNodeView.Delete();
}


// ------------------------------
// showView()
// ------------------------------

void
WidResEditor::showView(Lwidget *lwidget)
{
  ::WidResEditor *view = NULL;
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
    view = new ::WidResEditor(lwidget);
  }
  view->open();
}


// ----------------------------
//      update()
// ----------------------------
void WidResEditor::update( unsigned long flags )
{
  if(flags & NAME_CHANGED) {
    char title[256];
    msgCat->getMsg(title, RES_EDIT_TITLE, 
		   model->getName(), 
		   model->getClass()->getName() );
    XtVaSetValues(popupShell, 
		  XmNtitle, title,
		  XmNiconName, title,
		  NULL );
  }
  if( flags & CONSTRAINTS_CHANGED ) {
    while( constraint.getSize() )
      constraint[0].Delete();
    if( constraintW )
      XtDestroyWidget( constraintW );
    constraintW = NULL;
    switchTo( currentPropertyWin );
  }
}

// ----------------------------
//    setCategoryLabel()
// ----------------------------
void 
WidResEditor::setCategoryLabel(char *msg)
{
  char title[256];
  XmString xms;

  title[0] = 0;
  msgCat->getMsg(title, msg);
  xms = XmStringCreate(title, "bold");
  XtUnmanageChild(currentCategoryLabel);
  XtVaSetValues(currentCategoryLabel, XmNlabelString, xms, NULL);
  XtManageChild(currentCategoryLabel);
  XmStringFree(xms);
}


// ------------------------------
// setWidget()
// ------------------------------

void WidResEditor::setWidget(Lwidget *m)
{
  unsigned int i;
  Lwidget *old = this->model;
  this->model = m;
  setModel(m);

  selectionCallback.call();

  update(NAME_CHANGED);

  XmListDeleteAllItems(list);
  LHashDictionaryIterator<Lstring> iterator(m->getClass()->unhandledResources);
  while(iterator.isValid()) {
    Lstring name, type;
    XmString xms, xmName, xmType;

    iterator.get(name, type);

    name += " ";
    xmName = XmStringCreate(name, XmSTRING_DEFAULT_CHARSET);
    xmType = XmStringCreate(type, "bold");
    xms = XmStringConcat(xmName, xmType);
    XmListAddItem(list, xms, 0);
    XmStringFree(xms);
    XmStringFree(xmName);
    XmStringFree(xmType);

    iterator();
  }

  if( coreW )
    for( i=0; i<core.getSize(); i++ )
      core[i]->setNewLresource(model->getProperties()->getCore()[i]);

  if( model->getClass() != old->getClass() ) { 
                                               // specific and callback changed
    while( specific.getSize() )
      specific[0].Delete();
    if( specificW )
      XtDestroyWidget( specificW );
    specificW = NULL;

    while( callbacks.getSize() )
      callbacks[0].Delete();
    if( callbacksW )
      XtDestroyWidget( callbacksW );
    callbacksW = NULL;
  } else {
    if( specificW )
      for( i=0; i<specific.getSize(); i++ )
	specific[i]->setNewLresource(model->getProperties()->
				     getSpecific()[i]);
    if( callbacksW )
      for( i=0; i<callbacks.getSize(); i++ )
	callbacks[i]->setNewLresource(model->getProperties()->
				      getCallbacks()[i]);
  }

  if( ( !model->getParent() || !old->getParent() ) ||
     (( model->getParent() && old->getParent() ) &&
	model->getParent()->getClass() != old->getParent()->getClass()) ||
     constraint.getSize()!=model->getProperties()->getConstraint().getSize())
    {
      // constraints changed
      while( constraint.getSize() )
	constraint[0].Delete();
      if( constraintW )
	XtDestroyWidget( constraintW );
      constraintW = NULL;
    } else {
      if(constraintW )
	for( i=0; i<constraint.getSize(); i++ )
	  constraint[i]->setNewLresource(model->getProperties()->
					 getConstraint()[i]);
    }

  if(model->getProperties()->getConstraint().getSize() > 0)
    XtSetSensitive(constraintButton, TRUE);
  else
    XtSetSensitive(constraintButton, FALSE);

  if(!widNameView.isNil())
    widNameView->setNewLwidget(model);
  if(!widManageView.isNil())
    widManageView->setNewLwidget(model);
  if(!widDescriptionView.isNil())
    widDescriptionView->setNewLwidget(model);
  if(!widQuickHelpView.isNil())
    widQuickHelpView->setNewLwidget(model);
  if(!widHelpNodeView.isNil())
    widHelpNodeView->setNewLwidget(model);

  switchTo( currentPropertyWin );
  
}

// ------------------------------
// do_load()
// ------------------------------
void WidResEditor::do_load(Widget, XtPointer)
{
  RefArray<Selectable> selection(Selectable::getSelection());

  setWaitCursor(TRUE);

  if(!strcmp(Selectable::getCurrentClass(), "Linterface")
     && selection.getSize() > 0) {
    Linterface *linterface = (Linterface*)(Selectable*)selection[0];
    setWidget(linterface->getShell());
  } else if(!strcmp(Selectable::getCurrentClass(), "Lwidget")
	    && selection.getSize() > 0) {
    Lwidget *lwidget = (Lwidget*)(Selectable*)selection[0];
    setWidget(lwidget);
  }

  setWaitCursor(FALSE);
}


// ------------------------------
// do_apply()
// ------------------------------
void WidResEditor::do_apply(Widget, XtPointer)
{
  setWaitCursor(TRUE);
  apply();
  setWaitCursor(FALSE);
}


// ------------------------------
// do_close()
// ------------------------------
void WidResEditor::do_close(Widget, XtPointer)
{
  if(somethingChanged()) {
    char title[256];
    char msg[1024];
    msgCat->getMsg( title, LRES_SOME_CHANGES_TITLE );
    msgCat->getMsg( msg, LRES_SOME_CHANGES_MSG );
    if(MSGBOX_OK == MsgBox(title, msg, MSGBOX_STYLE_YESNO) ) {
      close();
      delete this;
    }
  } else {
    close();
    delete this;
  }
}


// ------------------------------
// do_viewChanged()
// ------------------------------
void WidResEditor::do_viewChanged(Widget, XtPointer callData)
{
  XmRowColumnCallbackStruct *cbs = (XmRowColumnCallbackStruct*)callData;
  
  setWaitCursor(TRUE);

  if(cbs->widget == coreButton 
     && XmToggleButtonGetState(cbs->widget)) {
    switchTo(PW_CORE);
  } else if(cbs->widget == specificButton 
	    && XmToggleButtonGetState(cbs->widget)) {
    switchTo(PW_SPECIFIC);
  } else if(cbs->widget == constraintButton 
	    && XmToggleButtonGetState(cbs->widget)) {
    switchTo(PW_CONSTRAINT);
  } else if(cbs->widget == callbackButton 
	    && XmToggleButtonGetState(cbs->widget)) {
    switchTo(PW_CALLBACKS);
  } else if(cbs->widget == extraButton 
	    && XmToggleButtonGetState(cbs->widget)) {
    switchTo(PW_EXTRA);
  } else if(cbs->widget == userButton 
	    && XmToggleButtonGetState(cbs->widget)) {
    switchTo(PW_USER);
  }

  setWaitCursor(FALSE);
}


// ------------------------------
// do_automaticLoad()
// ------------------------------
void WidResEditor::do_automaticLoad(Widget, XtPointer)
{
  XmString xms;
  char msg[256];

  if(XmToggleButtonGetState(automaticLoad)) {
    if(!automaticLoadView.isNil())
      XmToggleButtonSetState(automaticLoadView->automaticLoad, FALSE,
			     TRUE);
    automaticLoadView = this;
    msgCat->getMsg(msg, WR_EDITOR_AUTOMATIC_LOAD_ON);
    xms = XmStringCreate(msg, XmSTRING_DEFAULT_CHARSET);
    XtVaSetValues(automaticLoadLabel, XmNlabelString, xms, NULL);
    XmStringFree(xms);
  } else {
    msgCat->getMsg(msg, WR_EDITOR_AUTOMATIC_LOAD_OFF);
    xms = XmStringCreate(msg, XmSTRING_DEFAULT_CHARSET);
    XtVaSetValues(automaticLoadLabel, XmNlabelString, xms, NULL);
    XmStringFree(xms);
    automaticLoadView = NULL;
  }
}


// ------------------------------
// do_withSource()
// ------------------------------
void WidResEditor::do_withSource(Widget wg, XtPointer)
{
  printf("Callback WidResEditor::do_withSource called by widget '%s'.\n",
         XtName(wg));
}


// ------------------------------
// do_onHelp()
// ------------------------------
void WidResEditor::do_onHelp(Widget, XtPointer)
{
  getHelp(HID_USING_HELP);
}


// ------------------------------
// do_onContext()
// ------------------------------
void WidResEditor::do_onContext(Widget, XtPointer)
{
  contextHelp();
}


// ------------------------------
// do_help()
// ------------------------------
void WidResEditor::do_help(Widget, XtPointer)
{
  getHelp(HID_WIDGET_RESOURCE_EDITOR);
}




// --------------------
// createResView()
// --------------------

ResView *WidResEditor::createResView( Lresource *lres, 
				      Widget parent, 
				      Cardinal r)
{
  char *className = lres->getClassName();
  if(!strcmp(className,"LresBoolean")) {
    return new BooleanResView(lres,parent,this,r);
  }
  if(!strcmp(className,"LresEnum")) {
    return new EnumResView(lres,parent,this,r);
  }
  if(!strcmp(className,"LresFontList")) {
    return new FontResView(lres,parent,this,r);
  }
  if(!strcmp(className,"LresPixel")) {
    return new ColorResView(lres,parent,this,r);
  }
  return new MultiTextResView(lres,parent,this,r);
}


//----------------------------------
//  switchTo()
//----------------------------------

void WidResEditor::switchTo( PropertyWin pw )
{
  unsigned int i;
  Boolean move = FALSE;

  if( pw != currentPropertyWin ) {
    if( coreW ) {
      XtUnmanageChild( coreW );
      dropSiteFix(coreW,FALSE);
    }
    if( specificW ) {
      XtUnmanageChild( specificW );
      dropSiteFix(specificW,FALSE);
    }
    if( constraintW ) {
      XtUnmanageChild( constraintW );
      dropSiteFix(constraintW,FALSE);
    }
    if( callbacksW ) {
      XtUnmanageChild( callbacksW );
      dropSiteFix(callbacksW,FALSE);
    }
    if( extraW ) {
      XtUnmanageChild( extraW );
      dropSiteFix(extraW,FALSE);
    }

    move = TRUE;
  }
  
  if(pw == PW_CONSTRAINT &&
     model->getProperties()->getConstraint().getSize() == 0) {
    pw = (enum PropertyWin)app->getEditorDefaultView();
    if(pw == PW_CONSTRAINT)
      pw = PW_CORE;
  }
  currentPropertyWin = pw;

  WidgetClass wc = xlCellTableWidgetClass;

  XmToggleButtonSetState(coreButton, FALSE, FALSE);
  XmToggleButtonSetState(specificButton, FALSE, FALSE);
  XmToggleButtonSetState(constraintButton, FALSE, FALSE);
  XmToggleButtonSetState(callbackButton, FALSE, FALSE);
  XmToggleButtonSetState(extraButton, FALSE, FALSE);
  XmToggleButtonSetState(userButton, FALSE, FALSE);

  switch( pw ) {
  case PW_CORE:
    if( !coreW ) {
      coreW = XtVaCreateWidget("Box", wc,
			       scrolledWindow_1,
			       XmNpacking, XmPACK_COLUMN,
			       XmNorientation, XmVERTICAL,
			       NULL);

      for( i=0 ; i<model->getProperties()->getCore().getSize() ; i++ ) {
	core.add( createResView(model->getProperties()->getCore()[i],
				coreW, i));
      }
    }
    if(move)
      XtMoveWidget(coreW, 0, 0);
    XmScrolledWindowSetAreas( scrolledWindow_1, NULL, NULL, coreW );
    XtManageChild(coreW);
    dropSiteFix(coreW,TRUE);
    setCategoryLabel(WR_EDITOR_CORE);
    XmToggleButtonSetState(coreButton, TRUE, FALSE);

    break;
  case PW_SPECIFIC:
    if( !specificW ) {
      specificW = XtVaCreateWidget("Box",wc,
					  scrolledWindow_1,
					  XmNorientation, XmVERTICAL,
					  NULL);
      for( i=0 ; i<model->getProperties()->getSpecific().getSize() ; i++ ) {
	specific.add( createResView(model->getProperties()->
				    getSpecific()[i], specificW, i));
      }
    }
    if(move)
      XtMoveWidget(specificW, 0, 0);
    XmScrolledWindowSetAreas( scrolledWindow_1, NULL, NULL, specificW );
    XtManageChild(specificW);
    dropSiteFix(specificW,TRUE);
    setCategoryLabel(WR_EDITOR_SPECIFIC);
    XmToggleButtonSetState(specificButton, TRUE, FALSE);

    break;
  case PW_CONSTRAINT:
    if( !constraintW ) {
      constraintW = XtVaCreateWidget("Box",wc,
				     scrolledWindow_1,
				     XmNorientation, XmVERTICAL,
				     NULL);
      for( i=0 ; i<model->getProperties()->getConstraint().getSize() ; i++ ){
	constraint.add( createResView(model->getProperties()->
				      getConstraint()[i],constraintW, i));
      }
    }
    if(move)
      XtMoveWidget(constraintW, 0, 0);
    XmScrolledWindowSetAreas( scrolledWindow_1, NULL, NULL, constraintW );
    XtManageChild(constraintW);
    dropSiteFix(constraintW,TRUE);
    setCategoryLabel(WR_EDITOR_CONSTRAINT);
    XmToggleButtonSetState(constraintButton, TRUE, FALSE);

    break;
  case PW_CALLBACKS:
    if( !callbacksW ) {
      callbacksW = XtVaCreateWidget("Box",wc,
				    scrolledWindow_1,
				    XmNorientation, XmVERTICAL,
				    NULL);
      for( i=0 ; i<model->getProperties()->getCallbacks().getSize() ; i++ ){
	callbacks.add( createResView(model->getProperties()->
				      getCallbacks()[i],callbacksW, i));
      }
    }
    if(move)
      XtMoveWidget(callbacksW, 0, 0);
    XmScrolledWindowSetAreas( scrolledWindow_1, NULL, NULL, callbacksW );
    XtManageChild(callbacksW);
    dropSiteFix(callbacksW,TRUE);
    setCategoryLabel(WR_EDITOR_CALLBACK);
    XmToggleButtonSetState(callbackButton, TRUE, FALSE);

    break;
  case PW_EXTRA:
    if(!extraW) {
      extraW = XtVaCreateWidget("Box", xlCellTableWidgetClass,
				scrolledWindow_1, NULL);
      widNameView = new WidNameView(model, extraW, this, 0);
      widManageView = new WidManageView(model, extraW, this, 1);
      widDescriptionView = new WidDescriptionView(model, extraW, this, 2);
#ifndef WITHOUT_LAC
      widQuickHelpView = new WidQuickHelpView(model, extraW, this, 3);
      widHelpNodeView = new WidHelpNodeView(model, extraW, this, 4);
#endif
    }
    if(move)
      XtMoveWidget(extraW, 0, 0);
    XmScrolledWindowSetAreas( scrolledWindow_1, NULL, NULL, extraW );
    XtManageChild(extraW);
    dropSiteFix(extraW,TRUE);
    setCategoryLabel(WR_EDITOR_EXTRA);
    XmToggleButtonSetState(extraButton, TRUE, FALSE);

    break;
  case PW_USER:     // not implemented
    setCategoryLabel(WR_EDITOR_USER);
    XmToggleButtonSetState(userButton, TRUE, FALSE);

    break;
  }

}

//----------------------------------
//  apply()
//----------------------------------
  
Boolean WidResEditor::apply()
{
  Boolean extraChanged = FALSE;

  unsigned int i;
  for( i=0; i<core.getSize(); i++ )
    core[i]->apply();
  for( i=0; i<specific.getSize(); i++ )
    specific[i]->apply();
  for( i=0; i<constraint.getSize(); i++ )
    constraint[i]->apply();
  for( i=0; i<callbacks.getSize(); i++ )
    callbacks[i]->apply();
#if(0)
  char *str = XmTextGetString( nameTextW );
  model->setName( str );
  XtFree(str);
  
  model->setManage(XmToggleButtonGetState(manageToggleW));

#ifndef WITHOUT_LAC
  str = XmTextGetString( quickHelpTextW );
  model->setQuickhelp( str );
  XtFree(str);
  
  model->setHelpNode(hnView->getHelpNode());
#endif
#endif

  if(!widNameView.isNil())
    widNameView->apply();

  if(!widManageView.isNil()) {
    widManageView->apply();
    extraChanged = TRUE;
  }

  if(!widDescriptionView.isNil()) {
    widDescriptionView->apply();
    extraChanged = TRUE;
  }

  if(!widQuickHelpView.isNil()) {
    widQuickHelpView->apply();
    extraChanged = TRUE;
  }

  if(!widHelpNodeView.isNil()) {
    widHelpNodeView->apply();
    extraChanged = TRUE;
  }

  if(extraChanged)
    model->changed(RESOURCE_CHANGED | EXTRA_CHANGED);
  model->changed(RESOURCE_CHANGED);
  return TRUE;
}

// --------------------
// somethingChnaged()
// --------------------
Boolean WidResEditor::somethingChanged()
{
  Boolean ret = FALSE;
  unsigned int i;

  for( i=0; i<core.getSize(); i++ ) 
    if(core[i]->isChanged())
      return TRUE;
  for( i=0; i<specific.getSize(); i++ )
    if(specific[i]->isChanged())
      return TRUE;
  for( i=0; i<constraint.getSize(); i++ )
    if(constraint[i]->isChanged())
      return TRUE;
  for( i=0; i<callbacks.getSize(); i++ )
    if(callbacks[i]->isChanged())
      return TRUE;
  
  if(!widNameView.isNil() && widNameView->isChanged())
    return TRUE;

  if(!widManageView.isNil() && widManageView->isChanged())
    return TRUE;

  return ret;
}

// ------------------------------
// SelectationCallback::call()
// ------------------------------

void
WidResEditor::SelectionCallback::call()
{
  RefArray<Selectable> selection(Selectable::getSelection());
  if(!strcmp(Selectable::getCurrentClass(), "Lwidget")
     && selection.getSize() == 1) {
    XtSetSensitive(parent->loadButton, TRUE);
  } else {
    XtSetSensitive(parent->loadButton, FALSE);
  }
}

