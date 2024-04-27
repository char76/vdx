/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: RefArray.C,v $
 *  $Date: 1999/08/27 15:30:08 $
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
 * $Log: RefArray.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:30:08  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:45  lazy
 * Imported to CVS
 *
 * Revision 1.2  1997/07/25  20:04:58  lazy
 * *** empty log message ***
 *
 * Revision 1.1  1995/09/27  21:12:03  lazy
 * Initial revision
 *
 */

#include <lac/RefArray.h>


template <class T>
RefArray<T>::RefArray()
{
  removeOnDelete = 1;
  size = 0;
  elements = NULL;
}

template <class T>
RefArray<T>::RefArray( const RefArray &toCopy ) 
{
  removeOnDelete = 1;
  size = toCopy.size;
  elements = new Ref<T>*[ size ];
  for( unsigned int n = 0 ; n < size ; n++ ) {
    elements[ n ] = new Ref<T>( NULL, this ); 
    *elements[ n ] = *toCopy.elements[ n ];
  }
}


template <class T>
RefArray<T>::~RefArray() 
{
  empty();
}


template <class T>
RefArray<T>& RefArray<T>::operator=( const RefArray<T> &toCopy ) 
{
  empty();
  size = toCopy.size;
  elements = new Ref<T>*[ size ];
  for( unsigned int n = 0 ; n < size ; n++ ) {
    elements[ n ] = new Ref<T>( NULL, this ); 
    *elements[ n ] = *toCopy.elements[ n ];
  }
  return *this;
}


template <class T>
unsigned int RefArray<T>::getSize( void ) 
{
  return size;
}


template <class T>
void RefArray<T>::add( T *toAdd ) 
{
  if( !toAdd ) {
    fprintf(stderr,"Fatal error: RefArray: try to add a NULL\n");
    return;
  }
  
  Ref<T> **old = elements;
  
  elements = new Ref<T>* [ size+1 ];
  for( unsigned int n = 0 ; n < size ; n++ )
    elements[ n ] = old[ n ];
  elements[ size ] = new Ref<T>(toAdd,this);
  size++;
  delete [] old;
}

template <class T>
void RefArray<T>::insert( T *toInsert, T *before )
{
  if( !before ) {
    add(toInsert);
    return;
  }

  if( !toInsert ) {
    fprintf(stderr,"Fatal error: RefArray: try to insert a NULL\n");
    return;
  }

  Ref<T> **old = elements;
  
  elements = new Ref<T>* [ size+1 ];
  unsigned int help = 0;
  for( unsigned int n = 0 ; n < size ; n++ ) {
    if( help == 0 && *old[ n ] == before ) {
      elements[ n ] = new Ref<T>(toInsert,this);
      help = 1;
    }
    elements[ n + help ] = old[ n ];
  }
  size++;
  delete [] old;
}      


template <class T>
short RefArray<T>::remove( T *toRemove ) 
{
  unsigned int n, ret = 0; 
  char f = 0;
  
  for( n = 0 ; n < size  ; n++ ) {
    if( f ) {
      elements[n-1] = elements[n];
    } else {
      if( *elements[ n ] == toRemove ) {
	f = 1;
	ret = 1;
	delete elements[n];
      }
    }
  }
  if(f)
    size--;
  return ret;
}


template <class T>
Ref<T> &RefArray<T>::operator[]( unsigned int n ) 
{
  if( n >= size ) {
    fprintf( stderr, "bound checking: %d >= %d\n",n,size);
  }
  return *(elements[ n ]);
}


template <class T>
void RefArray<T>::empty() 
{
  for(unsigned int i=0; i<size; i++)
    delete elements[i];
  size = 0;
  delete [] elements;
  elements = NULL;
}


template <class T>
void RefArray<T>::setRemoveOnDelete(int s)
{
  removeOnDelete = s;
}

template <class T>
void RefArray<T>::delNotify( BaseRef *rm ) 
{
  unsigned int n; 
  char f=0;
  if(!removeOnDelete)
    return;
  for( n = 0 ; n < size  ; n++ )
    if( f ) {
      elements[ n-1 ] = elements[ n ];
    } else {
      if( elements[ n ] == rm ) {
	f = 1;
	delete elements[n];
      }
    }
  if(f) 
    size--;
}



