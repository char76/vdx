/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: MsgCat.C,v $
 *  $Date: 1999/08/27 15:29:57 $
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
 * $Log: MsgCat.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:29:57  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:45  lazy
 * Imported to CVS
 *
 * Revision 1.1  1995/09/27  21:10:16  lazy
 * Initial revision
 *
 */

/* -----------------------------------
   MsgCat.C
   Implementation of classes: MsgCat

   (C) Dirk Laessig, 1994
   ----------------------------------- */

#include <lac/MsgCat.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>


// --------------------------------------------
//  MsgCat - Read the Msgfile with filename
// --------------------------------------------
MsgCat::MsgCat(Display *dpy )
{
  database = XrmGetDatabase(dpy);
}

// --------------------------------------
//  ~MsgCat() - the destroyer
// --------------------------------------
MsgCat::~MsgCat()
{
  
}

// --------------------------------------------
//  getMsg(..) - query a message
// --------------------------------------------

int MsgCat::getMsg( char *buffer, char *msg, ... )
{
  va_list ap;
  char *str;
  XrmValue value;

  if(XrmGetResource(database, msg, msg, &str, &value))
  va_start(ap, msg);                  // the message may have the same form
  vsprintf( buffer, (char*)value.addr, ap ); // like format string in printf()
  va_end(ap);

  return 0;
}

