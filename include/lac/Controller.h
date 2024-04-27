/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: Controller.h,v $
 *  $Date: 1999/08/27 15:29:23 $
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
 * $Log: Controller.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:29:23  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:46  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/25  19:31:25  lazy
 * Initial revision
 *
 */

#ifndef _Controller_h_
#define _Controller_h_

#include <lac/Model.h>
#include <lac/View.h>
#include <lac/Lobject.h>
#include <lac/RefArray.h>
#include <lac/WidgetRef.h>
#include <lac/Lstring.h>

#include <X11/Intrinsic.h>

#define MAX_KEYSTRING 64

class Controller;

enum MenuType {
  ME_PUSHBUTTON, 
  ME_SEPARATOR, 
  ME_TOGGLEBUTTON,
  ME_SUBMENU,
  ME_RADIO_SUBMENU
};

class MenuEntry : public Lobject {
private:
  Widget widget;
  WidgetRef widgetRef;              // for takeMenu to remember the callback
  Widget menu;

  Controller *parent;

  MenuType menuType;
  char *action;
  Boolean once;
  Ref<MenuEntry> subMenu;

  Boolean visible;
  Boolean toggleButtonValue;
  Boolean sensitive;

  int buttonState;                   // modifier
  char keyString[MAX_KEYSTRING];     // F1, Delete ...

  static void menuEntryCB(Widget, XtPointer, XtPointer);

public:
  MenuEntry(Controller *controller,       // controller
	    MenuType menuType,            // PushButton, ToggleButton, ...
	    char *action,                 // action called in controller
	    Boolean once,                 // called action once or for every
	    MenuEntry *subMenu = NULL);   // is entry in submenu
  ~MenuEntry();

  int match(MenuEntry *);
  int match(char *);
  
  Boolean getVisible() { return visible; }
  void setVisible(Boolean v);
  Boolean getSensitive() { return sensitive; }
  void setSensitive(Boolean v);
  void setToggleButtonValue(Boolean v);
  Boolean getToggleButtonValue();

  void setKeyBinding(int bs, char *ks);
  Boolean processKey(int bs, char *ks);

  Widget getWidget() { return widget; }
  char *getAction() { return action; }

  virtual void createWidget();
  void assignWidget(Widget widget);          // for takeMenu()
};


class MenuEntryWidget: public Lobject {
public:
  Widget widget;
  Lstring action;

  MenuEntryWidget(Widget w, char *a) 
  { widget = w; action = a; }
};

// --------- Controller ------------

class Controller : public Lobject {
protected:
  WidgetRef menu;               // PopupMenu, default NULL, destroyed in ~Con..
  Widget label, separator;      // label and separator
  Ref<Iconable> model;          // the model
  Ref<View> view;
  RefArray<Controller> selection;

  RefArray<MenuEntry> entries;     // entries which should be filtered
  virtual void createMenuEntries();  // should be overloaded

  void maskMenuEntries(RefArray<MenuEntry> &toMask);

public:
  Controller(Iconable *m, View *v);
  ~Controller();

  // called by a view object
  // this function calls createMenuEntry for every object in selection
  // after that it filters the first with all others and unmanage all
  void popupMenu(Widget parent,                    // parent for the menu
		 Position x,                       // Position
		 Position y,
		 RefArray<Controller> selection);  // all controllers including
                                                   // this instance

  // call in a key board event
  // bs == KeyEvent.state
  // ks == XKeysymToString(keysym)
  // return TRUE if processed
  Boolean processKey(int bs, char *ks, RefArray<Controller> selection);

  // takeMenu
  void takeMenu(RefArray<MenuEntryWidget> entryWidgets, 
		RefArray<Controller> selection);

  virtual void actOnce(MenuEntry *me);
  virtual void act(MenuEntry *me);
  virtual void defaultAction() {}

  RefArray<Controller> &getSelection() { return selection; }
  Widget getMenuWidget() { return menu; }
  Iconable *getModel() { return model; }
#if(0)
  // Drag & Drop
  static RefArray<Controller> draggedObjects;

  // call for the receiver, calls dragOver() for everyDraggedObject
  virtual void dragOn(unsigned char &ops); 

  // call for the source, return TRUE if the source known what to do
  virtual Boolean dragOver(Controller *receiver, unsigned char &ops);

  // the drop operation
  virtual Boolean drop(unsigned char op);
#endif
};


#endif
