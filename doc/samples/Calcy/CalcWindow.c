/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/* ------------------------------------------ */
/* CalcWindow.c                                  */
/*                                            */
/* This file was automaticly generated by     */
/* View Designer/X                            */
/*                                            */
/* ------------------------------------------ */


#include <stdio.h>

#include "CalcWindow.h"
#include <stdlib.h>

/* Following header file is needed for XmTextGetString() */
#include <Xm/Text.h>


extern CalcWindow *createCalcWindow_base(
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

CalcWindow *createCalcWindow(parent, args, n)
	Widget parent;
	ArgList args;
	Cardinal n;
{
  CalcWindow *self;

  self = createCalcWindow_base(parent,args,n);
  
  /* Init you data associated with this view ... */

  return self;
}


/* ------------------------------------------ */
/* Impelemtation of your methods              */
/* ------------------------------------------ */


/* ------------------------------------------ */
/* Method: do_addition()                      */
/* ------------------------------------------ */

void do_addition(self, wg, callData)
     CalcWindow *self;
     Widget wg;
     XtPointer callData;
{
  char *str1, *str2;
  int result;
  char result_str[64];

  /* read contents of text widgets */
  str1 = XmTextGetString(self->base.number1_text);
  str2 = XmTextGetString(self->base.number2_text);

  /* convert and addition */
  result = atoi(str1) + atoi(str2);    

  /* convert to string and put it in the result text widget */
  sprintf(result_str, "%d", result);
  XmTextSetString(self->base.result_text, result_str);

  /* we have to free the memory */
  XtFree(str1);
  XtFree(str2);
}





