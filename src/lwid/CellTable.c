/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: CellTable.c,v $
 *  $Date: 1999/08/27 15:33:03 $
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
 * $Log: CellTable.c,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:33:03  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:54  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/24  17:32:37  lazy
 * Initial revision
 *
 */

/*#define DEBUG */

#ifdef DEBUG
#define DPRINTF(s) printf##s
#else
#define DPRINTF(s) 
#endif

#include "CellTableP.h"
#include <stdio.h>
#include <stdlib.h>

static void	ClassInitialize();
static void	Initialize(XlCellTableWidget request, 
			   XlCellTableWidget new, ArgList given_args, 
			   Cardinal *num_args);
static void	Destroy(XlCellTableWidget cellTable);
static void	ChangeManaged(XlCellTableWidget cellTable);
static void	InsertChild(Widget wg);
static void	Resize(XlCellTableWidget cellTable);
static void	Redisplay(XlCellTableWidget w, XEvent *event, Region region);
static XtGeometryResult GeometryManager(Widget w, 
					XtWidgetGeometry *request, 
					XtWidgetGeometry *reply);
static XtGeometryResult QueryGeometry(Widget w, 
				      XtWidgetGeometry *request, 
				      XtWidgetGeometry *reply);
static Boolean SetValues(XlCellTableWidget current, 
			  XlCellTableWidget request, XlCellTableWidget new);

#define CT_TABLE(w) (((XlCellTableWidget)(w))->cell_table.table)
#define CT_NUM_CHILD(w) (((XlCellTableWidget)(w))->composite.num_children)
#define CT_CHILD(w,n) (((XlCellTableWidget)(w))->composite.children[(n)])
#define CT_CONSTRAINTS(w) \
(&((XlCellTableConstraintPtr) (w)->core.constraints)->cell_table)
#define MAX(a,b) ((a)<(b) ? (b) : (a))


/*
 * getCell() returns the cell in the table
 */

static Cell *
getCell(CellTable *table, unsigned int x, unsigned int y)
{
  unsigned int xx, yy;
  CellRow *row;
  Cell *cell;

  for(yy = 0, row = table->firstRow; row; yy++, row = row->next) {
    if(yy == y) {
      for(xx = 0, cell = row->firstCell; cell; xx++, cell = cell->next) {
	if(xx == x) {
	  return cell;
	}
      }
    }
  }
  return NULL;
}

/*
 * getColumnSize()  returns the number of rows
 */

static unsigned int 
getColumnSize(CellTable *table)
{
  return table->columnSize;
}


/*
 * getRowSize()  return the number of columns
 */

static unsigned int 
getRowSize(CellTable *table)
{
  return table->rowSize;
}


static Cell *
newCell(CellTable *table) 
{
  Cell *ret;

  if(table->cellPool.firstBundle == NULL) {
    table->cellPool.current = table->cellPool.firstBundle = CT_NEW(CellBundle);
    table->cellPool.nextFree = 0;
  }

  ret = &table->cellPool.current->cells[table->cellPool.nextFree];
  table->cellPool.nextFree++;

  if(table->cellPool.nextFree == BUNDLE_NUM_CELLS) {
    table->cellPool.current = table->cellPool.current->next = 
      CT_NEW(CellBundle);
    table->cellPool.nextFree = 0;
  }

  return ret;
}

static void
freeCellBundles(CellTable *table)
{
  CellBundle *bundle, *next;
  for(bundle = table->cellPool.firstBundle; bundle;  bundle = next) {
    next = bundle->next;
    free(bundle);
  }
}

/*
 * newCellTable()  allocates a new table
 */

static CellTable *
newCellTable()
{
  CellTable *table;
  
  table = CT_NEW(CellTable);
  table->firstColumn = CT_NEW(CellColumn);
  table->firstRow = CT_NEW(CellRow);
  table->firstRow->firstCell = newCell(table);
  table->firstColumn->firstCell = table->firstRow->firstCell;
  table->firstRow->firstCell->column = table->firstColumn;
  table->firstRow->firstCell->row = table->firstRow;
  table->lastRow = table->firstRow;
  table->lastColumn = table->firstColumn;
  table->rowSize = 1;
  table->columnSize = 1;
  return table;
}


/*
 * freeCellTable()  frees the table
 */

