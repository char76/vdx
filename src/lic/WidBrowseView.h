/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: WidBrowseView.h,v $
 *  $Date: 1999/08/27 15:32:14 $
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
 * $Log: WidBrowseView.h,v $
 * Revision 1.1.1.1.2.2  1999/08/27 15:32:14  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1.2.1  1998/07/01 18:31:45  lazy
 * Patches gcc 2.8
 *
 * Revision 1.1.1.1  1998/04/24 23:45:16  lazy
 * Imported to CVS
 *
 * Revision 1.2  1998/02/10  00:56:32  lazy
 * Added support for enable/disable
 * menu items in create menu.
 *
 * Revision 1.1  1997/07/25  20:36:06  lazy
 * Initial revision
 *
 */

// ----------------------------
// WidBrowseView.h
// ----------------------------

#ifndef _WidBrowseView_H_
#define _WidBrowseView_H_

#include "WidBrowseView_base.h"
#include "ControllerImpl.h"
#include "WidClassMenu.h"

class WidgetTreeView;
class Lwidget;

class WidBrowseView : public WidBrowseView_base {
protected:
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

  void wmDelete() { do_close(NULL, NULL); }

  Lwidget *model;

  Ref<WidgetTreeView> treeView;
  ControllerImpl controllerImpl;

  static RefArray<WidBrowseView> allViews;
  static Ref<WidBrowseView> automaticLoadView;

  // private constuctor, call showView() instead
  WidBrowseView(Lwidget *lwidget);

  // update (title bar)
  void update(unsigned long flags);

  // display the widget within browser
  void setWidget(Lwidget *m);
  
  // callback of WidClassMenu

  class CreateCallback : public WidClassCallback {
  private:
    WidBrowseView *view;
  public:
    CreateCallback(WidBrowseView *v) : view(v) {}
    void call(Lcreator &creator) { view->createWidget(creator); }
  } createCallback;

  // callback of WidClassMenu

  class PopupCallback : public WidClassPopupCallback {
  private:
    WidBrowseView *view;
  public:
    PopupCallback(WidBrowseView *v) : view(v) {}
    void call() { view->popupCreateMenu(); }
  } popupCallback;

  // The widget create menu

  WidClassMenu *createMenu;

public:

  // display browser for an lwidget
  static void showView(Lwidget *lwidget);

  // destructor
  ~WidBrowseView();

  // browsers size is persisted
  Boolean saveSize() { return TRUE; }

  char *getName() { return "WidgetTreeBrowser"; }

  // create a widget
  void createWidget(Lcreator &creator);

  // CreateMenu is poped up
  void popupCreateMenu();

};


#endif /* Don't add stuff after this #endif */
