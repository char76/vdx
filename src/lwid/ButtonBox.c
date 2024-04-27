/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: ButtonBox.c,v $
 *  $Date: 1999/08/27 15:32:59 $
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
 * $Log: ButtonBox.c,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:32:59  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:54  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/24  17:32:01  lazy
 * Initial revision
 *
 */

/*#define DEBUG */

#ifdef DEBUG
#define DPRINTF(s) printf##s
#else
#define DPRINTF(s) 
#endif

#include "ButtonBoxP.h"
#include <stdio.h>

static void	ClassInitialize AA(());
static void	Initialize AA((XlButtonBoxWidget request, 
			       XlButtonBoxWidget new, ArgList given_args, 
			       Cardinal *num_args));
static void	Destroy AA((XlButtonBoxWidget combo));
static void	ChangeManaged AA((XlButtonBoxWidget combo));
static void	InsertChild AA((Widget wg));
static void	Resize AA((XlButtonBoxWidget combo));
static void	Redisplay AA((XlButtonBoxWidget w, XEvent *event, 
			      Region region));
static XtGeometryResult GeometryManager AA((Widget w, 
					    XtWidgetGeometry *request, 
					    XtWidgetGeometry *reply));
static XtGeometryResult QueryGeometry AA((Widget w, 
					    XtWidgetGeometry *request, 
					    XtWidgetGeometry *reply));
static void	LayoutChildren AA((XlButtonBoxWidget combo));
static XtGeometryResult	SetButtonBoxSize AA((XlButtonBoxWidget combo));
static Boolean	SetValues AA((XlButtonBoxWidget current, 
			      XlButtonBoxWidget request, XlButtonBoxWidget new));

/*
 * XlButtonBoxWidget specific defines.
 */
#define BB_CHILD_N(n) (combo->composite.children[n])
#define BB_CHILD_NUM  (combo->composite.num_children)
#define BB_WIDTH(w)   ((w)->core.width)
#define BB_HEIGHT(w)   ((w)->core.height)

#define BB_SPACING(wg) (((XlButtonBoxWidget)(wg))->button_box.spacing)
#define BB_ORIENTATION(wg) (((XlButtonBoxWidget)(wg))->button_box.orientation)
#define BB_MARGIN_HEIGHT(wg) \
(((XlButtonBoxWidget)(wg))->button_box.entry_margin_height)
#define BB_MARGIN_WIDTH(wg) \
(((XlButtonBoxWidget)(wg))->button_box.entry_margin_width)

/* 
 * XlButtonBoxWidget resources 
 */
#define offset(field) XtOffset(XlButtonBoxWidget, field)
static XtResource resources[] = {
    {XmNorientation, XmCOrientation, XmROrientation, 
	 sizeof(Cardinal), offset(button_box.orientation),
	 XmRImmediate, (XtPointer)XmHORIZONTAL},
    {XmNspacing, XmCSpacing, XmRDimension, 
	 sizeof(Dimension), offset(button_box.spacing),
	 XmRImmediate, (XtPointer)10},
    {XmNentryMarginWidth, XmCEntryMarginWidth, XmRHorizontalDimension, 
	 sizeof(Dimension), offset(button_box.entry_margin_width),
	 XmRImmediate, (XtPointer)4},
    {XmNentryMarginHeight, XmCEntryMarginHeight, XmRVerticalDimension, 
	 sizeof(Dimension), offset(button_box.entry_margin_height),
	 XmRImmediate, (XtPointer)4},

};

#undef offset


/*
 * Define Class Record.
 */
