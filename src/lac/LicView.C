/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: LicView.C,v $
 *  $Date: 1999/08/27 15:29:39 $
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
 * $Log: LicView.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:29:39  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:45  lazy
 * Imported to CVS
 *
 * Revision 1.4  1997/07/25  20:06:55  lazy
 * Remove String2XmString.h inclusion.
 *
 * Revision 1.3  1997/07/25  19:49:39  lazy
 * *** empty log message ***
 *
 * Revision 1.2  1996/06/07  09:21:32  lazy
 * *** empty log message ***
 *
 * Revision 1.1  1995/09/27  21:08:35  lazy
 * Initial revision
 *
 */

/* ------------------------------------------------------------
   Implemetation of class LicView
   ------------------------------------------------------------ */

#include <Xm/BulletinB.h>
#include <Xm/MessageB.h>
#include <Xm/DialogS.h>
#include <Xm/FileSB.h>
#include <lac/LicView.h>
#include <lac/Model.h>
#include <Xm/Protocols.h>
#include <X11/cursorfont.h>
#include <Xm/DialogS.h>
#include <X11/IntrinsicP.h>
#include <X11/CoreP.h>
#include "MLXHelp.h"

#ifdef CDE_WIDGETS
#include <Dt/Dt.h>
#endif

/* ##########################################################
                        LicView
   ########################################################## */

XtAppContext LicView::context;
Widget LicView::firstTopLevel;
RefArray<LicView> LicView::allOpenViews;
RefArray<LicView> LicView::allViews;
Cursor LicView::waitCursor;
Boolean LicView::waitState;
Ref<LicView> LicView::mainView;
Boolean LicView::quickHelpEnabled = TRUE;
static Ref<MLXHelp> mlxHelp;


// -------------------------------
// LicView:    LicView()
// -------------------------------

LicView::LicView( Model *m )
: WinView( m ), popupShell(*this) 
{
  currentQuickHelpData = NULL;
  topLevel = firstTopLevel;
  display = XtDisplay(firstTopLevel);
  _saveSize = FALSE;
  _savePosition = FALSE;
  name = NULL;
  this->m = m;

  if( mainView.isNil() ) {
    mainView = this;
    quickHelpLabel = NULL;
  } else {
    quickHelpLabel = mainView->quickHelpLabel;
  }
  allViews.add(this);
}

LicView::LicView( Widget top, Model *m )
: WinView( m ), popupShell(*this) 
{
  currentQuickHelpData = NULL;
  topLevel = top;
  display = XtDisplay(top);
  _saveSize = FALSE;
  _savePosition = FALSE;
  name = NULL;
  this->m = m;

  if( mainView.isNil() ) {
    mainView = this;
    quickHelpLabel = NULL;
  } else {
    quickHelpLabel = mainView->quickHelpLabel;
  }
  allViews.add(this);
}

// -------------------------------
// LicView:    setModel()
// -------------------------------

void 
LicView::setModel(Model *m)
{
  this->m = m;
  if(geoModel.isNil())
    geoModel = m;

  changeModel(m);
}

// -------------------------------
// LicView:    setGeometryModel()
// -------------------------------

void 
LicView::setGeometryModel(Model *m)
{
  geoModel = m;
}

// -------------------------------
// LicView:    ~LicView()
// -------------------------------

LicView::~LicView()
{
  for( unsigned int i=0; i<quickHelpData.getSize(); i++ ) {
    if(quickHelpData[i]->xmString)
      XmStringFree(quickHelpData[i]->xmString);
    delete quickHelpData[i];
  }

  if( Widget(popupShell) != NULL ) {
    Widget w = popupShell;
    close();
    popupShell = NULL;
    XtDestroyWidget(w);
  }
  if(name)
    delete name;
}

// -------------------------------
// LicView:    open()
// -------------------------------

