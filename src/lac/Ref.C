/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: Ref.C,v $
 *  $Date: 1999/08/27 15:30:06 $
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
 * $Log: Ref.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:30:06  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:45  lazy
 * Imported to CVS
 *
 * Revision 1.1  1995/09/27  21:11:37  lazy
 * Initial revision
 *
 */

// ----------------------------------
// Ref-Template implementation
//
// (C) Dirk Laessig
// ----------------------------------

#include <lac/Ref.h>

template <class T>
void Ref<T>::delNotify() 
{
  pointer = NULL;
  next = NULL;
  if( parent )
    parent->delNotify( this );
}

template <class T>
Ref<T>::Ref( T *ptr, Lobject *p ) 
{
  pointer = ptr;
  parent = p;
  addRelation( pointer );
}


template <class T>
Ref<T>::~Ref() 
{ 
  if(pointer) 
    delRelation( pointer );
}

template <class T>
T* Ref<T>::operator->()
{                                  // derefenz
  if( !pointer )
    fprintf( stderr, "Warning: Ref is nil\n" );
  return pointer;
}


template <class T>
Ref<T>& Ref<T>::operator=(T *ptr)
{                            // assignment operator
  if( pointer )
    delRelation( pointer );
  pointer = ptr;
  addRelation( pointer );
  return *this;
}


template <class T>
Ref<T>& Ref<T>::operator=(Ref &ref)
{                       // assignment operator
  if( pointer )
    delRelation( pointer );
  pointer = ref.pointer;
  addRelation( pointer );
  return *this;
}


template <class T>
int Ref<T>::operator==(T *toCmp) 
{
  return pointer==toCmp;
}

template <class T>
int Ref<T>::operator==(Ref &toCmp)
{
  return pointer==toCmp.pointer;
}

template <class T>
int Ref<T>::isNil() 
{ 
  return pointer ? 0 : 1; 
}

template <class T>
Ref<T>::operator T*() 
{ 
  return pointer; 
}


template <class T>
void Ref<T>::Delete() 
{ 
  delete pointer; 
}