static void
freeCellTable(CellTable *table)
{
  CellColumn *column, *nextColumn;
  CellRow *row, *nextRow;

  for(row = table->firstRow; row; row = nextRow) {
    nextRow = row->next;
    free(row);
  }
  for(column = table->firstColumn; column; column = nextColumn) {
    nextColumn = column->next;
    free(column);
  }
  freeCellBundles(table);
  free(table);
}

/*
 * appendColumn()  resize the table and adds a new column
 */

static void
appendColumn(CellTable *table)
{
  CellColumn *column, *lastColumn;
  Cell *lastColumnCell, *cell, *saveCell;
  
  /* find the last column */
  lastColumn = table->lastColumn; 

  column = CT_NEW(CellColumn);
  table->lastColumn = lastColumn->next = column;
  table->rowSize++;

  column->firstCell = saveCell = cell = newCell(table);
  cell->column = column;
  cell->row = lastColumn->firstCell->row;
  lastColumn->firstCell->next = cell;
  
  for(lastColumnCell = lastColumn->firstCell->nextInColumn;
      lastColumnCell;    
      lastColumnCell = lastColumnCell->nextInColumn) {
    cell = lastColumnCell->next = newCell(table);
    cell->column = column;
    cell->row = lastColumnCell->row;
    saveCell->nextInColumn = cell;
    saveCell = cell;
  }
}


/*
 * appendRow()  resize the table and appends a new row
 */

static void
appendRow(CellTable *table)
{
  CellRow *row, *lastRow;
  Cell *cell, *aNewCell, *saveCell;
  
  /* find the last row */
  lastRow = table->lastRow; 

  row = CT_NEW(CellRow);
  table->lastRow = lastRow->next = row;
  table->columnSize++;

  row->firstCell = aNewCell = newCell(table);
  aNewCell->row = row;
  aNewCell->column = lastRow->firstCell->column;
  lastRow->firstCell->nextInColumn = aNewCell;

  for(cell = lastRow->firstCell->next; cell; cell = cell->next) {
    saveCell = aNewCell;
    aNewCell = newCell(table);
    saveCell->next = aNewCell;
    aNewCell->row = row;
    aNewCell->column = cell->column;
    cell->nextInColumn = aNewCell;
  }
}

/*
 * setWidget()  sets the widget and calculates the geometry of column and row
 */

static void
setWidget(Cell *cell, Widget w)
{
  cell->widget = w;
  
  CT_CONSTRAINTS(w)->cell = cell;

  if(CT_CELL_WIDTH(cell) < w->core.width)
    CT_CELL_WIDTH(cell) = w->core.width;
  if(CT_CELL_HEIGHT(cell) < w->core.height)
    CT_CELL_HEIGHT(cell) = w->core.height;
  cell->requested_width = w->core.width;
  cell->requested_height = w->core.height;
}


/*
 * calculateCellPosition()  calculate the x and y of every cell in the table
 */

static void
calculateCellPositions(XlCellTableWidget wg, CellTable *table)
{
  CellRow *row;
  CellColumn *column;
  Position x, y;
  
  x = wg->cell_table.margin_height;
  y = wg->cell_table.margin_width;

  CT_FOREACH(row, table->firstRow) {
    row->y = y;
    y += row->height + wg->cell_table.vertical_spacing;
  }

  CT_FOREACH(column, table->firstColumn) {
    column->x = x;
    x += column->width + wg->cell_table.horizontal_spacing;
  }

}

/*
 * calculatesRequestedGeometry() 
 *
 * calcualtes the geometry of the table depending on the requested widget size
 */

static void 
calculateRequestedGeometry(XlCellTableWidget wg, CellTable *table)
{
  CellColumn *column;
  CellRow *row;
  Cell *cell;

  for(column = table->firstColumn; column; column = column->next)
    column->requested_width = 0;

  for(row = table->firstRow; row; row = row->next) {
    row->requested_height = 0;
    for(cell = row->firstCell; cell; cell = cell->next) {
      row->requested_height = 
	MAX(row->requested_height, cell->requested_height);
      cell->column->requested_width = 
	MAX(cell->column->requested_width, cell->requested_width);
    }
  }
  table->requested_width = wg->cell_table.margin_width;
  table->requested_height = wg->cell_table.margin_height;

  for(column = table->firstColumn; column->next; column = column->next)
    table->requested_width += column->width+wg->cell_table.horizontal_spacing;
  table->requested_width += column->width+wg->cell_table.margin_width;
  
  for(row = table->firstRow; row->next; row = row->next)
    table->requested_height += row->height+wg->cell_table.vertical_spacing;
  table->requested_height += row->height+wg->cell_table.margin_height;
  
}

