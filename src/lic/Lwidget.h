/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: Lwidget.h,v $
 *  $Date: 1999/08/27 15:31:34 $
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
 * $Log: Lwidget.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:31:34  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:13  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/25  20:29:04  lazy
 * Initial revision
 *
 */

/* --------------------------------------------------------------------
   (C) Dirk Laessig 1994
   
   Lwidget.h
   Class Lwidget
   Base Class: Iconable
   Derived Classes: -
   -------------------------------------------------------------------- */
#ifndef _LWIDGET_H_
#define _LWIDGET_H_

#include <X11/IntrinsicP.h>
#include <X11/CoreP.h>
#include <stdio.h>
#include <lac/IconView.h>
#include <lac/TreeNode.h>
#include <lac/TreeView.h>
#include <lac/HelpNode.h>
#include <parse.h>

#include "Lproject.h"
#include "Lproperty.h"
#include "Lcreator.h"
#include "LApp.h"

#define RESOURCE_CHANGED           (USER_CHANGED<<1)
#define RESOURCE_TODEFAULT_CHANGED (USER_CHANGED<<2)
#define EXTRA_CHANGED              (USER_CHANGED<<3)
#define CONSTRAINTS_CHANGED        (USER_CHANGED<<4)
#define GEOMETRY_CHANGED           (USER_CHANGED<<5)

// ---------------------------------------------
// Lwidget 
// is a GuiObject, which is represented 
// by a Widget
// ---------------------------------------------

class Linterface;
class Lwhere;
class InterfaceInfo;
class ResourceFileInfo;

class Lwidget : public TreeNode<Lwidget> {

private:
  Lcreator *aclass;                   // the class
  char *name;                         // the name of widget or linked interface
  Lproperty *properties;              // Resources, callbacks,...

  Boolean isLink;
  Ref<Linterface> linked;
  char *nameOfLinkedInterface;

  RefArray<LresRelation> nameReferences; // Relations refering to the name
                                         // of the Widget. If NAME_CHANGED 
                                         // Relations, refering to this Widget,
                                         // must change the value also
  
  Boolean manage;

  char *quickhelp;
  Ref<HelpNode> helpNode;
  char *description;

public:
  // ------ creation and saving --------
  Lwidget(Lcreator *aclass,                // Widget class
	  char *name,                      // Widget name
	  const Lwhere &wo );                    // position

  Lwidget(Lwidget *parent, char *linked, char *name);

  Lwidget( YWidget *yWidget, 
	  Lwidget *parent=NULL );           // Lwidget from structure LWidget

  YWidget *createYWidget();                // creates a YWidget-Tree by malloc
  Lwidget *copyTo( Lwidget *newParent );   // copy
  void moveTo( Lwidget *newParent );       // move to a new Parent

  ~Lwidget();                          // destroy all children

  // ------- informations ------------
  RefArray<Lwidget> & getChildren();
  Boolean existNamedWidget( char *name );  // recursive searching
  Linterface *getInterface();              // return the interface 
  Lcreator *getClass();                    // returns the class
  char *getName() { return name; }
  Boolean toManage() { return manage; }
  void setManage(Boolean s) { manage=s; }

  Lproperty *getProperties();

  Lwidget *find( Window id );          // recursive searching to Widget with id

  char *getClassName() { return "Lwidget"; }
  char *getPixmapFile() { return getClass()->getPixmapFile(); }

  void changed( unsigned long );

  Boolean isLinked() { return isLink; }
  char *getNameOfLinkedInterface() 
    { return isLink ? nameOfLinkedInterface : (char*)NULL; }

  HelpNode *getHelpNode() { return helpNode; }
  void setHelpNode(HelpNode *hn) { helpNode = hn; }
  char *getQuickhelp() { return quickhelp; }
  void setQuickhelp(char *qh);
  char *getDescription() { return description; }
  void setDescription(char *s);


  // --------- code generation ------------
  void fillInterfaceInfo( InterfaceInfo * );
  void fillResourceFileInfo( ResourceFileInfo *);

  // --------- name changing --------------
  Boolean isNameValid( char *name );
  Boolean setName( char *name );
  Boolean nameChangeable() { return TRUE; }

  // --------- name references --------------
  void nameReferenceAdd( LresRelation * );
  void nameReferenceRemove( LresRelation * );
  Lwidget *findNamedWidget( char * );

  // ---------- copy(), setParent(), asChildOk() ------------
  Lwidget* copy();
  void setParent(Lwidget *newParent);
  Boolean asChildOk(Lwidget* toCheck);

