/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: TransformDialog.h,v $
 *  $Date: 1999/08/27 15:32:06 $
 *  $Revision: 1.1.1.1.2.1 $
 *
 *  Copyright 1997, Dirk Laessig
 *  ALL RIGHTS RESERVED
 *  See the file Copyright for more information
 *
 *  Dirk Laessig
 *  Goettingstr. 5
 *  38106 Braunschweig
 *  Germany
 ****************************************************************/
/*
 * $Log: TransformDialog.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:32:06  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:18  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/25  20:35:44  lazy
 * Initial revision
 *
 */

// ----------------------------
// TransformDialog.h
//
// This file was automaticly generated by
// View Designer/X v1.1.0
//
// User: lazy@apfel.goetting5
// Date: Fri Jul 18 18:23:25 1997
//
// ----------------------------

#ifndef _TransformDialog_H_
#define _TransformDialog_H_

#include "TransformDialog_base.h"
#include <lac/OptionMenuView.h>

class Lwidget;

class TransformDialog : public TransformDialog_base {
protected:
  virtual void do_cancel(Widget,XtPointer);
  virtual void do_help(Widget,XtPointer);
  virtual void do_ok(Widget,XtPointer);

  Lwidget *model;
  //  OptionMenuView classView;

  static RefArray<TransformDialog> allViews;

  void wmDelete() { do_cancel(NULL, NULL); }

  void update(unsigned long flags);
  TransformDialog(Lwidget *lwidget);

public:
  static void showView(Lwidget *lwidget);

  ~TransformDialog();
  char *getName() { return "TransformDialog"; }
};


#endif /* Don't add stuff after this #endif */
