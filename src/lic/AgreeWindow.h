/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: AgreeWindow.h,v $
 *  $Date: 1999/08/27 15:30:36 $
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
 * $Log: AgreeWindow.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:30:36  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:16  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/25  20:23:01  lazy
 * Initial revision
 *
 */

// ----------------------------
// AgreeWindow.h
// Do not edit
// ----------------------------

#ifndef _AgreeWindow_H_
#define _AgreeWindow_H_

#include "AgreeWindow_base.h"

class AgreeWindow : public AgreeWindow_base {
protected:
  virtual void do_agree(Widget,XtPointer);
  virtual void do_not_agree(Widget,XtPointer);

  Boolean goOn;
public:
  AgreeWindow(Widget parent = NULL, ArgList args = NULL, Cardinal n = 0);
};


AgreeWindow *createAgreeWindow(Widget parent, ArgList args, Cardinal n);

#endif /* Don't add stuff after this #endif */