  // changes
  Boolean getChangedFlag();
  void resetChangedFlag();

  // ------------ clipboard public accessable
  static Container<Lwidget> clipboard;

};


// ------------------ WidgetController --------------------

#define LWIDGET_DELETE "Delete"
#define LWIDGET_EDIT   "Edit"
#define LWIDGET_BROWSE "Browse"
#define LWIDGET_MENUEDIT "MenuEdit"
#define LWIDGET_ATTACHMENTS "Attachments"
#define LWIDGET_TRANSFORM "Transform"
#define LWIDGET_REFRESH "Refresh"
#define LWIDGET_VISIBILITY "Visibility"
#define LWIDGET_ALIGNLEFT "AlignLeft"
#define LWIDGET_ALIGNTOP "AlignTop"
#define LWIDGET_ALIGNRIGHT "AlignRight"
#define LWIDGET_ALIGNBOTTOM "AlignBottom"
#define LWIDGET_ALIGNVCENTER "AlignVCenter"
#define LWIDGET_ALIGNHCENTER "AlignHCenter"
#define LWIDGET_ALIGNWIDTH "AlignWidth"
#define LWIDGET_ALIGNHEIGHT "AlignHeight"
#define LWIDGET_CUT "Cut"
#define LWIDGET_COPY "Copy"
#define LWIDGET_PASTE "Paste"
#define LWIDGET_RENAME "Rename"

class WidgetController : public Controller {
private:
  Lwidget *lwidget;
  void createMenuEntries();
public:
  WidgetController(Lwidget *am, View *v);
  void act(MenuEntry *me);
  void actOnce(MenuEntry *me);
  void defaultAction();
};


// ------------------- WidgetIconView ---------------------

class WidgetIconView : public IconView {
private:
  Boolean withClasses;

public:
  WidgetIconView(ContainerBase *cm, Widget p, Icon *icon=NULL )
    :IconView(cm,p,icon){ setWithClasses(TRUE);}

  Controller *getController(SensitiveRec *v) {
    return new WidgetController((Lwidget*)v->getModel(),v);
  }
  void setWithClasses(Boolean b);
  Boolean getWithClasses() { return withClasses; }
  XmString createXmString(Iconable *m);
};

// ------------------- WidgetTreeView ---------------------

class WidgetTreeView : public TreeView {
private:
  Boolean withClasses;

public:
  WidgetTreeView( TreeNodeBase *cm, Widget p, TreeNodeView *tnv = NULL)
    : TreeView(cm,p,tnv) { setWithClasses(TRUE);}

  Controller *getController(SensitiveRec *v) {
    return new WidgetController((Lwidget*)v->getModel(),v);
  }
  void setWithClasses(Boolean b);
  Boolean getWithClasses() { return withClasses; }
  XmString createXmString(Iconable *m);
};


// -------     WidgetView  ----------------

class WidgetView : public WinView {
private:
  static XContext uniqueContext;
  Display *display;

  static Boolean testMode;                // true-> normal event handling
  static Button1Mode button1Mode;
  static Boolean optimalRefresh;
  static RefArray<WidgetView> allViews;   // for finding the window id

  // Insert Position   -- HACK
  Boolean isPopup;
  static Widget updateParent;
  static int position;       
  static int insertPos(Widget newWidget);

  Lwidget *lwidget;                  // the model
  Widget  widget;                    // real widget
  Boolean linkOk;                    // if true interface exist
  Boolean original;                  // orginal Interface, no link

  WidgetView *parent;
  RefArray<WidgetView> children;     // children widgets
  static RefArray<Controller> controllers; // popup menu on right mouse button
  GC      gc;                        // gc for selection drawing
  
  // ---- for palette ------
  Boolean isPalette;                 // events are performed another way
  void setPalette( Boolean toSet );  // recursive setting of isPalette 

  void createWidget( Boolean populate = FALSE );               
                                     // create the widget, populate=TRUE ->
                                     // also children are created
  void widgetDestroyed();            // setting recursive widget=NULL
  void draw_selected();              // draw selection
  void refresh(Window win = 0);      // widget without a selection
  void testLink();                   // called in expose event
  WidgetView *updateFrom();           // find recursive

  // ----------- Die EventHandler ---------
  static void ButtonPressEvent(Widget wg, XtPointer this_class, 
			       XEvent *event, Boolean *b );
  static void ButtonReleaseEvent(Widget wg, XtPointer this_class,
				 XEvent *event, Boolean *b );
  static void Button2MotionEvent(Widget wg, XtPointer this_class,
				 XEvent *event, Boolean *b );
                
