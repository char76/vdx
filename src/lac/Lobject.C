/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: Lobject.C,v $
 *  $Date: 1999/08/27 15:29:42 $
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
 * $Log: Lobject.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:29:42  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:45  lazy
 * Imported to CVS
 *
 * Revision 1.1  1995/09/27  21:09:21  lazy
 * Initial revision
 *
 */

// -----------------------------------------
// Lobject.C
// Implementetion of classes:  Lobject
// (C) Dirk Laessig
// -----------------------------------------

#include <stdio.h>
#include <lac/Lobject.h>

// ---------------------------------
//       Virtual Destruktor
// ---------------------------------
Lobject::~Lobject()
{
  BaseRef *tmp, *last;
  // tell all referenzes, that it's object is deleted
  for(tmp=firstReferenz;   tmp; 
      last = tmp, tmp=tmp->next, last->delNotify() );
}


// ---------------------------------
//       addRelation
// ---------------------------------
void Lobject::addRelation( BaseRef *toAdd ) 
{
  if( toAdd->next ) {
    fprintf( stderr, "Fatal Error: Ref already in a list\n" );
    return;
  }
  // add relation to the linked list
  toAdd->next = firstReferenz;
  firstReferenz = toAdd;
}

// ------------------------------------------
//       delRelation
// ------------------------------------------

void Lobject::delRelation( BaseRef *removed )
{
  BaseRef *last, *tmp;
  
  if( !removed )
    return;
  tmp = firstReferenz;                // delete the first item
  if( tmp && (tmp == removed) ) {
    firstReferenz = tmp->next;
    tmp->next = NULL;
    return;
  }
  last = tmp;                         // delete next items
  tmp = tmp->next;
  while( tmp ) {
    if( tmp == removed ) {
      last->next = tmp->next;
      tmp->next = NULL;
      return;
    }
    last = tmp;
    tmp = tmp->next;
  }
}



