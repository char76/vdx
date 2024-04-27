/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
// ------------------------------ 
// MainWindow.C                      
// ------------------------------


#include "MainWindow.h"
#include <stdio.h>
#include <Xm/List.h>
#include "HelpView.h"

// ------------------------------
// MainWindow()
// ------------------------------

MainWindow::MainWindow(ToDoList &tdList)
:MainWindow_base(NULL, NULL, 0), toDoList(tdList)
{
  void updateListWidget();
  itemView.setMainWindow(this);
}


// ------------------------------
// updateListWidget()
// ------------------------------

void MainWindow::updateListWidget()
{
  XmListDeleteAllItems(list);
  for(unsigned int i=0; i<toDoList.getSize(); i++) {
    XmString xms;
    
    xms = XmStringCreateLtoR((char *)toDoList[i].getTitle(), XmSTRING_DEFAULT_CHARSET);
    XmListAddItem(list, xms, 0);
    XmStringFree(xms);
  }
}

// ------------------------------
// itemChanged()
// ------------------------------

void MainWindow::itemChanged(unsigned long id)
{
  toDoList.itemChanged(id);
  updateListWidget();
}

// ------------------------------
// getIdFromPos()
// ------------------------------

unsigned long MainWindow::getIdFromPos(int pos)
{
  for(unsigned int i=0; i<toDoList.getSize(); i++) {
    if((int)i == pos-1)
      return toDoList[i].getId();
  }
  return 0;
}

// -------------------------
// list_double_click()
// -------------------------

void MainWindow::list_double_click(Widget, XtPointer)
{
  show_item(NULL, NULL);
}


// -------------------------
// new_item()
// -------------------------

void MainWindow::new_item(Widget, XtPointer)
{
  toDoList.newItem();
  updateListWidget();
}


// -------------------------
// show_item()
// -------------------------

void MainWindow::show_item(Widget, XtPointer)
{
  int *positions, count;
  
  positions = NULL;
  XmListGetSelectedPos(list, &positions, &count);
  if(count>0) {
    ToDoListItem *item = &toDoList[positions[0]-1];
    itemView.setItem(item);
  }
  if(positions)
    XtFree((char*)positions);
}


// -------------------------
// delete_item()
// -------------------------

void MainWindow::delete_item(Widget, XtPointer)
{
  int *positions, count;
  
  positions = NULL;
  XmListGetSelectedPos(list, &positions, &count);
  for(unsigned int i=0; (int)i<count; i++) {
    toDoList.deleteItem(getIdFromPos(positions[i]));
  }
  if(positions)
    XtFree((char*)positions);
  updateListWidget();
}


// -------------------------
// help_me()
// -------------------------

void MainWindow::help_me(Widget wg, XtPointer)
{
  HelpView::showHelp("MainWindow", XtName(wg));
}