void 
LicView::open()
{
  if( !name ) {
    const char *n = getName();
    if( n ) {
      name = new char[strlen(n)+1];
      strcpy(name,n);
    }
  }
  _saveSize = saveSize();
  _savePosition = savePosition();
  if( popupShell ) {
    if(!XtWindow((Widget)popupShell)) {
      if( !geoModel.isNil() && saveSize() ) {
	Dimension width=0, height=0;
	long t;
	if(geoModel->getVDLong(this,"width", t)) {
	  width = (Dimension)t;
	  XtVaSetValues(popupShell,
			XmNwidth, width,
			NULL);
	}
	if(geoModel->getVDLong(this,"height", t)) {
	  height = (Dimension)t;
	  XtVaSetValues(popupShell,
			XmNheight, height,
			NULL);
	}
      }
      if( !geoModel.isNil() && savePosition() ) {
	Position x=0, y=0;
	long t;
	if(geoModel->getVDLong(this,"x", t)) {
	  x = (Position)t;
	  XtVaSetValues(popupShell,
			XmNx, x,
			XmNwinGravity, CenterGravity,
			NULL);
	}
	if(geoModel->getVDLong(this,"y", t)) {
	  y = (Position)t;
	  XtVaSetValues(popupShell,
			XmNy, y,
			XmNwinGravity, CenterGravity,
			NULL);
	}
      }
      
    }
    if(XtWindow((Widget)popupShell)) {
      Widget wg = popupShell;
      XWindowAttributes attr;

      XGetWindowAttributes(XtDisplay(wg), XtWindow(wg), &attr);
      if(attr.map_state == IsUnmapped)
	XtPopdown(popupShell);
    }
    XtPopup(popupShell, XtGrabNone);
    allOpenViews.add(this);

    showQuickHelpLabel(quickHelpEnabled);
    setWaitCursorRec(popupShell);

  }
  opened();
}

// -------------------------------
// LicView:      close()
// -------------------------------

void 
LicView::close()
{
  beforeClose();
  if( popupShell ) {
    allOpenViews.remove(this);

    if(!geoModel.isNil() && saveSize() ) {
      Dimension width, height;
      XtVaGetValues(popupShell,
		    XmNwidth, &width,
		    XmNheight, &height,
		    NULL);
      geoModel->setVDLong(this,"width", (long)width);
      geoModel->setVDLong(this,"height", (long)height);
    }
    if(!geoModel.isNil() && savePosition() ) {
      Position x,y;
      XtVaGetValues(popupShell,
		    XmNx, &x,
		    XmNy, &y,
		    NULL);
      geoModel->setVDLong(this,"x", (long)x);
      geoModel->setVDLong(this,"y", (long)y);
    }
    unmanageDialogs(popupShell);
    XtPopdown( popupShell );
  }
}


// --------------------------------
// LicView:   closeAllOpenViews()
// --------------------------------

void 
LicView::closeAllOpenViews()
{
  RefArray<LicView> views(allOpenViews);

  for(unsigned int i=0; i<views.getSize(); i++)
    views[i]->close();
}

// --------------------------------
// LicView:   unmanageDialogs()
// --------------------------------

void LicView::unmanageDialogs(Widget wg)
{
  unsigned int i;
  
  // unmanage the dialog
  if(XtParent(wg) && XmIsDialogShell(XtParent(wg))) {
    XtUnmanageChild(wg);    
  }
  
  // check all the children
  if(XtIsComposite(wg)) {
    WidgetList children;
    Cardinal numChildren;
    XtVaGetValues(wg,
		  XmNchildren, &children,
		  XmNnumChildren, &numChildren,
		  NULL);
    for(i=0; i<numChildren; i++)
      if(XtIsWidget(children[i]))
	unmanageDialogs(children[i]);
    
  }
  for(i=0; i<wg->core.num_popups; i++)  // check all the popups
    if(XtIsWidget(wg->core.popup_list[i]))
      unmanageDialogs(wg->core.popup_list[i]);
  
}


