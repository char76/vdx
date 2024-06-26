/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/* ----------------------------------------- */
/* OrderWindow_base.c                            */
/*                                           */
/* This file was automaticly generated by    */
/* View Designer/X                           */
/*                                           */
/* Don't edit this file, please!             */
/*                                           */
/* ----------------------------------------- */


/* Used in createWidgets() */

#define RES_CONVERT(t,s) cvtResourceFromString(parent, t, s)
  

/* Include the header files for Motif */

#include <stdlib.h>
#include <Xm/Frame.h>
#include <X11/Shell.h>
#include <Xm/RowColumn.h>
#include <Xm/Frame.h>
#include <Xm/PushB.h>
#include <Xm/MessageB.h>






/* Include linked interfaces */

#include "SecondInterface.h"
#include "FirstInterface.h"



#include "OrderWindow_base.h"
#include "OrderWindow.h"
#include "vcmisc.h"


/* Forward declarations */

static void OrderWindow_createWidgets(
#if NeedFunctionPrototypes
	OrderWindow *self
#endif
);

static void OrderWindow_addCallbacks(
#if NeedFunctionPrototypes
	OrderWindow *self
#endif
);

static void OrderWindow_addRelations(
#if NeedFunctionPrototypes
	OrderWindow *self
#endif
);


/* ----------------------------------------- */
/* Forward declarations for methods          */
/* ----------------------------------------- */

static void do_order_CB(
#if NeedFunctionPrototypes
	Widget, 
	XtPointer, 
	XtPointer
#endif
);
static void do_close_CB(
#if NeedFunctionPrototypes
	Widget, 
	XtPointer, 
	XtPointer
#endif
);




/* ----------------------------------------- */
/* The initialization function of this       */
/* module                                    */
/* ----------------------------------------- */

OrderWindow *createOrderWindow_base(p, f_args, f_n)
	Widget p;
	ArgList f_args;
	Cardinal f_n;
{
	Widget parent;
	Arg args[100];
	Cardinal n = 0;
	OrderWindow *self;

	self = (OrderWindow*)XtMalloc(sizeof(OrderWindow));   	/* Allocate Memory */
	memset(self, 0, sizeof(OrderWindow));

	if(p)
		parent = p;
	else
		parent = getTopLevel();

	if(p) {                                 
		self->base.topWidget = self->base.OrderWindow = 
			XtCreateWidget("OrderWindow",xmFrameWidgetClass,
				       parent, f_args, f_n);
	} else {
	        

		self->base.topWidget = self->base.popupShell = self->base.OrderWindow = 
			XtCreatePopupShell("OrderWindow", applicationShellWidgetClass,
			parent, args, n);
	}
	OrderWindow_createWidgets(self); 	/* create widgets               */
	OrderWindow_addCallbacks(self);	/* add callbacks                */
	OrderWindow_addRelations(self);	/* set resources of type widget */

	if(self->base.OrderWindow)		/* add callback to free memory  */
		XtAddCallback(self->base.OrderWindow, XmNdestroyCallback,
			      vcDestroyCallback, self);
	return self;
}



/* ----------------------------------------- */
/* Create widgets                            */
/* ----------------------------------------- */

