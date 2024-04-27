/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: LresEditor.C,v $
 *  $Date: 1999/08/27 15:31:23 $
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
 * $Log: LresEditor.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:31:23  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:13  lazy
 * Imported to CVS
 *
 * Revision 1.3  1998/04/06 17:25:53  lazy
 * Enable quick help on resource label.
 *
 * Revision 1.2  1997/09/07 14:21:29  lazy
 * Manage toggle is insensitive when manage policy
 * is NEVER_MANAGE.
 *
 * Revision 1.1  1997/07/25  20:28:10  lazy
 * Initial revision
 *
 */

/* ---------------------------------------------------------
   (C) Dirk Laessig 1994
   ---------------------------------------------------------*/

#include "lic.h"
#include "lic_hlp.h"
#include "Lproject.h"
#include "LresEditor.h"
#include "Lwidget.h"
#include "Lresource.h"
#include "Lcreator.h"
#include "misc.h"
#include "FontSelect.h"
#include "ColorSelect.h"
#include "TextEdit.h"

#include <Xm/Label.h>
#include <Xm/RowColumn.h>
#include <Xm/PushB.h>
#include <Xm/ScrolledW.h>
#include <Xm/Form.h>
#include <Xm/Text.h>
#include <Xm/ToggleB.h>

#include <X11/Shell.h>
#include <X11/StringDefs.h>

#include <ctype.h>


#define WITH_CELL_TABLE 
#ifdef WITH_CELL_TABLE
#include <lwid/CellTable.h>
#endif

#if(0)

Ref<LresEditor> LresEditor::autoLoad;
RefArray<LresEditor> LresEditor::allViews;

#ifndef WITH_CELL_TABLE
#define LABEL_WIDTH 170
#endif

#define LRESEDIT_CLOSE        "Close"
#define LRESEDIT_APPLY        "Apply"
#define LRESEDIT_HELP         "Help"
#define LRESEDIT_CORE         "Core"
#define LRESEDIT_SPECIFIC     "Specific"
#define LRESEDIT_CONSTRAINT   "Constraint"
#define LRESEDIT_CALLBACKS    "Callbacks"
#define LRESEDIT_EXTRA        "EXTRA"
#define LRESEDIT_HELPIDCLEAR  "HelpIdClear"