// --------------------------------
// LicView:   init() - class method
// --------------------------------

Widget LicView::init( char *applClass, int &argc, char **argv, char *fbRes )
{
  Display *display;
  Widget topLevel;

  if( context == NULL ) {
    // initialize X-Toolkit
    XtToolkitInitialize();
    
    context = XtCreateApplicationContext();
    
  }

  display = XtOpenDisplay(context, 
			  NULL, NULL,
			  applClass, 
			  NULL, 0,
			  &argc, argv);
  if(display == NULL) {
    fprintf(stderr, "Error: Can't open display.\n");
    exit(1);
  }
  if(fbRes) {
    XrmDatabase database, fallback;
    
    fallback = XrmGetStringDatabase(fbRes);
    database = XrmGetDatabase(display);
    
    XrmCombineDatabase(fallback, &database, FALSE);
  }
  
  topLevel = XtAppCreateShell(NULL, applClass, 
			      applicationShellWidgetClass,
			      display, NULL, 0);

#ifdef CDE_WIDGETS
  if(!DtAppInitialize(context, display, topLevel, argv[0], applClass)) {
    fprintf(stderr, "DtAppInitialize() returns FALSE\n");
  }
#endif

  if(firstTopLevel == NULL) {
    firstTopLevel = topLevel;
//    XmRegisterNewXmStringConverter(XtCacheNone | XtCacheRefCount);
  }

  if(waitCursor == 0)
    waitCursor = XCreateFontCursor(display, XC_watch);

  return topLevel;
}


// -------------------------------
// LicView:   run() - class method
// -------------------------------

void LicView::run()
{
  XtAppMainLoop(context);
}


// -------------------------------
// LicView:   setWaitCursor()
// -------------------------------

void LicView::setWaitCursor(Boolean w)
{
  waitState = w;
  for(unsigned int i=0; i<allOpenViews.getSize(); i++) {
    setWaitCursorRec(allOpenViews[i]->popupShell);
    XFlush(XtDisplay(Widget(allOpenViews[i]->popupShell)));
  }
}

// -------------------------------
// LicView:   setWaitCursorRec()
// -------------------------------

void LicView::setWaitCursorRec(Widget wg)
{
  Window window;
  unsigned int i;

  if(XtIsComposite(wg)) {
    if(XtIsShell(wg)) {
      window = XtWindow(wg);
      if(window) {
	if(waitState)
	  XDefineCursor(XtDisplay(wg), window, waitCursor);
	else
	  XUndefineCursor(XtDisplay(wg), window);
      }
    }
    WidgetList children;
    Cardinal numChildren;
    XtVaGetValues(wg,
		  XmNchildren, &children,
		  XmNnumChildren, &numChildren,
		  NULL);
    for(i=0; i<numChildren; i++)
      if(XtIsWidget(children[i]))
	setWaitCursorRec(children[i]);
    
  }
  for(i=0; i<wg->core.num_popups; i++)
    if(XtIsWidget(wg->core.popup_list[i]))
      setWaitCursorRec(wg->core.popup_list[i]);
}

// -----------------------------------
// MessageBoxes
// -----------------------------------
struct MsgBoxResourceData {
  XmString yesLabel;
  XmString noLabel;
};

static XtResource msgBoxResources [] = {
  {
    "yesLabelString", "YesLabelString", XmRXmString, sizeof(XmString),
    XtOffsetOf(MsgBoxResourceData, yesLabel), XtRString, (XtPointer)"Yes"
  },
  {
    "noLabelString", "noLabelString", XmRXmString, sizeof(XmString),
    XtOffsetOf(MsgBoxResourceData, noLabel), XtRString, (XtPointer)"No"
  }
};


// -----------------------------------
// LicView:  MsgBox()
// -----------------------------------
int LicView::MsgBox(char *title, char *msg, MsgBoxStyle msgBoxStyle )

