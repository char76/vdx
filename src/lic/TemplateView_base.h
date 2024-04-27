/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
// -----------------------------------------------------
// TemplateView_base.h
// 
// This file was automaticly generated by
// View Designer/X  v1.2
//
// User: lazy@apfel
// Date: Tue Jun  2 17:02:48 1998
//
// Don't edit this file, please !
// -----------------------------------------------------

#ifndef _TemplateView_base_H_
#define _TemplateView_base_H_

#include <X11/Intrinsic.h>
#include <lac/LicView.h>



// -----------------------------------------------------
// Class definition 
// class TemplateView_base is a derived class of LicView
// -----------------------------------------------------

class TemplateView_base : public LicView {
private:
  void createWidgets();
  void addRelations();
  void addCallbacks();

protected:
  Widget TemplateView;
  Widget templateMainWindow;       /* XmMainWindow */
  Widget templateMenuBar;       /* XmCreateMenuBar */
  Widget fileButton;       /* XmCascadeButton */
  Widget fileMenu;       /* XmCreatePulldownMenu */
  Widget saveButton;       /* XmPushButton */
  Widget saveAsButton;       /* XmPushButton */
  Widget closeButton;       /* XmPushButton */
  Widget viewButton;       /* XmCascadeButton */
  Widget viewMenu;       /* XmCreatePulldownMenu */
  Widget smallIconButton;       /* XmToggleButton */
  Widget withIconButton;       /* XmToggleButton */
  Widget withClassNameButton;       /* XmToggleButton */
  Widget widgetButton;       /* XmCascadeButton */
  Widget widgetMenu;       /* XmCreatePulldownMenu */
  Widget pasteToTemplateButton;       /* XmPushButton */
  Widget separator_1;       /* XmSeparator */
  Widget editButton;       /* XmPushButton */
  Widget browseButton;       /* XmPushButton */
  Widget cutButton;       /* XmPushButton */
  Widget copyButton;       /* XmPushButton */
  Widget pasteButton;       /* XmPushButton */
  Widget separator;       /* XmSeparator */
  Widget deleteButton;       /* XmPushButton */
  Widget optionsButton;       /* XmCascadeButton */
  Widget optionsMenu;       /* XmCreatePulldownMenu */
  Widget createOnClick;       /* XmToggleButton */
  Widget helpButton;       /* XmCascadeButton */
  Widget helpMenu;       /* XmCreatePulldownMenu */
  Widget onHelp;       /* XmPushButton */
  Widget onContext;       /* XmPushButton */
  Widget onWidResEditor;       /* XmPushButton */
  Widget templateForm;       /* XmForm */
  Widget quickHelp;       /* XmLabel */
  Widget templateFrame;       /* XmFrame */
  Widget saveAsDialog;       /* XmCreateFileSelectionDialog */


  static void do_save_CB(Widget,XtPointer,XtPointer);
  static void do_close_CB(Widget,XtPointer,XtPointer);
  static void do_smallIcon_CB(Widget,XtPointer,XtPointer);
  static void do_withIcon_CB(Widget,XtPointer,XtPointer);
  static void do_withClassName_CB(Widget,XtPointer,XtPointer);
  static void do_widgetMenuMap_CB(Widget,XtPointer,XtPointer);
  static void do_pasteToTemplate_CB(Widget,XtPointer,XtPointer);
  static void do_clickOnCreate_CB(Widget,XtPointer,XtPointer);
  static void do_onHelp_CB(Widget,XtPointer,XtPointer);
  static void do_onContext_CB(Widget,XtPointer,XtPointer);
  static void do_help_CB(Widget,XtPointer,XtPointer);
  static void do_mapSaveAsDialog_CB(Widget,XtPointer,XtPointer);
  static void do_saveAs_CB(Widget,XtPointer,XtPointer);



  // override the following methods in class TemplateView

  virtual void do_save(Widget,XtPointer) = 0;
  virtual void do_close(Widget,XtPointer) = 0;
  virtual void do_smallIcon(Widget,XtPointer) = 0;
  virtual void do_withIcon(Widget,XtPointer) = 0;
  virtual void do_withClassName(Widget,XtPointer) = 0;
  virtual void do_widgetMenuMap(Widget,XtPointer) = 0;
  virtual void do_pasteToTemplate(Widget,XtPointer) = 0;
  virtual void do_clickOnCreate(Widget,XtPointer) = 0;
  virtual void do_onHelp(Widget,XtPointer) = 0;
  virtual void do_onContext(Widget,XtPointer) = 0;
  virtual void do_help(Widget,XtPointer) = 0;
  virtual void do_mapSaveAsDialog(Widget,XtPointer) = 0;
  virtual void do_saveAs(Widget,XtPointer) = 0;


public:
  TemplateView_base(Widget parent = NULL, ArgList args = NULL, Cardinal n = 0, char
*fbRes = NULL);

  Widget getTop() { return TemplateView; }
  Pixmap createPixmapFromData(char **data);
  Pixmap createPixmapFromFile(char *filename);
  static void manageWidget(Widget wg, XtPointer c, XtPointer call);
};

#endif /* Don't add stuff after this #endif */