//----------------------------------
//  Contructor
//----------------------------------
LresEditor::LresEditor( Lwidget *lw )
: LicView( lw )
{
  Widget form, menu, button, firstB, oMenu;
  lwidget = lw;
  coreW = specificW = constraintW = callbacksW = extraW = NULL;
  hnView = NULL;

  allViews.add(this);

  popupShell = shell = XtVaCreatePopupShell("LresEditor",
					     topLevelShellWidgetClass,
					     LicView::getTopLevel(),NULL);
  form = XtVaCreateManagedWidget("Form", xmFormWidgetClass, shell,
				 XmNwidth, 480,
				 XmNheight, 400,
				 NULL );
  XtAddCallback(form, XmNhelpCallback, helpCallback, NULL);

  quickHelpLabel = XtVaCreateManagedWidget("QuickHelpLabel", 
					   xmLabelWidgetClass, form,
					   XmNalignment, XmALIGNMENT_BEGINNING,
					   XmNleftAttachment, XmATTACH_FORM,
					   XmNleftOffset, 1,
					   XmNrightAttachment, XmATTACH_FORM,
					   XmNrightOffset, 1,
					   XmNbottomAttachment, XmATTACH_FORM,
					   XmNbottomOffset, 1,
					   NULL);
  
  applyB = XtVaCreateManagedWidget("Apply", xmPushButtonWidgetClass,form,
				  XmNbottomAttachment, XmATTACH_WIDGET,
				  XmNbottomOffset, 3,
				  XmNbottomWidget, quickHelpLabel,
				  XmNleftAttachment, XmATTACH_FORM,
				  XmNleftOffset, 5,
				  XmNwidth, 100,
				  XmNheight, 30,
				  NULL);
  addAction( applyB, LRESEDIT_APPLY );
  addQuickHelp(applyB);

  closeB = XtVaCreateManagedWidget("Close", xmPushButtonWidgetClass,form,
				  XmNbottomAttachment, XmATTACH_WIDGET,
				  XmNbottomOffset, 3,
				  XmNbottomWidget, quickHelpLabel,
				  XmNleftAttachment, XmATTACH_POSITION,
				  XmNleftOffset, -50,
				  XmNleftPosition, 50,
				  XmNwidth, 100,
				  XmNheight, 30,
				  NULL);
  addAction( closeB, LRESEDIT_CLOSE );
  addQuickHelp(closeB);

  helpB = XtVaCreateManagedWidget("Help", xmPushButtonWidgetClass,form,
				  XmNbottomAttachment, XmATTACH_WIDGET,
				  XmNbottomOffset, 3,
				  XmNbottomWidget, quickHelpLabel,
				  XmNrightAttachment, XmATTACH_FORM,
				  XmNrightOffset, 3,
				  XmNwidth, 100,
				  XmNheight, 30,
				  NULL);
  addAction(helpB, LRESEDIT_HELP );
  addQuickHelp(helpB);

  LicView::quickHelpLabel = quickHelpLabel;

  scrolledW = XtVaCreateManagedWidget("ScrolledWindow",
				      xmScrolledWindowWidgetClass, form,
				      XmNrightAttachment, XmATTACH_FORM,
				      XmNleftAttachment, XmATTACH_FORM,
				      XmNtopAttachment, XmATTACH_FORM,
				      XmNtopOffset, 40,
				      XmNbottomAttachment, XmATTACH_WIDGET,
				      XmNbottomWidget, applyB,
				      XmNbottomOffset, 3,
				      XmNscrollingPolicy, XmAUTOMATIC,
				      NULL );
//  XtAddEventHandler(scrolledW, StructureNotifyMask, 
//		    False,configureEvent,this);
  
  autoLoadToggle = XtVaCreateManagedWidget("AutoLoad", 
					   xmToggleButtonWidgetClass, form,
					   XmNtopAttachment, XmATTACH_FORM,
					   XmNtopOffset, 5,
					   XmNrightAttachment, XmATTACH_FORM,
					   XmNrightOffset, 5,
					   NULL );
  XtAddCallback(autoLoadToggle, XmNvalueChangedCallback,
		autoLoadCallback, this );
  addQuickHelp(autoLoadToggle);

  menu = XmCreatePulldownMenu(form, "Switch", (Arg*)NULL, 0 ); 

  firstB = button = XtVaCreateManagedWidget("Core", 
					    xmPushButtonWidgetClass, menu,
					    NULL );
  addAction( button, LRESEDIT_CORE );
  addQuickHelp(button);
  button = XtVaCreateManagedWidget("Specific", 
				   xmPushButtonWidgetClass, menu,
				   NULL );
  addAction( button, LRESEDIT_SPECIFIC );
  addQuickHelp(button);
  button = XtVaCreateManagedWidget("Constraint", 
				   xmPushButtonWidgetClass, menu,
				   NULL );
  addAction( button, LRESEDIT_CONSTRAINT );
  addQuickHelp(button);
  button = XtVaCreateManagedWidget("Callbacks", 
				   xmPushButtonWidgetClass, menu,
				   NULL );
  addAction( button, LRESEDIT_CALLBACKS );
  addQuickHelp(button);
  button = XtVaCreateManagedWidget("Extra", 
				   xmPushButtonWidgetClass, menu,
				   NULL );
  addAction( button, LRESEDIT_EXTRA );
  addQuickHelp(button);

  Arg args[10]; Cardinal n=0;

  XtSetArg( args[n], XmNleftAttachment, XmATTACH_FORM ); n++;
  XtSetArg( args[n], XmNleftOffset, 5 ); n++;
  XtSetArg( args[n], XmNtopAttachment, XmATTACH_FORM ); n++;
  XtSetArg( args[n], XmNtopOffset, 5 ); n++;
  XtSetArg( args[n], XmNsubMenuId, menu); n++;
  oMenu = button = XmCreateOptionMenu( form, "Menu", args, n );

  XtManageChild(oMenu);


  extraW = XtVaCreateWidget("Box",xmFormWidgetClass,
				   scrolledW,
				   NULL);

  nameLabelW = XtVaCreateManagedWidget("ExtraNameLabel", xmLabelWidgetClass,
				       extraW, 
				       XmNtopAttachment, XmATTACH_FORM,
				       XmNtopOffset, 20,
				       XmNleftAttachment, XmATTACH_FORM,
				       XmNleftOffset, 5,
				       XmNwidth, 100,
				       XmNalignment, XmALIGNMENT_BEGINNING,
				       NULL );
  nameTextW = XtVaCreateManagedWidget("ExtraNameText", xmTextWidgetClass,
				      extraW,
				      XmNtopAttachment, 
				                   XmATTACH_OPPOSITE_WIDGET,
				      XmNtopOffset, -10,
				      XmNtopWidget, nameLabelW,
				      XmNleftAttachment, XmATTACH_WIDGET,
				      XmNleftWidget, nameLabelW,
				      XmNleftOffset, 5,
				      NULL );
  addQuickHelp(nameTextW);

  manageLabelW = XtVaCreateManagedWidget("ExtraManageLabel",xmLabelWidgetClass,
					 extraW, 
					 XmNtopAttachment, XmATTACH_WIDGET,
					 XmNtopWidget, nameLabelW,
					 XmNtopOffset, 20,
					 XmNleftAttachment, XmATTACH_FORM,
					 XmNleftOffset, 5,
					 XmNwidth, 100,
					 XmNalignment, XmALIGNMENT_BEGINNING,
					 NULL );
  manageToggleW = XtVaCreateManagedWidget("ExtraManageToggle", 
					  xmToggleButtonWidgetClass,
					  extraW,
					  XmNtopAttachment, 
					            XmATTACH_OPPOSITE_WIDGET,
					  XmNtopWidget, manageLabelW,
					  XmNtopOffset, -5,
					  XmNleftAttachment, XmATTACH_WIDGET,
					  XmNleftWidget, manageLabelW,
					  XmNleftOffset, 5,
					  NULL );
  addQuickHelp(manageToggleW);
  
#ifndef WITHOUT_LAC
  quickHelpLabelW = XtVaCreateManagedWidget("ExtraQuickHelpLabel", 
					    xmLabelWidgetClass,
					    extraW, 
					    XmNtopAttachment, XmATTACH_WIDGET,
					    XmNtopWidget, manageLabelW,
					    XmNtopOffset, 20,
					    XmNleftAttachment, XmATTACH_FORM,
					    XmNleftOffset, 5,
					    XmNwidth, 100,
					    XmNalignment, XmALIGNMENT_BEGINNING,
					    NULL );
  quickHelpTextW = XtVaCreateManagedWidget("ExtraQuickHelpText", 
					   xmTextWidgetClass,
					   extraW,
					   XmNtopAttachment, 
					           XmATTACH_OPPOSITE_WIDGET,
					   XmNtopWidget, quickHelpLabelW,
					   XmNtopOffset, -10,
					   XmNleftAttachment, XmATTACH_WIDGET,
					   XmNleftWidget, quickHelpLabelW,
					   XmNleftOffset, 5,
					   XmNcolumns, 40,
					   NULL );
  addQuickHelp(quickHelpTextW);
  

  helpNodeLabelW = XtVaCreateManagedWidget("ExtraHelpIdLabel", 
					   xmLabelWidgetClass,
					   extraW, 
					   XmNtopAttachment, XmATTACH_WIDGET,
					   XmNtopWidget, quickHelpLabelW,
					   XmNtopOffset, 20,
					   XmNleftAttachment, XmATTACH_FORM,
					   XmNleftOffset, 5,
					   XmNwidth, 100,
					   XmNalignment, XmALIGNMENT_BEGINNING,
					   NULL );
  helpNodeTextW = XtVaCreateManagedWidget("ExtraHelpIdText", 
					  xmTextWidgetClass,
					  extraW,
					  XmNtopAttachment, 
					  XmATTACH_OPPOSITE_WIDGET,
					  XmNtopWidget, helpNodeLabelW,
					  XmNtopOffset, -10,
					  XmNleftAttachment, XmATTACH_WIDGET,
					  XmNleftWidget, helpNodeLabelW,
					  XmNleftOffset, 5,
					  XmNeditable, False,
					  XmNcolumns, 30,
					  NULL );
  addQuickHelp(helpNodeTextW);
  
  helpNodeButtonW = XtVaCreateManagedWidget("Clear", xmPushButtonWidgetClass,
					    extraW,
					    XmNtopAttachment, 
					          XmATTACH_OPPOSITE_WIDGET,
					    XmNtopWidget, helpNodeTextW,
					    XmNtopOffset, 5,
					    XmNbottomAttachment, 
					          XmATTACH_OPPOSITE_WIDGET,
					    XmNbottomWidget, helpNodeTextW,
					    XmNtopOffset, 5,
					    XmNleftAttachment, XmATTACH_WIDGET,
					    XmNleftWidget, helpNodeTextW,
					    XmNleftOffset, 5,
					    NULL);
  addQuickHelp(helpNodeButtonW);
  addAction(helpNodeButtonW, LRESEDIT_HELPIDCLEAR);
  helpNodeDropSiteRegister();
#endif

  dropSiteFix(extraW,FALSE);

  withLibLac(app->getProject()->getLang()->getWithLibLac());

  update( EXTRA_CHANGED | NAME_CHANGED );

  currentPropertyWin = PW_CORE;
  switchTo( PW_CORE );

}

//----------------------------------
//  Destructor
//----------------------------------

LresEditor::~LresEditor()
{
  delete hnView;

  while( core.getSize() )
    core[0].Delete();
  while( specific.getSize() )
    specific[0].Delete();
  while( constraint.getSize() )
    constraint[0].Delete();
  while( callbacks.getSize() )
    callbacks[0].Delete();

//  XtDestroyWidget(shell);
}


// ---------------------------------
// showEditor()
// ---------------------------------
LresEditor *LresEditor::showEditor(Lwidget *lwidget)
{
  LresEditor *ret = NULL;

  if(ret == NULL) {                               // search for open view
    for(unsigned int i=0; i<allViews.getSize(); i++) {
      if(allViews[i]->lwidget == lwidget) {
	ret = allViews[i];
	break;
      }
    }
  }

  if(ret == NULL && getAutoLoad()) {             // look for autoload view
    ret = getAutoLoad();
    if(ret->somethingChanged()) {
      char title[256];
      char msg[1024];
      ret->open();
      msgCat->getMsg( title, LRES_SOME_CHANGES_TITLE );
      msgCat->getMsg( msg, LRES_SOME_CHANGES_MSG );
      if(MSGBOX_OK == MsgBox(title, msg, MSGBOX_STYLE_YESNO) ) {
	ret->setNewLwidget(lwidget);
      }
    } else {
      ret->setNewLwidget(lwidget);
    }
  }
  
  if(ret == NULL)                                 // nothing found 
    ret = new LresEditor(lwidget);
  ret->open();

  return ret;
}

// ---------------------------------
// autoLoadCallback()
// ---------------------------------

void LresEditor::autoLoadCallback( Widget, XtPointer client, XtPointer )
{
  LresEditor *self = (LresEditor*)client;
  if( !autoLoad.isNil() )
    XtVaSetValues(autoLoad->autoLoadToggle,
		  XmNset, FALSE,
		  NULL );

  if( autoLoad == self ) {
    autoLoad = NULL;
  } else {
    autoLoad = self;
    XtVaSetValues(autoLoad->autoLoadToggle,
		  XmNset, TRUE,
		  NULL );
  }
}

