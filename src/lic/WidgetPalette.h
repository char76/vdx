/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: WidgetPalette.h,v $
 *  $Date: 1999/08/27 15:32:27 $
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
 * $Log: WidgetPalette.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:32:27  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:16  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/25  20:37:17  lazy
 * Initial revision
 *
 */

#ifndef _WidgetPalette_H_
#define _WidgetPalette_H_

#include "WidgetPalette_base.h"
#include <lac/IconView.h>
#include <lac/Ref.h>

class LApp;
class LcreatorIconView;

class WidgetPalette : public WidgetPalette_base {
protected:
  LApp *model;

  Ref<LcreatorIconView> shellIconView;
  Ref<LcreatorIconView> managerIconView;
  Ref<LcreatorIconView> primitiveIconView;
  Ref<LcreatorIconView> dialogIconView;

  void do_close(Widget, XtPointer);
  void do_help(Widget, XtPointer);
  void do_viewEntry(Widget,XtPointer);
  void do_optionsEntry(Widget,XtPointer);
  void do_onHelp(Widget,XtPointer);
  void do_onContext(Widget,XtPointer);

  void act(char*);
  void wmDelete() { close(); }

public:
  WidgetPalette(LApp *);
  ~WidgetPalette();

  char *getName() { return "WidgetPalette"; }

  Boolean saveSize() { return TRUE; }
  Boolean savePosition() { return TRUE; }

  void beforeClose();
};


WidgetPalette *createWidgetPalette(Widget parent, ArgList args, Cardinal n);

#endif /* Don't add stuff after this #endif */
