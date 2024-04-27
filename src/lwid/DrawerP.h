/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: DrawerP.h,v $
 *  $Date: 1999/08/27 15:33:10 $
 *  $Revision: 1.2.2.1 $
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
 * $Log: DrawerP.h,v $
 * Revision 1.2.2.1  1999/08/27 15:33:10  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.2  1998/06/06 18:32:32  lazy
 * ToggleButton -> ArrowButton, Label
 *
 * Revision 1.1.1.1  1998/04/24 23:45:54  lazy
 * Imported to CVS
 *
 * Revision 1.2  1998/03/30 19:10:35  lazy
 * *** empty log message ***
 *
 * Revision 1.1  1998/02/10  01:45:39  lazy
 * Initial revision
 *
 * Revision 1.1  1997/07/24  17:32:17  lazy
 * Initial revision
 *
 */

#ifndef _DrawerP_h
#define _DrawerP_h

#ifndef AA
#define AA(args) ()
#endif

#include <X11/IntrinsicP.h>
#include <Xm/ManagerP.h>
#include "Drawer.h"


/* 
 * Class Records
 */
typedef struct {
    Boolean junk;  /* Need something */
} XlDrawerClassPart;

typedef struct _XlDrawerClassRec {
    CoreClassPart	    core_class;
    CompositeClassPart	    composite_class;
    ConstraintClassPart	    constraint_class;
    XmManagerClassPart	    manager_class;
    XlDrawerClassPart	    drawer_class;
} XlDrawerClassRec;

extern XlDrawerClassRec xlDrawerClassRec;


/*
 * Instance Record.
 */
typedef struct _XlDrawerPart {

  /* public access via resources */
  Boolean expand;              /* expanded or collapsed               */
  Dimension expandSize;        /* height of child widget              */
  XmString labelString;        /* Label displayed in the toggleButton */
  Dimension sashSize;          /* Width and height of sash            */

  /* private */
  Widget sash;
  Widget arrow;
  Widget label;
  Widget child;
  Widget separator;

  Dimension minHeight;         /* Size of toggle button */
  Dimension requestHeight;     /* Height while dragging sash */
  int lastY;
  int saveY;
  GC gc;

} XlDrawerPart;


typedef struct _XlDrawerRec {
    CorePart		core;
    CompositePart	composite;
    ConstraintPart	constraint;
    XmManagerPart	manager;
    XlDrawerPart	drawer;
} XlDrawerRec;

#endif /* _XmDrawerP_h */
