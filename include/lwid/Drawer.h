/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: Drawer.h,v $
 *  $Date: 1999/08/27 15:33:08 $
 *  $Revision: 1.2.2.1 $
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
 * $Log: Drawer.h,v $
 * Revision 1.2.2.1  1999/08/27 15:33:08  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.2  1998/06/06 18:32:32  lazy
 * ToggleButton -> ArrowButton, Label
 *
 * Revision 1.1.1.1  1998/04/24 23:45:54  lazy
 * Imported to CVS
 *
 * Revision 1.2  1998/03/30 19:10:34  lazy
 * *** empty log message ***
 *
 * Revision 1.1  1998/02/10  01:38:44  lazy
 * Initial revision
 *
 * Revision 1.1  1997/07/24  17:32:09  lazy
 * Initial revision
 *
 */

#ifndef _Drawer_h
#define _Drawer_h

#ifdef __cplusplus
extern "C" {
#endif

#ifndef AA
#define AA(args) ()
#endif

#include <Xm/Xm.h>

#define XmNexpandSize "expandSize"
#define XmNexpand     "expand"
#define XmNsashSize   "sashSize"

#define XmCExpandSize "ExpandSize"
#define XmCExpand     "Expand"
#define XmCSashSize   "SashSize"

extern WidgetClass xlDrawerWidgetClass;

typedef struct _XlDrawerClassRec *XtDrawerWidgetClass;
typedef struct _XlDrawerRec      *XlDrawerWidget;

extern Widget XlCreateDrawer(Widget parent, char *name,
			     Arg *arglist, int num_args);

extern void XlDrawerSetExpand(Widget drawer, Boolean expand);

#ifdef __cplusplus
}
#endif
#endif	/* _Drawer_h */

