/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
// ---------------------------------------
// ToDoList
// - defines a collection of ToDoListItem
// ---------------------------------------

#include "ToDoList.h"
#include <assert.h>
#include <stdio.h>

// -----------------------------
// ToDoList()
// -----------------------------

ToDoList::ToDoList()
{
  first = NULL;
}


// -----------------------------
// ~ToDoList()
// -----------------------------

ToDoList::~ToDoList()
{
  Ship *ptr, *next;

  for(ptr = first; ptr; ptr = next) {
    next = ptr->next;
    delete ptr;
  }
}

// -----------------------------
// findInsertPosition()
// -----------------------------

ToDoList::Ship *
ToDoList::findInsertPosition(Ship *toInsert)
{
  Ship *ptr;
  
  assert(toInsert != NULL);

  for(ptr = first; ptr; ptr = ptr->next) {
    if(ptr->next) {
      if(ptr->next->item.getPriority() < toInsert->item.getPriority()) 
	return ptr;
    }
    if(ptr->next == NULL) {
      return ptr;
    }
  }
  return NULL;
}


// -----------------------------
// newItem()
// -----------------------------

ToDoListItem &
ToDoList::newItem()
{
  Ship *ptr, *found;

  ptr = new Ship();
  ptr->next = NULL;
  
  found = findInsertPosition(ptr);
  if(found) {
    ptr->next = found->next;
    found->next = ptr;
  } else {
    ptr->next = first;
    first = ptr;
  }

  return ptr->item;
}

// -----------------------------
// getSize()
// -----------------------------

unsigned int 
ToDoList::getSize()
{
  unsigned int ret;
  Ship *ptr;
  for(ret = 0, ptr = first; ptr; ptr = ptr->next)
    ret++;
  return ret;
}

// -----------------------------
// itemChanged()
// -----------------------------

void 
ToDoList::itemChanged(unsigned long id)
{
  Ship *ptr, *last, *found;

  for(ptr = first, last = NULL; ptr; last = ptr, ptr = ptr->next) {
    if(id == ptr->item.getId()) {
      break;
    }
  }
  if(ptr) {
    if(last) {
      last->next = ptr->next;
    } else {
      first = ptr->next;
    }
  }
  found = findInsertPosition(ptr);
  if(found) {
    ptr->next = found->next;
    found->next = ptr;
  } else {
    ptr->next = first;
    first = ptr;
  }
}

// -----------------------------
// deleteItem()
// -----------------------------

void 
ToDoList::deleteItem(unsigned long id)
{
  Ship *ptr, *last;

  for(ptr = first, last = NULL; ptr; last = ptr, ptr = ptr->next) {
    if(id == ptr->item.getId()) {
      break;
    }
  }

  if(ptr) {
    if(last) {
      last->next = ptr->next;
    } else {
      first = ptr->next;
    }
    delete ptr;
  }
}

// -----------------------------
// operator[]()
// -----------------------------

ToDoListItem &
ToDoList::operator[](unsigned int j)
{
  unsigned int i;
  Ship *ptr;

  for(ptr = first, i=0; ptr; i++, ptr = ptr->next) {
    if(i == j)
      return ptr->item;
  }
  assert(0);
}
  
