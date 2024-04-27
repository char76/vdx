/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: WidgetRef.h,v $
 *  $Date: 1999/08/27 15:30:29 $
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
 * $Log: WidgetRef.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:30:29  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:45  lazy
 * Imported to CVS
 *
 * Revision 1.1  1995/09/27  21:15:11  lazy
 * Initial revision
 *
 */

#ifndef _WIDGETREF_H_
#define _WIDGETREF_H_

#include <X11/Intrinsic.h>

class WidgetRef {
private:
  static void destroyCallback(Widget,XtPointer,XtPointer);
protected:
  Widget wg;
public:
  WidgetRef() { wg=NULL; }
  virtual ~WidgetRef();
  WidgetRef& operator=(Widget wg);
  operator Widget(){ return wg; }
};

#endif