{
  unsigned char type;

  switch(msgBoxStyle) {
  case MSGBOX_STYLE_OK:
    type = XmDIALOG_INFORMATION;
    break;
  case MSGBOX_STYLE_OKCANCEL:
  case MSGBOX_STYLE_YESNO:
  default:
    type = XmDIALOG_QUESTION;
    break;
  }

  return MsgBox(title,msg,XmDIALOG_MODELESS, type, msgBoxStyle);
}


int LicView::MsgBox(char *title, char *msg, 
		    unsigned char style, unsigned char type, 
		    MsgBoxStyle msgBoxStyle)
{
  XmString t, m;
  XEvent event;
  Widget msgBoxShell, msgBox;
  MsgInfo info;
  Dimension width, height;
  
  t = XmStringCreateLtoR(title, XmSTRING_DEFAULT_CHARSET );
  m = XmStringCreateLtoR(msg, XmSTRING_DEFAULT_CHARSET );
  msgBoxShell = XtVaCreatePopupShell("MessageBoxShell", 
				     topLevelShellWidgetClass,
				     firstTopLevel,
				     XmNdeleteResponse, XmUNMAP,
				     NULL );
  msgBox = XtVaCreateWidget("MessageBox", xmMessageBoxWidgetClass,
			    msgBoxShell,
			    NULL );
  XtAddCallback( msgBox, XmNokCallback, msgOkCB, &info );
  XtAddCallback( msgBox, XmNcancelCallback, msgCancelCB, &info );
  XtAddCallback( msgBoxShell, XmNpopdownCallback, msgPopdownCB, &info );

  XtUnmanageChild(XmMessageBoxGetChild(msgBox, XmDIALOG_HELP_BUTTON));
  if(msgBoxStyle == MSGBOX_STYLE_OK) {
    XtUnmanageChild(XmMessageBoxGetChild(msgBox, XmDIALOG_CANCEL_BUTTON));
  }

  if(msgBoxStyle == MSGBOX_STYLE_YESNO) {
    MsgBoxResourceData data;

    XtGetSubresources(msgBox, &data, NULL, NULL, 
		      msgBoxResources, XtNumber(msgBoxResources),
		      NULL, 0);
    XtVaSetValues(msgBox, 
		  XmNokLabelString, data.yesLabel,
		  XmNcancelLabelString, data.noLabel,
		  NULL);
  }

  XtVaSetValues(msgBox,
		XmNdialogTitle, t,
		XmNmessageString, m,
		XmNdialogStyle, style,
		XmNdialogType, type,
		NULL );
  XtManageChild(msgBox);
  
  XtSetMappedWhenManaged(msgBoxShell, FALSE);
  XtPopup(msgBoxShell, XtGrabNone);

  // query width and height of message box
  XtVaGetValues(msgBox, 
		XmNwidth, &width,
		XmNheight, &height,
		NULL);

  XtUnrealizeWidget(msgBoxShell);

  // put message box in the middle of the screen
  XtVaSetValues(msgBoxShell,
		XmNx, WidthOfScreen(XtScreen(msgBox))/2-width/2,
		XmNy, HeightOfScreen(XtScreen(msgBox))/2-height/2,
		NULL);
  XtSetMappedWhenManaged(msgBoxShell, TRUE);
  XtRealizeWidget(msgBoxShell);

  XtPopup(msgBoxShell, XtGrabNone);
  XtMapWidget(msgBoxShell);

  
  info.result = 0;
  info.exit = False;
  while( !info.exit ) {       // Displatching all events
    XtAppNextEvent(context,&event);
    XtDispatchEvent(&event);
  }

  Display *display = XtDisplay(msgBoxShell);
  XtDestroyWidget( msgBoxShell );
  XFlush(display);

  return info.result;
}

// -----------------------------------
// LicView:  FileBox()
// -----------------------------------
int LicView::FileBox(char *title, char *fileRet ) 
{
  return FileBox(title,fileRet,XmDIALOG_MODELESS);
}

