/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: CellTable.h,v $
 *  $Date: 1999/08/27 15:33:04 $
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
 * $Log: CellTable.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:33:04  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:54  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/24  17:32:43  lazy
 * Initial revision
 *
 */

#ifndef _CellTable_h
#define _CellTable_h

#ifdef __cplusplus
extern "C" {
#endif
  
#include <Xm/Xm.h>

typedef enum {
  XmCELL_ALIGNMENT_BEGINNING,
  XmCELL_ALIGNMENT_CENTER,
  XmCELL_ALIGNMENT_END,
  XmCELL_ALIGNMENT_JUSTIFY
} CellTableAlignment;

#define XmCELL_UNDEFINED -1

#define XmCHorizontalSpacing "horizontalSpacing"
#define XmCVerticalSpacing "VerticalSpacing"
#define XmNresizeRow "resizeRow"
#define XmCResizeRow "ResizeRow"
#define XmNresizeColumn "resizeColumn"
#define XmCResizeColumn "ResizeColumn"
#define XmNcellRow "cellRow"
#define XmCCellRow "CellRow"
#define XmNcellColumn "cellColumn"
#define XmCCellColumn "CellColumn"
#define XmNhorizontalAlignment "horizontalAlignment"
#define XmCHorizontalAlignment "HorizontalAlignment"
#define XmRCellTableAlignment "CellTableAlignment"
#define XmNverticalAlignment "verticalAlignment"


extern WidgetClass xlCellTableWidgetClass;

typedef struct _XlCellTableClassRec *XlCellTableWidgetClass;
typedef struct _XlCellTableRec      *XlCellTableWidget;

extern Widget XlCreateCellTable(Widget parent, char *name,
				Arg *arglist, int num_args);

#ifdef __cplusplus
}
#endif
#endif	/* _CellTable_h */