XlButtonBoxClassRec xlButtonBoxClassRec =
{
    {		/* core_class fields      */
    (WidgetClass)&(xmManagerClassRec),		/* superclass         */    
    (String)"XlButtonBox",			/* class_name         */    
    (Cardinal)sizeof(XlButtonBoxRec),		/* widget_size        */    
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
    (XtResourceList)NULL,			/* resources	      */     
    (Cardinal)0,				/* num_resources      */     
    (Cardinal)0,				/* constraint_size    */     
    (XtInitProc)NULL,				/* initialize	      */     
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
    {		/* combo_box_class fields */     
    (Boolean)0,
    }
};

WidgetClass xlButtonBoxWidgetClass = (WidgetClass)&xlButtonBoxClassRec;

static void
ClassInitialize()
{
}

static void
Initialize(request, new, given_args, num_args)
XlButtonBoxWidget request;
XlButtonBoxWidget new;
ArgList given_args;
Cardinal *num_args;
{
}


static void 
Destroy(combo)
XlButtonBoxWidget combo;
{
}


static void 
ChangeManaged(combo)
XlButtonBoxWidget combo;
{
  DPRINTF(("change managed (%s)\n", XtName((Widget)combo)));
  if(XtIsRealized((Widget)combo))
    DPRINTF(("--> is realized\n"));
  if(XtGeometryNo != SetButtonBoxSize(combo)) {
    LayoutChildren(combo);
  } else {
    LayoutChildren(combo);
  }
}

static void 
InsertChild(wg)
     Widget wg;
{
  XlButtonBoxWidget combo;
  
  DPRINTF(("insert child (%s)\n", XtName(wg)));

  combo = (XlButtonBoxWidget)XtParent(wg);

  if(((CompositeWidgetClass)compositeWidgetClass)
     ->composite_class.insert_child)
    ((CompositeWidgetClass)compositeWidgetClass)
      ->composite_class.insert_child(wg);

  XtVaSetValues(wg,
		XmNmarginHeight, BB_MARGIN_HEIGHT(combo),
		XmNmarginWidth, BB_MARGIN_WIDTH(combo),
		NULL);
  
//  if(XtGeometryNo != SetButtonBoxSize(combo))
//    LayoutChildren(combo);
}


/*
 * Resize function called by toolkit.  The size of our combo-box
 * has already been changed.  That is why we must store 
 * old_width and old_height.
 */
static void
Resize(combo)
XlButtonBoxWidget combo;
{
  LayoutChildren(combo);
  DPRINTF(("resize: %d %d\n", BB_WIDTH((Widget)combo), BB_HEIGHT((Widget)combo)));
}


/*
 * Redisplay function called by toolkit. The widget didn't change size, 
 * so just redisplay the shadow.
 */
static void
Redisplay(w, event, region)
XlButtonBoxWidget w;
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
  XlButtonBoxWidget combo = (XlButtonBoxWidget)w->core.parent;
  Dimension old_width, old_height;

  DPRINTF(("geometry mananger (%s)\n", XtName(w)));

  old_width = w->core.width;
  old_height = w->core.height;

  /* Set the size to the requested size */
  if (request->request_mode & CWWidth)
    w->core.width = request->width;
  if (request->request_mode & CWHeight)
    w->core.height = request->height;

  if( XtGeometryNo != SetButtonBoxSize(combo))
    XtResizeWidget(w, w->core.width, w->core.height, w->core.border_width);
  else {
    w->core.width = old_width;    
    w->core.height = old_height;
    return XtGeometryNo;
  }
  LayoutChildren(combo);
  
  return(XtGeometryYes);
}

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


static XtGeometryResult
SetButtonBoxSize(combo)
     XlButtonBoxWidget combo;
{
  Dimension mw, mh, req_width, req_height, new_width, new_height;
  int i;
  XtGeometryResult geo_res;

  DPRINTF(("set button box size\n"));
  if(!XtIsManaged((Widget)combo)) {
    DPRINTF(("not managed\n"));
    return XtGeometryNo;
  }

  mw = mh = 0;
  for(i = 0; i < BB_CHILD_NUM ; i++) {
    mw = BB_WIDTH(BB_CHILD_N(i)) > mw ? BB_WIDTH(BB_CHILD_N(i)) : mw;
    mh = BB_HEIGHT(BB_CHILD_N(i)) > mh ? BB_HEIGHT(BB_CHILD_N(i)) : mh;
  }

  if(BB_ORIENTATION(combo) == XmHORIZONTAL) {
    req_width = mw*BB_CHILD_NUM + BB_SPACING(combo)*(BB_CHILD_NUM+1);
    req_height = mh + 2*BB_SPACING(combo);
  } else {
    req_width = mw + 2*BB_SPACING(combo);
    req_height = mh*BB_CHILD_NUM + BB_SPACING(combo)*(BB_CHILD_NUM+1);
  }

  if(BB_WIDTH((Widget)combo) == req_width &&
     BB_HEIGHT((Widget)combo) == req_height)
    return XtGeometryNo;

  geo_res = XtMakeResizeRequest((Widget)combo, 
				req_width, req_height,
				&new_width, &new_height);

  DPRINTF(("geo_res: %d (%d %d)\n",geo_res, req_width, req_height));

  switch(geo_res) {
  case XtGeometryAlmost:
    XtResizeWidget((Widget)combo, new_width, new_height, 
		   combo->core.border_width);
    break;
  case XtGeometryYes:                   /* if he says yes, we take it */
    XtResizeWidget((Widget)combo, req_width, req_height, 
		   combo->core.border_width);
    break;
  case XtGeometryNo:                   
    if(req_width < BB_WIDTH((Widget)combo) && 
       req_height < BB_HEIGHT((Widget)combo))
       return XtGeometryYes;
  default:
    break;
  }
  return geo_res;
}

