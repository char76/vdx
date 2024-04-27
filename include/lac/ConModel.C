/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: ConModel.C,v $
 *  $Date: 1999/08/27 15:29:19 $
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
 * $Log: ConModel.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:29:19  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:45  lazy
 * Imported to CVS
 *
 * Revision 1.2  1998/02/10  01:03:13  lazy
 * Add empty() method.
 *
 * Revision 1.1  1995/09/27  21:07:16  lazy
 * Initial revision
 *
 */

// ------------------------------------
// Implementation of template ConModel
// (C) Dirk Laessig
// ------------------------------------

#include <lac/ConModel.h>


template <class T>
Container<T>::Container()
: contents(this) 
{
} 

template <class T>
void Container<T>::add( T *toAdd ) 
{ 
  contents.add( toAdd ); 
} 

template <class T>
void Container<T>::insert( T *toIns, T *before ) 
{ 
  contents.insert( toIns, before ); 
}

template <class T>
void Container<T>::remove( T *toRemove ) 
{ 
  contents.remove(toRemove); 
}

template <class T>
unsigned int Container<T>::getSize() 
{ 
  return contents.getSize(); 
}

template <class T>
void Container<T>::empty()
{
  contents.empty();
}

template <class T>
T * Container<T>::operator[]( unsigned int i ) 
{ 
  return contents[i]; 
}

template <class T>
Iconable *Container<T>::at( unsigned int i ) 
{ 
  return contents[i]; 
}

template <class T>
void Container<T>::cb_add( Iconable *toAdd ) 
{ 
  add( (T*)toAdd ); 
}

template <class T>
char *Container<T>::getClassName() 
{ 
  return "Container"; 
}