int LicView::FileBox( char *title, char *fileRet, unsigned char style )
{
  XmString t;
  XEvent event;
  Widget fileBoxShell, fileBox;
  MsgInfo info;
  Arg arg[10];
  int argc;
  char *str;
  XmString xmstr;

  t = XmStringCreateLtoR( title, XmSTRING_DEFAULT_CHARSET );

  fileBoxShell = XtVaCreatePopupShell( "FileBoxShell", 
				      xmDialogShellWidgetClass,
				      firstTopLevel,
				      XmNdeleteResponse, XmUNMAP,
				      NULL );

  argc = 0;
  XtSetArg( arg[argc], XmNdialogType, XmDIALOG_FILE_SELECTION ); argc++;
  fileBox =  XmCreateFileSelectionBox( fileBoxShell, "FileBox", arg, argc );

  XtAddCallback( fileBox, XmNokCallback, msgOkCB, &info );
  XtAddCallback( fileBox, XmNcancelCallback, msgCancelCB, &info );
  XtAddCallback( fileBoxShell, XmNpopdownCallback, msgPopdownCB, &info );

  XtVaSetValues( fileBox,
		XmNdialogTitle, t,
		XmNdialogStyle, style,
		NULL );

  if(fileRet[0]) {
    xmstr = XmStringCreateLtoR(fileRet, XmSTRING_DEFAULT_CHARSET );
    XtVaSetValues(fileBox, XmNtextString, xmstr, NULL);
    XmStringFree(xmstr);
  }

  XtManageChild( fileBox );
  XtPopup( fileBoxShell, XtGrabNone );

  info.result = 0;
  info.exit = False;
  while( !info.exit ) {       // Displatching all events
    XtAppNextEvent(context,&event);
    XtDispatchEvent(&event);
  }
  
  XtVaGetValues( fileBox, 
		XmNtextString, &xmstr,
		NULL );
  XmStringGetLtoR( xmstr, XmSTRING_DEFAULT_CHARSET, &str );
  strcpy( fileRet, str );

  Display *display = XtDisplay(fileBoxShell);
  XtDestroyWidget( fileBoxShell );
  XFlush(display);


  return info.result;
}

// -------------------------------------
// LicView:        msgOkCB()
// -------------------------------------
void LicView::msgOkCB( Widget, XtPointer client, XtPointer )
{
  ((MsgInfo*)client)->result = MSGBOX_OK;
  ((MsgInfo*)client)->exit = True;
}

// -------------------------------------
// LicView:        msgCancelCB()
// -------------------------------------
void LicView::msgCancelCB( Widget, XtPointer client, XtPointer )
{
  ((MsgInfo*)client)->result = MSGBOX_CANCEL;
  ((MsgInfo*)client)->exit = True;
}

// -------------------------------------
// LicView:        msgPopdownCB()
// -------------------------------------
void LicView::msgPopdownCB( Widget, XtPointer client, XtPointer )
{
  ((MsgInfo*)client)->result = MSGBOX_CANCEL;
  ((MsgInfo*)client)->exit = True;
}

// -------------------------------------
// LicView:        wmDelete()
// -------------------------------------
void LicView::wmDelete()
{
  close();
  XtDestroyWidget(popupShell);
  delete this;
}

// -------------------------------------
// LicView:        findQuickHelpData()
// -------------------------------------

static XtResource quickHelpResources [] = {
  {
    "quickHelpLabel", "QuickHelpLabel", XmRXmString, sizeof(XmString),
    XtOffsetOf(QuickHelpData, xmString), XtRImmediate, (XtPointer)NULL
  }
};


