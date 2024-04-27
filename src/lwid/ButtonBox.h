/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: ButtonBox.h,v $
 *  $Date: 1999/08/27 15:33:01 $
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
 * $Log: ButtonBox.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:33:01  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:54  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/24  17:32:09  lazy
 * Initial revision
 *
 */

#ifndef _ButtonBox_h
#define _ButtonBox_h

#ifdef __cplusplus
extern "C" {
#endif

#ifndef AA
#define AA(args) ()
#endif

#include <Xm/Xm.h>

#define XmNentryMarginWidth "entryMarginWidth"
#define XmNentryMarginHeight "entryMarginHeight"

#define XmCEntryMarginWidth "EntryMarginWidth"
#define XmCEntryMarginHeight "EntryMarginHeight"

extern WidgetClass xlButtonBoxWidgetClass;

typedef struct _XlButtonBoxClassRec *XtButtonBoxWidgetClass;
typedef struct _XlButtonBoxRec      *XlButtonBoxWidget;

extern Widget XlCreateButtonBox AA((Widget parent, char *name,
				   Arg *arglist, int num_args));

#ifdef __cplusplus
}
#endif
#endif	/* _ButtonBox_h */

