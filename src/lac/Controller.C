/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: Controller.C,v $
 *  $Date: 1999/08/27 15:29:22 $
 *  $Revision: 1.1.1.1.2.1 $
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
 * $Log: Controller.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:29:22  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:46  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/25  19:31:22  lazy
 * Initial revision
 *
 */

#include "Controller.h"

#include <X11/Intrinsic.h>
#include <X11/IntrinsicP.h>
#include <X11/CoreP.h>
#include <Xm/Xm.h>
#include <Xm/PushB.h>
#include <Xm/ToggleB.h>
#include <Xm/CascadeB.h>
#include <Xm/Separator.h>
#include <Xm/Label.h>
#include <Xm/RowColumn.h>

// ####################################################################
//
//                 Controller
//
// ####################################################################

MenuEntry me(NULL,ME_PUSHBUTTON,"",FALSE,NULL);

// ---------------------------------
//       Controller()
// ---------------------------------

Controller::Controller(Iconable *m, View *v)
{
  menu = NULL;
  model = m;
  view = v;
}
 
// ---------------------------------
//       ~Controller()
// ---------------------------------

Controller::~Controller()
{
  while(entries.getSize())
    entries[0].Delete();
  if(menu) {
    XtDestroyWidget(menu);
  }
}

// ---------------------------------
//       createMenuEntries()
// ---------------------------------

void Controller::createMenuEntries()
{
  MenuEntry *me = new MenuEntry(this, ME_PUSHBUTTON, "Delete", FALSE);
  entries.add(me);
}
  
// ---------------------------------
//       maskMenuEntries()
// ---------------------------------

void Controller::maskMenuEntries(RefArray<MenuEntry> &toMask)
{
  for(unsigned int i=0; i<toMask.getSize(); i++) {
    if(toMask[i]->getVisible()) {
      Boolean found = FALSE;
      unsigned int j;
      for(j=0; j<entries.getSize(); j++) {
	if(entries[j]->match(toMask[i])) {
	  found = TRUE;
	  break;
	}
      }
      if(!found) {      // if we not found the menu entry, then hide it
	toMask[i]->setVisible(FALSE);
      } else if(!entries[j]->getSensitive()) { 
	// not sensitive -> make my entry insensitive
	toMask[i]->setSensitive(FALSE);
      }
    }
  }
}


// ---------------------------------
//       popupMenu()
// ---------------------------------

void Controller::popupMenu(Widget parent, Position x, Position y,
			   RefArray<Controller> selection)
{
  for(unsigned int i=0; i<selection.getSize(); i++) {
    while(selection[i]->entries.getSize())
      selection[i]->entries[0].Delete();
  }

  // give every controller an overview of the others
  for(unsigned int i=0; i<selection.getSize(); i++)  
    selection[i]->selection = selection;

  // create the menu entries
  for(unsigned int i=0; i<selection.getSize(); i++)
    selection[i]->createMenuEntries();

  // and now filter the menus
  for(unsigned int i=0; i<selection.getSize(); i++) {
    if(selection[i] != this) {
      selection[i]->maskMenuEntries(entries);
    }
  }
  
  if(menu)
    XtDestroyWidget(menu);
  menu = XmCreatePopupMenu(parent, "Popupmenu", (Arg*)NULL, 0 );
  label = XtVaCreateManagedWidget("PopupMenuLabel", xmLabelWidgetClass, menu, 
				  NULL);
  if(selection.getSize() == 1) {
    XmString xms;
    xms = XmStringCreateLtoR(model->getName(), XmSTRING_DEFAULT_CHARSET);
    XtVaSetValues(label, XmNlabelString, xms, NULL);
    XmStringFree(xms);
  }
  separator = XtVaCreateManagedWidget("Separator",xmSeparatorWidgetClass, menu,
				      NULL);
  separator = XtVaCreateManagedWidget("Separator",xmSeparatorWidgetClass, menu,
				      NULL);
  for(unsigned int i=0; i<entries.getSize(); i++) {
    entries[i]->createWidget();
  }

  {                                         // popup the menu
    XButtonEvent be;
    Window dummy;
    Window root = XRootWindowOfScreen(XtScreen(parent));
    XTranslateCoordinates(XtDisplay(parent), XtWindow(parent), root,
			  x, y, &be.x_root, &be.y_root, &dummy );
    XmMenuPosition(menu,&be);
    XtManageChild(menu);
  }
}


// ---------------------------------
//       takeMenu()
// ---------------------------------