/*
 * takeRequestedGeometry()  copy requested geometry to desired geometry
 */

static void
takeRequestedGeometry(XlCellTableWidget wg)
{
  CellTable *table;
  CellColumn *column;
  CellRow *row;
  
  table = CT_TABLE(wg);
  
  for(column = table->firstColumn; column; column = column->next)
    column->width = column->requested_width;
  for(row = table->firstRow; row; row = row->next)
    row->height = row->requested_height;
}

/*
 * getXOfWidget()  returns the x value of a cell
 */

static Position
getXOfWidget(Cell *cell)
{
  switch(CT_CONSTRAINTS(cell->widget)->horizontal_alignment) {
  case XmCELL_ALIGNMENT_BEGINNING:
  case XmCELL_ALIGNMENT_JUSTIFY:
    return cell->column->x;
  case XmCELL_ALIGNMENT_END:
    return cell->column->x +(cell->column->width - cell->widget->core.width);
  case XmCELL_ALIGNMENT_CENTER:
    return cell->column->x +(cell->column->width - cell->widget->core.width)/2;
  }  
  return cell->column->x;
}


/*
 * getYOfWidget()  returns the y value of a cell
 */

static Position
getYOfWidget(Cell *cell)
{
  switch(CT_CONSTRAINTS(cell->widget)->vertical_alignment) {
  case XmCELL_ALIGNMENT_BEGINNING:
  case XmCELL_ALIGNMENT_JUSTIFY:
    return cell->row->y;
  case XmCELL_ALIGNMENT_END:
    return cell->row->y + (cell->row->height - cell->widget->core.height);
  case XmCELL_ALIGNMENT_CENTER:
    return cell->row->y + (cell->row->height - cell->widget->core.height)/2;
  }  
  return cell->row->y;
}

/*
 * getTableWidth()  returns the desired width of the table
 */

static Dimension
getTableWidth(XlCellTableWidget wg, CellTable *table)
{
  CellColumn *column;
  for(column = table->firstColumn; column->next; column = column->next);
  return column->x + column->width + wg->cell_table.margin_width;
}

/*
 * getTableHeight()  returns the desired height of the table
 */

static Dimension
getTableHeight(XlCellTableWidget wg, CellTable *table)
{
  CellRow *row;
  for(row = table->firstRow; row->next; row = row->next);
  return row->y + row->height + wg->cell_table.margin_height;
}

/*
 * alignWidgets()  set the geometry for every widget
 */

static void
alignWidgets(CellTable *table)
{
  CellRow *row;
  Cell *cell;
  Dimension width, height;
  Boolean needResize;

  CT_FOREACH(row, table->firstRow) {
    CT_FOREACH(cell, row->firstCell) {
      if(cell->widget) {
	if(cell->widget->core.x != getXOfWidget(cell) ||
	   cell->widget->core.y != getYOfWidget(cell))
	  XtMoveWidget(cell->widget, getXOfWidget(cell), getYOfWidget(cell));
	
	needResize = FALSE;
	if(CT_CONSTRAINTS(cell->widget)->vertical_alignment ==
	   XmCELL_ALIGNMENT_JUSTIFY) {
	  height = CT_CELL_HEIGHT(cell);
	  needResize = TRUE;
	} else {
	  height = cell->widget->core.height;
	}
	if(CT_CONSTRAINTS(cell->widget)->horizontal_alignment ==
	   XmCELL_ALIGNMENT_JUSTIFY) {
	  width = CT_CELL_WIDTH(cell);
	  needResize = TRUE;
	} else {
	  width = cell->widget->core.width;
	}
	if(needResize) {
	  XtResizeWidget(cell->widget, width, height, 
			 cell->widget->core.border_width);
	}
      }
    }
  }
}


/* 
 * printOut()  needed for debugging
 */

static void
printOut(CellTable *table)
{
  CellRow *row;
  Cell *cell;

  DPRINTF(("Row Size: %d\n", getRowSize(table)));
  DPRINTF(("Column Size: %d\n", getColumnSize(table)));
  
  CT_FOREACH(row, table->firstRow) {
    CT_FOREACH(cell, row->firstCell) {
      DPRINTF(("%s(%d,%d)\t", (cell->widget ? XtName(cell->widget) : "NULL"),
	     CT_CELL_WIDTH(cell), CT_CELL_HEIGHT(cell)));
    }
    DPRINTF(("\n"));
  }
}


