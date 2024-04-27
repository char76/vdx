/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/* ------------------------------------------ */
/* OrderWindow.h                                  */
/*                                            */
/* This file was automaticly generated by     */
/* View Designer/X                            */ 
/*                                            */
/* ------------------------------------------ */

#ifndef _OrderWindow_H_
#define _OrderWindow_H_


/* Include the base module */

#include "OrderWindow_base.h"


/* ------------------------------------------ */
/*                                            */
/* Edit the following structure to add        */
/* associated data                            */
/*                                            */
/* ------------------------------------------ */

typedef struct _OrderWindow {
	OrderWindow_base base;             /* The widgets */
} OrderWindow;



/* ------------------------------------------ */
/* initialization function of this module     */
/* ------------------------------------------ */

extern OrderWindow *createOrderWindow(
#if NeedFunctionPrototypes
	Widget,	ArgList, Cardinal
#endif
);


/* ------------------------------------------ */
/* Methods, you have to implement             */
/* ------------------------------------------ */

extern void do_order(
#if NeedFunctionPrototypes
    	OrderWindow*, Widget, XtPointer
#endif
);


extern void do_close(
#if NeedFunctionPrototypes
    	OrderWindow*, Widget, XtPointer
#endif
);




#endif /* Don't add stuff after this #endif */
