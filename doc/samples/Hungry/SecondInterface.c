/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/* ------------------------------------------ */
/* SecondInterface.c                                  */
/*                                            */
/* This file was automaticly generated by     */
/* View Designer/X                            */
/*                                            */
/* ------------------------------------------ */


#include <stdio.h>

#include "SecondInterface.h"

/* Needed for XmToggleButtonGetState() */
#include <Xm/ToggleB.h>

extern SecondInterface *createSecondInterface_base(
#if NeedFunctionPrototypes
    	Widget,	ArgList, Cardinal
#endif
);




/* ------------------------------------------ */
/* Initialization function of this module     */
/*                                            */
/* If you want to create a popupShell         */
/* parent must be NULL, otherwise you create  */
/* a Frame                                    */
/* ------------------------------------------ */

SecondInterface *createSecondInterface(parent, args, n)
	Widget parent;
	ArgList args;
	Cardinal n;
{
  SecondInterface *self;

  self = createSecondInterface_base(parent,args,n);
  
  /* Init you data associated with this view ... */
  self->burger = FALSE;
  self->pizza = FALSE;

  return self;
}


/* ------------------------------------------ */
/* Impelemtation of your methods              */
/* ------------------------------------------ */

extern void printf_product(self)
     SecondInterface *self;
{
  if(self->burger) {
    printf("Burger");
  }
  if(self->burger && self->pizza) {
    printf(" and ");
  }
  if(self->pizza) {
    printf("Pizza");
  }
  if(!self->pizza && !self->burger) {
    printf("nothing");
  }
  printf("\n");
}

/* ------------------------------------------ */
/* Method: product_value_changed()                      */
/* ------------------------------------------ */

void product_value_changed(self, wg, callData)
     SecondInterface *self;
     Widget wg;
     XtPointer callData;
{
  Boolean state;

  state = XmToggleButtonGetState(wg);
  if(wg == self->base.burger_toggle) {
    self->burger = state;
  } else if(wg == self->base.pizza_toggle) {
    self->pizza = state;
  }
}





