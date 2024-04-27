/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/* ----------------------------------------- */
/* SecondInterface_base.c                            */
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
#include <Xm/ToggleB.h>






/* Include linked interfaces */




#include "SecondInterface_base.h"
#include "SecondInterface.h"
#include "vcmisc.h"


/* Forward declarations */

static void SecondInterface_createWidgets(
#if NeedFunctionPrototypes
	SecondInterface *self
#endif
);

static void SecondInterface_addCallbacks(
#if NeedFunctionPrototypes
	SecondInterface *self
#endif
);

static void SecondInterface_addRelations(
#if NeedFunctionPrototypes
	SecondInterface *self
#endif
);


/* ----------------------------------------- */
/* Forward declarations for methods          */
/* ----------------------------------------- */

static void product_value_changed_CB(
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

SecondInterface *createSecondInterface_base(p, f_args, f_n)
	Widget p;
	ArgList f_args;
	Cardinal f_n;
{
	Widget parent;
	Arg args[100];
	Cardinal n = 0;
	SecondInterface *self;

	self = (SecondInterface*)XtMalloc(sizeof(SecondInterface));   	/* Allocate Memory */
	memset(self, 0, sizeof(SecondInterface));

	if(p)
		parent = p;
	else
		parent = getTopLevel();

	if(p) {                                 
		self->base.topWidget = self->base.SecondInterface = 
			XtCreateWidget("SecondInterface",xmFrameWidgetClass,
				       parent, f_args, f_n);
	} else {
	        

		self->base.topWidget = self->base.popupShell = self->base.SecondInterface = 
			XtCreatePopupShell("SecondInterface", topLevelShellWidgetClass,
			parent, args, n);
	}
	SecondInterface_createWidgets(self); 	/* create widgets               */
	SecondInterface_addCallbacks(self);	/* add callbacks                */
	SecondInterface_addRelations(self);	/* set resources of type widget */

	if(self->base.SecondInterface)		/* add callback to free memory  */
		XtAddCallback(self->base.SecondInterface, XmNdestroyCallback,
			      vcDestroyCallback, self);
	return self;
}



/* ----------------------------------------- */
/* Create widgets                            */
/* ----------------------------------------- */

static void SecondInterface_createWidgets(self)
SecondInterface *self;
{
  Widget parent;
  Arg args[100];
  Cardinal n;

  
  /* ---------- Creating Widget:    rowColumn -------------- */
  parent = self->base.SecondInterface;

  /* Building resource list */
  n = 0;


  /* Creating Widget */
  self->base.rowColumn = XtCreateWidget("rowColumn", xmRowColumnWidgetClass,
			parent, args, n);
  
  /* Manage the Widget */
  XtManageChild(self->base.rowColumn);
  

  
  /* ---------- Creating Widget:    burger_toggle -------------- */
  parent = self->base.rowColumn;

  /* Building resource list */
  n = 0;
  XtSetArg(args[n], "x", 0); n++;
  XtSetArg(args[n], "y", 0); n++;


  /* Creating Widget */
  self->base.burger_toggle = XtCreateWidget("burger_toggle", xmToggleButtonWidgetClass,
			parent, args, n);
  
  /* Manage the Widget */
  XtManageChild(self->base.burger_toggle);
  

  
  /* ---------- Creating Widget:    pizza_toggle -------------- */
  parent = self->base.rowColumn;

  /* Building resource list */
  n = 0;
  XtSetArg(args[n], "x", 0); n++;
  XtSetArg(args[n], "y", 0); n++;


  /* Creating Widget */
  self->base.pizza_toggle = XtCreateWidget("pizza_toggle", xmToggleButtonWidgetClass,
			parent, args, n);
  
  /* Manage the Widget */
  XtManageChild(self->base.pizza_toggle);
  


}



/* ----------------------------------------- */
/* Add Callbacks                             */
/* ----------------------------------------- */

static void SecondInterface_addCallbacks(self)
SecondInterface *self;
{

  XtAddCallback( self->base.burger_toggle, "valueChangedCallback",
                 product_value_changed_CB, self);

  XtAddCallback( self->base.pizza_toggle, "valueChangedCallback",
                 product_value_changed_CB, self);

}



/* ----------------------------------------- */
/* Set resources of type widget              */
/* ----------------------------------------- */

void SecondInterface_addRelations(self)
SecondInterface *self;
{

}



/* ----------------------------------------- */
/* Now follows the callbacks                 */
/* ----------------------------------------- */


/* --------------------------------- */
/* product_value_changed_CB()                    */
/* --------------------------------- */

static void product_value_changed_CB(wg, clientData, callData)
    Widget wg;
    XtPointer clientData;
    XtPointer callData;
{
    /* Calling method which is implemented in SecondInterface.c */

    product_value_changed((SecondInterface*)clientData, wg, callData);
}






