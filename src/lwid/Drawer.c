/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: Drawer.c,v $
 *  $Date: 1999/08/27 15:33:07 $
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
 * $Log: Drawer.c,v $
 * Revision 1.2.2.1  1999/08/27 15:33:07  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.2  1998/06/06 18:32:32  lazy
 * ToggleButton -> ArrowButton, Label
 *
 * Revision 1.1.1.1  1998/04/24 23:45:54  lazy
 * Imported to CVS
 *
 * Revision 1.2  1998/03/30 19:10:33  lazy
 * *** empty log message ***
 *
 * Revision 1.1  1998/02/10  02:06:52  lazy
 * Initial revision
 *
 * Revision 1.1  1997/07/24  17:32:01  lazy
 * Initial revision
 *
 */

/*
  #define DEBUG 
*/

#define DEFAULT_EXPAND_SIZE 100

#ifdef DEBUG
#define DPRINTF(s) printf##s
#else
#define DPRINTF(s) 
#endif

#include "DrawerP.h"
#include <stdio.h>
#include <Xm/SashP.h>
#include <Xm/Label.h>
#include <Xm/ArrowB.h>
#include <Xm/Separator.h>


static void ClassInitialize();
static void Initialize(XlDrawerWidget request, 
		       XlDrawerWidget new, 
		       ArgList given_args, 
		       Cardinal *num_args);
static void Destroy(XlDrawerWidget combo);
static void ChangeManaged(XlDrawerWidget combo);
static void InsertChild(Widget wg);
static void Resize(XlDrawerWidget combo);
static void Redisplay(XlDrawerWidget w, 
		      XEvent *event, 
		      Region region);
static XtGeometryResult GeometryManager(Widget w, 
					XtWidgetGeometry *request, 
					XtWidgetGeometry *reply);
static XtGeometryResult QueryGeometry(Widget w, 
				      XtWidgetGeometry *request, 
				      XtWidgetGeometry *reply);
static void LayoutChildren(XlDrawerWidget combo);
static Boolean SetValues(XlDrawerWidget current, 
			 XlDrawerWidget request, 
			 XlDrawerWidget new);

static void arrowCallback(Widget wg, 
			  XtPointer clientData, 
			  XtPointer callData);

static void sashAction(Widget wg, XtPointer clientData, XtPointer callData);
static void drawPreview(XlDrawerWidget wg, int root_y);
static void setArrowDirection(XlDrawerWidget wg, Boolean expand);
 
/*
 * XlDrawerWidget specific defines.
 */
#define CHILD_N(n) (drawer->composite.children[n])
#define CHILD_NUM  (drawer->composite.num_children)
#define WIDTH(w)   (((Widget)w)->core.width)
#define HEIGHT(w)   (((Widget)w)->core.height)
#define BORDER_WIDTH(w)   (((Widget)w)->core.border_width)
#define MAX(a,b) ((a > b) ? a : b)
#define MIN(a,b) ((a < b) ? a : b)

/* 
 * XlDrawerWidget resources 
 */
#define offset(field) XtOffset(XlDrawerWidget, field)
static XtResource resources[] = {
    {XmNexpand, XmCExpand, XmRBoolean, 
	 sizeof(Boolean), offset(drawer.expand),
	 XmRImmediate, (XtPointer)TRUE},
    {XmNexpandSize, XmCExpandSize, XmRDimension, 
	 sizeof(Dimension), offset(drawer.expandSize),
	 XmRImmediate, (XtPointer)0},
    {XmNsashSize, XmCSashSize, XmRDimension, 
	 sizeof(Dimension), offset(drawer.sashSize),
	 XmRImmediate, (XtPointer)10},
    {XmNlabelString, XmCLabelString, XmRXmString, 
	 sizeof(XmString), offset(drawer.labelString),
	 XmRString, (XtPointer)"drawer"},

};

#undef offset


/*
 * Define Class Record.
 */
