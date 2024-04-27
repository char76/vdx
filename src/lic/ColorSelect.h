/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: ColorSelect.h,v $
 *  $Date: 1999/08/27 15:30:46 $
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
 * $Log: ColorSelect.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:30:46  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:15  lazy
 * Imported to CVS
 *
 * Revision 1.2  1998/03/30 19:08:12  lazy
 * *** empty log message ***
 *
 * Revision 1.1  1997/07/25  20:25:11  lazy
 * Initial revision
 *
 */


#ifndef _ColorSelect_H_
#define _ColorSelect_H_

#include "ColorSelect_base.h"
#include <lac/TArray.h>
#include <lac/Lstring.h>

class ValueView;

class ColorSelect : public ColorSelect_base {
private:
  Display *display;
  Colormap cmap;
  XColor xcolor;
  int maxRedValue, maxGreenValue, maxBlueValue;
  Boolean useCvt;

  static TSortArray<Lstring> colorDB;
  static Boolean init;
  void initColorDB();

  Ref<ValueView> textResView;
  void delNotify( BaseRef * );

protected:
  virtual void valueChanged(Widget,XtPointer);
  virtual void textValueChanged(Widget,XtPointer);
  virtual void colorSelectOk(Widget,XtPointer);
  virtual void colorSelectCancel(Widget,XtPointer);
  virtual void colorSelectHelp(Widget,XtPointer);
  virtual void do_browseSelection(Widget,XtPointer);


public:
  ColorSelect(Widget parent = NULL, ArgList args = NULL, Cardinal n = 0);

  ColorSelect(ValueView *);
  ~ColorSelect();
};


ColorSelect *createColorSelect(Widget parent, ArgList args, Cardinal n);

#endif /* Don't add stuff after this #endif */