/*
 * resizeRowColumn()  
 *
 * depending on desired size and parent requested size, we have to resize
 * the resize_row and resize_column
 */

void
resizeRowColumn(XlCellTableWidget cellTable, 
		Dimension new_width, Dimension new_height)
{
  int diff_width, diff_height;

  diff_width = new_width - getTableWidth(cellTable, CT_TABLE(cellTable));
  diff_height = new_height - getTableHeight(cellTable, CT_TABLE(cellTable));

  if(diff_width != 0) {
    CellColumn *column;
    unsigned int xx;
    if(cellTable->cell_table.resize_column == XmCELL_UNDEFINED) {
      for(column = CT_TABLE(cellTable)->firstColumn; column->next; 
	  column = column->next);    /* find last column */
    } else {
      for(column = CT_TABLE(cellTable)->firstColumn, xx = 0; 
	  column && xx != cellTable->cell_table.resize_column; 
	  column = column->next, xx++);    /* find right column */
    }
    if(column) {
      column->width += (column->width+diff_width > 0) 
	? diff_width : -column->width+1;  
    }
  }
  if(diff_height != 0) {
    CellRow *row;
    unsigned int xx;
    if(cellTable->cell_table.resize_row == XmCELL_UNDEFINED) {
      for(row = CT_TABLE(cellTable)->firstRow; row->next; 
	  row = row->next);    /* find last Row */
    } else {
      for(row = CT_TABLE(cellTable)->firstRow, xx = 0; 
	  row && xx != cellTable->cell_table.resize_row; 
	  row = row->next, xx++);    /* find right Row */
    }
    if(row) {
      row->height += (row->height+diff_height > 0) 
	? diff_height : -row->height+1;  
    }
  }
}


/*
 * tryResize()
 *
 * try to resize the widget, if XmNwidth or XmNheight is set, take this size
 * instead of desired size, make a resizeRowColumn, if new size is other
 * then desired size
 */

static Boolean
tryResize(XlCellTableWidget wg)
{
  Dimension req_width, req_height, new_width, new_height;
  XtGeometryResult geo_res;
  Boolean need_table_resize;

  if(!XtIsManaged((Widget)wg)) {
    return TRUE;
  }

  need_table_resize = FALSE;
  
  if(wg->cell_table.old_width != 0) {
    req_width = wg->cell_table.old_width;
    need_table_resize = TRUE;
    DPRINTF(("%s: req_width = old_width\n", XtName((Widget)wg)));
  } else {
    req_width = getTableWidth(wg, CT_TABLE(wg));
  }
  if(wg->cell_table.old_height != 0) {
    req_height = wg->cell_table.old_height;
    need_table_resize = TRUE;
    DPRINTF(("%s: req_height = old_height\n", XtName((Widget)wg)));
  } else {
    req_height = getTableHeight(wg, CT_TABLE(wg));
  }
  geo_res = XtMakeResizeRequest((Widget)wg, 
				req_width, req_height,
				&new_width, &new_height);

  DPRINTF(("%s: geo_res: %d (%d %d)\n", XtName((Widget)wg),
	   geo_res, new_width, new_height));

  switch(geo_res) {
  case XtGeometryAlmost:
    req_width = new_width;
    req_height = new_height;
    need_table_resize = TRUE;
    XtResizeWidget((Widget)wg, req_width, req_height, 
		   wg->core.border_width);
    break;
  case XtGeometryYes:                   /* if he says yes, we take it */
    /*
    if(!XtIsRealized((Widget)wg)))
        XtResizeWidget((Widget)wg, req_width, req_height, 
                       wg->core.border_width);
    */
    break;
  case XtGeometryNo:
    req_width = wg->core.width;
    req_height = wg->core.height;
    need_table_resize = TRUE;
    break;
  default:
    break;
  }
  if(need_table_resize) {
    resizeRowColumn(wg, req_width, req_height);
    calculateCellPositions(wg, CT_TABLE(wg));
    alignWidgets(CT_TABLE(wg));
    return TRUE;
  }
  return FALSE;
}


/*
 * layout()
 *
 * take a widget and put it into the table, if needed
 * call other functions to complete the layout
 */