void Controller::takeMenu(RefArray<MenuEntryWidget> entryWidgets,
			  RefArray<Controller> selection)
{
  for(unsigned int i=0; i<selection.getSize(); i++) {
    while(selection[i]->entries.getSize())
      selection[i]->entries[0].Delete();
  }
  
  // give every controller an overview of the others
  for(unsigned int i=0; i<selection.getSize(); i++)  
    selection[i]->selection = selection;

  // create the menu entries
  for(unsigned int i=0; i<selection.getSize(); i++)
    selection[i]->createMenuEntries();
  
  // and now filter the menus
  for(unsigned int i=0; i<selection.getSize(); i++) {
    if(selection[i] != this) {
      selection[i]->maskMenuEntries(entries);
    }
  }

  for(unsigned int j=0; j<entryWidgets.getSize(); j++) {
    Boolean found = FALSE;
    for(unsigned int i=0; i<entries.getSize(); i++) {
      if(entryWidgets[j]->action == Lstring(entries[i]->getAction())) {
	entries[i]->assignWidget(entryWidgets[j]->widget);
	found = TRUE;
	break;
      }
    }
    if(!found)
      XtSetSensitive(entryWidgets[j]->widget, FALSE);
  }
}

// ---------------------------------
//       processKey()
// ---------------------------------

Boolean Controller::processKey(int bs, char *ks, 
			       RefArray<Controller> selection)
{
  for(unsigned int i=0; i<selection.getSize(); i++) {
    while(selection[i]->entries.getSize())
      selection[i]->entries[0].Delete();
  }
  
  // give every controller an overview of the others
  for(unsigned int i=0; i<selection.getSize(); i++)  
    selection[i]->selection = selection;

  // create the menu entries
  for(unsigned int i=0; i<selection.getSize(); i++)
    selection[i]->createMenuEntries();
  
  // and now filter the menus
  for(unsigned int i=0; i<selection.getSize(); i++) {
    if(selection[i] != this) {
      selection[i]->maskMenuEntries(entries);
    }
  }

  // find menu entries with key
  for(unsigned int i=0; i<entries.getSize(); i++) {
    if(entries[i]->processKey(bs,ks))
      return TRUE;
  }
  return FALSE;
}
  
// ---------------------------------
//       actOnce()
// ---------------------------------

void Controller::actOnce(MenuEntry *)
{
  
}

// ---------------------------------
//       act()
// ---------------------------------

void Controller::act(MenuEntry *me)
{
  if(me->match("Delete"))
    model.Delete();
}

// ####################################################################
//
//                 MenuEntry
//
// ####################################################################


// ---------------------------------
//       MenuEntry()
// ---------------------------------

MenuEntry::MenuEntry(Controller *controller, MenuType menuType, char *action,
		     Boolean once, MenuEntry *subMenu)
{
  widget = NULL;
  menu = NULL;
  parent = controller;
  this->menuType = menuType;
  this->action = new char[strlen(action)+1];
  strcpy(this->action, action);
  this->once = once;
  this->subMenu = subMenu;
  visible = TRUE;
  toggleButtonValue = FALSE;
  sensitive = TRUE;
  keyString[0] = 0;
  buttonState = 0;
}
  
MenuEntry::~MenuEntry()
{
  if(widgetRef != NULL && !((Widget)widgetRef)->core.being_destroyed) {
    if(menuType == ME_PUSHBUTTON)
      XtRemoveCallback(widgetRef, XmNactivateCallback, menuEntryCB, this);
    if(menuType == ME_TOGGLEBUTTON)
      XtRemoveCallback(widgetRef, XmNvalueChangedCallback, menuEntryCB, this);
  }
  delete action;
}

// ---------------------------------
//       match()
// ---------------------------------

int MenuEntry::match(MenuEntry *other)
{
  if(other->menuType == ME_SEPARATOR)
    return TRUE;
  if(!other->action)
    return FALSE;
  if(!action)
    return TRUE;
  return (strcmp(action,other->action) == 0);
}
  
int MenuEntry::match(char *str)
{
  return (strcmp(action,str) == 0);
}
  
// ---------------------------------
//       setVisible()
// ---------------------------------

void MenuEntry::setVisible(Boolean v)
{
  visible = v;
  if(widget) {
    if(v) 
      XtManageChild(widget);
    else
      XtUnmanageChild(widget);
  }
}

// ---------------------------------
//       setSensitive()
// ---------------------------------

void MenuEntry::setSensitive(Boolean s)
{
  sensitive = s;
  if(widget) {
    XtSetSensitive(widget, s);
  }
}

// ---------------------------------
//      createWidget()
// ---------------------------------

