/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: MainWindow.h,v $
 *  $Date: 1999/08/27 15:31:37 $
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
 * $Log: MainWindow.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:31:37  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:15  lazy
 * Imported to CVS
 *
 * Revision 1.2  1998/03/30 19:08:35  lazy
 * *** empty log message ***
 *
 * Revision 1.1  1997/07/25  20:29:12  lazy
 * Initial revision
 *
 */



#ifndef _MainWindow_H_
#define _MainWindow_H_

#include "MainWindow_base.h"
#include "LApp.h"
#include <lac/IconView.h>
#include "Lcreator.h"
#include "Lwidget.h"
#include "Lpalette.h"
#include "Ltmpl.h"
#include <signal.h>
#include "WidgetPalette.h"

class MainWindow : public MainWindow_base {
private:
  LApp *lApp;
  RefArray<Lfile> toOverwrite;

  static RefArray<MainWindow> allViews;

  Ref<IconView> interfaceIconView;
  Ref<WidgetPalette> widgetPalette;

  XtInputId inputId;
  static void inputCallback(XtPointer clientData, int *, XtInputId *);

  static void createWidgetCB(Widget wg, XtPointer client, XtPointer call);

  void testModeChanged(Widget wg, XtPointer callData);
  void newProject(Widget,XtPointer);
  void newProjectCancel(Widget,XtPointer);
  void newProjectHelp(Widget,XtPointer);
  void projectSettingsOk(Widget,XtPointer);
  void projectSettingsCancel(Widget,XtPointer);
  void projectSettingsHelp(Widget,XtPointer);
  void generateOk(Widget,XtPointer);
  void generateCancel(Widget,XtPointer);
  void generateHelp(Widget,XtPointer);
  void gridOkCB(Widget,XtPointer);
  void gridCancelCB(Widget,XtPointer);
  void gridHelpCB(Widget,XtPointer);
  void gridMap(Widget,XtPointer);
  void projectSettingsMap(Widget,XtPointer);
  void loadInterfaceOk(Widget,XtPointer);
  void loadProjectOk(Widget,XtPointer);
  void saveProjectOk(Widget,XtPointer);
  void updatePolicyChanged(Widget,XtPointer);
  void quickHelpMenuMap(Widget,XtPointer);
  void quickHelpChanged(Widget,XtPointer);
  void saveOptions(Widget,XtPointer);
  void showHelp(Widget,XtPointer);
  void do_overwrite(Widget,XtPointer);
  void overwriteCancel(Widget,XtPointer);
  void overwriteHelp(Widget,XtPointer);
  void executeOk(Widget,XtPointer);
  void executeCancel(Widget,XtPointer);
  void executeHelp(Widget,XtPointer);
  void do_stop(Widget,XtPointer);
  void showWidgetPalette(Widget,XtPointer);
  void PSPaletteFileChanged(Widget,XtPointer);
  void PSSourceDirChanged(Widget,XtPointer);
  void DoContextHelp(Widget,XtPointer);
  void DoHelpForHelp(Widget,XtPointer);
  void projectNewMapped(Widget,XtPointer);
  void autoSaveEntry(Widget,XtPointer);
  void autoSaveMap(Widget,XtPointer);
  void do_newTemplates(Widget,XtPointer);
  void do_openTemplates(Widget,XtPointer);
  void do_qsDo(Widget,XtPointer);
  void do_qsChanged(Widget,XtPointer);
  void do_projectSettings(Widget,XtPointer);
  void defaultShellChanged(Widget, XtPointer);
  void do_defaultPublicMap(Widget, XtPointer);
  void do_defaultPublicChanged(Widget, XtPointer);
  void do_defaultPublicAdd(Widget, XtPointer);
  void do_defaultPublicDelete(Widget, XtPointer);
  void do_genericOptionsMap(Widget, XtPointer);
  void do_genericOptionsOk(Widget, XtPointer);
  void do_viewDefaultsMap(Widget, XtPointer);
  void do_viewDefaultsOk(Widget, XtPointer);
  void do_defaultPublicCancel(Widget,XtPointer);
  void do_defaultPublicSelect(Widget,XtPointer);
  void do_defaultPublicFocus(Widget,XtPointer);
  void do_openGlobalResources(Widget,XtPointer);

  static void sigchild_handler(int);

  static pid_t current_pid;

  enum { NOTHING, IMAKEFILE, MAKE_DEPEND, MAKE, PROGRAM } done;

  void updateExecuteDialog(int status);
  void opened();

public: 
  MainWindow(LApp *model);
  ~MainWindow();
  void act(char *action);
  void update(unsigned long flags);
  void wmDelete();

  Boolean saveSize() { return TRUE; }
  Boolean savePosition() { return TRUE; }
  char *getName() { return "MainWindow"; }
  void beforeClose();

  static void withLibLac(Boolean);
};

#endif /* Don't add stuff after this #endif */
