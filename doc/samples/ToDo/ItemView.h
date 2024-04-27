/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
// ----------------------------
// ItemView.h
// ----------------------------

#ifndef _ItemView_H_
#define _ItemView_H_

#include "ItemView_base.h"

class ToDoListItem;
class MainWindow;

class ItemView : public ItemView_base {
protected:

  // callbacks

  virtual void save_and_close(Widget,XtPointer);
  virtual void close_view(Widget,XtPointer);
  virtual void help_me(Widget,XtPointer);

  // data 
  ToDoListItem *item;

  // my main window
  MainWindow *mainWindow;

public:
  ItemView(Widget parent = NULL, ArgList args = NULL, Cardinal n = 0);

  // set data, update and show the view
  void setItem(ToDoListItem *item);

  // return the current displayed data
  ToDoListItem *getItem() { return item; }

  // called by main window
  void setMainWindow(MainWindow *mw) { mainWindow = mw; }
};

// don't need it
ItemView *createItemView(Widget parent, ArgList args, Cardinal n);

#endif /* Don't add stuff after this #endif */
