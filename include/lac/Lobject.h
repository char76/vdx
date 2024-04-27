/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: Lobject.h,v $
 *  $Date: 1999/08/27 15:29:43 $
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
 * $Log: Lobject.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:29:43  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:45  lazy
 * Imported to CVS
 *
 * Revision 1.2  1997/07/25  20:04:58  lazy
 * *** empty log message ***
 *
 * Revision 1.1  1995/09/27  21:09:31  lazy
 * Initial revision
 *
 */

// -----------------------------------------
// Lobject.h
// Definition of classes : Lobject
//                         BaseRef
// (C) Dirk Laessig
// -----------------------------------------

#ifndef _LOBJECT_H_
#define _LOBJECT_H_

extern "C" {
#include <stdio.h>
}
class BaseRef;

// ################################################
//    ---------       Lobject         ----------
//  this is a base class for objects which uses
//  Ref-template
// ################################################

class Lobject {
private:
  BaseRef *firstReferenz;         // pointer to a linked list
  
  // private methods - only used by BaseRef
  void addRelation( BaseRef *toAdd );   // add Item to linked list
  void delRelation( BaseRef *removed ); // remove item

public:
  Lobject() { firstReferenz = NULL; } 
  virtual ~Lobject();             // sending notify to referenz

  // overload this function to get a notify, if one of
  // the referenzes in this class is removed
  virtual void delNotify( BaseRef * ) {}

  friend class BaseRef;
};


// ################################################
//  ------------      BaseRef        -------------
//  Base class for Ref-template
// ################################################

class BaseRef {
protected:
  BaseRef *next;

  virtual void delNotify() = 0; // overloaded by Ref-template

  void addRelation( Lobject *ptr ) { if(ptr) ptr->addRelation( this ); }
  void delRelation( Lobject *ptr ) { if(ptr) ptr->delRelation( this ); }

public:
  BaseRef() { next=NULL; }
  virtual ~BaseRef() {};

friend class Lobject;        // access for private methods
};  

#endif /* DON'T ADD STUFF AFTER THIS #endif */


