/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: TreeNode.h,v $
 *  $Date: 1999/08/27 15:30:21 $
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
 * $Log: TreeNode.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:30:21  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:45  lazy
 * Imported to CVS
 *
 * Revision 1.3  1998/03/30 19:09:40  lazy
 * *** empty log message ***
 *
 * Revision 1.2  1997/07/25 20:04:58  lazy
 * *** empty log message ***
 *
 * Revision 1.1  1995/09/27  21:13:17  lazy
 * Initial revision
 *
 */

// -----------------------------
// TreeNode
// (C) Dirk Laessig
// -----------------------------

#ifndef _TREENODE_H_
#define _TREENODE_H_


#include <lac/ConModel.h>

// --------------------------------
// TreeNodeBase
// --------------------------------

class TreeNodeBase : public ContainerBase {
public:
  virtual TreeNodeBase *child(unsigned int i) = 0;
  Iconable *at(unsigned int i) { return child(i); }
  void cb_add( Iconable *toAdd ) { tnb_add((TreeNodeBase*)toAdd); }
  
  virtual void tnb_add( TreeNodeBase *toAdd ) = 0;
  virtual void tnb_insert( TreeNodeBase *toIns, TreeNodeBase *before ) = 0;
  virtual void tnb_remove( TreeNodeBase *toRemove ) = 0;
  virtual TreeNodeBase *tnb_getParent() = 0;
  virtual Boolean tnb_asChildOk( TreeNodeBase *toAdd ) = 0;
  virtual TreeNodeBase *tnb_copy() = 0;

  virtual Boolean hasChildren() { return getSize(); }
  virtual Boolean populate() { return FALSE; }

  unsigned int countSubTree() {
    unsigned int count = 1;
    for(unsigned int i=0; i<getSize(); i++) {
      count += ((TreeNodeBase*)child(i))->countSubTree();
    }
    return count;
  }
};

/* -----------------------------------------------------
                TreeNode
   ----------------------------------------------------- */

template <class T>
class TreeNode : public TreeNodeBase {
private:
  Boolean _inDeletion;
  
  class MyArray: public RefArray<T> {
  private:
    TreeNode<T> *parent;
  public:
    MyArray(TreeNode<T> *p){ parent=p; }
    void delNotify( BaseRef *nowNil ){
      RefArray<T>::delNotify( nowNil );
      if( !parent->inDeletion() ) {
	parent->changed( CONTAINER_CHANGED);
      }
    }
  };
  
protected:
  MyArray children;
  T *parent;

public:
  TreeNode();
  ~TreeNode();
  
  void add( T *toAdd );  
  void insert( T *toIns, T *before );
  void remove( T *toRemove );
  unsigned int getSize();
  T * operator[]( unsigned int i );
  
  Boolean inDeletion();
  
  char *getClassName();

  T *getParent();
  virtual void setParent(T* np);
  virtual Boolean asChildOk(T*);
  virtual T* copy();
  
  TreeNodeBase *child(unsigned int i);
  
  void tnb_add(TreeNodeBase *toAdd);
  void tnb_insert(TreeNodeBase *toIns, TreeNodeBase *before);
  void tnb_remove( TreeNodeBase *toRemove );
  TreeNodeBase *tnb_getParent();
  Boolean tnb_asChildOk( TreeNodeBase *toAdd );
  TreeNodeBase *tnb_copy();
  
};



#endif