//----------------------------------
//  apply()
//----------------------------------
  
Boolean LresEditor::apply()
{
  unsigned int i;
  for( i=0; i<core.getSize(); i++ )
    core[i]->apply();
  for( i=0; i<specific.getSize(); i++ )
    specific[i]->apply();
  for( i=0; i<constraint.getSize(); i++ )
    constraint[i]->apply();
  for( i=0; i<callbacks.getSize(); i++ )
    callbacks[i]->apply();

  char *str = XmTextGetString( nameTextW );
  lwidget->setName( str );
  XtFree(str);
  
  lwidget->setManage(XmToggleButtonGetState(manageToggleW));

#ifndef WITHOUT_LAC
  str = XmTextGetString( quickHelpTextW );
  lwidget->setQuickhelp( str );
  XtFree(str);
  
  lwidget->setHelpNode(hnView->getHelpNode());
#endif

  lwidget->changed( RESOURCE_CHANGED );
  return TRUE;
}

//----------------------------------
//  act()
//----------------------------------

void LresEditor::act( char *action )
{
  if(!strcmp(action, LRESEDIT_HELPIDCLEAR)) {
    if(hnView)
      delete hnView;
    hnView = new HelpNodeView(helpNodeTextW);
    return;
  }
  if(!strcmp( action, LRESEDIT_APPLY )) {
    apply();
  }
  if( !strcmp( action, LRESEDIT_CLOSE ) ) {
    if(somethingChanged()) {
      char title[256];
      char msg[1024];
      msgCat->getMsg( title, LRES_SOME_CHANGES_TITLE );
      msgCat->getMsg( msg, LRES_SOME_CHANGES_MSG );
      if(MSGBOX_OK == MsgBox(title, msg, MSGBOX_STYLE_YESNO) ) {
	delete this;
      }
    } else {
      delete this;
    }
  }
  if( !strcmp( action, LRESEDIT_HELP ) ) {
    LicView::getHelp(HID_WIDGET_RESOURCE_EDITOR);
    return;
  }
  if( !strcmp( action, LRESEDIT_CORE ) ) {
    switchTo( PW_CORE );
  }
  if( !strcmp( action, LRESEDIT_SPECIFIC ) ) {
    switchTo( PW_SPECIFIC );
  }
  if( !strcmp( action, LRESEDIT_CONSTRAINT ) ) {
    switchTo( PW_CONSTRAINT );
  }
  if( !strcmp( action, LRESEDIT_CALLBACKS ) ) {
    switchTo( PW_CALLBACKS );
  }
  if( !strcmp( action, LRESEDIT_EXTRA ) ) {
    switchTo( PW_EXTRA );
  }
}

//----------------------------------
//  update()
//----------------------------------

void LresEditor::update( unsigned long flags )
{
  if( (flags & NAME_CHANGED) || (flags & EXTRA_CHANGED) ) {
    char title[256];
    msgCat->getMsg(title, RES_EDIT_TITLE, 
		   lwidget->getName(), 
		   lwidget->getClass()->getName() );
    XtVaSetValues(popupShell, 
		  XmNtitle, title,
		  XmNiconName, title,
		  NULL );

    fillExtra();
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

//----------------------------------
//  switchTo()
//----------------------------------

void LresEditor::switchTo( PropertyWin pw )
{
  unsigned int i;

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
  }
  
  currentPropertyWin = pw;
#ifdef WITH_CELL_TABLE
  WidgetClass wc = xlCellTableWidgetClass;
#else
  WidgetClass wc = xmRowColumnWidgetClass;
#endif
  switch( pw ) {
  case PW_CORE:
    if( !coreW ) {
      coreW = XtVaCreateWidget("Box",wc,
			       scrolledW,
			       XmNpacking, XmPACK_COLUMN,
			       XmNorientation, XmVERTICAL,
			       NULL);

      for( i=0 ; i<lwidget->getProperties()->getCore().getSize() ; i++ ) {
	core.add( createResView(lwidget->getProperties()->getCore()[i],
				coreW, i));
      }
    }
    XmScrolledWindowSetAreas( scrolledW, NULL, NULL, coreW );
    XtManageChild(coreW);
    dropSiteFix(coreW,TRUE);

    break;
  case PW_SPECIFIC:
    if( !specificW ) {
      specificW = XtVaCreateWidget("Box",wc,
					  scrolledW,
					  XmNorientation, XmVERTICAL,
					  NULL);
      for( i=0 ; i<lwidget->getProperties()->getSpecific().getSize() ; i++ ) {
	specific.add( createResView(lwidget->getProperties()->
				    getSpecific()[i], specificW, i));
      }
    }
    XmScrolledWindowSetAreas( scrolledW, NULL, NULL, specificW );
    XtManageChild(specificW);
    dropSiteFix(specificW,TRUE);
    break;
  case PW_CONSTRAINT:
    if( !constraintW ) {
      constraintW = XtVaCreateWidget("Box",wc,
				     scrolledW,
				     XmNorientation, XmVERTICAL,
				     NULL);
      for( i=0 ; i<lwidget->getProperties()->getConstraint().getSize() ; i++ ){
	constraint.add( createResView(lwidget->getProperties()->
				      getConstraint()[i],constraintW, i));
      }
    }
    XmScrolledWindowSetAreas( scrolledW, NULL, NULL, constraintW );
    XtManageChild(constraintW);
    dropSiteFix(constraintW,TRUE);
    break;
  case PW_CALLBACKS:
    if( !callbacksW ) {
      callbacksW = XtVaCreateWidget("Box",wc,
				    scrolledW,
				    XmNorientation, XmVERTICAL,
				    NULL);
      for( i=0 ; i<lwidget->getProperties()->getCallbacks().getSize() ; i++ ){
	callbacks.add( createResView(lwidget->getProperties()->
				      getCallbacks()[i],callbacksW, i));
      }
    }
    XmScrolledWindowSetAreas( scrolledW, NULL, NULL, callbacksW );
    XtManageChild(callbacksW);
    dropSiteFix(callbacksW,TRUE);
    break;
  case PW_EXTRA:
    XmScrolledWindowSetAreas( scrolledW, NULL, NULL, extraW );
    XtManageChild(extraW);
    dropSiteFix(extraW,TRUE);
    break;
  }
}

// --------------------
// fillExtra()
// --------------------
void LresEditor::fillExtra()
{
  XmTextSetString(nameTextW, lwidget->getName() );
  
  XtSetSensitive(manageToggleW,
		 (lwidget->getClass()->getManagePolicy() != NEVER_MANAGE));
  
  XmToggleButtonSetState(manageToggleW, lwidget->toManage(), FALSE);

#ifndef WITHOUT_LAC  
  if(lwidget->getQuickhelp())
    XmTextSetString(quickHelpTextW, lwidget->getQuickhelp());
  else
    XmTextSetString(quickHelpTextW, "");

  if(hnView)
    delete hnView;
  
  hnView = new HelpNodeView(helpNodeTextW, lwidget->getHelpNode());
#endif

}


// --------------------
// createResView()
// --------------------

ResView *LresEditor::createResView( Lresource *lres, Widget parent, Cardinal r)
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

// --------------------
// somethingChnaged()
// --------------------
Boolean LresEditor::somethingChanged()
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
  
  return ret;
}

