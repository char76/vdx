/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: Bubble.c,v $
 *  $Date: 1999/08/27 15:32:55 $
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
 * $Log: Bubble.c,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:32:55  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:54  lazy
 * Imported to CVS
 *
 * Revision 1.5  1998/03/30 19:10:23  lazy
 * *** empty log message ***
 *
 * Revision 1.4  1997/09/06  11:42:10  lazy
 * added enabled flag
 *
 * Revision 1.3  1997/06/22  20:37:55  lazy
 * Check screens geometry in showBubblt().
 *
 * Revision 1.2  1997/06/22  20:27:42  lazy
 * It works.
 *
 * Revision 1.1  1997/06/22  20:09:13  lazy
 * Initial revision
 *
 */

/*#define DEBUG */

#ifdef DEBUG
#define DPRINTF(s) printf##s
#else
#define DPRINTF(s) 
#endif

#include "BubbleP.h"
#include <stdio.h>
#include <X11/Shell.h>
#include <Xm/Label.h>

#define DEFAULT_STRING "This is a bubble."


/* Forward declarations */

static void 
ClassInitialize();

static void 
Initialize(XlBubbleWidget request, XlBubbleWidget new, 
	   ArgList given_args, Cardinal *num_args);

static void 
Destroy(XlBubbleWidget combo);

static Boolean 
SetValues(XlBubbleWidget current, XlBubbleWidget request, XlBubbleWidget new);

static void
bubbleEvent(Widget wg, XtPointer clientData, XEvent *event, Boolean *b);

static void
showBubble(XtPointer clientData, XtIntervalId *id) ;

/* 
 * XlBubbleWidget resources 
 */
#define offset(field) XtOffset(XlBubbleWidget, field)

static XtResource resources[] = {
    { XmNallowShellResize, XmCAllowShellResize, XmRBoolean, 
      sizeof(Boolean), offset(shell.allow_shell_resize),
      XmRImmediate, (XtPointer)TRUE},
    { XmNlabelWidget, XmCLabelWidget, XmRWidget, 
      sizeof(Widget), offset(bubble.label),
      XmRImmediate, (XtPointer)NULL},
    { XmNlabelString, XmCLabelString, XmRXmString, 
      sizeof(XmString), offset(bubble.labelString),
      XmRString, (XtPointer)DEFAULT_STRING},
    { XmNoffsetX, XmCOffsetX, XmRPosition, 
      sizeof(Position), offset(bubble.offsetX),
      XmRString, (XtPointer)"20" },
    { XmNoffsetY, XmCOffsetY, XmRPosition, 
      sizeof(Position), offset(bubble.offsetY),
      XmRString, (XtPointer)"3" },
    { XmNtimeout, XmCTimeout, XmRDimension, 
      sizeof(Dimension), offset(bubble.timeout),
      XmRString, (XtPointer)"800" },
    { XmNuseEvents, XmCUseEvents, XmRBoolean, 
      sizeof(Boolean), offset(bubble.useEvents),
      XmRString, (XtPointer)"TRUE" },
    { XmNplacement, XmCPlacement, XmRBubblePlacement, 
      sizeof(BubblePlacement), offset(bubble.placement),
      XmRImmediate, (XtPointer)XmBUBBLE_BOTTOM_LEFT }
};

#undef offset


/*
 * Define Class Record.
 */
