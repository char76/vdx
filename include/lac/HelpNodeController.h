/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: HelpNodeController.h,v $
 *  $Date: 1999/08/27 15:29:29 $
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
 * $Log: HelpNodeController.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:29:29  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:46  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/25  19:31:35  lazy
 * Initial revision
 *
 * Revision 1.2  1995/09/27  21:02:46  lazy
 * Header fertig.
 *
 */


#ifndef _HELPNODECONTROLLER_H_
#define _HELPNODECONTROLLER_H_

#include <lac/Controller.h>
class MLXHelp;
class HelpNode;

class HelpNodeController : public Controller {
private:
  MLXHelp *mlxHelp;
  HelpNode *m;

  void createMenuEntries();

public:
  HelpNodeController( HelpNode *am, View *view, MLXHelp* mlxHelp);

  void act(MenuEntry *me);
  void actOnce(MenuEntry *me);
};

#endif