// --------------------
// setNewLwidget()
// --------------------
void LresEditor::setNewLwidget( Lwidget *lwidget )
{
  unsigned int i;
  Lwidget *old = this->lwidget;
  this->lwidget = lwidget;

  changeModel( lwidget );
  update( NAME_CHANGED );

  if( coreW )
    for( i=0; i<core.getSize(); i++ )
      core[i]->setNewLresource(lwidget->getProperties()->getCore()[i]);

  if( lwidget->getClass() != old->getClass() ) { 
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
	specific[i]->setNewLresource(lwidget->getProperties()->
				     getSpecific()[i]);
    if( callbacksW )
      for( i=0; i<callbacks.getSize(); i++ )
	callbacks[i]->setNewLresource(lwidget->getProperties()->
				      getCallbacks()[i]);
  }

  if( ( !lwidget->getParent() || !old->getParent() ) ||
     (( lwidget->getParent() && old->getParent() ) &&
	lwidget->getParent()->getClass() != old->getParent()->getClass()) ||
     constraint.getSize()!=lwidget->getProperties()->getConstraint().getSize())
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
	  constraint[i]->setNewLresource(lwidget->getProperties()->
					 getConstraint()[i]);
    }
  switchTo( currentPropertyWin );
  
}

// -------------------------------
//    configureEvent()
// -------------------------------

void LresEditor::configureEvent(Widget , XtPointer, 
				       XEvent* event, Boolean*) {
//  LresEditor *self = (LresEditor*)clientData;
  if( event->type==ConfigureNotify || event->type==MapNotify ) {
  }
}


// -------------------------------
//    withLibLac()
// -------------------------------

void LresEditor::withLibLac(Boolean w) 
{
#ifndef WITHOUT_LAC
  for(unsigned int i=0; i<allViews.getSize(); i++) {
    XtSetSensitive(allViews[i]->quickHelpLabelW, w);
    XtSetSensitive(allViews[i]->quickHelpTextW, w);
    XtSetSensitive(allViews[i]->helpNodeLabelW, w);
    XtSetSensitive(allViews[i]->helpNodeTextW, w);
    XtSetSensitive(allViews[i]->helpNodeButtonW, w);
  }
#endif
}

// ---------------------------------
// dropSiteRegister()
// ---------------------------------

void LresEditor::helpNodeDropSiteRegister()
{
  static imports[1];
  Widget wg;
  
  wg = helpNodeTextW;
  imports[0] = XmInternAtom(XtDisplay(wg), "HelpNode", False);
  
  Arg args[10];
  Cardinal n = 0;
  XtSetArg(args[n], XmNimportTargets, imports); n++;
  XtSetArg(args[n], XmNnumImportTargets, 1); n++;
  XtSetArg(args[n], XmNdropSiteOperations, XmDROP_LINK); n++;
  XtSetArg(args[n], XmNdropProc, helpNodeDropProc); n++;
  XmDropSiteUnregister(wg);
  XmDropSiteRegister(wg,args,n);
}

// ---------------------------------
// dropProp
// ---------------------------------

void LresEditor::helpNodeDropProc(Widget wg, XtPointer, XtPointer callData)
{
  static XmDropTransferEntryRec transList[1];
  XmDropProcCallback dd = (XmDropProcCallback)callData;
  Arg args[10];
  Cardinal n=0;
  LresEditor *v = NULL;

  for(unsigned int i=0; i<allViews.getSize(); i++ ) {
    if( wg == allViews[i]->helpNodeTextW ) {
      v = allViews[i];
    }
  }

  if(!v) {
    fprintf(stderr, "Fatal Error: v==NULL in LresEditor\n");
  }
  transList[0].target = XmInternAtom(XtDisplay(wg), "HelpNode", False);
  transList[0].client_data = (XtPointer)v;
  XtSetArg(args[n], XmNdropTransfers, transList); n++;
  XtSetArg(args[n], XmNnumDropTransfers, 1); n++;
  XtSetArg(args[n], XmNtransferProc, helpNodeTransferProc); n++;
  XmDropTransferStart(dd->dragContext,args,n);

}

// ---------------------------------
// transferProc()
// ---------------------------------

void LresEditor::helpNodeTransferProc(Widget w, XtPointer closure, 
				      Atom *, Atom *,
				      XtPointer value, unsigned long *, 
				      int *)
{
  if(!value) {
    XtVaSetValues(w, XmNtransferStatus, XmTRANSFER_FAILURE, NULL);
    return;
  }
  LresEditor *v  = (LresEditor*)closure;
  HelpNode **ptr = (HelpNode**)value;
  HelpNode *helpNode = *ptr;

  v->linkWithHelpNode(helpNode);
}

void LresEditor::linkWithHelpNode(HelpNode *helpNode)
{
  if(hnView)
    delete hnView;
  hnView = new HelpNodeView(helpNodeTextW, helpNode);
}

#endif
			   
// ######################################################
// ResView
// ######################################################
// --------------------
// Constructor
// --------------------
ResView::ResView( Lresource *model, Widget parent, LicView *pView, Cardinal r)
:ValueView( model )
{
  XmString string;
  char strBuffer[100];
  Lstring quickHelp;

  this->r = r;
  this->pView = pView;
  lresource = model;
  table = parent;

  strcpy( strBuffer, "  " );
  strcat( strBuffer, lresource->getName() );
  strcat( strBuffer, ":" );
  string = XmStringCreateLtoR( strBuffer, XmSTRING_DEFAULT_CHARSET );
  label = XtVaCreateManagedWidget("Label", xmToggleButtonWidgetClass,
				  table,
				  XmNalignment, XmALIGNMENT_END,
				  XmNlabelString, string,
				  XmNcellRow, r,
				  XmNcellColumn, 0,
				  XmNrecomputeSize, FALSE,
				  XmNset, !lresource->isDefault(),
				  NULL );
  XtAddCallback( label, XmNvalueChangedCallback, valueChangedCallback, this );
  XmStringFree( string );
  changed = FALSE;

  quickHelp = "Resource Type: ";
  quickHelp += lresource->getType();
  pView->addQuickHelp(label);
  pView->setQuickHelp(label, quickHelp);

  createAttributeMenu();
}

void 
ResView::createAttributeMenu()
{
  Widget pdMenu, wg, current = NULL, preferThis = NULL;
  Cardinal n = 0;
  Arg args[10];
  char buf[256];

  TArray<LresAttribute> attrs = lresource->getPossibleAttributes();

  pdMenu = XmCreatePulldownMenu(table, "Attributes", (Arg*)NULL, 0 ); 

  FOREACH(i,attrs) {
    wg = XtVaCreateManagedWidget(attrs[i]->getString(), 
				 xmPushButtonWidgetClass, pdMenu,
				 NULL );
    XtAddCallback(wg, XmNactivateCallback,
		  valueChangedCallback, this);
    pView->addQuickHelp(wg);
    strcpy(buf, "Error: Quick-Help not found.");
    if(attrs[i] == &LresAttribute::attrPrivate) {
      msgCat->getMsg(buf, ATTRIB_PRIVATE);
    } else if(attrs[i] == &LresAttribute::attrPublic) {
      msgCat->getMsg(buf, ATTRIB_PUBLIC);
      if(lresource->isDefault() && app->isPublicResource(lresource->getName()))
	preferThis = wg;
    } else if(attrs[i] == &LresAttribute::attrInclude) {
      msgCat->getMsg(buf, ATTRIB_INCLUDE);
    } else if(attrs[i] == &LresAttribute::attrLoad) {
      msgCat->getMsg(buf, ATTRIB_LOAD);
    } else if(attrs[i] == &LresAttribute::attrMethod) {
      msgCat->getMsg(buf, ATTRIB_METHOD);
    } else if(attrs[i] == &LresAttribute::attrManage) {
      msgCat->getMsg(buf, ATTRIB_MANAGE);
    } 
    pView->setQuickHelp(wg, buf);
    
    if(attrs[i] == lresource->getAttribute())
      current = wg;
  }
  XtSetArg(args[n], XmNsubMenuId, pdMenu); n++;
  XtSetArg(args[n], XmNcellRow, r); n++;
  XtSetArg(args[n], XmNcellColumn, 3); n++;
  XtSetArg(args[n], XmNverticalAlignment, XmCELL_ALIGNMENT_CENTER); n++;

  if(preferThis)
    current = preferThis;
  if(current) {
    XtSetArg(args[n], XmNmenuHistory, current); n++;
  }
  attrMenu = XmCreateOptionMenu(table, "AttributesMenu", args, n);
  XtManageChild(attrMenu);

}