static void 
layout(XlCellTableWidget w)
{
  Cardinal i;
  Widget c;
  int cell_row, cell_column;
  Cell *cell;

  for(i = 0; i<CT_NUM_CHILD(w); i++) {
    c = CT_CHILD(w, i);
    cell_row = CT_CONSTRAINTS(c)->cell_row;
    cell_column = CT_CONSTRAINTS(c)->cell_column;
    if(!CT_CONSTRAINTS(c)->cell) {
      if(cell_row != XmCELL_UNDEFINED) {
	if(cell_column != XmCELL_UNDEFINED) {
	  while(cell_row >= getColumnSize(CT_TABLE(w)))
	    appendRow(CT_TABLE(w));
	  while(cell_column >= getRowSize(CT_TABLE(w)))
	    appendColumn(CT_TABLE(w));
	  cell = getCell(CT_TABLE(w), cell_column, cell_row);
	  setWidget(cell, c);
	}
      }
    }
  }
  calculateCellPositions(w, CT_TABLE(w));
  if(!tryResize(w))
    alignWidgets(CT_TABLE(w));
}


/*
 * childDestroyed()
 */
static void
childDestroyed(Widget child, XtPointer clientData, XtPointer callData)
{
  if(CT_CONSTRAINTS(child)->cell)
    CT_CONSTRAINTS(child)->cell->widget = NULL;
  
}

/* 
 * XlCellTableWidget resources 
 */

#define offset(field) XtOffset(XlCellTableWidget, field)
static XtResource resources[] = {
    {XmNmarginWidth, XmCMarginWidth, XmRHorizontalDimension, 
	 sizeof(Dimension), offset(cell_table.margin_width),
	 XmRImmediate, (XtPointer)5},
    {XmNmarginHeight, XmCMarginHeight, XmRVerticalDimension, 
	 sizeof(Dimension), offset(cell_table.margin_height),
	 XmRImmediate, (XtPointer)5},

    {XmNhorizontalSpacing, XmCHorizontalSpacing, XmRHorizontalDimension, 
	 sizeof(Dimension), offset(cell_table.horizontal_spacing),
	 XmRImmediate, (XtPointer)5},
    {XmNverticalSpacing, XmCVerticalSpacing, XmRVerticalDimension, 
	 sizeof(Dimension), offset(cell_table.vertical_spacing),
	 XmRImmediate, (XtPointer)5},

    {XmNresizeRow, XmCResizeRow, XmRInt, 
	 sizeof(int), offset(cell_table.resize_row),
	 XmRImmediate, (XtPointer)XmCELL_UNDEFINED},
    {XmNresizeColumn, XmCResizeColumn, XmRInt, 
	 sizeof(int), offset(cell_table.resize_column),
	 XmRImmediate, (XtPointer)XmCELL_UNDEFINED},

};
#undef offset

/* 
 * XlCellTableWidget constraint_resources 
 */

#define offset(field) XtOffset(XlCellTableConstraintPtr, field)
static XtResource constraint_resources[] = {
    {XmNcellRow, XmCCellRow, XmRInt, 
	 sizeof(int), offset(cell_table.cell_row),
	 XmRImmediate, (XtPointer)XmCELL_UNDEFINED},
    {XmNcellColumn, XmCCellColumn, XmRInt, 
	 sizeof(int), offset(cell_table.cell_column),
	 XmRImmediate, (XtPointer)XmCELL_UNDEFINED},

    {XmNhorizontalAlignment, XmCHorizontalAlignment, XmRCellTableAlignment, 
	 sizeof(CellTableAlignment), offset(cell_table.horizontal_alignment),
	 XmRImmediate, (XtPointer)XmCELL_ALIGNMENT_JUSTIFY},
    {XmNverticalAlignment, XmCVerticalAlignment, XmRCellTableAlignment, 
	 sizeof(CellTableAlignment), offset(cell_table.vertical_alignment),
	 XmRImmediate, (XtPointer)XmCELL_ALIGNMENT_JUSTIFY},
};
#undef offset


/*
 * Define Class Record.
 */

