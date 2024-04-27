/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: CallbackMethod.h,v $
 *  $Date: 1999/08/27 15:29:18 $
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
 * $Log: CallbackMethod.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:29:18  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:46  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/25  19:31:17  lazy
 * Initial revision
 *
 */

#ifndef _CALLBACK_METHOD_H
#define _CALLBACK_METHOD_H

#include <lac/Lobject.h>
#include <lac/RefArray.h>

class CallbackMethod : public Lobject {
public:
  virtual void call() = 0;
};

class CallbackList : public RefArray<CallbackMethod> {
public:
  void call();
};

#endif
