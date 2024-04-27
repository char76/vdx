/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: WidgetRef.C,v $
 *  $Date: 1999/08/27 15:30:28 $
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
 * $Log: WidgetRef.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:30:28  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:45  lazy
 * Imported to CVS
 *
 * Revision 1.2  1997/07/25  20:04:58  lazy
 * *** empty log message ***
 *
 * Revision 1.1  1995/09/27  21:14:58  lazy
 * Initial revision
 *
 */

#include <lac/WidgetRef.h>

WidgetRef &WidgetRef::operator=(Widget w)
{
  if( wg ) {
    XtRemoveCallback(wg,"destroyCallback",destroyCallback,this);
  }
  wg = w;
  if( wg ) {
    XtAddCallback(wg,"destroyCallback",destroyCallback,this);
  }
  return *this;
}

void WidgetRef::destroyCallback(Widget ,XtPointer self,XtPointer )
{
  ((WidgetRef*)self)->wg = NULL;
}

WidgetRef::~WidgetRef()
{
  if( wg ) {
    XtRemoveCallback(wg,"destroyCallback",destroyCallback,this);
  }
}



