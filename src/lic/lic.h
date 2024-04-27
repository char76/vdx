/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: lic.h,v $
 *  $Date: 1999/08/27 15:32:33 $
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
 * $Log: lic.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:32:33  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:13  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/25  20:38:00  lazy
 * Initial revision
 *
 */

/* --------------------------------------
   lic.h
   generale header file
   (C) Dirk Laessig
   -------------------------------------- */


#ifndef _LIC_H_
#define _LIC_H_

#include "lic_msg.h"
#include "lic_hlp.h"

#include <lac/MsgCat.h>


// max number of widget allowed for writing

#define DEMO_MAX_WIDGETS 20

class MainWindow;

extern MsgCat *msgCat;
extern MainWindow *mainWindow;

#define FOREACH(i,a) for(unsigned int i=0; i<a.getSize(); i++)

#endif /* DON'T ADD STUFF AFTER THIS #endif */



