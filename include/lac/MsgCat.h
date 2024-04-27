/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: MsgCat.h,v $
 *  $Date: 1999/08/27 15:29:59 $
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
 * $Log: MsgCat.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:29:59  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:45  lazy
 * Imported to CVS
 *
 * Revision 1.1  1995/09/27  21:11:06  lazy
 * Initial revision
 *
 */

/* ---------------------------------------

   MsgCat.h
   Definition of classes: MsgCat


   (C) Dirk Laessig, 1994
   --------------------------------------- */


#ifndef _MSGCAT_H_
#define _MSGCAT_H_

#include <lac/Lobject.h>
#include <X11/Intrinsic.h>

class MsgCat : public Lobject {
private:
  XrmDatabase database;

public:
  MsgCat(Display *);
  ~MsgCat();

  int getMsg( char *buffer, char *msgID, ... );

};

#endif /* DON'T ADD STUFF AFTER THIS #endif */