XlCellTableClassRec xlCellTableClassRec =
{
    {		/* core_class fields      */
    (WidgetClass)&(xmManagerClassRec),		/* superclass         */    
    (String)"XlCellTable",			/* class_name         */    
    (Cardinal)sizeof(XlCellTableRec),		/* widget_size        */    
    (XtProc)ClassInitialize,			/* class_initialize   */    
    (XtWidgetClassProc)NULL,			/* class_part_init    */    
    (XtEnum)FALSE,				/* class_inited       */    
    (XtInitProc)Initialize,			/* initialize         */    
    (XtArgsProc)NULL,				/* initialize_hook    */    
    (XtRealizeProc)XtInheritRealize,		/* realize            */    
    (XtActionList)NULL,         		/* actions	       */    
    (Cardinal)0,                            	/* num_actions        */    
    (XtResourceList)resources,			/* resources          */    
    (Cardinal)XtNumber(resources),		/* num_resources      */    
    (XrmClass)NULLQUARK,			/* xrm_class          */    
    (Boolean)TRUE,				/* compress_motion    */    
    (XtEnum)XtExposeCompressMaximal,		/* compress_exposure  */    
    (Boolean)TRUE,				/* compress_enterleave*/    
    (Boolean)FALSE,				/* visible_interest   */    
    (XtWidgetProc)Destroy,			/* destroy            */    
    (XtWidgetProc)Resize,			/* resize             */    
    (XtExposeProc)Redisplay,			/* expose             */    
    (XtSetValuesFunc)SetValues,			/* set_values         */    
    (XtArgsFunc)NULL,				/* set values hook    */    
    (XtAlmostProc)XtInheritSetValuesAlmost,	/* set values almost  */    
    (XtArgsProc)NULL,				/* get values hook    */    
    (XtAcceptFocusProc)NULL,			/* accept_focus       */    
    (XtVersionType)XtVersion,			/* Version            */    
    (XtPointer)NULL,				/* PRIVATE cb list    */
    (String)XtInheritTranslations,		/* tm_table           */
    (XtGeometryHandler)QueryGeometry,    	/* query_geom         */
    (XtStringProc)XtInheritDisplayAccelerator,	/* display_accelerator*/
    (XtPointer)NULL     			/* extension	      */
    },
    {		/* composite_class fields */
    (XtGeometryHandler)GeometryManager,		/* geometry_manager   */     
    (XtWidgetProc)ChangeManaged,	        /* change_managed     */     
    (XtWidgetProc)InsertChild,		/* insert_child	      */     
    (XtWidgetProc)XtInheritDeleteChild,		/* delete_child	      */     
    (XtPointer)NULL				/* extension	      */     
    },
    {		/* constraint_class fields */
    (XtResourceList)constraint_resources,	/* resources	      */     
    (Cardinal)XtNumber(constraint_resources),	/* num_resources      */     
    (Cardinal)sizeof(XlCellTableConstraintRec),	/* constraint_size    */     
    (XtInitProc)NULL,           		/* initialize	      */     
    (XtWidgetProc)NULL,				/* destroy	      */     
    (XtSetValuesFunc)NULL,			/* set_values	      */     
    (XtPointer)NULL				/* extension          */     
    },
    {		/* manager class     */
    (String)XtInheritTranslations,		/* translations       */     
    (XmSyntheticResource*)NULL,	                /* syn resources      */     
    (int)0,                     		/* num syn_resources  */     
    (XmSyntheticResource*)NULL,			/* get_cont_resources */     
    (int)0,					/* num_get_cont_resources */ 
    (XmParentProcessProc)XmInheritParentProcess,/* parent_process     */     
    (XtPointer)NULL				/* extension          */     
    },
    {		/* cellTable_box_class fields */     
    (Boolean)0,
    }
};

WidgetClass xlCellTableWidgetClass = (WidgetClass)&xlCellTableClassRec;


static void
ClassInitialize()
{
}


static void
Initialize(request, new, given_args, num_args)
XlCellTableWidget request;
XlCellTableWidget new;
ArgList given_args;
Cardinal *num_args;
{
  CT_TABLE(new) = newCellTable();
  new->cell_table.old_width = request->core.width;
  new->cell_table.old_height = request->core.height;
}


static void 
Destroy(cellTable)
XlCellTableWidget cellTable;
{
  freeCellTable(CT_TABLE(cellTable));
}


static void 
ChangeManaged(cellTable)
XlCellTableWidget cellTable;
{
  DPRINTF(("change managed (%s)\n", XtName((Widget)cellTable)));

  layout(cellTable);
  printOut(CT_TABLE(cellTable));
}

