/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/* ----------------------------------------------------- */
/* File: FirstInterface_base.h                                  */
/*                                                       */
/* This file was automaticly generated by                */
/* View Designer/X                                       */
/*                                                       */
/* Don't edit this file, please!                         */
/*                                                       */
/* ----------------------------------------------------- */


#ifndef _FirstInterface_base_H_
#define _FirstInterface_base_H_

#include <X11/Intrinsic.h>



/* ----------------------------------------------------- */
/* Base structure with all Widgets of the interface      */
/* ----------------------------------------------------- */

typedef struct _FirstInterface_base {
  Widget topWidget;             /* same as FirstInterface          */
  Widget popupShell;          	/* has the same value as FirstInterface */
				/* if view is used by a parent widget, */
				/* popupShell is NULL                  */
  

  Widget FirstInterface;    /* the top widget of this view,        */
				/* a PopupShell or a Frame             */


				/* all widgets of this view            */
  Widget radioBox;
  Widget amex_toggle;
  Widget visa_toggle;
  Widget master_toggle;


} FirstInterface_base;


#endif /* Don't add stuff after this #endif */




