/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: WidClassMenu.h,v $
 *  $Date: 1999/08/27 15:32:19 $
 *  $Revision: 1.1.1.1.2.1 $
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
 * $Log: WidClassMenu.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:32:19  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:18  lazy
 * Imported to CVS
 *
 * Revision 1.2  1998/02/10  00:55:32  lazy
 * Added support for enable/disable menu items
 *
 * Revision 1.1  1997/09/13  16:43:42  lazy
 * Initial revision
 *
 */

#include <lac/View.h>
#include "Lcreator.h"
#include <lac/RefArray.h>

// Forward declaration
class WidCategoryMenu;
class WidClassButton;

//
// WidClassCallback - must be implemented by menu client
//

class WidClassCallback : public Lobject {
public:
  virtual void call(Lcreator &) = 0;
};

//
// WidClassPopupCallback - can be implemented (to call enableIfAsChildOk)
//

class WidClassPopupCallback : public Lobject {
public:
  virtual void call() = 0;
};

//
// The menu that contains all widget classes within category sub menus
//

class WidClassMenu : public WinView {
private:
  Widget pulldownMenu;
  WidClasses *model;
  Ref<WidClassCallback> callback;
  Ref<WidClassPopupCallback> popupCallback;

  // Contents of the menu
  RefArray<WidCategoryMenu> menus;

  // private callback function -> calls popupCallback
  static void mapCallback(Widget, XtPointer, XtPointer);

public:
  WidClassMenu(WidClasses *m, Widget parent, Widget cascadeButton);
  ~WidClassMenu();
  
  void call(Lcreator &l);
  void setCallback(WidClassCallback &wcc) { callback = &wcc; }
  void setCallback(WidClassPopupCallback &wcc) { popupCallback = &wcc; }

  Widget getWidget() { return pulldownMenu; }
  void act(char *) {}
  void update(unsigned long flags);

  void enableIfAsChildOk(Lcreator *wc);
};


//
// The sub menu for WidClassCategory
//

class WidCategoryMenu : public WinView {
private:
  Widget pulldownMenu;
  Widget cascadeButton;
  WidClassCategory *model;
  WidClassMenu *parent;

  RefArray<WidClassButton> buttons;

public:
  WidCategoryMenu(WidClassCategory *m, WidClassMenu *parent);
  ~WidCategoryMenu();

  void call(Lcreator &l) { parent->call(l); }
  Widget getWidget() { return pulldownMenu; }
  void act(char *) {}
  void update(unsigned long flags);

  void enableIfAsChildOk(Lcreator *wc);
};


//
// The Button that contains a widget class
//

class WidClassButton : public WinView {
private:
  Widget button;
  Lcreator *model;
  WidCategoryMenu *parent;

public:
  WidClassButton(Lcreator *m, WidCategoryMenu *parent);
  ~WidClassButton();

  void act(char *) { parent->call(*model); }
  void update(unsigned long flags);

  void enableIfAsChildOk(Lcreator *wc);
};
