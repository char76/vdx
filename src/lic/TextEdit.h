/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: TextEdit.h,v $
 *  $Date: 1999/08/27 15:32:00 $
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
 * $Log: TextEdit.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:32:00  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:15  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/25  20:31:04  lazy
 * Initial revision
 *
 */



#ifndef _TextEdit_H_
#define _TextEdit_H_

#include "TextEdit_base.h"

class ValueView;

class TextEdit : public TextEdit_base {
private:
  Ref<ValueView> textResView;

  static RefArray<TextEdit> allViews;

  void delNotify(BaseRef *);

protected:
  virtual void saveAndExit(Widget,XtPointer);
  virtual void cutText(Widget,XtPointer);
  virtual void copyText(Widget,XtPointer);
  virtual void pasteText(Widget,XtPointer);
  virtual void helpMe(Widget,XtPointer);
  virtual void quickHelpChanged(Widget,XtPointer);
  virtual void helpCallback(Widget,XtPointer);
  virtual void importFile(Widget,XtPointer);
  virtual void exportFile(Widget,XtPointer);
  virtual void doExit(Widget,XtPointer);
  virtual void do_onHelp(Widget, XtPointer);
  virtual void do_onContext(Widget, XtPointer);


public:
  TextEdit(ValueView *textResView);

};


#endif /* Don't add stuff after this #endif */