static void OrderWindow_createWidgets(self)
OrderWindow *self;
{
  Widget parent;
  Arg args[100];
  Cardinal n;

  
  /* ---------- Creating Widget:    rowColumn_1 -------------- */
  parent = self->base.OrderWindow;

  /* Building resource list */
  n = 0;
  XtSetArg(args[n], "height", 137); n++;
  XtSetArg(args[n], "width", 217); n++;
  XtSetArg(args[n], "x", 10); n++;
  XtSetArg(args[n], "y", 10); n++;


  /* Creating Widget */
  self->base.rowColumn_1 = XtCreateWidget("rowColumn_1", xmRowColumnWidgetClass,
			parent, args, n);
  
  /* Manage the Widget */
  XtManageChild(self->base.rowColumn_1);
  

  
  /* ---------- Creating Widget:    rowColumn_2 -------------- */
  parent = self->base.rowColumn_1;

  /* Building resource list */
  n = 0;
  XtSetArg(args[n], "height", 16); n++;
  XtSetArg(args[n], "width", 66); n++;
  XtSetArg(args[n], "x", 20); n++;
  XtSetArg(args[n], "y", 10); n++;
  XtSetArg(args[n], "orientation", XmHORIZONTAL); n++;


  /* Creating Widget */
  self->base.rowColumn_2 = XtCreateWidget("rowColumn_2", xmRowColumnWidgetClass,
			parent, args, n);
  
  /* Manage the Widget */
  XtManageChild(self->base.rowColumn_2);
  

  
  /* ---------- Creating Widget:    product_link -------------- */
  parent = self->base.rowColumn_2;

  /* Building resource list */
  n = 0;
  XtSetArg(args[n], "x", 130); n++;
  XtSetArg(args[n], "y", 40); n++;


  /* Creating Widget */
  self->base.product_link = createSecondInterface(parent,
			args, n);
  
  /* Manage the Widget */
  XtManageChild(self->base.product_link->base.topWidget);
  

  
  /* ---------- Creating Widget:    credit_card_link -------------- */
  parent = self->base.rowColumn_2;

  /* Building resource list */
  n = 0;
  XtSetArg(args[n], "x", 10); n++;
  XtSetArg(args[n], "y", 0); n++;


  /* Creating Widget */
  self->base.credit_card_link = createFirstInterface(parent,
			args, n);
  
  /* Manage the Widget */
  XtManageChild(self->base.credit_card_link->base.topWidget);
  

  
  /* ---------- Creating Widget:    rowColumn -------------- */
  parent = self->base.rowColumn_1;

  /* Building resource list */
  n = 0;
  XtSetArg(args[n], "orientation", XmHORIZONTAL); n++;
  XtSetArg(args[n], "packing", XmPACK_COLUMN); n++;


  /* Creating Widget */
  self->base.rowColumn = XtCreateWidget("rowColumn", xmRowColumnWidgetClass,
			parent, args, n);
  
  /* Manage the Widget */
  XtManageChild(self->base.rowColumn);
  

  
  /* ---------- Creating Widget:    apply_button -------------- */
  parent = self->base.rowColumn;

  /* Building resource list */
  n = 0;


  /* Creating Widget */
  self->base.apply_button = XtCreateWidget("apply_button", xmPushButtonWidgetClass,
			parent, args, n);
  
  /* Manage the Widget */
  XtManageChild(self->base.apply_button);
  

  
  /* ---------- Creating Widget:    close_button -------------- */
  parent = self->base.rowColumn;

  /* Building resource list */
  n = 0;


  /* Creating Widget */
  self->base.close_button = XtCreateWidget("close_button", xmPushButtonWidgetClass,
			parent, args, n);
  
  /* Manage the Widget */
  XtManageChild(self->base.close_button);
  

  
  /* ---------- Creating Widget:    help_button -------------- */
  parent = self->base.rowColumn;

  /* Building resource list */
  n = 0;


  /* Creating Widget */
  self->base.help_button = XtCreateWidget("help_button", xmPushButtonWidgetClass,
			parent, args, n);
  
  /* Manage the Widget */
  XtManageChild(self->base.help_button);
  

  
  /* ---------- Creating Widget:    helpDialog -------------- */
  parent = self->base.rowColumn_1;

  /* Building resource list */
  n = 0;


  /* Creating Widget */
  self->base.helpDialog = XmCreateInformationDialog( parent, "helpDialog", args, n);
  


}



/* ----------------------------------------- */
/* Add Callbacks                             */
/* ----------------------------------------- */

static void OrderWindow_addCallbacks(self)
OrderWindow *self;
{

  XtAddCallback( self->base.rowColumn_1, "helpCallback",
                 manageWidget, (XtPointer)self->base.helpDialog); 

  XtAddCallback( self->base.apply_button, "activateCallback",
                 do_order_CB, self);

  XtAddCallback( self->base.close_button, "activateCallback",
                 do_close_CB, self);

  XtAddCallback( self->base.help_button, "activateCallback",
                 manageWidget, (XtPointer)self->base.helpDialog); 

}



/* ----------------------------------------- */
/* Set resources of type widget              */
/* ----------------------------------------- */

void OrderWindow_addRelations(self)
OrderWindow *self;
{

}



/* ----------------------------------------- */
/* Now follows the callbacks                 */
/* ----------------------------------------- */


/* --------------------------------- */
/* do_order_CB()                    */
/* --------------------------------- */

static void do_order_CB(wg, clientData, callData)
    Widget wg;
    XtPointer clientData;
    XtPointer callData;
{
    /* Calling method which is implemented in OrderWindow.c */

    do_order((OrderWindow*)clientData, wg, callData);
}




/* --------------------------------- */
/* do_close_CB()                    */
/* --------------------------------- */

static void do_close_CB(wg, clientData, callData)
    Widget wg;
    XtPointer clientData;
    XtPointer callData;
{
    /* Calling method which is implemented in OrderWindow.c */

    do_close((OrderWindow*)clientData, wg, callData);
}