QuickHelpData *LicView::findQuickHelpData(Widget wg, Boolean takeParent)
{
  QuickHelpData *data = NULL;

  for(unsigned int i=0; i<quickHelpData.getSize(); i++ ) {
    if(quickHelpData[i]->widget == wg) {
      data = quickHelpData[i];
      break;
    }
  }
  
  if(!data) {
    data = new QuickHelpData;
    memset(data, 0, sizeof(QuickHelpData));
    data->widget = wg;
    XtGetSubresources(wg, data, NULL, NULL, 
		      quickHelpResources, XtNumber(quickHelpResources),
		      NULL, 0);
    quickHelpData.add(data);
  }

  if(takeParent && data->xmString == NULL && XtParent(wg)) {
    data = findQuickHelpData(XtParent(wg));
  }
  return data;
}

// -------------------------------------
// LicView:        quickHelpEvent()
// -------------------------------------

void LicView::quickHelpEvent(Widget wg,XtPointer clientData,
			     XEvent *event,Boolean *)
{
  QuickHelpData *data;
  static XmString emptyString = NULL;  
  LicView *self = (LicView*)clientData;
  XCrossingEvent *xce = (XCrossingEvent*)event;

  if(!emptyString) {
    emptyString = XmStringCreateLtoR(" ", XmSTRING_DEFAULT_CHARSET);
  }

  if(!self->quickHelpLabel)
    return;

  if(event->type == EnterNotify) {          // looking for a new string
    data = self->findQuickHelpData(wg);
    data->parent = self->currentQuickHelpData;
    self->currentQuickHelpData = data;
    if(self->currentQuickHelpData->xmString)
      XtVaSetValues(self->quickHelpLabel, XmNlabelString,
		    self->currentQuickHelpData->xmString, NULL);
    else
      XtVaSetValues(self->quickHelpLabel, XmNlabelString,
		    emptyString, NULL);
  }

  // show the old string
  if(event->type == LeaveNotify 
     && xce->detail != NotifyInferior   
     && xce->detail != NotifyNonlinearVirtual
     && xce->detail != NotifyNonlinear) {
    XtVaSetValues(self->quickHelpLabel, 
		  XmNlabelString, emptyString, 
		  NULL);
  }
}

// ------------------------
//  addQuickHelp()
// ------------------------
void LicView::addQuickHelp(Widget wg)
{
  XtAddEventHandler(wg, 
		    EnterWindowMask | LeaveWindowMask,
		    False, quickHelpEvent, this );
}

// ------------------------
//  setQuickHelp()
// ------------------------
void LicView::setQuickHelp(Widget wg, char *text)
{
  QuickHelpData *data;
  data = findQuickHelpData(wg, FALSE);    // don't take the parent
  
  if(data->xmString)
    XmStringFree(data->xmString);
  data->xmString = XmStringCreateLtoR(text, XmSTRING_DEFAULT_CHARSET);
  if(data == currentQuickHelpData) {
    XtVaSetValues(quickHelpLabel, XmNlabelString, data->xmString, NULL);
  }
}

// ------------------------
//  getHelp()
// ------------------------
void LicView::getHelp(Cardinal id)
{
  setWaitCursor(TRUE);
  if(mlxHelp.isNil()) {
    mlxHelp = new MLXHelp();
  }
  mlxHelp->open();
  mlxHelp->find(id);
  setWaitCursor(FALSE);
}


// ------------------------
//  addHelpId()
// ------------------------
void LicView::addHelpId(Widget w, int id)
{
  if(id >= 0) {
    XtAddCallback(w, XmNhelpCallback, helpCallback, (XtPointer)id);
  }
}

// ------------------------
//  helpCallback()
// ------------------------
void LicView::helpCallback(Widget, XtPointer clientData, XtPointer)
{
  int id = (int)clientData;
  if(id >= 0)
    getHelp(id);
}

// ------------------------
//  findHelpNode()
// ------------------------
HelpNode *LicView::findHelpNode(int id)
{
  HelpNode *hn, *root;
  
  if(mlxHelp.isNil()) {
    mlxHelp = new MLXHelp();
  }
  
  root = mlxHelp->getHelpNode();
  hn = root->find(id);

  return hn;
}

