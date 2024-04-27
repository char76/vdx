/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
// ----------------------------
// MainWindow.h
// ----------------------------

#ifndef _MainWindow_H_
#define _MainWindow_H_

#include "MainWindow_base.h"
#include "ToDoList.h"
#include "ItemView.h"

class MainWindow : public MainWindow_base {
protected:

  // the callbacks

  virtual void list_double_click(Widget,XtPointer);
  virtual void new_item(Widget,XtPointer);
  virtual void show_item(Widget,XtPointer);
  virtual void delete_item(Widget,XtPointer);
  virtual void help_me(Widget,XtPointer);

  // delete all items from the list widget and rereads the data
  void updateListWidget();

  // transform a position of an item in the list widget to the
  // id of a ToDoListItem
  unsigned long getIdFromPos(int pos);

  // the data
  ToDoList &toDoList;

  // one instance of a item view
  ItemView itemView;

public:
  MainWindow(ToDoList &toDoList);        // called by main()
  void itemChanged(unsigned long id);    // called by ItemView to update
};


#endif /* Don't add stuff after this #endif */
