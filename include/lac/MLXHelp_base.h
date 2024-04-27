/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
// -----------------------------------------------------
// MLXHelp_base.h
// 
// This file was automaticly generated by
// View Designer/X                        
//
// Don't edit this file, please !
// -----------------------------------------------------

#ifndef _MLXHelp_base_H_
#define _MLXHelp_base_H_

#include <X11/Intrinsic.h>
#include <lac/LicView.h>



// -----------------------------------------------------
// Class definition 
// class MLXHelp_base is a derived class of LicView
// -----------------------------------------------------

class MLXHelp_base : public LicView {
private:
  void createWidgets();
  void addRelations();
  void addCallbacks();

protected:
  Widget MLXHelp;
  Widget form;
  Widget titleDialog;
  Widget identDialog;
  Widget findDialog;
  Widget rowColumn_1;
  Widget findBeginToggle;
  Widget findCaseToggle;
  Widget menuBar_1;
  Widget File;
  Widget FileMenu;
  Widget Save;
  Widget exportLatex;
  Widget Exit;
  Widget Edit;
  Widget EditMenu;
  Widget View;
  Widget ViewMenu;
  Widget contentsButton;
  Widget Navigate;
  Widget NavigateMenu;
  Widget findButton;
  Widget historyBack;
  Widget historyForward;
  Widget lastSection;
  Widget nextSection;
  Widget backButton;
  Widget panedWindow;
  Widget frame;
  Widget scrolledWindow;
  Widget text;
  Widget forwardButton;
  Widget titleLabel;
  Widget titleText;
  Widget quickHelp;
  Widget exportDialog;
  Widget exportType;
  Widget exportPulldown;
  Widget plainText;
  Widget latexFormat;
  Widget htmlText;


  static void titleDialogMap_CB(Widget,XtPointer,XtPointer);
  static void titleChanged_CB(Widget,XtPointer,XtPointer);
  static void identDialogMap_CB(Widget,XtPointer,XtPointer);
  static void identChanged_CB(Widget,XtPointer,XtPointer);
  static void cancelFindDialog_CB(Widget,XtPointer,XtPointer);
  static void mapFindDialog_CB(Widget,XtPointer,XtPointer);
  static void okFindDialog_CB(Widget,XtPointer,XtPointer);
  static void saveFile_CB(Widget,XtPointer,XtPointer);
  static void exitMLXHelp_CB(Widget,XtPointer,XtPointer);
  static void contentsButtonChanged_CB(Widget,XtPointer,XtPointer);
  static void do_backward_CB(Widget,XtPointer,XtPointer);
  static void do_forward_CB(Widget,XtPointer,XtPointer);
  static void do_lastSection_CB(Widget,XtPointer,XtPointer);
  static void do_nextSection_CB(Widget,XtPointer,XtPointer);
  static void textValueChanged_CB(Widget,XtPointer,XtPointer);
  static void mapExportDialog_CB(Widget,XtPointer,XtPointer);
  static void do_export_CB(Widget,XtPointer,XtPointer);
  static void exportTypeChanged_CB(Widget,XtPointer,XtPointer);



  // override the following methods in class MLXHelp

  virtual void titleDialogMap(Widget,XtPointer) = 0;
  virtual void titleChanged(Widget,XtPointer) = 0;
  virtual void identDialogMap(Widget,XtPointer) = 0;
  virtual void identChanged(Widget,XtPointer) = 0;
  virtual void cancelFindDialog(Widget,XtPointer) = 0;
  virtual void mapFindDialog(Widget,XtPointer) = 0;
  virtual void okFindDialog(Widget,XtPointer) = 0;
  virtual void saveFile(Widget,XtPointer) = 0;
  virtual void exitMLXHelp(Widget,XtPointer) = 0;
  virtual void contentsButtonChanged(Widget,XtPointer) = 0;
  virtual void do_backward(Widget,XtPointer) = 0;
  virtual void do_forward(Widget,XtPointer) = 0;
  virtual void do_lastSection(Widget,XtPointer) = 0;
  virtual void do_nextSection(Widget,XtPointer) = 0;
  virtual void textValueChanged(Widget,XtPointer) = 0;
  virtual void mapExportDialog(Widget,XtPointer) = 0;
  virtual void do_export(Widget,XtPointer) = 0;
  virtual void exportTypeChanged(Widget,XtPointer) = 0;


public:
  MLXHelp_base(Widget parent = NULL, ArgList args = NULL, Cardinal n = 0, char
*fbRes = NULL);

  Widget getTop() { return MLXHelp; }
  Pixmap createPixmapFromData(char **data);
  Pixmap createPixmapFromFile(char *filename);
  static void manageWidget(Widget wg, XtPointer c, XtPointer call);
};

#endif /* Don't add stuff after this #endif */






