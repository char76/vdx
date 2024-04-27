/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: ControllerImpl.C,v $
 *  $Date: 1999/08/27 15:30:50 $
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
 * $Log: ControllerImpl.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:30:50  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:17  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/25  20:25:27  lazy
 * Initial revision
 *
 */

#include "ControllerImpl.h"
#include <lac/Controller.h>
#include <lac/SensitiveView.h>

ControllerImpl::~ControllerImpl()
{
  while(menuEntries.getSize()>0)
    menuEntries[0].Delete();
  while(controllers.getSize()>0)
    controllers[0].Delete();
}

void 
ControllerImpl::add(Widget w, char *action)
{
  menuEntries.add(new MenuEntryWidget(w, action));
}


void 
ControllerImpl::process(SensitiveContainer *container)
{
  while(controllers.getSize()>0)
    controllers[0].Delete();

  container->getSelectedControllers(controllers);

  if(controllers.getSize()>0) {
    controllers[0]->takeMenu(menuEntries, controllers);
  } else {
    for(unsigned int i=0; i<menuEntries.getSize(); i++) {
      XtSetSensitive(menuEntries[i]->widget, FALSE);
    }
  }
}
