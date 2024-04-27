/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: ProjectSettings.h,v $
 *  $Date: 1999/08/27 15:31:50 $
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
 * $Log: ProjectSettings.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:31:50  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:17  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/25  20:30:13  lazy
 * Initial revision
 *
 */

// ----------------------------
// ProjectSettings.h
// ----------------------------

#ifndef _ProjectSettings_H_
#define _ProjectSettings_H_

#include "ProjectSettings_base.h"
#include <lac/TArray.h>
#include <lac/Lstring.h>
#include <lac/OptionMenuView.h>

class Lproject;


class ProjectSettings : public ProjectSettings_base {
protected:
  virtual void do_loseFocus(Widget,XtPointer);
  virtual void PSSourceDirChanged(Widget,XtPointer);
  virtual void do_setStartupInterface(Widget,XtPointer);
  virtual void do_mapMoreSourceFiles(Widget,XtPointer);
  virtual void do_moreSourceFiles(Widget,XtPointer);
  virtual void do_ok(Widget,XtPointer);
  virtual void do_cancel(Widget,XtPointer);
  virtual void do_help(Widget,XtPointer);

  static RefArray<ProjectSettings> allViews;

  ProjectSettings(Lproject *lp);
  void wmDelete();

  TSortArray<Lstring> files;
  Lproject *model;
  OptionMenuView startupInterfaceView;

public:
  ~ProjectSettings();

  static void showView(Lproject *lp);

};


#endif /* Don't add stuff after this #endif */