static void 
InsertChild(wg)
     Widget wg;
{
  XlCellTableWidget cellTable;
  
  DPRINTF(("insert child (%s)\n", XtName(wg)));

  cellTable = (XlCellTableWidget)XtParent(wg);

  CT_CONSTRAINTS(wg)->cell = NULL;     /* set this to zero */
  XtAddCallback(wg, XmNdestroyCallback, childDestroyed, NULL);

  if(((CompositeWidgetClass)compositeWidgetClass)
     ->composite_class.insert_child)
    ((CompositeWidgetClass)compositeWidgetClass)
      ->composite_class.insert_child(wg);

}


/*
 * Resize function called by toolkit.  The size of our cellTable
 * has already been changed. 
 */
static void
Resize(cellTable)
XlCellTableWidget cellTable;
{
  Dimension req_width, req_height;

  DPRINTF(("%s: resize\n", XtName((Widget)cellTable)));
  
  req_width = getTableWidth(cellTable, CT_TABLE(cellTable));
  req_height = getTableHeight(cellTable, CT_TABLE(cellTable));

  /* if widgets has a desired size, resize the desired size */
  if(cellTable->cell_table.old_width != 0)
    cellTable->cell_table.old_width = cellTable->core.width;
  if(cellTable->cell_table.old_height != 0)
    cellTable->cell_table.old_height = cellTable->core.height;

  DPRINTF(("width: %d -> %d, height: %d -> %d\n", 
	   req_width, cellTable->core.width,
	   req_height, cellTable->core.height));

  resizeRowColumn(cellTable, cellTable->core.width, cellTable->core.height);

  calculateCellPositions(cellTable, CT_TABLE(cellTable));
  alignWidgets(CT_TABLE(cellTable));
}


/*
 * nothing to do
 */
static void
Redisplay(w, event, region)
XlCellTableWidget w;
XEvent *event;
Region region;
{
}


static XtGeometryResult
GeometryManager(w, request, reply)
Widget w; /* child */
XtWidgetGeometry *request;
XtWidgetGeometry *reply;
{
  Dimension old_width, old_height;
  Cell *cell;
  Boolean need_resize;
  XlCellTableWidget cellTable;

  cellTable = (XlCellTableWidget) XtParent(w);

  DPRINTF(("geometry mananger (%s) current (%d,%d) request(%d,%d)\n", 
	   XtName(w), w->core.width, w->core.height, 
	   request->width, request->height));

  old_width = w->core.width;
  old_height = w->core.height;

  cell = CT_CONSTRAINTS(w)->cell;

  /* Set the size to the requested size */
  if (request->request_mode & CWWidth)
    w->core.width = request->width;
  if (request->request_mode & CWHeight)
    w->core.height = request->height;

  if (w->core.width != old_width || w->core.height != old_height)
    need_resize = TRUE;

  if(cell == NULL) {
    if(need_resize) {
      XtResizeWidget(w, w->core.width, w->core.height, w->core.border_width);
      return XtGeometryYes;
    } else {
      return XtGeometryNo;
    }
  }

  cell->requested_width = w->core.width;
  cell->requested_height = w->core.height;

  calculateRequestedGeometry(cellTable, CT_TABLE(cellTable));
  takeRequestedGeometry(cellTable);
  calculateCellPositions(cellTable, CT_TABLE(cellTable));
  if(!tryResize(cellTable))
    alignWidgets(CT_TABLE(cellTable));
  return(XtGeometryYes);
}


/* 
 * should be implemented
 */


static XtGeometryResult
QueryGeometry(w, request, reply)
     Widget w; 
     XtWidgetGeometry *request;
     XtWidgetGeometry *reply;
{
  DPRINTF(("request: (%d,%d) %d, %d\n", 
	 request->x, request->y, request->width, request->height));
  return(XtGeometryYes);
}


/*
 * SetValues() routine for CellTableBox widget. 
 */
static Boolean
SetValues(current, request, new)
XlCellTableWidget current;
XlCellTableWidget request;
XlCellTableWidget new;
{
  /* Cell table wants a size */
  if(current->core.width != request->core.width)
    new->cell_table.old_width = request->core.width;

  if(current->core.height != request->core.height)
    new->cell_table.old_height = request->core.height;

  return(FALSE);
}

/*
 * Routines which manipulate the CellTable.  These are external
 * for use by users of our widget.
 */
Widget 
XlCreateCellTable(parent, name, arglist, num_args)
Widget parent;
char *name;
Arg *arglist;
int num_args;
{
    return(XtCreateWidget(name, xlCellTableWidgetClass, parent,
			  arglist, num_args));
}