// ------------------------
//  contextHelp()
// ------------------------
void LicView::contextHelp()
{
  static Cursor cursor = 0;
  if(cursor == 0) {
    cursor = XCreateFontCursor(display, XC_question_arrow);
  }

  Widget wg = XmTrackingLocate(popupShell, cursor, FALSE);
  Widget found = NULL;

  if(wg) {
    for(found = wg; found; found = XtParent(found)) {
      if(XtHasCallbacks(found, XmNhelpCallback)) {
	XtCallbackList cbl = NULL;
	XtVaGetValues(found, XmNhelpCallback, &cbl, NULL);
	if(cbl && cbl[0].callback)
	  break;
      }
    }
  }
  if(found) {
    XmAnyCallbackStruct cbs;
    cbs.reason = XmCR_HELP;
    cbs.event = NULL;
    XtCallCallbacks(found, XmNhelpCallback, &cbs);
  } else {
    XBell(display, 500);
  }
}

// ------------------------
//  showQuickHelpLabel()
// ------------------------
void LicView::showQuickHelpLabel(Boolean state)
{
  if(quickHelpLabel) {
    if(state) {
      XtVaSetValues(quickHelpLabel,
		    XmNrecomputeSize, TRUE,
		    XmNheight, 0,
		    NULL);
      XtMapWidget(Widget(quickHelpLabel));
      XtUnmanageChild(Widget(quickHelpLabel));
      XtManageChild(Widget(quickHelpLabel));
    } else {
      XtVaSetValues(quickHelpLabel,
		    XmNrecomputeSize, FALSE,
		    XmNheight, 1,
		    NULL);
      XtUnmanageChild(Widget(quickHelpLabel));
      XtManageChild(Widget(quickHelpLabel));
      XtUnmapWidget(Widget(quickHelpLabel));
    }
  }
}

// ------------------------
//  enableQuickHelp()
// ------------------------
void LicView::enableQuickHelp(Boolean state)
{
  quickHelpEnabled = state;
  for(unsigned int i=0; i<allViews.getSize(); i++) {
    allViews[i]->showQuickHelpLabel(quickHelpEnabled);
  }
}


/* ####################################################
                   ShellWidgetRef
   #################################################### */

// -------------------------
//      wmDelete()
// -------------------------

void LicView::ShellWidgetRef::wmDelete(Widget,XtPointer self,XtPointer)
{
  ((ShellWidgetRef*)self)->licView.wmDelete();
}

// -------------------------
//      ~ShellWidgetRef
// -------------------------

LicView::ShellWidgetRef::~ShellWidgetRef()
{
  XtPointer self = (XtPointer)this;

  if(wg) {
    Atom atom = XmInternAtom(XtDisplay(wg),"WM_DELETE_WINDOW",TRUE);
    if(!atom)
      printf("can't find WM_DELETE_WINDOW\n");
    XmRemoveWMProtocolCallback(wg,atom,wmDelete,self);
  }
}


// -------------------------
//       operator=()
// -------------------------

LicView::ShellWidgetRef& LicView::ShellWidgetRef::operator=(Widget w)
{
  XtPointer self = (XtPointer)this;

  if(wg) {
    Atom atom = XmInternAtom(XtDisplay(wg),"WM_DELETE_WINDOW",TRUE);
    if(!atom)
      printf("can't find WM_DELETE_WINDOW\n");
    XmRemoveWMProtocolCallback(wg,atom,wmDelete,self);
  }

  WidgetRef::operator=(w);

  if(wg) {
    XtVaSetValues(wg,XmNdeleteResponse,XmDO_NOTHING,NULL);
    Atom atom = XmInternAtom(XtDisplay(wg),"WM_DELETE_WINDOW",TRUE);
    if(!atom)
      printf("can't find WM_DELETE_WINDOW\n");
    XmAddWMProtocolCallback(wg,atom,wmDelete,self);
  }    

  return *this;
}
