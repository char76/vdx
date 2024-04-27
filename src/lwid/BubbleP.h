/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: BubbleP.h,v $
 *  $Date: 1999/08/27 15:32:58 $
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
 * $Log: BubbleP.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:32:58  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:54  lazy
 * Imported to CVS
 *
 * Revision 1.4  1998/03/30 19:10:32  lazy
 * *** empty log message ***
 *
 * Revision 1.3  1997/09/06  11:42:37  lazy
 * added enabled flag
 *
 * Revision 1.2  1997/06/22  20:11:46  lazy
 * clean up
 *
 * Revision 1.1  1997/06/22  20:10:05  lazy
 * Initial revision
 *
 */

#ifndef _BubbleP_h
#define _BubbleP_h

#include <X11/IntrinsicP.h>
#include <X11/ShellP.h>
#include "Bubble.h"


/* 
 * Class Records
 */
typedef struct {
    Boolean enabled;                   /* Bubble enabled */
} XlBubbleClassPart;

typedef struct _XlBubbleClassRec {
    CoreClassPart	    core_class;
    CompositeClassPart	    composite_class;
    ShellClassPart	    shell_class;
    OverrideShellClassPart  override_shell_class;
    XlBubbleClassPart	    bubble_class;
} XlBubbleClassRec;

extern XlBubbleClassRec xlBubbleClassRec;


/*
 * Instance Record.
 */
typedef struct _XlBubblePart {

  /* public data (resources) */
  XmString labelString;
  Position offsetX;
  Position offsetY;
  Dimension timeout;
  BubblePlacement placement;
  Widget label;
  Boolean useEvents;

  /* private data */
  XtIntervalId timer;
  Position areaX;
  Position areaY;
  Dimension areaWidth;
  Dimension areaHeight;

} XlBubblePart;


typedef struct _XlBubbleRec {
    CorePart		core;
    CompositePart	    composite;
    ShellPart		    shell;
    OverrideShellPart	    override;
    XlBubblePart	bubble;
} XlBubbleRec;

#endif /* _XmBubbleP_h */
