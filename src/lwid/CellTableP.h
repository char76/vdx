/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: CellTableP.h,v $
 *  $Date: 1999/08/27 15:33:06 $
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
 * $Log: CellTableP.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:33:06  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:54  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/24  17:32:46  lazy
 * Initial revision
 *
 */

#ifndef _CellTableP_h
#define _CellTableP_h

#include <X11/IntrinsicP.h>
#include <Xm/ManagerP.h>
#include "CellTable.h"


/*
 * Datatypes for internal table handling
 */

#define CT_FOREACH(p, l) for(p = l; p; p = p->next)
#define CT_CELL_WIDTH(cell) cell->column->width
#define CT_CELL_HEIGHT(cell) cell->row->height
#define CT_CELL_WIDGET(cell) cell->widget
#define CT_NEW(T) (T*)calloc(1, sizeof(T))

struct _CellRow;
struct _CellColumn;
struct _CellPool;

typedef struct _Cell {
  Widget widget;             /* assigned widget */
  Dimension requested_width;
  Dimension requested_height;
  struct _Cell *next;
  struct _CellRow *row;
  struct _CellColumn *column;

  /* for optimizing */
  struct _Cell *nextInColumn;
} Cell;

typedef struct _CellRow {
  Cell *firstCell;
  Dimension height;
  Dimension requested_height;
  Position y;
  struct _CellRow *next;
} CellRow;

typedef struct _CellColumn {
  Dimension width;
  Dimension requested_width;
  Position x;
  struct _CellColumn *next;

  /* for optimizing */
  Cell *firstCell;
} CellColumn;

/*
 * for optimizing the cell creation
 */
#define BUNDLE_NUM_CELLS 16

typedef struct _CellBundle {
  struct _CellBundle *next;
  Cell cells[BUNDLE_NUM_CELLS];
} CellBundle;

typedef struct _CellPool {
  CellBundle *firstBundle;
  Cardinal nextFree;
  CellBundle *current;
} CellPool;

/*
 * the table
 */

typedef struct _CellTable {
  CellRow *firstRow;
  CellColumn *firstColumn;
  Dimension requested_width;
  Dimension requested_height;

  /* for optimizing */
  CellRow *lastRow;
  CellColumn *lastColumn;
  int rowSize;
  int columnSize;
  CellPool cellPool;
} CellTable;




/* 
 * Class Records
 */
typedef struct {
    Boolean junk;  /* Need something */
} XlCellTableClassPart;

typedef struct _XlCellTableClassRec {
    CoreClassPart	    core_class;
    CompositeClassPart	    composite_class;
    ConstraintClassPart	    constraint_class;
    XmManagerClassPart	    manager_class;
    XlCellTableClassPart    cell_table_class;
} XlCellTableClassRec;

extern XlCellTableClassRec xlCellTableClassRec;


/*
 * Instance Record.
 */
typedef struct _XlCellTablePart {
  Dimension margin_width;
  Dimension margin_height;
  Dimension horizontal_spacing;
  Dimension vertical_spacing;
  int resize_row;
  int resize_column;
  CellTable *table;
  Dimension old_width;
  Dimension old_height;
} XlCellTablePart;


typedef struct _XlCellTableRec {
    CorePart		core;
    CompositePart	composite;
    ConstraintPart	constraint;
    XmManagerPart	manager;
    XlCellTablePart	cell_table;
} XlCellTableRec;


/*
 * Contraint Record
 */

typedef struct _XlCellTableConstraintPart
{
  int cell_row;
  int cell_column;
  CellTableAlignment horizontal_alignment;
  CellTableAlignment vertical_alignment;
  Cell *cell;
} XlCellTableConstraintPart, * XlCellTableConstraint;

typedef struct _XlCellTableConstraintRec
{
   XmManagerConstraintPart manager;
   XlCellTableConstraintPart   cell_table;
} XlCellTableConstraintRec, * XlCellTableConstraintPtr;


#endif /* _CellTableP_h */
