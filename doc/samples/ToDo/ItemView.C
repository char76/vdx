/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
// ------------------------------ 
// ItemView.C                      
// ------------------------------


#include "ItemView.h"
#include <stdio.h>
#include "ToDoListItem.h"
#include <Xm/Text.h>
#include <Xm/ToggleB.h>
#include "MainWindow.h"
#include "HelpView.h"

// ------------------------------
// createItemView()
// ------------------------------

ItemView *createItemView(Widget parent, ArgList args, Cardinal n)
{
  return new ItemView(parent,args,n);
}


// ------------------------------
// ItemView()
// ------------------------------

ItemView::ItemView(Widget wg, ArgList args, Cardinal n)
:ItemView_base(wg,args,n) 
{
  item = NULL;
}

// ------------------------------
// ItemView()
// ------------------------------

void ItemView::setItem(ToDoListItem *item)
{
  this->item = item;
  if(item == NULL) {
    close();
    return;
  }

  // put strings into the text widgets

  XmTextSetString(titleText, (char*)item->getTitle());
  XmTextSetString(text, (char*)item->getDescription());

  // set the toggle button states
  // BTW, the 3rd parameter must be TRUE if the toggle button is
  // child of a radio box
  
  switch(item->getPriority()) {
  case PRIO_VERY_HIGH:
    XmToggleButtonSetState(veryHighToggle, TRUE, TRUE);
    break;
  case PRIO_HIGH:
    XmToggleButtonSetState(highToggle, TRUE, TRUE);
    break;
  case PRIO_MIDDLE:
    XmToggleButtonSetState(middleToggle, TRUE, TRUE);
    break;
  case PRIO_LOW:
    XmToggleButtonSetState(lowToggle, TRUE, TRUE);
    break;
  case PRIO_NICE_TO_HAVE:
    XmToggleButtonSetState(niceToHaveToggle, TRUE, TRUE);
  }

  // show me
  
  open();
}

// -------------------------
// save_and_close()
// -------------------------

void ItemView::save_and_close(Widget, XtPointer)
{
  char *str;

  if(item == NULL)
    return;

  // read contents of text widgets

  str = XmTextGetString(titleText);
  item->setTitle(str);
  XtFree(str);
  str = XmTextGetString(text);
  item->setDescription(str);
  XtFree(str);

  // query the toggle button state to set the priority

  if(XmToggleButtonGetState(veryHighToggle)) {
    item->setPriority(PRIO_VERY_HIGH);
  } else if(XmToggleButtonGetState(highToggle)) {
    item->setPriority(PRIO_HIGH);
  } else if(XmToggleButtonGetState(middleToggle)) {
    item->setPriority(PRIO_MIDDLE);
  } else if(XmToggleButtonGetState(lowToggle)) {
    item->setPriority(PRIO_LOW);
  } else if(XmToggleButtonGetState(niceToHaveToggle)) {
    item->setPriority(PRIO_NICE_TO_HAVE);
  }

  // Ok means: save and CLOSE

  close();

  // notify the main window to update

  mainWindow->itemChanged(item->getId());
}


// -------------------------
// close_view()
// -------------------------

void ItemView::close_view(Widget, XtPointer)
{
  close();
}


// -------------------------
// help_me()
// -------------------------

void ItemView::help_me(Widget wg, XtPointer)
{
  HelpView::showHelp("ItemView", XtName(wg));
}





