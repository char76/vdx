/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/* ----------------------------------------------------- */
/* File: OrderWindow_base.h                                  */
/*                                                       */
/* This file was automaticly generated by                */
/* View Designer/X                                       */
/*                                                       */
/* Don't edit this file, please!                         */
/*                                                       */
/* ----------------------------------------------------- */


#ifndef _OrderWindow_base_H_
#define _OrderWindow_base_H_

#include <X11/Intrinsic.h>

#include "SecondInterface.h"
#include "FirstInterface.h"


/* ----------------------------------------------------- */
/* Base structure with all Widgets of the interface      */
/* ----------------------------------------------------- */

typedef struct _OrderWindow_base {
  Widget topWidget;             /* same as OrderWindow          */
  Widget popupShell;          	/* has the same value as OrderWindow */
				/* if view is used by a parent widget, */
				/* popupShell is NULL                  */
  

  Widget OrderWindow;    /* the top widget of this view,        */
				/* a PopupShell or a Frame             */


				/* all widgets of this view            */
  Widget rowColumn_1;
  Widget rowColumn_2;
  SecondInterface* product_link;
  FirstInterface* credit_card_link;
  Widget rowColumn;
  Widget apply_button;
  Widget close_button;
  Widget help_button;
  Widget helpDialog;


} OrderWindow_base;


#endif /* Don't add stuff after this #endif */