  static void TrashEvent(Widget wg, XtPointer this_class,   // other events
			 XEvent *event, Boolean *b );       // focusIn focusOut

  static void ExposeEvent(Widget wg, XtPointer this_class,  // inserted at 
			  XEvent *event, Boolean *b );      // beginning of 
                                                            // event list
  static void ConfigureEvent(Widget wg, XtPointer this_class,   
			     XEvent *event, Boolean *b );      


  // ------------ Drag & Drop Procedures --------------
  struct DropFinishInfo {
    Lwidget *droppedOn;   // if not NULL -> CONTAINER_CHANGED
    Lwidget *lwidget;     // if not NULL -> RESOURCE_CHANGED
    Lwidget *parent;      // if not NULL -> CONTAINER_CHANGED
  };
  struct DropInfo {         // als Client-Data in Transferproc
    WidgetView *widgetView;
    Position x;
    Position y;
    unsigned char operation;
    DropFinishInfo dfi;
  };
  struct DragInfo {      // als Klassenvariable beim draggen eines Widgetviews
    WidgetView *dragged;
    Position offsetX;    // Festhaltepunkt am Widgets
    Position offsetY;
    Rec lastDraw;
    WidgetView *lastDrawWidgetView;
  };

  Atom imports[1];
  Atom exports[2];
  static DragInfo draggedObject;    // Beim draggen eines WidgetViews,sonst 0

  void drawXorRec(Rec &rec);
  Rec getWindowRec();
  static Boolean isDropValid(Lwidget* &droppedOn, Lwidget *lwidget, 
			     unsigned char operation,Position &x, Position &y);
  void startDrag(XEvent *event, Position x, Position y);
  void registerDropSite(Widget wg);
  static Boolean convertProc(Widget w, Atom *selection, 
			     Atom *target, Atom *type,
			     XtPointer *value, unsigned long *length, 
			     int *format, unsigned long *max_length,
			     XtPointer clientData, XtRequestId *requId);
  static void dropFinish(Widget wg, XtPointer clientData, XtPointer callData );
  static void topLevelEnter(Widget wg,XtPointer clientData,XtPointer callData);
  static void topLevelLeave(Widget wg,XtPointer clientData,XtPointer callData);
  static void dropProc(Widget wg, XtPointer clientData, XtPointer callData );
  static void dragProc(Widget wg, XtPointer clientData, XtPointer callData );
  static void transferProc(Widget w, XtPointer closure, 
			   Atom *seltype, Atom *type,
			   XtPointer value, unsigned long *length, 
			   int *format);

  // Popdown-Callback for dialogs
  static void dialogPopdown(Widget wg, XtPointer clientData, XtPointer call);

  // Help callback
  static void helpCallback(Widget wg, XtPointer clientData, XtPointer call);

  // recursive function to setup event handler and drop site
  void prepareWidget(Widget wg);

public:
  WidgetView(Lwidget *model, WidgetView *parent = NULL );
  ~WidgetView();

  Widget getWidget() { return widget; }
  Lwidget *getLwidget() { return lwidget; }
  WidgetView *getParent() { return parent; }

  // set the ressources of widget
  void update( unsigned long flags );

  // this functions is called from Lic_MainWindow
  static void SetTestMode( Boolean b );  

  static void setButton1Mode( Button1Mode m ) { button1Mode = m; }
  static Button1Mode getButton1Mode() { return button1Mode; }

  static void setOptimalRefresh(Boolean v) { optimalRefresh=v; }

  static WidgetView *findWidget(Widget wg);
  static WidgetView *findWidget(Lwidget *lwidget);

  Widget findNamedWidget(char *name);  // recursive searching
  WidgetView *findTop();               // looking for shell or link
  void setRelation();                  // set Resourcetype Widget
  void manageDialogs();                // recursive dialog managing

  static XContext getContext();

  // dummy , we don't need it
  void act( char * ) {}

  char *getName() { return "WidgetView"; }
};


// ------------- WidgetBrowse -----------------

class WidgetBrowse : public LicView {
private:
  static RefArray<WidgetBrowse> allViews;

  Ref<TreeView> tv;
  Lwidget *lwidget;

  WidgetBrowse(Lwidget *am);

public:
  ~WidgetBrowse();

  static WidgetBrowse *showBrowser(Lwidget *lwidget);

  void update( unsigned long flags );
  void act(char*);
  virtual Boolean saveSize() { return TRUE; }
};


#endif /* DON'T ... */