ResView::~ResView()
{
}

Boolean 
ResView::apply()
{
  if( changed ) {
    Boolean notDefault;

    XtVaGetValues( label, XmNset, &notDefault, NULL );
    if( !notDefault ) {
      lresource->setDefault(TRUE);
      update(VALUE_CHANGED);
    } else {
      Widget current = NULL;
      XtVaGetValues(attrMenu, XmNmenuHistory, &current, NULL);
      if(current) {
	lresource->setAttribute(XtName(current));
      }

      unsigned int len;
      getStringValue( NULL, len );
      char str[len];
      getStringValue( str, len );
      lresource->setString( str );
      lresource->changed(VALUE_CHANGED);
    }
  }
  return TRUE;
}

void 
ResView::valueChangedCallback(Widget wg, 
				   XtPointer clientData, 
				   XtPointer )
{
  ResView *self = (ResView*)clientData;
  if( !self->changed ) {
    XmString string;
    char strBuffer[100];
    
    self->changed = TRUE;

    strcpy( strBuffer, "* " );
    strcat( strBuffer, self->lresource->getName() );
    strcat( strBuffer, ":" );
    string = XmStringCreateLtoR( strBuffer, XmSTRING_DEFAULT_CHARSET );
    XtVaSetValues(self->label,
		  XmNlabelString, string,
		  NULL );
    XmStringFree(string);
  }
  if(strcmp(XtName(wg),"Label")) 
    XtVaSetValues(self->label, XmNset, TRUE, NULL );
}

void 
ResView::update( unsigned long flags ) 
{
  if( flags & VALUE_CHANGED ) {
    XmString string;
    char strBuffer[100];

    changed = FALSE;
    strcpy( strBuffer, "  " );
    strcat( strBuffer, lresource->getName() );
    strcat( strBuffer, ":" );
    string = XmStringCreateLtoR( strBuffer, XmSTRING_DEFAULT_CHARSET );
    XtVaSetValues(label,
		  XmNlabelString, string,
		  XmNset, !lresource->isDefault(),
		  NULL );
    XmStringFree(string);

    Widget menu, pushbutton;
    const char *attrToFind = NULL;

    if(attrMenu) {
      XtVaGetValues(attrMenu, XmNsubMenuId, &menu, NULL);
      pushbutton = NULL;
      if(lresource->getAttribute())
	attrToFind = lresource->getAttribute()->getString();
      else {            // default attribute
	TArray<LresAttribute> a = lresource->getPossibleAttributes();
	if(a.getSize() > 0)
	  attrToFind = a[0]->getString();
      }
      if(lresource->isDefault() && app->isPublicResource(lresource->getName()))
	pushbutton = XtNameToWidget(menu, "public");

      if(attrToFind && pushbutton == NULL)
	pushbutton = XtNameToWidget(menu, attrToFind);
      
      if(pushbutton) {
	XtVaSetValues(attrMenu, XmNmenuHistory, pushbutton, NULL);
      }
    }
  }
}


void ResView::setNewLresource( Lresource *lr )
{
  lresource = lr;
  changeModel(lr);
  update(VALUE_CHANGED);
}


// ##################################################################
// TextResView
// ##################################################################

// ------------------
// TextResView()
// ------------------

TextResView::TextResView( Lresource *model, Widget parent, LicView *pView, Cardinal r) 
:ResView( model, parent, pView, r)
{
  textWidget = XtVaCreateManagedWidget(model->getClassName(), 
				       xmTextWidgetClass, table, 
				       XmNcellRow, r,
				       XmNcellColumn, 1,
				       XmNverticalAlignment, XmCELL_ALIGNMENT_CENTER,
				       NULL );
  pView->addQuickHelp(textWidget);
  XtAddCallback(textWidget, XmNvalueChangedCallback,
		valueChangedCallback, this );

  update( VALUE_CHANGED );
}

// ------------------
// getText()
// ------------------

void 
TextResView::getText(char *text, unsigned long &len)
{
  char *t;

  t = XmTextGetString(textWidget);
  if(text == NULL) {
    len = strlen(t)+1;
  } else {
    strcpy(text,t);
  }
  XtFree(t);
}

// ------------------
// setText()
// ------------------

void 
TextResView::setText(char *text)
{
  Boolean hasNewLine = FALSE;
  for(char *ptr=text ; *ptr && !hasNewLine ; ptr++)
    if(*ptr == '\n')
      hasNewLine = TRUE;
  XtSetSensitive(textWidget, !hasNewLine);
  if(hasNewLine)
    XtVaSetValues(textWidget, XmNeditMode, 
		  XmMULTI_LINE_EDIT, NULL);
  else
    XtVaSetValues(textWidget, XmNeditMode, 
		  XmSINGLE_LINE_EDIT, NULL);
    
  XmTextSetString(textWidget, text);
  valueChangedCallback(textWidget,this,NULL);
}

// ------------------
// update()
// ------------------

void 
TextResView::update( unsigned long flags ) 
{
  if( flags & VALUE_CHANGED ) {
    unsigned int len;
    Boolean hasNewLine = FALSE;

    lresource->getString( NULL, len );
    char str[len];
    lresource->getString( str, len );

    for(char *ptr=str ; *ptr && !hasNewLine ; ptr++)
      if(*ptr == '\n')
	hasNewLine = TRUE;
    XtSetSensitive(textWidget, !hasNewLine);

    if(hasNewLine)
      XtVaSetValues(textWidget, XmNeditMode, 
		    XmMULTI_LINE_EDIT, NULL);
    else
      XtVaSetValues(textWidget, XmNeditMode, 
		    XmSINGLE_LINE_EDIT, NULL);
    

    XmTextSetString(textWidget, str );
  }
  ResView::update(flags);
}

// ------------------
// getStringValue
// ------------------

void 
TextResView::getStringValue( char *buffer, unsigned int &len )
{
  char *str = XmTextGetString( textWidget );
  if( !buffer ) {
    len = strlen(str)+1;
    XtFree( str );
    return;
  }
  strncpy( buffer, str, len-1 );
  buffer[len-1]=0;
  XtFree( str );
}


// ##################################################################
// FontResView
// ##################################################################

// ------------------
// FontResView()
// ------------------

FontResView::FontResView(Lresource *model, Widget parent, LicView *pView,
Cardinal r)
:TextResView(model,parent, pView, r)
{
  button = XtVaCreateManagedWidget("F", xmPushButtonWidgetClass, table, 
				   XmNcellRow, r,
				   XmNcellColumn, 2,
				   XmNhorizontalAlignment, XmCELL_ALIGNMENT_CENTER,
				   XmNverticalAlignment, XmCELL_ALIGNMENT_CENTER,
				   NULL );
  pView->addQuickHelp(button);
  XtAddCallback(button, XmNactivateCallback,
		fontSelectCallback, this);

}

// ------------------
// fontSelectCallback
// ------------------

void 
FontResView::fontSelectCallback(Widget,XtPointer client,XtPointer)
{
  FontResView *self = (FontResView*)client;
  
  LicView::setWaitCursor(TRUE);
  if( self->fontSelect.isNil() ) {
    self->fontSelect = new FontSelect(self);
  } 
  self->fontSelect->open();
  LicView::setWaitCursor(FALSE);
}


// ##################################################################
// MultiTextResView
// ##################################################################

// ------------------
// MultiTextResView()
// ------------------

