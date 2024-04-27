/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: LicView.h,v $
 *  $Date: 1999/08/27 15:29:40 $
 *  $Revision: 1.1.1.1.2.2 $
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
 * $Log: LicView.h,v $
 * Revision 1.1.1.1.2.2  1999/08/27 15:29:40  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1.2.1  1998/07/01 18:31:39  lazy
 * Patches gcc 2.8
 *
 * Revision 1.1.1.1  1998/04/24 23:45:45  lazy
 * Imported to CVS
 *
 * Revision 1.2  1997/07/25  19:49:45  lazy
 * *** empty log message ***
 *
 * Revision 1.1  1995/09/27  21:08:47  lazy
 * Initial revision
 *
 */

#ifndef _LICVIEW_H_
#define _LICVIEW_H_

#include <Xm/Xm.h>

#if XmVERSION < 2
#define XmSET 1
#define XmNEAR_SLIDER 1
#define XmNEAR_BORDER 1
#endif


#include <lac/View.h>
#include <lac/WidgetRef.h>
#include <lac/TArray.h>

class HelpNode;

// -------------------  LicView ----------------------

typedef struct _QuickHelpData{
  Widget widget;
  XmString xmString;
  struct _QuickHelpData *parent;
} QuickHelpData;

enum MsgResult {
  MSGBOX_CANCEL, MSGBOX_OK
  };

enum MsgBoxStyle {
  MSGBOX_STYLE_OK,
  MSGBOX_STYLE_OKCANCEL,	
  MSGBOX_STYLE_YESNO	
  };

class LicView : public WinView {
private:
  Model *m;
  Ref<Model> geoModel;

  Boolean _saveSize;
  Boolean _savePosition;
  char *name;

  static RefArray<LicView> allViews;
  static RefArray<LicView> allOpenViews;
  static Cursor waitCursor;
  static Boolean waitState;
  static Ref<LicView> mainView;

  struct MsgInfo {
    Boolean exit;
    int result;
    };
  static void msgOkCB( Widget, XtPointer, XtPointer );
  static void msgCancelCB( Widget, XtPointer, XtPointer );
  static void msgPopdownCB( Widget, XtPointer, XtPointer );

  static void setWaitCursorRec(Widget);

  static void helpCallback(Widget, XtPointer, XtPointer);

  void unmanageDialogs(Widget wg);

protected:
  class ShellWidgetRef : public WidgetRef {
  private:
    LicView &licView;
    static void wmDelete(Widget,XtPointer,XtPointer);
  public:
    ShellWidgetRef(LicView &l) : licView(l) {}
    ~ShellWidgetRef();
    ShellWidgetRef& operator=(Widget w);
  };

  ShellWidgetRef popupShell;
  static Widget firstTopLevel;     // the first created toplevel
  static XtAppContext context;  // the application context

  Display *display;
  Widget topLevel;

  WidgetRef quickHelpLabel;
  TArray<QuickHelpData> quickHelpData;
  QuickHelpData *currentQuickHelpData;
  static Boolean quickHelpEnabled;
  static void quickHelpEvent(Widget wg, XtPointer clientData, 
			     XEvent *event,Boolean *cont);
  QuickHelpData *findQuickHelpData(Widget wg, Boolean takeParent = FALSE);

public:
  LicView( Model *m = NULL );
  LicView( Widget top, Model *m = NULL );
  void setModel(Model *m);
  void setGeometryModel(Model *m);

  ~LicView();
  void open();             // open a View
  void close();            // close a View

  // init Xt-Intrinsic, open the display 
  // and create the toplevel widget
  static Widget init(char *applClass, 
		     int &argc, char **argv, char *fbRes=NULL);

  // running the application main loop
  static void run();
  
  // set in all views the wait cursor or not
  static void setWaitCursor(Boolean);

  // make a dialog and dispatching events
  static int MsgBox(char *title,               // the string in title bar
		    char *msg,                 // the real message
		    unsigned char dialogStyle, 
		    unsigned char dialogType,
		    MsgBoxStyle msgBoxStyle);

  static int MsgBox(char *title,               // the string in title bar
		    char *msg,                 // the real message
		    MsgBoxStyle msgBoxStyle = MSGBOX_STYLE_OKCANCEL);

  static int FileBox(char *title,              // string in title bar
		     char *fileRet,            // buffer with enought space
		     unsigned char dialogStyle );

  static int FileBox(char *title,              // string in title bar
		     char *fileRet );          // buffer with enought space

  static Widget getTopLevel() { return firstTopLevel; }

  void update(unsigned long) {}
  void act(char*){}

  // persistence of size and position
  virtual Boolean saveSize() { return _saveSize; }
  virtual Boolean savePosition() { return _savePosition; }
  virtual const char *getName() { return name ? name : "LicView"; }
  Widget getPopupShell() { return popupShell; }

  // the help system
  void addHelpId(Widget w, int id); // add callbacks for help display
  void contextHelp();             // XmTracking and show help
  static HelpNode *findHelpNode(int id);     // search in the help tree

  // show the help window with specific help text
  static void getHelp(Cardinal id);

  // close all open views
  static void closeAllOpenViews();

  // Window manager delete
  virtual void wmDelete();

  // events, called by open() and close()
  virtual void opened() {}
  virtual void beforeClose() {}

  // QuickHelp Label
  void addQuickHelp(Widget w);    // add the callbacks and event handlers
  void setQuickHelp(Widget wg, char *text);   // set the quick help explicily
  void showQuickHelpLabel(Boolean state);
  void setQuickHelpLabel(Widget wg) { quickHelpLabel = wg; }
  static void enableQuickHelp(Boolean state);
  static Boolean getEnableQuickHelp() { return quickHelpEnabled; }
};


#endif