void MenuEntry::createWidget()
{
  Widget parentWidget = NULL;
  if(!subMenu.isNil()) {
    if(!subMenu->menu)
      subMenu->createWidget();
    parentWidget = subMenu->menu;
  } else {
    parentWidget = parent->getMenuWidget();
  }
  switch(menuType) {
  case ME_PUSHBUTTON:
    widget = XtVaCreateWidget(action, xmPushButtonWidgetClass, 
			      parentWidget, NULL);
    XtAddCallback(widget, XmNactivateCallback, menuEntryCB, this);
    break;
  case ME_SEPARATOR:
    widget = XtVaCreateWidget(action, xmSeparatorWidgetClass, 
			      parentWidget, NULL);
    break;
  case ME_TOGGLEBUTTON:
    widget = XtVaCreateWidget(action, xmToggleButtonWidgetClass, 
			      parentWidget, NULL);
    XtAddCallback(widget, XmNvalueChangedCallback, menuEntryCB, this);
    XmToggleButtonSetState(widget, toggleButtonValue, FALSE);
    break;
  case ME_SUBMENU:
    menu = XmCreatePulldownMenu(parentWidget, "PulldownMenu", NULL, 0);
    widget = XtVaCreateWidget(action, xmCascadeButtonWidgetClass, 
			      parentWidget, 
			      XmNsubMenuId, menu,
			      NULL);
    break;
  case ME_RADIO_SUBMENU:
    menu = XmCreatePulldownMenu(parentWidget, "PulldownMenu", NULL, 0);
    XtVaSetValues(menu, XmNradioBehavior, TRUE, NULL);
    widget = XtVaCreateWidget(action, xmCascadeButtonWidgetClass, 
			      parentWidget, 
			      XmNsubMenuId, menu,
			      NULL);
    break;
  default:
    break;
  }
  if(visible && widget)
    XtManageChild(widget);
  if(widget)
    XtSetSensitive(widget, sensitive);
}

// ---------------------------------
//       menuEntryCB()
// ---------------------------------

void MenuEntry::menuEntryCB(Widget, XtPointer clientData, XtPointer)
{
  MenuEntry *me = (MenuEntry*)clientData;
  if(me->once) {
    if(me->parent->getModel()) {
      View::transactionBegin();
      me->parent->actOnce(me);
      View::transactionEnd();
    }
  }
  else {
    View::transactionBegin();
    RefArray<Controller> all(me->parent->getSelection());
    all.setRemoveOnDelete(FALSE);
    for(unsigned int i=0; i<all.getSize(); i++)
      if(all[i]->getModel())
	all[i]->act(me);
    View::transactionEnd();
  }
}


// ---------------------------------
//   setToggleButtonValue()
// ---------------------------------

void MenuEntry::setToggleButtonValue(Boolean v)
{
  toggleButtonValue = v;
  if(widget && ME_TOGGLEBUTTON == menuType) {
    XmToggleButtonSetState(widget, toggleButtonValue, FALSE);
  }
}

// ---------------------------------
//       getToggleButtonValue()
// ---------------------------------

Boolean MenuEntry::getToggleButtonValue()
{
  Boolean value = FALSE;
  if(widget && ME_TOGGLEBUTTON == menuType) {
    value = XmToggleButtonGetState(widget);
  }
  return value;
}


// ---------------------------------
//     processKey()
// ---------------------------------

Boolean MenuEntry::processKey(int bs, char *ks)
{
  if(visible && sensitive && buttonState == bs && !strcmp(ks, keyString)) {
    // a little hack
    menuEntryCB(NULL, this, NULL);
    return TRUE;
  }
  return FALSE;
}

// ---------------------------------
//       setKeyBinding()
// ---------------------------------

void MenuEntry::setKeyBinding(int bs, char *ks)
{ 
  buttonState = bs;
  if(strlen(ks) < MAX_KEYSTRING) {
    strcpy(keyString, ks);
  }
}


// ---------------------------------
//       assignWidget()
// ---------------------------------

void MenuEntry::assignWidget(Widget widget)
{
  if(widget == NULL)
    return;

  widgetRef = widget;

  if(menuType == ME_PUSHBUTTON)
    XtAddCallback(widgetRef, XmNactivateCallback, menuEntryCB, this);
  if(menuType == ME_TOGGLEBUTTON) {
    XtAddCallback(widgetRef, XmNvalueChangedCallback, menuEntryCB, this);
    XmToggleButtonSetState(widgetRef, toggleButtonValue, FALSE);
  }

  if(visible) {
    XtManageChild(widgetRef);
    XtSetSensitive(widgetRef, sensitive);
  } else {
    XtSetSensitive(widgetRef, FALSE);
  }
}


