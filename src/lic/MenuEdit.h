/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: MenuEdit.h,v $
 *  $Date: 1999/08/27 15:31:45 $
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
 * $Log: MenuEdit.h,v $
 * Revision 1.1.1.1.2.2  1999/08/27 15:31:45  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1.2.1  1998/07/01 18:31:45  lazy
 * Patches gcc 2.8
 *
 * Revision 1.1.1.1  1998/04/24 23:45:14  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/25  20:29:35  lazy
 * Initial revision
 *
 */

// ----------------------------
// MenuEdit.h
// Do not edit
// ----------------------------

#ifndef _MenuEdit_H_
#define _MenuEdit_H_

#include <lac/IconView.h>
#include <lac/CallbackMethod.h>

#include "MenuEdit_base.h"
#include "Lproject.h"
#include "Lwidget.h"
#include "ControllerImpl.h"

class MenuEdit : public MenuEdit_base {
private:

  // we want notifications from Selectable

  class SelectionCallback : public CallbackMethod {
  private:
    MenuEdit *parent;
  public:
    SelectionCallback(MenuEdit *m) { parent = m; }
    void call();
  } selectionCallback;
  
  friend class SelectionCallback;

  static RefArray<MenuEdit> allViews;

  Lwidget *model;
  Ref<WidgetIconView> iconView;

protected:
  virtual void moveUp(Widget,XtPointer);
  virtual void moveDown(Widget,XtPointer);
  virtual void addLabel(Widget,XtPointer);
  virtual void addPushbutton(Widget,XtPointer);
  virtual void addSeparator(Widget,XtPointer);
  virtual void addToggleButton(Widget,XtPointer);
  virtual void addSubMenu(Widget,XtPointer);
  virtual void do_load(Widget,XtPointer);
  virtual void do_loadParent(Widget,XtPointer);
  virtual void do_close(Widget,XtPointer);
  virtual void do_smallIcon(Widget,XtPointer);
  virtual void do_withIcon(Widget,XtPointer);
  virtual void do_withClassName(Widget,XtPointer);
  virtual void do_widgetMenuMap(Widget,XtPointer);
  virtual void do_onHelp(Widget,XtPointer);
  virtual void do_onContext(Widget,XtPointer);
  virtual void do_help(Widget,XtPointer);
  virtual void do_automaticLoad(Widget,XtPointer);

  static Ref<MenuEdit> automaticLoadView;
  ControllerImpl controllerImpl;

  void wmDelete() { do_close(NULL, NULL); }

  void setWidget(Lwidget *m);
  void update(unsigned long);

  MenuEdit(Lwidget *lw);

public:
  ~MenuEdit();

  static MenuEdit *showEditor(Lwidget *lwidget);

  static Boolean isOfValidClass(Lwidget*);

  Boolean saveSize() { return TRUE; }
  char *getName() { return "MenuEditor"; }
};

#endif /* Don't add stuff after this #endif */
