/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: TArray.h,v $
 *  $Date: 1999/08/27 15:30:15 $
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
 * $Log: TArray.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:30:15  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:45  lazy
 * Imported to CVS
 *
 * Revision 1.2  1997/07/25  20:04:58  lazy
 * *** empty log message ***
 *
 * Revision 1.1  1995/09/27  21:12:45  lazy
 * Initial revision
 *
 */

#ifndef _TARRAY_H_
#define _TARRAY_H_

#include <stdlib.h>

template <class T>
class TArray {
protected:
  T **elements;
  unsigned int size;

public:
  TArray()
    {
      size = 0;
      elements = NULL;
    }

  TArray( const TArray &toCopy ) 
    {
      size = toCopy.size;
      elements = new T*[ size ];
      for( unsigned int n = 0 ; n < size ; n++ )
	elements[ n ] = toCopy.elements[ n ];
    }

  ~TArray() 
    {
      delete [] elements;
    }

  TArray<T>& operator=( const TArray<T> &toCopy )
    {
      if(elements)
	delete [] elements;
      size = toCopy.size;
      elements = new T*[ size ];
      for( unsigned int n = 0 ; n < size ; n++ )
	elements[ n ] = toCopy.elements[ n ];
      return *this;
    }

  unsigned int getSize( void ) 
    {
      return size;
    }

  void add( T *toAdd ) 
    {
      T **old = elements;
      
      elements = new T*[ size+1 ];
      for( unsigned int n = 0 ; n < size ; n++ )
	elements[ n ] = old[ n ];
      elements[ size ] = toAdd;
      size++;
      delete [] old;
    }

  void insert( T *toInsert, T *before )
    {
      if( !before ) {
	add(toInsert);
	return;
      }
      
      T **old = elements;
      
      elements = new T*[ size+1 ];
      unsigned int help = 0;

      for( unsigned int n = 0 ; n < size ; n++ ) {
	if( help == 0 && old[ n ] == before ) {
	  elements[ n ] = toInsert;
	  help = 1;
	}
	elements[ n + help ] = old[ n ];
      }
      size++;
      delete [] old;
    }      

  short remove( T *toRemove ) 
    {
      unsigned int n, ret = 0; 
      
      for( n = 0 ; n < size  ; n++ )
	if( elements[ n ] == toRemove ) {
	  elements[ n ] = elements[ size-1 ];
	  size--;
	  ret = 1;
	}
      return ret;
    }

  T *operator[]( unsigned int n ) 
    {
      return n < size ? elements[ n ] : (T*)NULL ;
    }
  
  void empty()
    {
      size = 0;
      delete [] elements;
      elements = NULL;
    }
};


// ------------------------------------------
//     SortArray
// ------------------------------------------

template <class T>
class TSortArray : public TArray<T> {
public:
  void sort() {
    if( TArray<T>::size>0 )
      qsort( TArray<T>::elements, TArray<T>::size, sizeof(T*), T::compare );
  }
};



#endif /* DONT ADD STUFF AFTER THIS #endif */