MultiTextResView::MultiTextResView(Lresource *model, Widget parent, LicView *pView, Cardinal r)
:TextResView(model,parent, pView, r)
{
  button = XtVaCreateManagedWidget("T", xmPushButtonWidgetClass, table, 
				   XmNcellRow, r,
				   XmNcellColumn, 2,
				   XmNhorizontalAlignment, XmCELL_ALIGNMENT_CENTER,
				   XmNverticalAlignment, XmCELL_ALIGNMENT_CENTER,
				   NULL );
  pView->addQuickHelp(button);
  XtAddCallback(button, XmNactivateCallback,
		multiTextCallback, this);
}

// ------------------
// multiTextCallback
// ------------------

void 
MultiTextResView::multiTextCallback(Widget,XtPointer client,XtPointer)
{
  MultiTextResView *self = (MultiTextResView*)client;
  
  LicView::setWaitCursor(TRUE);
  if( self->textEdit.isNil() ) {
    self->textEdit = new TextEdit(self);
  } 
  self->textEdit->open();
  LicView::setWaitCursor(FALSE);
}


// ##################################################################
// ColorResView
// ##################################################################

// ------------------
// ColorResView()
// ------------------

ColorResView::ColorResView(Lresource *model, Widget parent, LicView *pView,
			   Cardinal r)
:TextResView(model,parent, pView, r)
{
  button = XtVaCreateManagedWidget("C", xmPushButtonWidgetClass, table, 
				   XmNcellRow, r,
				   XmNcellColumn, 2,
				   XmNhorizontalAlignment, XmCELL_ALIGNMENT_CENTER,
				   XmNverticalAlignment, XmCELL_ALIGNMENT_CENTER,
				   NULL );
  pView->addQuickHelp(button);
  XtAddCallback(button, XmNactivateCallback,
		colorSelectCallback, this);
}

// ------------------
// ColorSelectCallback
// ------------------

void 
ColorResView::colorSelectCallback(Widget,XtPointer client,XtPointer)
{
  ColorResView *self = (ColorResView*)client;

  LicView::setWaitCursor(TRUE);
  if( self->colorSelect.isNil() ) {
    self->colorSelect = new ColorSelect(self);
  } 
  self->colorSelect->open();
  LicView::setWaitCursor(FALSE);
}



// ##################################################################
// BooleanResView
// ##################################################################

// ------------------
// BooleanResView()
// ------------------

BooleanResView::BooleanResView( Lresource *model, Widget parent, 
				LicView *pView, Cardinal r) 
:ResView( model, parent, pView, r)
{
  toggleWidget = XtVaCreateManagedWidget("true", xmToggleButtonWidgetClass,
					 table, 
					 XmNcellRow, r,
					 XmNcellColumn, 1,
					 XmNhorizontalAlignment, XmCELL_ALIGNMENT_BEGINNING,
					 NULL );
  XtAddCallback(toggleWidget, XmNvalueChangedCallback,
		valueChangedCallback, this );
  
  update( VALUE_CHANGED );
}

// ------------------
// update()
// ------------------

void 
BooleanResView::update( unsigned long flags ) 
{
  ResView::update(flags);
  if( flags & VALUE_CHANGED ) {
    XtVaSetValues(toggleWidget,
		  XmNset, lresource->getValue(),
		  NULL );
  }
}

// ------------------
// getStringValue
// ------------------

void 
BooleanResView::getStringValue( char *buffer, unsigned int &len )
{
  if( !buffer ) {
    len = 1+1;
    return;
  }
  if( len < 2 )
    return;
  Boolean set;
  XtVaGetValues( toggleWidget,
		XmNset, &set,
		NULL );
  sprintf( buffer,"%d", set );
}


// ##################################################################
// EnumResView
// ##################################################################

// ------------------
// EnumResView()
// ------------------

EnumResView::EnumResView( Lresource *model, Widget parent, LicView *pView,
			  Cardinal r) 
:ResView( model, parent, pView, r)
{
  int  n=0;
  unsigned int i=0;
  Widget pdMenu, wg;
  Arg args[10];
  char str[256];

  LresEnum *lresEnum = (LresEnum *)model;

  unsigned int len;
  lresEnum->getPossibleIdentifiers(NULL,len);
  char *ids[len];
  lresEnum->getPossibleIdentifiers(ids,len);

  pdMenu = XmCreatePulldownMenu(table, "Options", (Arg*)NULL, 0 ); 

  for( i=0; i<len; i++ ) {
    strcpy(str, ids[i]);
    XmString xms;
    char *ptr = str;
    if(str[0] == 'X' && str[1] == 'm') {
      for(ptr = str+2; *ptr; ptr++)
	*ptr = tolower(*ptr);
      ptr = str+2;
    }
    xms = XmStringCreateLtoR(ptr, XmSTRING_DEFAULT_CHARSET);
    wg = XtVaCreateManagedWidget(ids[i], 
				 xmPushButtonWidgetClass, pdMenu,
				 XmNlabelString, xms,
				 NULL );
    XmStringFree(xms);
    XtAddCallback(wg, XmNactivateCallback,
		  valueChangedCallback, this );
  }
  XtSetArg( args[n], XmNsubMenuId, pdMenu ); n++;
  XtSetArg( args[n], XmNcellRow, r); n++;
  XtSetArg( args[n], XmNcellColumn, 1); n++;
  XtSetArg( args[n], XmNhorizontalAlignment, XmCELL_ALIGNMENT_BEGINNING); n++;
  XtSetArg( args[n], XmNverticalAlignment, XmCELL_ALIGNMENT_CENTER); n++;
  menu = XmCreateOptionMenu(table, "ResourceMenu", args, n );
  XtManageChild( menu );


  update( VALUE_CHANGED );
}

// ------------------
// update()
// ------------------

void 
EnumResView::update( unsigned long flags ) 
{
  Widget wg, pdMenu;
  unsigned int len;

  ResView::update(flags);
  if( flags & VALUE_CHANGED ) {
    lresource->getString( NULL, len );
    char id[len];
    lresource->getString(id,len);
    XtVaGetValues( menu, XmNsubMenuId, &pdMenu, NULL );
    wg = XtNameToWidget( pdMenu, id );
    if( !wg )
      fprintf(stderr,"can not find widget %s\n",id);
    else
      XtVaSetValues( menu, XmNmenuHistory, wg, NULL);
  }
}

// ------------------
// getStringValue
// ------------------

void 
EnumResView::getStringValue( char *buffer, unsigned int &len )
{
  Widget wg;
  XtVaGetValues( menu, XmNmenuHistory, &wg, NULL );
  if( !buffer ) {
    len = strlen(XtName(wg))+1;
    return;
  }
  if( len < strlen(XtName(wg))+1 )
    return;
  strcpy( buffer, XtName(wg));
}



// ###############################
// WidNameView
// ###############################
WidNameView::WidNameView(Lwidget *model, Widget parent, 
			 LicView *pView, Cardinal r)
  : ValueView(model)
{
  this->model = model;
  label = XtVaCreateManagedWidget("WidNameLabel", xmLabelWidgetClass,
				  parent,
				  XmNhorizontalAlignment, XmCELL_ALIGNMENT_END,
				  XmNcellRow, r,
				  XmNcellColumn, 0,
				  //  XmNrecomputeSize, FALSE,
				  XmNalignment, XmALIGNMENT_END,
				  NULL );
  text = XtVaCreateManagedWidget("WidNameText", 
				 xmTextWidgetClass, parent, 
				 XmNcellRow, r,
				 XmNcellColumn, 1,
				 XmNverticalAlignment, 
				 XmCELL_ALIGNMENT_CENTER,
				 NULL );
  pView->addQuickHelp(text);
  XtAddCallback(text, XmNvalueChangedCallback,
		valueChangedCallback, this );
  
  update(NAME_CHANGED);
}
  
