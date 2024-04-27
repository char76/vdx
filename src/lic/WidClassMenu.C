/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: WidClassMenu.C,v $
 *  $Date: 1999/08/27 15:32:18 $
 *  $Revision: 1.1.1.1.2.1 $
 *
 *  Copyright 1997, Dirk Laessig
 *  ALL RIGHTS RESERVED
 *  See the file Copyright for more information
 *
 *  Dirk Laessig
 *  Goettingstr. 5
 *  38106 Braunschweig
 *  Germany
 ****************************************************************/
/*
 * $Log: WidClassMenu.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:32:18  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:18  lazy
 * Imported to CVS
 *
 * Revision 1.2  1998/02/10  00:57:38  lazy
 * Added support for enable/disable
 * of menu items.
 *
 * Revision 1.1  1997/09/13  16:43:47  lazy
 * Initial revision
 *
 */


#include "WidClassMenu.h"

#include <Xm/PushB.h>
#include <Xm/CascadeB.h>
#include <Xm/RowColumn.h>

// ################################################################
//
// WidClassButton
//
// ################################################################

WidClassButton::WidClassButton(Lcreator *m, WidCategoryMenu *p)
  : WinView(m)
{
  XmString xms;

  model = m;
  parent = p;

  xms = XmStringCreateLtoR(m->getShortName(), XmSTRING_DEFAULT_CHARSET);

  button = XtVaCreateManagedWidget("WidClassButton" , xmPushButtonWidgetClass,
				   parent->getWidget(),
				   XmNlabelString, xms,
				   NULL);

  XmStringFree(xms);

  addAction(button, "OnlyOneAction");
}

WidClassButton::~WidClassButton()
{
  XtDestroyWidget(button);
}

void 
WidClassButton::update(unsigned long)
{
}

void 
WidClassButton::enableIfAsChildOk(Lcreator *wc)
{
  if(wc->asChildOk(model)) {
    XtSetSensitive(button, TRUE);
  } else {
    XtSetSensitive(button, FALSE);
  }
}


// ################################################################
//
// WidCategoryMenu
//
// ################################################################

WidCategoryMenu::WidCategoryMenu(WidClassCategory *m, WidClassMenu *p)
  : WinView(m)
{
  model = m;
  parent = p;
  pulldownMenu = XmCreatePulldownMenu(parent->getWidget(), "WidClassCategory",
				      NULL, 0);
  cascadeButton = XtVaCreateManagedWidget(model->getName(),
					  xmCascadeButtonWidgetClass,
					  parent->getWidget(),
					  XmNsubMenuId, pulldownMenu,
					  NULL);
  for(unsigned int i=0; i<model->getCreators().getSize(); i++) {
    buttons.add(new WidClassButton(model->getCreators()[i], this));
  }
}

WidCategoryMenu::~WidCategoryMenu()
{
  while(buttons.getSize())
    buttons[0].Delete();
}

void 
WidCategoryMenu::update(unsigned long)
{
}

void 
WidCategoryMenu::enableIfAsChildOk(Lcreator *wc)
{
  for(unsigned int i=0; i<buttons.getSize(); i++) {
    buttons[i]->enableIfAsChildOk(wc);
  }
}

// ################################################################
//
// WidClassMenu
//
// ################################################################

WidClassMenu::WidClassMenu(WidClasses *m, Widget parent, Widget cascadeButton)
  : WinView(m)
{
  // save model
  model = m;

  // create menu and attach to subMenu
  pulldownMenu = XmCreatePulldownMenu(parent, "WidClasses", NULL, 0);
  XtVaSetValues(cascadeButton, XmNsubMenuId, pulldownMenu, NULL);

  // Add the callback
  XtAddCallback(pulldownMenu, XmNmapCallback, mapCallback, this);
  
  // create sub menus
  for(unsigned int i=0; i<model->getCategories().getSize(); i++) {
    menus.add(new WidCategoryMenu(model->getCategories()[i], this));
  }
}


WidClassMenu::~WidClassMenu()
{
  while(menus.getSize())
    menus[0].Delete();
}
  

void 
WidClassMenu::call(Lcreator &l)
{
  if(!callback.isNil())
    callback->call(l);
}

void 
WidClassMenu::update(unsigned long)
{
}

void 
WidClassMenu::enableIfAsChildOk(Lcreator *wc)
{
  for(unsigned int i=0; i<menus.getSize(); i++) {
    menus[i]->enableIfAsChildOk(wc);
  }
}


void 
WidClassMenu::mapCallback(Widget, XtPointer client, XtPointer)
{
  WidClassMenu *self = (WidClassMenu*)client;
  
  if(!self->popupCallback.isNil()) {
    self->popupCallback->call();
  }
}
