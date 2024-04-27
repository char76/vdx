/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: AgreeWindow.C,v $
 *  $Date: 1999/08/27 15:30:35 $
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
 * $Log: AgreeWindow.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:30:35  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:16  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/25  20:22:57  lazy
 * Initial revision
 *
 */

// ------------------------------ 
// AgreeWindow.C                      
// Do not edit
// ------------------------------

#include "AgreeWindow.h"
#include "lic.h"
#include "LApp.h"
#include "lic_hlp.h"
#include <Xm/Text.h>
#include <lac/HelpNode.h>

AgreeWindow *createAgreeWindow(Widget parent, ArgList args, Cardinal n)
{
  return new AgreeWindow(parent,args,n);
}


AgreeWindow::AgreeWindow(Widget wg, ArgList args, Cardinal n)
:AgreeWindow_base(wg,args,n) 
{
  char *msg;
  char *title;
  XEvent event;

  title = findHelpNode(HID_AGREEMENT)->getTitle();
  msg = findHelpNode(HID_AGREEMENT)->getText();

  XtVaSetValues(popupShell, XmNtitle, title, NULL);
  XmTextSetString(text_1, msg);
  open();

  goOn = FALSE;
  while( !goOn ) {       // Displatching all events
    XtAppNextEvent(context,&event);
    XtDispatchEvent(&event);
  }
  app->saveOptions();
}

void AgreeWindow::do_agree(Widget, XtPointer)
{
  goOn = TRUE;
}


void AgreeWindow::do_not_agree(Widget, XtPointer)
{
  exit(0);
}





