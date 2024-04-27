/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/* ----------------------------------------- */
/* CalcWindow_base.c                            */
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
#include <Xm/Text.h>
#include <Xm/PushB.h>






/* Include linked interfaces */




#include "CalcWindow_base.h"
#include "CalcWindow.h"
#include "vcmisc.h"


/* Forward declarations */

static void CalcWindow_createWidgets(
#if NeedFunctionPrototypes
	CalcWindow *self
#endif
);

static void CalcWindow_addCallbacks(
#if NeedFunctionPrototypes
	CalcWindow *self
#endif
);

static void CalcWindow_addRelations(
#if NeedFunctionPrototypes
	CalcWindow *self
#endif
);


/* ----------------------------------------- */
/* Forward declarations for methods          */
/* ----------------------------------------- */

static void do_addition_CB(
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

CalcWindow *createCalcWindow_base(p, f_args, f_n)
	Widget p;
	ArgList f_args;
	Cardinal f_n;
{
	Widget parent;
	Arg args[100];
	Cardinal n = 0;
	CalcWindow *self;

	self = (CalcWindow*)XtMalloc(sizeof(CalcWindow));   	/* Allocate Memory */
	memset(self, 0, sizeof(CalcWindow));

	if(p)
		parent = p;
	else
		parent = getTopLevel();

	if(p) {                                 
		self->base.topWidget = self->base.CalcWindow = 
			XtCreateWidget("CalcWindow",xmFrameWidgetClass,
				       parent, f_args, f_n);
	} else {
	        

		self->base.topWidget = self->base.popupShell = self->base.CalcWindow = 
			XtCreatePopupShell("CalcWindow", applicationShellWidgetClass,
			parent, args, n);
	}
	CalcWindow_createWidgets(self); 	/* create widgets               */
	CalcWindow_addCallbacks(self);	/* add callbacks                */
	CalcWindow_addRelations(self);	/* set resources of type widget */

	if(self->base.CalcWindow)		/* add callback to free memory  */
		XtAddCallback(self->base.CalcWindow, XmNdestroyCallback,
			      vcDestroyCallback, self);
	return self;
}



/* ----------------------------------------- */
/* Create widgets                            */
/* ----------------------------------------- */

static void CalcWindow_createWidgets(self)
CalcWindow *self;
{
  Widget parent;
  Arg args[100];
  Cardinal n;

  
  /* ---------- Creating Widget:    rowColumn_1 -------------- */
  parent = self->base.CalcWindow;

  /* Building resource list */
  n = 0;
  XtSetArg(args[n], "height", 133); n++;
  XtSetArg(args[n], "width", 144); n++;
  XtSetArg(args[n], "x", 290); n++;
  XtSetArg(args[n], "y", 140); n++;


  /* Creating Widget */
  self->base.rowColumn_1 = XtCreateWidget("rowColumn_1", xmRowColumnWidgetClass,
			parent, args, n);
  
  /* Manage the Widget */
  XtManageChild(self->base.rowColumn_1);
  

  
  /* ---------- Creating Widget:    number1_text -------------- */
  parent = self->base.rowColumn_1;

  /* Building resource list */
  n = 0;
  XtSetArg(args[n], "background", RES_CONVERT("Pixel", "#e4b4af")); n++;
  XtSetArg(args[n], "x", 20); n++;
  XtSetArg(args[n], "y", 10); n++;


  /* Creating Widget */
  self->base.number1_text = XtCreateWidget("number1_text", xmTextWidgetClass,
			parent, args, n);
  
  /* Manage the Widget */
  XtManageChild(self->base.number1_text);
  

  
  /* ---------- Creating Widget:    number2_text -------------- */
  parent = self->base.rowColumn_1;

  /* Building resource list */
  n = 0;
  XtSetArg(args[n], "background", RES_CONVERT("Pixel", "#e4b4af")); n++;
  XtSetArg(args[n], "x", 0); n++;
  XtSetArg(args[n], "y", 0); n++;


  /* Creating Widget */
  self->base.number2_text = XtCreateWidget("number2_text", xmTextWidgetClass,
			parent, args, n);
  
  /* Manage the Widget */
  XtManageChild(self->base.number2_text);
  

  
  /* ---------- Creating Widget:    add_button -------------- */
  parent = self->base.rowColumn_1;

  /* Building resource list */
  n = 0;
  XtSetArg(args[n], "x", 20); n++;
  XtSetArg(args[n], "y", 40); n++;
  XtSetArg(args[n], "alignment", XmALIGNMENT_BEGINNING); n++;


  /* Creating Widget */
  self->base.add_button = XtCreateWidget("add_button", xmPushButtonWidgetClass,
			parent, args, n);
  
  /* Manage the Widget */
  XtManageChild(self->base.add_button);
  

  
  /* ---------- Creating Widget:    result_text -------------- */
  parent = self->base.rowColumn_1;

  /* Building resource list */
  n = 0;
  XtSetArg(args[n], "x", 0); n++;
  XtSetArg(args[n], "y", 40); n++;
  XtSetArg(args[n], "cursorPositionVisible", 0); n++;
  XtSetArg(args[n], "editable", 0); n++;


  /* Creating Widget */
  self->base.result_text = XtCreateWidget("result_text", xmTextWidgetClass,
			parent, args, n);
  
  /* Manage the Widget */
  XtManageChild(self->base.result_text);
  


}



/* ----------------------------------------- */
/* Add Callbacks                             */
/* ----------------------------------------- */

static void CalcWindow_addCallbacks(self)
CalcWindow *self;
{

  XtAddCallback( self->base.add_button, "activateCallback",
                 do_addition_CB, self);

}



/* ----------------------------------------- */
/* Set resources of type widget              */
/* ----------------------------------------- */

void CalcWindow_addRelations(self)
CalcWindow *self;
{

}



/* ----------------------------------------- */
/* Now follows the callbacks                 */
/* ----------------------------------------- */


/* --------------------------------- */
/* do_addition_CB()                    */
/* --------------------------------- */

static void do_addition_CB(wg, clientData, callData)
    Widget wg;
    XtPointer clientData;
    XtPointer callData;
{
    /* Calling method which is implemented in CalcWindow.c */

    do_addition((CalcWindow*)clientData, wg, callData);
}