XlBubbleClassRec xlBubbleClassRec =
{
  {	      /* core_class fields      */
    (WidgetClass)&(overrideShellClassRec),	/* superclass         */    
    (String)"XlBubble",			        /* class_name         */    
    (Cardinal)sizeof(XlBubbleRec),		/* widget_size        */    
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
    (XtWidgetProc)XtInheritResize,		/* resize             */    
    (XtExposeProc)XtInheritExpose,		/* expose             */    
    (XtSetValuesFunc)SetValues,			/* set_values         */    
    (XtArgsFunc)NULL,				/* set values hook    */    
    (XtAlmostProc)XtInheritSetValuesAlmost,	/* set values almost  */    
    (XtArgsProc)NULL,				/* get values hook    */    
    (XtAcceptFocusProc)NULL,			/* accept_focus       */    
    (XtVersionType)XtVersion,			/* Version            */    
    (XtPointer)NULL,				/* PRIVATE cb list    */
    (String)XtInheritTranslations,		/* tm_table           */
    (XtGeometryHandler)XtInheritQueryGeometry, 	/* query_geom         */
    (XtStringProc)XtInheritDisplayAccelerator,	/* display_accelerator*/
    (XtPointer)NULL     			/* extension	      */
  },
  {              
    XtInheritGeometryManager, 
    XtInheritChangeManaged,   
    XtInheritInsertChild,     
    XtInheritDeleteChild,
    NULL,            
  },
  {                    
    NULL,            
  },
  {                    
    NULL,            
  },
  {
    TRUE
  }
};

WidgetClass xlBubbleWidgetClass = (WidgetClass)&xlBubbleClassRec;


static void
ClassInitialize()                /* Currently not needed */
{
}

static void
Initialize(request, new, given_args, num_args)
XlBubbleWidget request;
XlBubbleWidget new;
ArgList given_args;
Cardinal *num_args;
{
  Widget parent = XtParent((Widget)new);

  new->bubble.areaX = 0;
  new->bubble.areaY = 0;
  new->bubble.areaWidth = parent->core.width;
  new->bubble.areaHeight = parent->core.height;
  new->bubble.timer = 0;
  new->bubble.label = 
    XtVaCreateManagedWidget("label",
			    xmLabelWidgetClass,
			    (Widget)new,
			    XmNlabelString, new->bubble.labelString,
			    NULL);
  XtAddEventHandler(parent, 
		    EnterWindowMask | LeaveWindowMask,
		    False, bubbleEvent, new );
}

static void
showBubble(XtPointer clientData, XtIntervalId *id) 
{
  XlBubbleWidget bubble = (XlBubbleWidget)clientData;
  Window retRoot, retChild;
  int retRootX, retRootY, retX, retY;
  unsigned int retKey;
  Position x, y;
  Widget parent;
  Dimension pw, ph, sw, sh, bw, bh;

  if(!xlBubbleClassRec.bubble_class.enabled)   /* User wants no bubble */
    return;

  sw = WidthOfScreen(bubble->core.screen);
  sh = HeightOfScreen(bubble->core.screen);
  bw = bubble->bubble.label->core.width - 2*bubble->core.border_width;
  bh = bubble->bubble.label->core.height - 2*bubble->core.border_width;

  parent = XtParent((Widget)bubble);
  pw = bubble->bubble.areaWidth;
  ph = bubble->bubble.areaHeight;
  XQueryPointer(XtDisplay(parent), XtWindow(parent),
		&retRoot, &retChild,
		&retRootX, &retRootY,
		&retX, &retY,
		&retKey);
  XTranslateCoordinates(XtDisplay(parent), XtWindow(parent), retRoot,  
			bubble->bubble.areaX, bubble->bubble.areaY, 
			&retX, &retY, &retChild );

  switch(bubble->bubble.placement) {
  case XmBUBBLE_POINTER:
    x = retRootX;
    y = retRootY;
    break;
  case XmBUBBLE_BOTTOM_LEFT:
    x = retX;
    y = retY+ph;
    break;
  case XmBUBBLE_BOTTOM_RIGHT:
    x = retX+pw;
    y = retY+ph;
    break;
  case XmBUBBLE_TOP_RIGHT:
    x = retX+pw;
    y = retY-bh;
    break;
  case XmBUBBLE_TOP_LEFT:
    x = retX;
    y = retY-bh;
    break;
  }
  x += bubble->bubble.offsetX;
  y += bubble->bubble.offsetY;


  if(x < 0)
    x = 0;
  if(y < 0)
    y = 0;
  if(x+bw > sw)
    x -= x+bw - sw + 2;
  if(y+bh > sh)
    y -= y+bh - sh + 2;

  XtVaSetValues((Widget)bubble, 
		XmNx, x, 
		XmNy, y,
		NULL);

  XQueryPointer(XtDisplay(parent), XtWindow(XtParent(parent)),
		&retRoot, &retChild,
		&retRootX, &retRootY,
		&retX, &retY,
		&retKey);
  if(retChild != XtWindow(parent))
    return;
  XtPopup((Widget)bubble, XtGrabNone);
}


