/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: check.C,v $
 *  $Date: 1999/08/27 15:30:30 $
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
 * $Log: check.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:30:30  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:45  lazy
 * Imported to CVS
 *
 * Revision 1.2  1997/07/25  20:04:58  lazy
 * *** empty log message ***
 *
 * Revision 1.1  1995/09/27  21:15:17  lazy
 * Initial revision
 *
 */

#include "Ref.C"
#include "RefArray.C"
#include "ConModel.C"
#include "TreeNode.C"

#include "check.h"


template class TreeNode<LTree>;
template class Ref<LTree>;
template class RefArray<LTree>;

#if(0)
void LazyMenu::act(char *action)
{
  if(!strcmp(L_INS,action)) {
    ((LTree*)m)->getParent()->changed(CONTAINER_CHANGED);
  }
      
  if(!strcmp(L_ADD,action)) {
    ((LTree*)m)->changed(CONTAINER_CHANGED);
  }
  if(!strcmp(L_DEL,action)) {
    delete m;
  }
  if(!strcmp(L_BRW,action)) {
    Lazy1 *v = new Lazy1((LTree*)m);
    v->open();
  }
}
  
#endif

main( int argc, char **argv )
{
  LTree *t;

  t = LTree::createLTree("/home/lazy");
  
  LicView::init("Check",argc,argv);

  t->populate();
  Lazy1 *v1 = new Lazy1(t);
  v1->open();

  Lazy *v = new Lazy(t);
  v->open();

  LicView::run();
}

