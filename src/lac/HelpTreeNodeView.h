/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: HelpTreeNodeView.h,v $
 *  $Date: 1999/08/27 15:29:30 $
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
 * $Log: HelpTreeNodeView.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:29:30  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:46  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/25  19:31:38  lazy
 * Initial revision
 *
 * Revision 1.1  1995/09/27  21:03:10  lazy
 * Initial revision
 *
 */

#ifndef _HELPTREENODEVIEW_H_
#define _HELPTREENODEVIEW_H_

#include <lac/TreeView.h>

#include <lac/MLXHelp.h>
#include <lac/HelpNode.h>
#include <lac/HelpNodeController.h>

#define VD_WITH_CHILDREN "WithChildren"

class HelpTreeNodeView : public TreeNodeView {
private:
  MLXHelp *mlxHelp;
  HelpNode *helpNode;
public:
  HelpTreeNodeView(TreeView *treeView, TreeNodeView *p, HelpNode *m ) 
    : TreeNodeView(treeView, p, m) {
      mlxHelp = NULL;
      helpNode = m;
      intentX = 20;
      intentY = 5;
      if(helpNode && helpNode->getParent()) {
	Boolean wc;
	if(!helpNode->getVDBoolean(this, VD_WITH_CHILDREN, wc)) {
	  helpNode->setVDBoolean(this, VD_WITH_CHILDREN, FALSE );
	  helpNode->changed( VD_WITH_CHILDREN_CHANGED );
	}
      }
    }

  HelpTreeNodeView(MLXHelp *h):TreeNodeView() {
    mlxHelp = h;
    helpNode = NULL;
  }          

  virtual TreeNodeView *copy(TreeView *treeView, TreeNodeView *p, TreeNodeBase *m){
    HelpTreeNodeView *htnv = new HelpTreeNodeView(treeView, p, (HelpNode*)m);
    htnv->mlxHelp = mlxHelp;
    return htnv;
  }

  void select( Boolean s, Position x, Position y ) {
    TreeNodeView::select(s,x,y);
    if(helpNode && mlxHelp && helpNode->isSelected()) {
      mlxHelp->setSelectedHelpNode(helpNode);
    }
  }

  void move(Widget wg,XEvent *event,
	    Position x,Position y, 
	    unsigned char dragOperations) {

    if( mlxHelp->isEditable() ) {
      SensitiveRec::move(wg,event,x,y,dragOperations);
    }
  }
};



// ------------------- HelpTreeView ---------------------

class HelpTreeView : public TreeView {
private:
  MLXHelp *mlxHelp;

public:
  HelpTreeView(TreeNodeBase *cm, 
	       Widget p, 
	       MLXHelp *mlxHelp, 
	       TreeNodeView *tnv = NULL)
    : TreeView(cm,p,tnv) 
      { 
	this->mlxHelp = mlxHelp; 
      }

  Controller *getController(SensitiveRec *v) {
    return new HelpNodeController((HelpNode*)v->getModel(), v, mlxHelp);
  }
};



#endif