XlDrawerClassRec xlDrawerClassRec =
{
    {		/* core_class fields      */
    (WidgetClass)&(xmManagerClassRec),		/* superclass         */    
    (String)"XlDrawer",			/* class_name         */    
    (Cardinal)sizeof(XlDrawerRec),		/* widget_size        */    
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
    (XtWidgetProc)InsertChild,		        /* insert_child	      */     
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
    {		/* drawer fields */     
    (Boolean)0,
    }
};

WidgetClass xlDrawerWidgetClass = (WidgetClass)&xlDrawerClassRec;


/*******************************************************************
 *
 * ClassInitialize() - Register Converters
 *
 *******************************************************************/

static void
ClassInitialize()
{
}


/*******************************************************************
 *
 * Initialize() - Create Private Widgets
 *
 *******************************************************************/

static void
Initialize(request, new, given_args, num_args)
XlDrawerWidget request;
XlDrawerWidget new;
ArgList given_args;
Cardinal *num_args;
{
  XGCValues gcValues;

  if(new->drawer.expandSize == 0) {
    if(new->core.height == 0) {
      new->drawer.expandSize = DEFAULT_EXPAND_SIZE;
    } else {
      new->drawer.expandSize = new->core.height;
    }
  }
  
  gcValues.foreground = WhitePixelOfScreen(XtScreen(new));
  gcValues.background = BlackPixelOfScreen(XtScreen(new));
  gcValues.function = GXxor;
  gcValues.subwindow_mode = IncludeInferiors;
  new->drawer.gc = XCreateGC(XtDisplay(new), 
			     XRootWindowOfScreen(XtScreen(new)),
			     GCBackground | GCForeground | 
			     GCFunction | GCSubwindowMode,
			     &gcValues );

  new->drawer.child = (Widget)-1;
  new->drawer.arrow = 
    XtVaCreateManagedWidget("Arrow",
			    xmArrowButtonWidgetClass,
			    (Widget)new,
			    NULL);

  new->drawer.label = 
    XtVaCreateManagedWidget("DrawerLabel",
			    xmLabelWidgetClass,
			    (Widget)new,
			    XmNlabelString, new->drawer.labelString,
			    NULL);

			      
  new->drawer.minHeight = MAX(HEIGHT(new->drawer.arrow),
			      HEIGHT(new->drawer.label)) + 2;

  setArrowDirection(new, new->drawer.expand);

  XtAddCallback(new->drawer.arrow,
		XmNactivateCallback, arrowCallback, new);

  new->drawer.sash =
    XtVaCreateManagedWidget("Sash",
			    xmSashWidgetClass,
			    (Widget)new,
			    XmNwidth, new->drawer.sashSize,
			    XmNheight, new->drawer.sashSize,
			    NULL);
  XtAddCallback(new->drawer.sash, XmNcallback, sashAction, NULL);

  new->drawer.separator =
    XtVaCreateManagedWidget("Separator",
			    xmSeparatorWidgetClass,
			    (Widget)new,
			    NULL);

  new->drawer.child = NULL;
  
  if(!new->drawer.expand) {
    Dimension new_width, new_height;
    XtMakeResizeRequest((Widget)new, 
			WIDTH(new), new->drawer.minHeight,
			&new_width, &new_height);
  }

  if(new->drawer.expand) {
    Dimension new_width, new_height;
    XtMakeResizeRequest((Widget)new, 
			WIDTH(new), new->drawer.expandSize,
			&new_width, &new_height);
  }

  LayoutChildren(new);
}


/*******************************************************************
 *
 * arrowCallback() 
 *
 *******************************************************************/

static void 
arrowCallback(Widget wg, XtPointer clientData, XtPointer callData)
{
  Boolean oldState;

  XlDrawerWidget drawer = (XlDrawerWidget)clientData;

  oldState = drawer->drawer.expand;

  drawer->drawer.expand = !oldState;

  XlDrawerSetExpand((Widget)drawer, drawer->drawer.expand);
}

/*******************************************************************
 *
 * sashAction() - Call when moving sash
 *
 *******************************************************************/

static void 
sashAction(Widget wg, XtPointer clientData, XtPointer callData)
{
  SashCallData call_data = (SashCallData)callData;
  XlDrawerWidget drawer = (XlDrawerWidget)XtParent(wg);
  XButtonEvent *bev;
  XMotionEvent *mev;
  Dimension new_height, new_width;
  int y;

  switch (call_data->event->xany.type) {
  case ButtonPress:
    bev = (XButtonEvent*)call_data->event;
    drawer->drawer.saveY = bev->y;
    drawPreview(drawer, bev->y_root);
    drawer->drawer.lastY = bev->y_root;
    break;
  case ButtonRelease:
    bev = (XButtonEvent*)call_data->event;
    y = HEIGHT(drawer) + bev->y - drawer->drawer.saveY;
    drawPreview(drawer, drawer->drawer.lastY);
    if(y < drawer->drawer.minHeight) {
      XlDrawerSetExpand((Widget)drawer, FALSE);
    } else {
      XtMakeResizeRequest((Widget)drawer, 
			  WIDTH(drawer), (Dimension)y,
			  &new_width, &new_height);
      LayoutChildren(drawer);
    }
    break;
  case MotionNotify:
    mev = (XMotionEvent*)call_data->event;

    y = HEIGHT(drawer) + mev->y - drawer->drawer.saveY;
    if(y < drawer->drawer.minHeight)
      break;

    drawPreview(drawer, drawer->drawer.lastY);
    drawPreview(drawer, mev->y_root);
    drawer->drawer.lastY = mev->y_root;

    break;
  }
 }

/*******************************************************************
 *
 * drawPreview() - Show the new size
 *
 *******************************************************************/

static void 
drawPreview(XlDrawerWidget drawer, int root_y)
{
  int x, y;
  unsigned int dummy;
  Display *display = XtDisplay((Widget)drawer);
  Window root = XRootWindowOfScreen(XtScreen((Widget)drawer));

  XTranslateCoordinates(display, drawer->core.window, root,
			0, 0,
			&x, &y, &dummy);
  y = root_y;
  XDrawLine(display, root, drawer->drawer.gc, x, y, x + WIDTH(drawer) - 1, y);


}

/*******************************************************************
 *
 * setArrowDirection() - set arrow widgets direction
 *
 *******************************************************************/

static void 
setArrowDirection(XlDrawerWidget drawer, Boolean expand)
{
  XtVaSetValues(drawer->drawer.arrow,
		XmNarrowDirection, expand ? XmARROW_DOWN : XmARROW_RIGHT,
		NULL);
}


/*******************************************************************
 *
 * Destroy() - Nothing to do
 *
 *******************************************************************/

static void 
Destroy(drawer)
XlDrawerWidget drawer;
{
}


/*******************************************************************
 *
 * ChangedManaged - A child was managed -> layout children 
 *
 *******************************************************************/

static void 
ChangeManaged(drawer)
XlDrawerWidget drawer;
{
  DPRINTF(("change managed (%s)\n", XtName((Widget)drawer)));

  LayoutChildren(drawer);
#if(0)
  if(XtIsRealized((Widget)combo))
    DPRINTF(("--> is realized\n"));
  if(XtGeometryNo != SetDrawerSize(combo)) {
    LayoutChildren(combo);
  } else {
    LayoutChildren(combo);
  }
#endif
}

/*******************************************************************
 *
 * InsertChild() - Set the private variable child
 *
 *******************************************************************/

static void 
InsertChild(wg)
     Widget wg;
{
  XlDrawerWidget drawer;
  CompositeWidgetClass cwc;

  DPRINTF(("insert child (%s)\n", XtName(wg)));

  drawer = (XlDrawerWidget)XtParent(wg);

  cwc = (CompositeWidgetClass)compositeWidgetClass;

  if(cwc->composite_class.insert_child)
    cwc->composite_class.insert_child(wg);

  if(drawer->drawer.child != (Widget)-1) {
    drawer->drawer.child = wg;
  }
}


/*******************************************************************
 *
 * Resize() - Widget was resized -> layout children
 *
 *******************************************************************/

static void
Resize(drawer)
XlDrawerWidget drawer;
{
  if(drawer->drawer.expand) {
    drawer->drawer.expandSize = HEIGHT(drawer);
  }
  LayoutChildren(drawer);
  DPRINTF(("resize: %d %d\n", WIDTH(drawer), HEIGHT(drawer)));
}


/*******************************************************************
 *
 * Redisplay() - Nothing to do
 *
 *******************************************************************/

static void
Redisplay(w, event, region)
XlDrawerWidget w;
XEvent *event;
Region region;
{
}


/*******************************************************************
 *
 * GeometryManager() - A child wants to know its size
 *
 *******************************************************************/

static XtGeometryResult
GeometryManager(w, request, reply)
Widget w; /* child */
XtWidgetGeometry *request;
XtWidgetGeometry *reply;
{
  DPRINTF(("geometry mananger (%s)\n", XtName(w)));

#if(0)
  XlDrawerWidget combo = (XlDrawerWidget)w->core.parent;
  Dimension old_width, old_height;

  old_width = w->core.width;
  old_height = w->core.height;

  /* Set the size to the requested size */
  if( XtGeometryNo != SetDrawerSize(combo))
    XtResizeWidget(w, w->core.width, w->core.height, w->core.border_width);
  else {
    w->core.width = old_width;    
    w->core.height = old_height;
    return XtGeometryNo;
  }
  LayoutChildren(combo);
#endif
  return(XtGeometryYes);
}

/*******************************************************************
 *
 * QueryGeometry() - Called by parent
 *
 *******************************************************************/

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



/*******************************************************************
 *
 * LayoutChildren() - Calculate the layout
 *
 *******************************************************************/

static void
LayoutChildren(drawer)
XlDrawerWidget drawer;
{
  Position sx, sy;
  Position cx, cy;
  Dimension cw, ch;
  Dimension topHeight = 2;
  Dimension mH = 2;
  Dimension mW = 2;
  Dimension spacing = 2;

  if(drawer->drawer.arrow &&
     drawer->drawer.label) {
    topHeight = MAX(HEIGHT(drawer->drawer.arrow), 
		    HEIGHT(drawer->drawer.label)) + mH;
    XtMoveWidget(drawer->drawer.arrow, mW, 
		 topHeight/2 - HEIGHT(drawer->drawer.arrow)/2 );
    XtMoveWidget(drawer->drawer.label, 
		 mW + WIDTH(drawer->drawer.arrow) + spacing, 
		 topHeight/2 - HEIGHT(drawer->drawer.label)/2 );
  }

  if(drawer->drawer.sash) {
    if(drawer->drawer.expand) {
      sx = WIDTH(drawer) - WIDTH(drawer->drawer.sash) - mW;
      sy = HEIGHT(drawer) - HEIGHT(drawer->drawer.sash) - mH;
      
      XtMoveWidget(drawer->drawer.sash, sx, sy);
      XtManageChild(drawer->drawer.sash);
    } else {
      XtUnmanageChild(drawer->drawer.sash);
    }
  }

  if(drawer->drawer.separator) {
    if(drawer->drawer.expand) {
      ch = HEIGHT(drawer->drawer.separator);
      cw = - 2 + drawer->drawer.sash->core.x - 2;

      sx = 2;
      sy = HEIGHT(drawer) - HEIGHT(drawer->drawer.sash)/2 - ch/2 - 2;
      
      XtMoveWidget(drawer->drawer.separator, sx, sy);
      XtResizeWidget(drawer->drawer.separator, cw, ch,
		     BORDER_WIDTH(drawer->drawer.separator));
      XtManageChild(drawer->drawer.separator);
    } else {
      XtUnmanageChild(drawer->drawer.separator);
    }
  }

  if(drawer->drawer.child &&
     drawer->drawer.arrow &&
     drawer->drawer.label &&
     drawer->drawer.separator &&
     drawer->drawer.sash) {

    if(drawer->drawer.expand) {

      cx = 0;
      cy = topHeight;
      cw = WIDTH(drawer) - 2 * mW;
      ch = HEIGHT(drawer) - topHeight -
	HEIGHT(drawer->drawer.sash) - mH;

      XtMoveWidget(drawer->drawer.child, cx, cy);
      XtResizeWidget(drawer->drawer.child, cw, ch, 
		     BORDER_WIDTH(drawer->drawer.child));

      XtManageChild(drawer->drawer.child);
    } else {
      XtUnmanageChild(drawer->drawer.child);
    }
  }
}

/*******************************************************************
 *
 * SetValues() - Check the changing values for update
 *
 *******************************************************************/

static Boolean
SetValues(current, request, new)
XlDrawerWidget current;
XlDrawerWidget request;
XlDrawerWidget new;
{
  if(current->drawer.expandSize != request->drawer.expandSize) {
    if(request->drawer.expand)
      XtVaSetValues((Widget)new,
		    XmNwidth, request->drawer.expandSize,
		    NULL);
  }

  if(current->drawer.expand != request->drawer.expand) {
    XlDrawerSetExpand((Widget)request,
		      request->drawer.expand);
		
  }
  return(FALSE);
}

/*******************************************************************
 *
 * XlCreateDrawer() - Create a drawer widget
 *
 *******************************************************************/

Widget 
XlCreateDrawer(parent, name, arglist, num_args)
Widget parent;
char *name;
Arg *arglist;
int num_args;
{
    return(XtCreateWidget(name, xlDrawerWidgetClass, parent,
			  arglist, num_args));
}


/*******************************************************************
 *
 * XlDrawerSetExpand() - Set Expand resource and update
 *
 *******************************************************************/

void 
XlDrawerSetExpand(Widget wg, Boolean expand)
{
  XlDrawerWidget drawer = (XlDrawerWidget)wg;
  Dimension new_width, new_height;

  drawer->drawer.expand = expand;
  
  if(expand) {     /* is expanded */
    XtMakeResizeRequest((Widget)drawer, 
			WIDTH(drawer), drawer->drawer.expandSize,
			&new_width, &new_height);
			
  }

  if(!expand) {     /* is collapsed */
    XtVaGetValues((Widget)drawer,
		  XmNheight, &drawer->drawer.expandSize,
		  NULL);
    
    XtMakeResizeRequest((Widget)drawer, 
			WIDTH(drawer), drawer->drawer.minHeight,
			&new_width, &new_height);
  }

  setArrowDirection(drawer, expand);
  
  LayoutChildren(drawer);
}

