/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: CallbackMethod.C,v $
 *  $Date: 1999/08/27 15:29:16 $
 *  $Revision: 1.1.1.1.2.1 $
 *
 *  Copyright 1997, Dirk Laessig
 *  ALL RIGHTS RESERVED
 *  See the file Copyright for more information
 *
 *  Dirk Laessig
 *  Goettingstr. 5
 *  38106 Braunschweig
 *  Germany
 ****************************************************************/
/*
 * $Log: CallbackMethod.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:29:16  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:45  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/25  19:31:13  lazy
 * Initial revision
 *
 */

#include "CallbackMethod.h"

void
CallbackList::call()
{
  CallbackList &a(*this);

  for(unsigned int i=0; i<a.getSize(); i++)
    a[i]->call();
}
