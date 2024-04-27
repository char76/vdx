/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/* --------------------------------------- */
/* Helpfull function for generated C-code  */
/*                                         */
/* This file was automaticly generated.    */
/*                                         */
/* Don't edit this file, please!           */
/*                                         */
/* --------------------------------------- */


#include "vcmisc.h"
#include <X11/xpm.h>
#include <Xm/Xm.h>
#include <X11/Shell.h>
#include <stdio.h>

/* Global variables */

static Widget topLevel;
static XtAppContext context;


/* --------------------------------------- */
/* getTopLevel() - return TopLevel widget  */
/* --------------------------------------- */

Widget getTopLevel ()
{
  return topLevel;
}




/* --------------------------------------- */
/* manageWidget()                          */
/*                                         */
/* Callback for managing dialogs           */
/*                                         */
/* --------------------------------------- */

void manageWidget(wg, clientData, callData)
     Widget wg;
     XtPointer clientData;
     XtPointer callData;
{
  XtManageChild((Widget)clientData);
}



/* --------------------------------------- */
/* vcDestroyCallback()                     */
/*                                         */
/* Free interface structure                */
/*                                         */
/* --------------------------------------- */

void vcDestroyCallback(wg, clientData, callData)
     Widget wg;
     XtPointer clientData;
     XtPointer callData;
{
  XtFree(clientData);
}


/* --------------------------------------- */
/* createPixmapFromFile()                  */
/* --------------------------------------- */

Pixmap createPixmapFromFile(name)
     char *name;
{
  String string;
  Pixmap pix, mask;
  XpmAttributes attr;
  
  string = XtResolvePathname(XtDisplay(topLevel),
			     "pixmaps", name, "", NULL,
			     NULL, 0, NULL);
  if(string) {
    memset(&attr, 0, sizeof(attr));
    attr.valuemask = XpmReturnPixels;
    if( !XpmReadFileToPixmap(XtDisplay(topLevel),
			     XRootWindowOfScreen(XtScreen(topLevel)),
			     string,
			     &pix, &mask, &attr) )
      return pix;
    return XmUNSPECIFIED_PIXMAP;
    XtFree(string);
  }
  return XmUNSPECIFIED_PIXMAP;
}


/* --------------------------------------- */
/* createPixmapFromData()                  */
/* --------------------------------------- */

Pixmap createPixmapFromData(data)
    char **data;
{
  Pixmap pix, mask;
  XpmAttributes attr;

  memset(&attr, 0, sizeof(attr));
  attr.valuemask = XpmReturnPixels;

  if( !XpmCreatePixmapFromData(XtDisplay(getTopLevel()),
		               XRootWindowOfScreen(XtScreen(getTopLevel())),
			       data,
			       &pix, &mask, &attr) )
    return pix;
  return XmUNSPECIFIED_PIXMAP;
}



/* --------------------------------------- */
/* vcinit()                                */
/* --------------------------------------- */

void vcinit (applClass, argc, argv, fbRes)
     char *applClass;
     Cardinal argc;
     char **argv;
     char *fbRes;
{
  Display *display;

  XtToolkitInitialize();
    
  context = XtCreateApplicationContext();

  display = XtOpenDisplay(context, 
			  NULL, NULL,
			  applClass, 
			  NULL, 0,
			  &argc, argv);
  if(display == NULL) {
    fprintf(stderr, "Can't open display.\n");
    exit(0);
  }

  if(fbRes) {
    XrmDatabase database, fallback;
    
    fallback = XrmGetStringDatabase(fbRes);
    database = XrmGetDatabase(display);
    
    XrmCombineDatabase(fallback, &database, FALSE);
  }
  
  topLevel = XtAppCreateShell(NULL, applClass, 
			      applicationShellWidgetClass,
			      display, NULL, 0);
}


/* --------------------------------------- */
/* vcrun()                                 */
/* --------------------------------------- */

void vcrun()
{
  XtAppMainLoop(context); 
}


/* --------------------------------------- */
/* cvtResourceFromString()                 */
/* --------------------------------------- */

XtArgVal cvtResourceFromString(Widget wg, char *type, char *value)
{
  XtArgVal v;
  XrmValue from, to;

  from.addr = (caddr_t)value;
  from.size = strlen(value)+1;
  to.addr = (caddr_t)&v;
  to.size = sizeof(v);

  if( XtConvertAndStore(wg, XtRString, &from, type, &to) ) {
    return v;
  } 

  printf("Can't convert %s to %s.\n", value, type);
  return 0;
}