static void
bubbleEvent(Widget wg, XtPointer clientData,
	    XEvent *event, Boolean *b)
{
  Widget parent;
  XlBubbleWidget bubble = (XlBubbleWidget)clientData;
  
  if(event->type == EnterNotify) {         
    parent = XtParent((Widget)bubble);
    bubble->bubble.areaX = 0;
    bubble->bubble.areaY = 0;
    bubble->bubble.areaWidth = parent->core.width;
    bubble->bubble.areaHeight = parent->core.height;
    if(bubble->bubble.timer)
      XtRemoveTimeOut(bubble->bubble.timer);
    bubble->bubble.timer 
      = XtAppAddTimeOut(XtWidgetToApplicationContext(wg),
			bubble->bubble.timeout,
			showBubble, bubble);
  }


  if(event->type == LeaveNotify) {
    if(bubble->bubble.timer)
      XtRemoveTimeOut(bubble->bubble.timer);
    bubble->bubble.timer = 0;
    XtPopdown((Widget)bubble);
  }
}


static void 
Destroy(bubble)
     XlBubbleWidget bubble;
{
  XtRemoveEventHandler(XtParent((Widget)bubble), 
		       EnterWindowMask | LeaveWindowMask, False, 
		       bubbleEvent, bubble);
}






/*
 * SetValues() routine
 */
static Boolean
SetValues(current, request, new)
XlBubbleWidget current;
XlBubbleWidget request;
XlBubbleWidget new;
{
  if(request->bubble.labelString == current->bubble.labelString)
    XtVaSetValues(current->bubble.label,
		  XmNlabelString, request->bubble.labelString,
		  NULL);
  if(request->bubble.label != current->bubble.label)
    new->bubble.label = current->bubble.label;

  return(FALSE);
}


Widget 
XlCreateBubble(parent, name, arglist, num_args)
Widget parent;
char *name;
Arg *arglist;
int num_args;
{
    return(XtCreateWidget(name, xlBubbleWidgetClass, parent,
			  arglist, num_args));
}


Boolean 
XlBubbleIsEnabled()
{
  return xlBubbleClassRec.bubble_class.enabled;
}


void 
XlBubbleSetEnabled(Boolean enabled)
{
  xlBubbleClassRec.bubble_class.enabled = enabled;
}


void 
XlBubbleSimEnter(Widget wg, 
		 Position x, Position y,
		 Dimension width, Dimension height,
		 XmString xms)
{
  XlBubbleWidget bubble = (XlBubbleWidget)wg;

  bubble->bubble.areaX = x;
  bubble->bubble.areaY = y;
  bubble->bubble.areaWidth = width;
  bubble->bubble.areaHeight = height;

  XtVaSetValues(wg, XmNlabelString, XmStringCopy(xms), NULL);

  if(bubble->bubble.timer)
    XtRemoveTimeOut(bubble->bubble.timer);
  bubble->bubble.timer 
    = XtAppAddTimeOut(XtWidgetToApplicationContext(wg),
		      bubble->bubble.timeout,
		      showBubble, bubble);
}


void 
XlBubbleSimLeave(Widget wg)
{
  XlBubbleWidget bubble = (XlBubbleWidget)wg;

  if(bubble->bubble.timer)
    XtRemoveTimeOut(bubble->bubble.timer);
  bubble->bubble.timer = 0;
  XtPopdown((Widget)bubble);
}
