/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: Converter.c,v $
 *  $Date: 1999/08/27 15:30:54 $
 *  $Revision: 1.1.1.1.2.1 $
 *
 *  Copyright 1995, Dirk Laessig
 *  ALL RIGHTS RESERVED
 *  See the file Copyright for more information
 *
 *  Dirk Laessig
 *  Goettingstr. 5
 *  38106 Braunschweig
 *  Germany
 ****************************************************************/
/*
 * $Log: Converter.c,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:30:54  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:15  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/25  20:25:35  lazy
 * Initial revision
 *
 */


#include "Converter.h"
#include <stdio.h>
#include <X11/StringDefs.h>
#include <X11/Intrinsic.h>


#define	done(type, value) \
       {							\
            if (toVal->addr != NULL) {				\
                if (toVal->size < strlen(value)+1) {	\
		    toVal->size = strlen(value)+1;		\
		    return ;				\
		}						\
		strcpy((type)(toVal->addr), (value));		\
	    }							\
	    else {						\
		static type static_val;				\
		static_val = (value);				\
		toVal->addr = (XPointer)static_val;		\
	    }							\
	    toVal->size = strlen(value)+1;		\
	}


/* ------------------------------------ */
/*  XtCvtBooleanToString()              */
/* ------------------------------------ */

static void XtCvtBooleanToString(XrmValuePtr p1, Cardinal *p2, 
				 XrmValuePtr fromVal, XrmValuePtr toVal)
{
  Boolean b = *(Boolean*)fromVal->addr;
  if(b) 
    done(String, "True");
  done(String, "False");
}
    
/* ------------------------------------ */
/*  XtCvtStringToString()               */
/* ------------------------------------ */

static void XtCvtStringToString(XrmValuePtr p1, Cardinal *p2, 
				XrmValuePtr fromVal, XrmValuePtr toVal)
{
  String s = *(String*)fromVal->addr;
  done(String, s);
}
    

/* ------------------------------------ */
/*  XtCvtDimensionToString()            */
/* ------------------------------------ */

static void XtCvtDimensionToString(XrmValuePtr p1, Cardinal *p2, 
				   XrmValuePtr fromVal, XrmValuePtr toVal)
{
  Dimension b = *(Dimension*)fromVal->addr;

  char *ptr = (char*)XtMalloc(sizeof(char)*10);
  sprintf(ptr, "%d", b);
  done(String, ptr);
}

/* ------------------------------------ */
/*  XtCvtIntToString()            */
/* ------------------------------------ */

static void XtCvtIntToString(XrmValuePtr p1, Cardinal *p2, 
				   XrmValuePtr fromVal, XrmValuePtr toVal)
{
  int b = *(int*)fromVal->addr;

  char *ptr = (char*)XtMalloc(sizeof(char)*10);
  sprintf(ptr, "%d", b);
  done(String, ptr);
}



/* ------------------------------------ */
/*  addConverter()                      */
/* ------------------------------------ */

void addConverter(Widget wg)
{
  static init = 0;
  
  if(init == 0) {
    XtAppAddConverter(XtWidgetToApplicationContext(wg),
		      XtRBoolean, XtRString, 
		      XtCvtBooleanToString, NULL, 0);
    XtAppAddConverter(XtWidgetToApplicationContext(wg),
		      XtRDimension, XtRString, 
		      XtCvtDimensionToString, NULL, 0);
    XtAppAddConverter(XtWidgetToApplicationContext(wg),
		      XtRInt, XtRString, 
		      XtCvtIntToString, NULL, 0);
    XtAppAddConverter(XtWidgetToApplicationContext(wg),
		      XtRString, XtRString, 
		      XtCvtStringToString, NULL, 0);
    init = 1;
  }
}

