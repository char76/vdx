/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: ButtonBoxP.h,v $
 *  $Date: 1999/08/27 15:33:02 $
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
 * $Log: ButtonBoxP.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:33:02  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:53  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/24  17:32:17  lazy
 * Initial revision
 *
 */

#ifndef _ButtonBoxP_h
#define _ButtonBoxP_h

#ifndef AA
#define AA(args) ()
#endif

#include <X11/IntrinsicP.h>
#include <Xm/ManagerP.h>
#include "ButtonBox.h"


/* 
 * Class Records
 */
typedef struct {
    Boolean junk;  /* Need something */
} XlButtonBoxClassPart;

typedef struct _XlButtonBoxClassRec {
    CoreClassPart	    core_class;
    CompositeClassPart	    composite_class;
    ConstraintClassPart	    constraint_class;
    XmManagerClassPart	    manager_class;
    XlButtonBoxClassPart	    combo_box_class;
} XlButtonBoxClassRec;

extern XlButtonBoxClassRec xlButtonBoxClassRec;


/*
 * Instance Record.
 */
typedef struct _XlButtonBoxPart {
  Dimension entry_margin_height;
  Dimension entry_margin_width;
  Dimension spacing;
  Cardinal orientation;
} XlButtonBoxPart;


typedef struct _XlButtonBoxRec {
    CorePart		core;
    CompositePart	composite;
    ConstraintPart	constraint;
    XmManagerPart	manager;
    XlButtonBoxPart	button_box;
} XlButtonBoxRec;

#endif /* _XmButtonBoxP_h */