static void
LayoutChildren(combo)
XlButtonBoxWidget combo;
{
  Dimension mw, mh, new_width, new_height;
  int i;

  DPRINTF(("layout\n"));

  mw = mh = 0;
  for(i = 0; i < BB_CHILD_NUM ; i++) {
    mw = BB_WIDTH(BB_CHILD_N(i)) > mw ? BB_WIDTH(BB_CHILD_N(i)) : mw;
    mh = BB_HEIGHT(BB_CHILD_N(i)) > mh ? BB_HEIGHT(BB_CHILD_N(i)) : mh;
  }

  new_width = BB_WIDTH((Widget)combo);
  new_height = BB_HEIGHT((Widget)combo);


  for(i = 0; i < BB_CHILD_NUM ; i++) {  
    XtResizeWidget(BB_CHILD_N(i), mw, mh, BB_CHILD_N(i)->core.border_width);
  }
  if(BB_CHILD_NUM > 0) {
    if(BB_CHILD_NUM == 1) {
      if(BB_ORIENTATION(combo) == XmHORIZONTAL) {
	XtMoveWidget(BB_CHILD_N(0), new_width/2-mw/2, BB_SPACING(combo));
      } else {
	XtMoveWidget(BB_CHILD_N(0), BB_SPACING(combo), new_height/2-mh/2);
      }
    } else {
      Dimension child_offset;
      if(BB_ORIENTATION(combo) == XmHORIZONTAL) {
	child_offset = (new_width-mw-BB_SPACING(combo)*2) / (BB_CHILD_NUM-1);
      } else {
	child_offset = (new_height-mh-BB_SPACING(combo)*2) / (BB_CHILD_NUM-1);
      }
      for(i = 0; i < BB_CHILD_NUM ; i++) {  /* not the first and last widget */
	if(BB_ORIENTATION(combo) == XmHORIZONTAL) {
	  XtMoveWidget(BB_CHILD_N(i), 
		       BB_SPACING(combo) + i * child_offset, 
		       BB_SPACING(combo));
	} else {
	  XtMoveWidget(BB_CHILD_N(i), 
		       BB_SPACING(combo),
		       BB_SPACING(combo) + i * child_offset);
	}
      }
    }
  }
}

/*
 * SetValues() routine for ComboBox widget. 
 */
static Boolean
SetValues(current, request, new)
XlButtonBoxWidget current;
XlButtonBoxWidget request;
XlButtonBoxWidget new;
{
  XlButtonBoxWidget combo = new;
  int i=0;

  DPRINTF(("set values\n"));

  for(i=0; i<BB_CHILD_NUM; i++) {
    XtVaSetValues(BB_CHILD_N(i),
		  XmNmarginHeight, BB_MARGIN_HEIGHT(combo),
		  XmNmarginWidth, BB_MARGIN_WIDTH(combo),
		  NULL);
  }

  if(XtGeometryNo != SetButtonBoxSize(combo))
    LayoutChildren(combo);
    
  return(FALSE);
}

/*
 * Routines which manipulate the ComboBox list.  These are external
 * for use by users of our widget.
 */
Widget 
XlCreateButtonBox(parent, name, arglist, num_args)
Widget parent;
char *name;
Arg *arglist;
int num_args;
{
    return(XtCreateWidget(name, xlButtonBoxWidgetClass, parent,
			  arglist, num_args));
}

