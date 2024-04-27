/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: HelpNodeController.C,v $
 *  $Date: 1999/08/27 15:29:28 $
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
 * $Log: HelpNodeController.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:29:28  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:46  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/25  19:31:31  lazy
 * Initial revision
 *
 * Revision 1.3  1995/09/27  21:02:03  lazy
 * Header fertig.
 *
 */


#include "HelpNode.h"
#include "HelpNodeController.h"
#include "MLXHelp.h"

#define DELETE_HELPNODE "Delete"
#define NEW_SUBSECTION "Subsection"
#define NEW_LINK "Link"
#define EDIT_TITLE "EditTitle"
#define EDIT_IDENT "EditIdent"
#define SHOW_TEXT "ShowText"

HelpNodeController::HelpNodeController( HelpNode *am, View *v, MLXHelp *h )
:Controller(am,v)
{
  mlxHelp = h;
  m = am;
}


// -------------------------------------
//   createMenuEntries()
// -------------------------------------

void HelpNodeController::createMenuEntries()
{
  entries.add( new MenuEntry(this, ME_PUSHBUTTON, SHOW_TEXT, FALSE));
  
  if(mlxHelp && mlxHelp->isEditable()) {
    entries.add( new MenuEntry(this, ME_PUSHBUTTON, EDIT_TITLE, FALSE));
    entries.add( new MenuEntry(this, ME_PUSHBUTTON, EDIT_IDENT, FALSE));
    entries.add( new MenuEntry(this, ME_PUSHBUTTON, NEW_SUBSECTION, FALSE));
    entries.add( new MenuEntry(this, ME_PUSHBUTTON, NEW_LINK, FALSE));
    entries.add( new MenuEntry(this, ME_PUSHBUTTON, DELETE_HELPNODE, FALSE));
  }
}


// -------------------------------------
//   act()
// -------------------------------------

void HelpNodeController::act(MenuEntry *me )
{
  if(me->match(SHOW_TEXT)) {
    mlxHelp->setSelectedHelpNode( m );
  }
  if(me->match(EDIT_TITLE)) {
    mlxHelp->editTitle( m );
  }
  if(me->match(EDIT_IDENT)) {
    mlxHelp->editIdent( m );
  }
  if(me->match(NEW_LINK)) {
    mlxHelp->insertLink(m);
  }
  if(me->match(DELETE_HELPNODE)) {
    delete m;
  }
  if(me->match(NEW_SUBSECTION)) {   // id=0 -> id ermitteln
    m->add( new HelpNode( m, 0)); 
    m->changed( CONTAINER_CHANGED );
  }
}
  

// -------------------------------------
//   actOnce()
// -------------------------------------

void HelpNodeController::actOnce(MenuEntry *)
{
}