/* ---------------------------------------------
 * 
 * QuickHelp property
 *
 * --------------------------------------------- */

typedef struct _QuickHelpData{
  Widget widget;
  XmString xmString;
  String string;
  struct _QuickHelpData *next;
  struct _QuickHelpData *last;
} QuickHelpData;

static QuickHelpData *firstQuickHelpData = NULL;
static QuickHelpData *currentQuickHelpData = NULL;
static Widget quickHelpWidget;

static XtResource quickHelpResources [] = {
  {
    "quickHelpLabel", "QuickHelpLabel", XmRXmString, sizeof(XmString),
    XtOffsetOf(QuickHelpData, xmString), XtRString, " "
  },
  {
    "quickHelpLabel", "QuickHelpLabel", XtRString, sizeof(String),
    XtOffsetOf(QuickHelpData, string), XtRString, " "
  }
};



static QuickHelpData *findQuickHelpData(wg)
     Widget wg;
{
  QuickHelpData *ptr = firstQuickHelpData;

  if(ptr) {
    do {
      if(wg == ptr->widget)
	return ptr;
      ptr = ptr->next;
    } while(ptr);
  }
  return NULL;
}



static void quickHelpEvent(wg, clientData, event, cont)
     Widget wg;
     XtPointer clientData;
     XEvent *event;
     Boolean *cont;
{
  QuickHelpData *data, *ptr;
  static XmString emptyString = NULL;  

  if(!emptyString) {
    emptyString = XmStringCreateLtoR(" ", XmSTRING_DEFAULT_CHARSET);
  }

  if(!quickHelpWidget)
    return;

  if(event->type == EnterNotify) {
    data = findQuickHelpData(wg);
    if(!data) {
      data = (QuickHelpData*)XtMalloc(sizeof(QuickHelpData));
      memset(data, 0, sizeof(QuickHelpData));
      data->widget = wg;
      XtGetSubresources(wg, data, NULL, NULL, 
			quickHelpResources, XtNumber(quickHelpResources),
			NULL, 0);
      ptr = firstQuickHelpData;
      if(ptr) {
	while(ptr->next) ptr = ptr->next;
	ptr->next = data;
      } else {
	firstQuickHelpData = data;
      }
    }
    data->last = currentQuickHelpData;
    currentQuickHelpData = data;
    if(data->xmString)
      XtVaSetValues(quickHelpWidget, XmNlabelString, data->xmString, NULL);
  }
  if(event->type == LeaveNotify) {
    data = findQuickHelpData(wg);
    if(data) {
      currentQuickHelpData = data->last;
      if(currentQuickHelpData && currentQuickHelpData->xmString)
	XtVaSetValues(quickHelpWidget, 
		      XmNlabelString, data->xmString, 
		      NULL);
      else 
	XtVaSetValues(quickHelpWidget, 
		      XmNlabelString, emptyString, 
		      NULL);
    }
  }
}




static void quickHelpDestroyCallback(wg, clientData, callData)
     Widget wg;
     XtPointer clientData;
     XtPointer callData;
{
  QuickHelpData *toFree, *ptr;
  toFree = findQuickHelpData(wg);
  if(toFree) {
    ptr = firstQuickHelpData;
    if(ptr == toFree)
      firstQuickHelpData = toFree->next;
    do {
      if(ptr->next == toFree) {
	ptr->next = toFree->next;
	break;
      }
      ptr = ptr->next;
    } while(ptr);
    XtFree((char*)toFree);
  }
}



/* --------------------------------------- */
/* addQuickHelp()                          */
/* --------------------------------------- */

void addQuickHelp(wg)
     Widget wg;
{
  XtAddEventHandler(wg, 
		    EnterWindowMask | LeaveWindowMask,
		    False, quickHelpEvent, NULL );
  XtAddCallback(wg, XmNdestroyCallback, quickHelpDestroyCallback, NULL);
}



static void quickHelpWidgetDestroyCallback(wg, clientData, callData)
     Widget wg;
     XtPointer clientData;
     XtPointer callData;
{
  if(wg == quickHelpWidget)
    quickHelpWidget = NULL;
}

/* --------------------------------------- */
/* setQuickHelpWidget()                    */
/* --------------------------------------- */

void setQuickHelpWidget(wg)
     Widget wg;
{
  quickHelpWidget = wg;
  XtAddCallback(quickHelpWidget, XmNdestroyCallback, 
		quickHelpWidgetDestroyCallback, NULL);  
}


