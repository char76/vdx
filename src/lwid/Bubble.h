/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: Bubble.h,v $
 *  $Date: 1999/08/27 15:32:57 $
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
 * $Log: Bubble.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:32:57  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:54  lazy
 * Imported to CVS
 *
 * Revision 1.4  1998/03/30 19:10:26  lazy
 * *** empty log message ***
 *
 * Revision 1.3  1997/09/06  11:42:51  lazy
 * added enabled flag
 *
 * Revision 1.2  1997/06/22  20:23:53  lazy
 * Short comment inserted.
 *
 * Revision 1.1  1997/06/22  20:09:45  lazy
 * Initial revision
 *
 */

#ifndef _Bubble_h
#define _Bubble_h

#ifdef __cplusplus
extern "C" {
#endif

#include <Xm/Xm.h>

  /*
   * A short description of resources 
   *
   * labelString        displayed text
   * labelWidget        internal label widget   (read only)
   * offsetX            x offset from placement
   * offsetY            y offset from placement
   * placement          place where bubble is poped up
   * timeout            time after enter event til pop up
   *
   * Other resources of the internal label widget should be accessed
   * via:
   *       1. GetValues to get labelWidget and set explicitly
   *       2. Resource file with widget's name "Label"
   */


#ifndef XmNoffsetX
#define XmNoffsetX "offsetX"
#endif
#ifndef XmNoffsetY
#define XmNoffsetY "offsetY"
#endif
#ifndef XmCOffsetX
#define XmCOffsetX "OffsetX"
#endif
#ifndef XmCOffsetY
#define XmCOffsetY "OffsetY"
#endif
#ifndef XmNtimeout
#define XmNtimeout "timeout"
#endif
#ifndef XmCTimeout
#define XmCTimeout "timeout"
#endif
#ifndef XmNplacement
#define XmNplacement "placement"
#endif
#ifndef XmCPlacement
#define XmCPlacement "Placement"
#endif
#ifndef XmRBubblePlacement
#define XmRBubblePlacement "BubblePlacement"
#endif
#ifndef XmNlabelWidget
#define XmNlabelWidget "labelWidget"
#endif
#ifndef XmCLabelWidget
#define XmCLabelWidget "LabelWidget"
#endif
#ifndef XmNuseEvents
#define XmNuseEvents "useEvents"
#endif
#ifndef XmCUseEvents
#define XmCUseEvents "useEvents"
#endif

typedef enum {                 /* Resource Converter not available */
  XmBUBBLE_POINTER,
  XmBUBBLE_TOP_LEFT,
  XmBUBBLE_TOP_RIGHT,
  XmBUBBLE_BOTTOM_LEFT,
  XmBUBBLE_BOTTOM_RIGHT
} BubblePlacement;

extern WidgetClass xlBubbleWidgetClass;    /* Widget Class */

typedef struct _XlBubbleClassRec *XlBubbleWidgetClass;
typedef struct _XlBubbleRec      *XlBubbleWidget;

extern Widget XlCreateBubble(Widget parent, char *name,  /* Create function */
			     Arg *arglist, int num_args);

extern Boolean XlBubbleIsEnabled();
extern void XlBubbleSetEnabled(Boolean enabled);


extern void XlBubbleSimEnter(Widget wg, Position x, Position y,
			     Dimension width, Dimension height,
			     XmString xms);
extern void XlBubbleSimLeave(Widget wg);

#ifdef __cplusplus
}
#endif
#endif	/* _Bubble_h */

