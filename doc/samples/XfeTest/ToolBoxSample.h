/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
// ----------------------------
// ToolBoxSample.h
// Generated by View Designer/X v1.2
//
// User: lazy@apfel
// Date: Thu Apr 23 02:33:07 1998
// ----------------------------

#ifndef _ToolBoxSample_H_
#define _ToolBoxSample_H_

#include "ToolBoxSample_base.h"

class ToolBoxSample : public ToolBoxSample_base {
protected:
  virtual void do_exit(Widget,XtPointer);
  virtual void run(Widget,XtPointer);
  virtual void stop(Widget wg, XtPointer);  
  virtual void lowSpeed(Widget wg, XtPointer);  
  virtual void highSpeed(Widget wg, XtPointer);  

  XtIntervalId  timerId;
  Boolean running;

  int speed;
  
  static void timer(XtPointer clientData, XtIntervalId *id);

public:
  ToolBoxSample(Widget parent = NULL, ArgList args = NULL, Cardinal n = 0);
};


ToolBoxSample *createToolBoxSample(Widget parent, ArgList args, Cardinal n);

#endif /* Don't add stuff after this #endif */