void 
WidNameView::valueChangedCallback( Widget, XtPointer client, XtPointer )
{
  WidNameView *self = (WidNameView*)client;
  char *str = XmTextGetString(self->text);
  char msg[256];
  XmString xms;
  
  msgCat->getMsg(msg, WidName_LABEL);
  
  if(str == NULL)
    return;

  if(!strcmp(self->model->getName(), str)) {
    self->changed = FALSE;
    xms = XmStringCreate(msg, XmSTRING_DEFAULT_CHARSET);
  } else {
    char buf[256];
    self->changed = TRUE;
    strcpy(buf, "* ");
    strcat(buf, msg);
    xms = XmStringCreate(buf, XmSTRING_DEFAULT_CHARSET);
  }
  XtVaSetValues(self->label, XmNlabelString, xms, NULL);
  XmStringFree(xms);
  XtFree(str);
}

Boolean 
WidNameView::apply()
{
  char *str = XmTextGetString(text);
  if(str) {
    if(!model->setName(str))
      XBell(XtDisplay(label), 200);
    XtFree(str);
  }
  return TRUE;
}

void 
WidNameView::update(unsigned long flags)
{
  if(flags & NAME_CHANGED) {
    XmTextSetString(text, model->getName());
  }
}

void 
WidNameView::setNewLwidget(Lwidget *model)
{
  this->model = model;
  changeModel(model);
  update(NAME_CHANGED);
}

// ###############################
// WidDescriptionView
// ###############################
WidDescriptionView::WidDescriptionView(Lwidget *model, Widget parent, 
			 LicView *pView, Cardinal r)
  : ValueView(model)
{
  this->model = model;
  label = XtVaCreateManagedWidget("WidDescriptionLabel", xmLabelWidgetClass,
				  parent,
				  XmNhorizontalAlignment, XmCELL_ALIGNMENT_END,
				  XmNcellRow, r,
				  XmNcellColumn, 0,
				  //  XmNrecomputeSize, FALSE,
				  XmNalignment, XmALIGNMENT_END,
				  NULL );
  text = XtVaCreateManagedWidget("WidDescriptionText", 
				 xmTextWidgetClass, parent, 
				 XmNcellRow, r,
				 XmNcellColumn, 1,
				 XmNverticalAlignment, 
				 XmCELL_ALIGNMENT_CENTER,
				 XmNcolumns, 40,
				 NULL );
  pView->addQuickHelp(text);
  XtAddCallback(text, XmNvalueChangedCallback,
		valueChangedCallback, this );
  
  update(EXTRA_CHANGED);
}
  
void 
WidDescriptionView::valueChangedCallback( Widget, XtPointer client, XtPointer )
{
  WidDescriptionView *self = (WidDescriptionView*)client;
  char *str = XmTextGetString(self->text);
  char msg[256];
  XmString xms;
  
  msgCat->getMsg(msg, WidDescription_LABEL);
  
  if(str == NULL)
    return;

  if( (self->model->getDescription() && 
       !strcmp(self->model->getDescription(),str)) ||
      (self->model->getDescription() == NULL && str[0] == 0) ) {
    self->changed = FALSE;
    xms = XmStringCreate(msg, XmSTRING_DEFAULT_CHARSET);
  } else {
    char buf[256];
    self->changed = TRUE;
    strcpy(buf, "* ");
    strcat(buf, msg);
    xms = XmStringCreate(buf, XmSTRING_DEFAULT_CHARSET);
  }
  XtVaSetValues(self->label, XmNlabelString, xms, NULL);
  XmStringFree(xms);
  XtFree(str);
}

Boolean 
WidDescriptionView::apply()
{
  char *str = XmTextGetString(text);
  if(str) {
    model->setDescription(str);
    XtFree(str);
  }
  return TRUE;
}

void 
WidDescriptionView::update(unsigned long flags)
{
  if(flags & EXTRA_CHANGED) {
    XmTextSetString(text, model->getDescription());
  }
}

void 
WidDescriptionView::setNewLwidget(Lwidget *model)
{
  this->model = model;
  changeModel(model);
  update(EXTRA_CHANGED);
}

// ###############################
// WidQuickHelpView
// ###############################
WidQuickHelpView::WidQuickHelpView(Lwidget *model, Widget parent, 
			 LicView *pView, Cardinal r)
  : ValueView(model)
{
  this->model = model;
  label = XtVaCreateManagedWidget("WidQuickHelpLabel", xmLabelWidgetClass,
				  parent,
				  XmNhorizontalAlignment, XmCELL_ALIGNMENT_END,
				  XmNcellRow, r,
				  XmNcellColumn, 0,
				  //  XmNrecomputeSize, FALSE,
				  XmNalignment, XmALIGNMENT_END,
				  NULL );
  text = XtVaCreateManagedWidget("WidQuickHelpText", 
				 xmTextWidgetClass, parent, 
				 XmNcellRow, r,
				 XmNcellColumn, 1,
				 XmNverticalAlignment, 
				 XmCELL_ALIGNMENT_CENTER,
				 XmNcolumns, 40,
				 NULL );
  pView->addQuickHelp(text);
  XtAddCallback(text, XmNvalueChangedCallback,
		valueChangedCallback, this );
  
  update(EXTRA_CHANGED);
}
  
void 
WidQuickHelpView::valueChangedCallback( Widget, XtPointer client, XtPointer )
{
  WidQuickHelpView *self = (WidQuickHelpView*)client;
  char *str = XmTextGetString(self->text);
  char msg[256];
  XmString xms;
  
  msgCat->getMsg(msg, WidQuickHelp_LABEL);
  
  if(str == NULL)
    return;

  if((self->model->getQuickhelp() && !strcmp(self->model->getQuickhelp(), str))
     || (self->model->getQuickhelp() == NULL && str[0] == 0))
    {
      self->changed = FALSE;
      xms = XmStringCreate(msg, XmSTRING_DEFAULT_CHARSET);
    } else {
      char buf[256];
      self->changed = TRUE;
      strcpy(buf, "* ");
      strcat(buf, msg);
      xms = XmStringCreate(buf, XmSTRING_DEFAULT_CHARSET);
    }
  XtVaSetValues(self->label, XmNlabelString, xms, NULL);
  XmStringFree(xms);
  XtFree(str);
}

Boolean 
WidQuickHelpView::apply()
{
  char *str = XmTextGetString(text);
  if(str) {
    model->setQuickhelp(str);
    XtFree(str);
  }
  return TRUE;
}

void 
WidQuickHelpView::update(unsigned long flags)
{
  if(flags & EXTRA_CHANGED) {
    if(model->getQuickhelp())
      XmTextSetString(text, model->getQuickhelp());
    else
      XmTextSetString(text, NULL);
    valueChangedCallback(NULL, this, NULL);
  }
}

void 
WidQuickHelpView::setNewLwidget(Lwidget *model)
{
  this->model = model;
  changeModel(model);
  update(EXTRA_CHANGED);
}

// ###############################
// WidHelpNodeView
// ###############################

RefArray<WidHelpNodeView> WidHelpNodeView::allViews;

