/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
// ----------------------------
// HelpView.h
// ----------------------------

#ifndef _HelpView_H_
#define _HelpView_H_

#include "HelpView_base.h"

// implements a help window

class HelpView : public HelpView_base {
private:
  struct HelpText {
    char *interface;
    char *widget;
    char *text;
  };

  static HelpView *helpView;   // the one and only instance
  static HelpText helpText[];  // all help texts

protected:
  virtual void close_window(Widget,XtPointer);  // a callback

  HelpView();                 // is protected, called by showHelp()

public:

  // create an instance of HelpView if needed,
  // look for a help text in helpText[]
  // shows the view

  static void showHelp(char *interface, char *widget);
};

#endif /* Don't add stuff after this #endif */
