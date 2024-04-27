/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: Ref.h,v $
 *  $Date: 1999/08/27 15:30:07 $
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
 * $Log: Ref.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:30:07  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:45  lazy
 * Imported to CVS
 *
 * Revision 1.1  1995/09/27  21:11:53  lazy
 * Initial revision
 *
 */

// ---------------------------------------
// Ref.h
// Implementation of template Ref
// (C) Dirk Laessig
// ---------------------------------------

#ifndef _REF_H_
#define _REF_H_

#include <lac/Lobject.h>

// Use Ref for save pointers
// Decleration    Ref<X> ref : ref is a pointer of type X
// type X must be a derived class of Lobject
// use operators:  =         (assignment)
//                 ->        (dereferenz)
//                 isNil()   (is ref valid)
// You can tell ref, if the referenzed object is dead,
// that a parent (Lobject) should be notified.
// Ref is derived class of BaseRef

template <class T>
class Ref : public BaseRef {
private:
  T *pointer;
  Lobject *parent;

protected:
  void delNotify();

public:

  // ptr - initial value 
  // p   - parent, that is notified
  Ref( T *ptr = NULL, Lobject *p = NULL );

  ~Ref();
  T* operator->();
  Ref& operator=(T *ptr);
  Ref& operator=(Ref &ref);
  int operator==(T *toCmp);
  int operator==(Ref &toCmp);
  int isNil();
  operator T*();
  void Delete();
};

#endif


