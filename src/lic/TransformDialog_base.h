/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
// -----------------------------------------------------
// TransformDialog_base.h
// 
// This file was automaticly generated by
// View Designer/X  v1.2
//
// User: lazy@apfel
// Date: Tue Jun  2 17:02:50 1998
//
// Don't edit this file, please !
// -----------------------------------------------------

#ifndef _TransformDialog_base_H_
#define _TransformDialog_base_H_

#include <X11/Intrinsic.h>
#include <lac/LicView.h>



// -----------------------------------------------------
// Class definition 
// class TransformDialog_base is a derived class of LicView
// -----------------------------------------------------

class TransformDialog_base : public LicView {
private:
  void createWidgets();
  void addRelations();
  void addCallbacks();

protected:
  Widget TransformDialog;
  Widget messageBox;       /* XmMessageBox */
  Widget widgetClassOptionMenu;       /* XmCreateOptionMenu */
  Widget pulldownMenu;       /* XmCreatePulldownMenu */
  Widget pushButton;       /* XmPushButton */


  static void do_cancel_CB(Widget,XtPointer,XtPointer);
  static void do_ok_CB(Widget,XtPointer,XtPointer);



  // override the following methods in class TransformDialog

  virtual void do_cancel(Widget,XtPointer) = 0;
  virtual void do_ok(Widget,XtPointer) = 0;


public:
  TransformDialog_base(Widget parent = NULL, ArgList args = NULL, Cardinal n = 0, char
*fbRes = NULL);

  Widget getTop() { return TransformDialog; }
  Pixmap createPixmapFromData(char **data);
  Pixmap createPixmapFromFile(char *filename);
  static void manageWidget(Widget wg, XtPointer c, XtPointer call);
};

#endif /* Don't add stuff after this #endif */