WidHelpNodeView::WidHelpNodeView(Lwidget *model, Widget parent, 
			 LicView *pView, Cardinal r)
  : ValueView(model)
{
  this->model = model;
  helpNode = model->getHelpNode();
  label = XtVaCreateManagedWidget("WidHelpNodeLabel", xmLabelWidgetClass,
				  parent,
				  XmNhorizontalAlignment, XmCELL_ALIGNMENT_END,
				  XmNcellRow, r,
				  XmNcellColumn, 0,
				  //  XmNrecomputeSize, FALSE,
				  XmNalignment, XmALIGNMENT_END,
				  NULL );
  text = XtVaCreateManagedWidget("WidHelpNodeText", 
				 xmTextWidgetClass, parent, 
				 XmNcellRow, r,
				 XmNcellColumn, 1,
				 XmNverticalAlignment, 
				 XmCELL_ALIGNMENT_CENTER,
				 XmNcolumns, 40,
				 XmNeditable, FALSE,
				 NULL );
  clearButton = XtVaCreateManagedWidget("Clear",
					xmPushButtonWidgetClass, parent,
					XmNcellRow, r,
					XmNcellColumn, 2,
					XmNverticalAlignment, 
					XmCELL_ALIGNMENT_CENTER,
					XmNhorizontalAlignment, 
					XmCELL_ALIGNMENT_BEGINNING,
					NULL);
  addAction(clearButton, "clear");

  allViews.add(this);

  pView->addQuickHelp(text);
  pView->addQuickHelp(clearButton);
  XtAddCallback(text, XmNvalueChangedCallback,
		valueChangedCallback, this );
  
  dropSiteRegister();
  update(EXTRA_CHANGED);
}
  
void 
WidHelpNodeView::act(char *action)
{
  if(!strcmp(action, "clear")) {
    helpNode = NULL;
    valueChangedCallback(NULL, this, NULL);
    update(EXTRA_CHANGED);
  }
}

void 
WidHelpNodeView::valueChangedCallback( Widget, XtPointer client, XtPointer )
{
  WidHelpNodeView *self = (WidHelpNodeView*)client;
  char msg[256];
  XmString xms;
  
  msgCat->getMsg(msg, WidHelpNode_LABEL);
  
  if(self->model->getHelpNode() == self->helpNode) {
    self->changed = FALSE;
    xms = XmStringCreate(msg, XmSTRING_DEFAULT_CHARSET);
  } else {
    char buf[256];
    self->changed = TRUE;
    strcpy(buf, "* ");
    strcat(buf, msg);
    xms = XmStringCreate(buf, XmSTRING_DEFAULT_CHARSET);
  }
  XtVaSetValues(self->label, XmNlabelString, xms, NULL);
  XmStringFree(xms);
}

Boolean 
WidHelpNodeView::apply()
{
  model->setHelpNode(helpNode);
  return TRUE;
}

void 
WidHelpNodeView::update(unsigned long flags)
{
  if(flags & EXTRA_CHANGED) {
    if(helpNode)
      XmTextSetString(text, helpNode->getName());
    else
      XmTextSetString(text, "");
    valueChangedCallback(NULL, this, NULL);
  }
}

void 
WidHelpNodeView::setNewLwidget(Lwidget *model)
{
  this->model = model;
  changeModel(model);
  helpNode = model->getHelpNode();
  update(EXTRA_CHANGED);
}

// ---------------------------------
// dropSiteRegister()
// ---------------------------------

void 
WidHelpNodeView::dropSiteRegister()
{
  static Atom imports[1];
  Widget wg;
  
  wg = text;
  imports[0] = XmInternAtom(XtDisplay(wg), "HelpNode", False);
  
  Arg args[10];
  Cardinal n = 0;
  XtSetArg(args[n], XmNimportTargets, imports); n++;
  XtSetArg(args[n], XmNnumImportTargets, 1); n++;
  XtSetArg(args[n], XmNdropSiteOperations, XmDROP_LINK); n++;
  XtSetArg(args[n], XmNdropProc, dropProc); n++;
  XmDropSiteUnregister(wg);
  XmDropSiteRegister(wg,args,n);
}

// ---------------------------------
// dropProp
// ---------------------------------

void 
WidHelpNodeView::dropProc(Widget wg, XtPointer, XtPointer callData)
{
  static XmDropTransferEntryRec transList[1];
  XmDropProcCallback dd = (XmDropProcCallback)callData;
  Arg args[10];
  Cardinal n=0;
  WidHelpNodeView *v = NULL;

  for(unsigned int i=0; i<allViews.getSize(); i++ ) {
    if( wg == allViews[i]->text ) {
      v = allViews[i];
    }
  }

  if(!v) {
    fprintf(stderr, "Fatal Error: v==NULL in WidHelpNodeView\n");
  }
  transList[0].target = XmInternAtom(XtDisplay(wg), "HelpNode", False);
  transList[0].client_data = (XtPointer)v;
  XtSetArg(args[n], XmNdropTransfers, transList); n++;
  XtSetArg(args[n], XmNnumDropTransfers, 1); n++;
  XtSetArg(args[n], XmNtransferProc, transferProc); n++;
  XmDropTransferStart(dd->dragContext,args,n);

}

// ---------------------------------
// transferProc()
// ---------------------------------

void 
WidHelpNodeView::transferProc(Widget w, XtPointer closure, 
			      Atom *, Atom *,
			      XtPointer value, unsigned long *, 
			      int *)
{
  if(!value) {
    XtVaSetValues(w, XmNtransferStatus, XmTRANSFER_FAILURE, NULL);
    return;
  }
  WidHelpNodeView *v  = (WidHelpNodeView*)closure;
  HelpNode **ptr = (HelpNode**)value;
  HelpNode *helpNode = *ptr;

  v->helpNode = helpNode;
  v->update(EXTRA_CHANGED);
}

// ###############################
// WidManageView
// ###############################
WidManageView::WidManageView(Lwidget *model, Widget parent, 
			 LicView *pView, Cardinal r)
  : ValueView(model)
{
  this->model = model;
  label = XtVaCreateManagedWidget("WidManageLabel", xmLabelWidgetClass,
				  parent,
				  XmNhorizontalAlignment, XmCELL_ALIGNMENT_END,
				  XmNcellRow, r,
				  XmNcellColumn, 0,
				  //  XmNrecomputeSize, FALSE,
				  XmNalignment, XmALIGNMENT_END,
				  NULL );
  toggle = XtVaCreateManagedWidget("true", 
				   xmToggleButtonWidgetClass, parent, 
				   XmNcellRow, r,
				   XmNcellColumn, 1,
				   XmNverticalAlignment, 
				   XmCELL_ALIGNMENT_CENTER,
				   XmNhorizontalAlignment, 
				   XmCELL_ALIGNMENT_BEGINNING,
				   NULL );
  pView->addQuickHelp(toggle);
  XtAddCallback(toggle, XmNvalueChangedCallback,
		valueChangedCallback, this );
  if(model->getClass()->getManagePolicy() == NEVER_MANAGE)
    XtSetSensitive(toggle, FALSE);
  update(EXTRA_CHANGED);
}
  
void 
WidManageView::valueChangedCallback( Widget, XtPointer client, XtPointer )
{
  WidManageView *self = (WidManageView*)client;
  Boolean m = XmToggleButtonGetState(self->toggle);
  char msg[256];
  XmString xms;
  
  msgCat->getMsg(msg, WidManage_LABEL);

  if((m && self->model->toManage()) || (!m && !self->model->toManage())) {
    self->changed = FALSE;
    xms = XmStringCreate(msg, XmSTRING_DEFAULT_CHARSET);
  } else {
    char buf[256];
    self->changed = TRUE;
    strcpy(buf, "* ");
    strcat(buf, msg);
    xms = XmStringCreate(buf, XmSTRING_DEFAULT_CHARSET);
  }
  XtVaSetValues(self->label, XmNlabelString, xms, NULL);
  XmStringFree(xms);
}

Boolean 
WidManageView::apply()
{
  Boolean m = XmToggleButtonGetState(toggle);
  model->setManage(m);
  return TRUE;
}

void 
WidManageView::update(unsigned long flags)
{
  if(flags & EXTRA_CHANGED) {
    XmToggleButtonSetState(toggle, model->toManage(), FALSE);
    valueChangedCallback(NULL, this, NULL);
  }
}

void 
WidManageView::setNewLwidget(Lwidget *model)
{
  this->model = model;
  changeModel(model);
  update(EXTRA_CHANGED);
}
