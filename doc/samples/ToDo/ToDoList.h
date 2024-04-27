/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
// ---------------------------------------
// ToDoList
// - defines a collection of ToDoListItem
// ---------------------------------------

#ifndef TODOLIST_H
#define TODOLIST_H

#include "ToDoListItem.h"

class ToDoList {
private:
  struct Ship {                      // to make a chained list
    ToDoListItem item;
    Ship *next;
  };

  Ship *first;                       // the first item
  Ship *findInsertPosition(Ship *);  // implements the ordering

public:
  ToDoList();
  ~ToDoList();

  ToDoListItem &newItem();                  // insert item with default values
  void itemChanged(unsigned long id);       // item has changed -> reorder
  void deleteItem(unsigned long id);        // delete a item, use item id
  ToDoListItem &operator[](unsigned int n); // get the Nth item
  unsigned int getSize();                   // number of items
};

#endif
