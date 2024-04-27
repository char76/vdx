/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: RefArray.h,v $
 *  $Date: 1999/08/27 15:30:10 $
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
 * $Log: RefArray.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:30:10  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:45  lazy
 * Imported to CVS
 *
 * Revision 1.2  1997/07/25  20:04:58  lazy
 * *** empty log message ***
 *
 * Revision 1.1  1995/09/27  21:12:11  lazy
 * Initial revision
 *
 */


#include <lac/Ref.h>
#ifndef _REFARRAY_H_
#define _REFARRAY_H_

template <class T>
class RefArray : public Lobject {
protected:
  Ref<T> **elements;
  unsigned int size;
  int removeOnDelete;

public:
  RefArray();
  RefArray( const RefArray &toCopy );
  ~RefArray();
  RefArray<T>& operator=( const RefArray<T> &toCopy);

  unsigned int getSize( void );
  void add( T *toAdd );
  void insert( T *toInsert, T *before );
  short remove( T *toRemove );
  Ref<T> &operator[]( unsigned int n );
  void empty();
  void delNotify( BaseRef *rm );
  void setRemoveOnDelete(int s);

};

#endif




