/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
// -------------------------------------
// ToDoListItem
// - represents an item of a todo list
// - defines only the data, not the view
// -------------------------------------

#include "ToDoListItem.h"
#include <assert.h>
#include <string.h>

// -----------------------------
// ToDoListItem()
// -----------------------------

ToDoListItem::ToDoListItem()
{
  // setup the default values

  strcpy(title, "New Item");
  strcpy(description, "Enter a description\n");
  priority = PRIO_VERY_HIGH;
}

// -----------------------------
// setTitle()
// -----------------------------

void 
ToDoListItem::setTitle(const char *t)
{
  assert(strlen(t) <= titleLen);

  strcpy(title, t);
}

// -----------------------------
// setDescription()
// -----------------------------

void 
ToDoListItem::setDescription(const char *d)
{
  assert(strlen(d) <= descriptionLen);

  strcpy(description, d);
}

// -----------------------------
// setPriority()
// -----------------------------

void 
ToDoListItem::setPriority(Priority p)
{
  priority = p;
}

