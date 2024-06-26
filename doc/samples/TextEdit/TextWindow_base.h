/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
// -----------------------------------------------------
// TextWindow_base.h
// 
// This file was automaticly generated by
// View Designer/X                          
//
// Don't edit this file, please !
// -----------------------------------------------------

#ifndef _TextWindow_base_H_
#define _TextWindow_base_H_

#include <X11/Intrinsic.h>
#include "VcView.h"



// -----------------------------------------------------
// Class definition 
// class TextWindow_base is a derived class of VcView
// -----------------------------------------------------

class TextWindow_base : public VcView {
private:
  void createWidgets();
  void addRelations();
  void addCallbacks();

protected:
  Widget TextWindow;
  Widget mainWindow;
  Widget menuBar;
  Widget fileButton;
  Widget fileMenu;
  Widget openButton;
  Widget saveButton;
  Widget saveAsButton;
  Widget exitButton;
  Widget editButton;
  Widget editMenu;
  Widget cutButton;
  Widget copyButton;
  Widget pasteButton;
  Widget textWidget;
  Widget exitDialog;
  Widget fileOpenDialog;
  Widget fileSaveAsDialog;
  Widget noHelpDialog;


  static void do_save_CB(Widget,XtPointer,XtPointer);
  static void do_cut_CB(Widget,XtPointer,XtPointer);
  static void do_copy_CB(Widget,XtPointer,XtPointer);
  static void do_paste_CB(Widget,XtPointer,XtPointer);
  static void text_changed_CB(Widget,XtPointer,XtPointer);
  static void do_exit_CB(Widget,XtPointer,XtPointer);
  static void do_open_CB(Widget,XtPointer,XtPointer);
  static void do_saveAs_CB(Widget,XtPointer,XtPointer);



  // override the following methods in class TextWindow

  virtual void do_save(Widget,XtPointer) = 0;
  virtual void do_cut(Widget,XtPointer) = 0;
  virtual void do_copy(Widget,XtPointer) = 0;
  virtual void do_paste(Widget,XtPointer) = 0;
  virtual void text_changed(Widget,XtPointer) = 0;
  virtual void do_exit(Widget,XtPointer) = 0;
  virtual void do_open(Widget,XtPointer) = 0;
  virtual void do_saveAs(Widget,XtPointer) = 0;


public:
  TextWindow_base(Widget parent = NULL, ArgList args = NULL, Cardinal n = 0);

  Widget getTop() { return TextWindow; }
  Pixmap createPixmapFromData(char **data);
  Pixmap createPixmapFromFile(char *filename);
  static void manageWidget(Widget wg, XtPointer c, XtPointer call);
};

#endif /* Don't add stuff after this #endif */






