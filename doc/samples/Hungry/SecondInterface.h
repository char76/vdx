/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/* ------------------------------------------ */
/* SecondInterface.h                                  */
/*                                            */
/* This file was automaticly generated by     */
/* View Designer/X                            */ 
/*                                            */
/* ------------------------------------------ */

#ifndef _SecondInterface_H_
#define _SecondInterface_H_


/* Include the base module */

#include "SecondInterface_base.h"

/* ------------------------------------------ */
/*                                            */
/* Edit the following structure to add        */
/* associated data                            */
/*                                            */
/* ------------------------------------------ */

typedef struct _SecondInterface {
  Boolean pizza;
  Boolean burger;
  SecondInterface_base base;             /* The widgets */
} SecondInterface;



extern void printf_product(
#if NeedFunctionPrototypes
			   SecondInterface *
#endif
			   );


/* ------------------------------------------ */
/* initialization function of this module     */
/* ------------------------------------------ */

extern SecondInterface *createSecondInterface(
#if NeedFunctionPrototypes
	Widget,	ArgList, Cardinal
#endif
);


/* ------------------------------------------ */
/* Methods, you have to implement             */
/* ------------------------------------------ */

extern void product_value_changed(
#if NeedFunctionPrototypes
    	SecondInterface*, Widget, XtPointer
#endif
);




#endif /* Don't add stuff after this #endif */
