/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: ControllerImpl.h,v $
 *  $Date: 1999/08/27 15:30:52 $
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
 * $Log: ControllerImpl.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:30:52  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:17  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/25  20:25:31  lazy
 * Initial revision
 *
 */

// ###############################################################
// This class could be used as a component to implement a view.
// If a pulldown menu in the view is for acting with a selection
// in the tree or icon view, process should be called, when the
// pulldown menu is mapped. But before, the add-method must be
// called in the constructor to determine the menu entry to widget
// mapping.
// ###############################################################

#ifndef _CONTROLLER_IMPL_H_
#define _CONTROLLER_IMPL_H_

#include <lac/RefArray.h>
#include <X11/Intrinsic.h>

class Controller;
class MenuEntryWidget;
class SensitiveContainer;

class ControllerImpl {
private:
  RefArray<MenuEntryWidget> menuEntries;
  RefArray<Controller> controllers;
public:
  ControllerImpl() {}
  ~ControllerImpl();

  void add(Widget w, char *action);              // called in constructor
  void process(SensitiveContainer *container);    // called if menu is mapped
};

#endif
