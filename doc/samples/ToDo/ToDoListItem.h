/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
// -------------------------------------
// ToDoListItem
// - represents an item of a todo list
// - defines only the data, not the view
// -------------------------------------
#ifndef TODOLISTITEM_H
#define TODOLISTITEM_H

enum Priority {
  PRIO_NICE_TO_HAVE,
  PRIO_LOW,
  PRIO_MIDDLE,
  PRIO_HIGH,
  PRIO_VERY_HIGH
};

class ToDoListItem {
private:
  static constexpr unsigned int titleLen = 32;
  static constexpr unsigned int descriptionLen = 512;

  char title[titleLen+1];
  char description[descriptionLen+1];
  Priority priority;

public:
  ToDoListItem();

  const char *getTitle() const { return title; }
  const char *getDescription() const { return description; }
  Priority getPriority() const { return priority; }

  void setTitle(const char *t);
  void setDescription(const char *d);
  void setPriority(Priority p);

  unsigned long getId() const { return (unsigned long)this; }
};

#endif
