/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: ConModel.h,v $
 *  $Date: 1999/08/27 15:29:20 $
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
 * $Log: ConModel.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:29:20  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:45  lazy
 * Imported to CVS
 *
 * Revision 1.3  1998/02/10  01:03:33  lazy
 * Add empty() method.
 *
 * Revision 1.2  1997/07/25  20:04:58  lazy
 * *** empty log message ***
 *
 * Revision 1.1  1995/09/27  21:07:37  lazy
 * Initial revision
 *
 */

// -------------------------------------
// ConModel
//
// (C) Dirk Laessig
// -------------------------------------

#ifndef _CONMODEL_H_
#define _CONMODEL_H_

#include <lac/Model.h>

/* -----------------------------------------------------

                    ContainerBase

   ----------------------------------------------------- */

class ContainerBase: public Iconable {
public:
  virtual unsigned int getSize() = 0;
  virtual Iconable *at( unsigned int i ) = 0;

  virtual void cb_add( Iconable *toAdd ) = 0;

  // changes
  Boolean getChangedFlag() {
    if(Model::getChangedFlag())
      return TRUE;
    for(unsigned int i=0; i<getSize(); i++)
      if(at(i)->getChangedFlag())
	return TRUE;
    return FALSE;
  }
  void resetChangedFlag() {
    Model::resetChangedFlag();
    for(unsigned int i=0; i<getSize(); i++)
      at(i)->resetChangedFlag();
  }
};

/* -----------------------------------------------------
   
   Container
   
   ----------------------------------------------------- */


template <class T>
class Container : public ContainerBase {
private:
  class MyArray: public RefArray<T> {
  private:
    Container<T> *parent;
  public:
    MyArray(Container *p) { 
      parent=p; 
    }
    void delNotify( BaseRef *nowNil ) {
      RefArray<T>::delNotify( nowNil );
      parent->changed( CONTAINER_CHANGED );
    }
  };
  
  MyArray contents;
  
public:
  Container();
  void add( T *toAdd );
  void insert( T *toIns, T *before );
  void remove( T *toRemove );
  void empty();
  unsigned int getSize();
  T * operator[]( unsigned int i );
  
  Iconable *at( unsigned int i );
  void cb_add( Iconable *toAdd );
  
  char *getClassName();
};


#endif


