/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: TreeNode.C,v $
 *  $Date: 1999/08/27 15:30:19 $
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
 * $Log: TreeNode.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:30:19  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:45  lazy
 * Imported to CVS
 *
 * Revision 1.1  1995/09/27  21:13:06  lazy
 * Initial revision
 *
 */

// -------------------------------------------
// TreeNode.C implementation of template TreeNode
//
// (C) Dirk Laessig
// -------------------------------------------

#include <lac/TreeNode.h>

template <class T>
TreeNode<T>::TreeNode(): children(this) 
{
  parent = NULL; 
  _inDeletion = FALSE;
}

template <class T>
TreeNode<T>::~TreeNode() 
{ 
  _inDeletion = TRUE;
  while( children.getSize() ) 
    children[0].Delete();
}

template <class T>
void TreeNode<T>::add( T *toAdd ) 
{ 
  toAdd->setParent((T*)this); 
  children.add( toAdd ); 
} 

template <class T>
void TreeNode<T>::insert( T *toIns, T *before ) 
{ 
  toIns->setParent((T*)this); 
  children.insert( toIns, before ); 
}

template <class T>
void TreeNode<T>::remove( T *toRemove ) 
{ 
  children.remove(toRemove);
  toRemove->setParent(NULL);
}

template <class T>
unsigned int TreeNode<T>::getSize() 
{ 
  return children.getSize();
}

template <class T>
T * TreeNode<T>::operator[]( unsigned int i ) 
{ 
  return children[i];
}

template <class T>
TreeNodeBase *TreeNode<T>::child(unsigned int i) 
{ 
  return children[i];
}

template <class T>
Boolean TreeNode<T>::inDeletion() 
{ 
  return _inDeletion;
}

template <class T>
char *TreeNode<T>::getClassName() 
{ 
  return "TreeNode"; 
}

template <class T>
T *TreeNode<T>::getParent() 
{ 
  return parent;
}

template <class T>
void TreeNode<T>::setParent(T* np) { 
  if(!parent || !np) 
    parent = np;
  else 
    fprintf(stderr,"Fatal error: try to set parent at %s\n",getName());
}

template <class T>
Boolean TreeNode<T>::asChildOk(T*) 
{ 
  return TRUE;
}

template <class T>
T* TreeNode<T>::copy()
{ 
  return NULL;
}

template <class T>
void TreeNode<T>::tnb_add(TreeNodeBase *toAdd)
{ 
  add( (T*)toAdd );
} 

template <class T>
void TreeNode<T>::tnb_insert(TreeNodeBase *toIns, TreeNodeBase *before) 
{ 
  insert((T*)toIns, (T*)before);
}

template <class T>
void TreeNode<T>::tnb_remove( TreeNodeBase *toRemove ) 
{ 
  remove((T*)toRemove);
}

template <class T>
TreeNodeBase *TreeNode<T>::tnb_getParent()
{
  return parent;
}

template <class T>
Boolean TreeNode<T>::tnb_asChildOk( TreeNodeBase *toAdd )
{
  return asChildOk((T*)toAdd);
}

template <class T>
TreeNodeBase *TreeNode<T>::tnb_copy()
{
  return copy();
}
