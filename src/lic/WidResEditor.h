/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: WidResEditor.h,v $
 *  $Date: 1999/08/27 15:32:22 $
 *  $Revision: 1.1.1.1.2.2 $
 *
 *  Copyright 1997, Dirk Laessig
 *  ALL RIGHTS RESERVED
 *  See the file Copyright for more information
 *
 *  Dirk Laessig
 *  Goettingstr. 5
 *  38106 Braunschweig
 *  Germany
 ****************************************************************/
/*
 * $Log: WidResEditor.h,v $
 * Revision 1.1.1.1.2.2  1999/08/27 15:32:22  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1.2.1  1998/07/01 18:31:45  lazy
 * Patches gcc 2.8
 *
 * Revision 1.1.1.1  1998/04/24 23:45:16  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/25  20:37:06  lazy
 * Initial revision
 *
 */

// ----------------------------
// WidResEditor.h
// ----------------------------

#ifndef _WidResEditor_H_
#define _WidResEditor_H_

#include "WidResEditor_base.h"
#include <lac/CallbackMethod.h>

class Lwidget;
class ResView;
class Lresource;
class WidNameView;
class WidManageView;
class WidDescriptionView;
class WidQuickHelpView;
class WidHelpNodeView;

enum PropertyWin {         // used to determine the view type
  PW_CORE, PW_SPECIFIC, PW_CONSTRAINT, PW_CALLBACKS, PW_EXTRA, PW_USER
};

class WidResEditor : public WidResEditor_base {
private:
  PropertyWin currentPropertyWin;    // the current view to resources

  // we want notifications from Selectable

  class SelectionCallback : public CallbackMethod {
  private:
    WidResEditor *parent;
  public:
    SelectionCallback(WidResEditor *m) { parent = m; }
    void call();
  } selectionCallback;

  friend class SelectionCallback;

  // the parent widgets of the resources
  Widget coreW, specificW, constraintW, callbacksW, extraW;

  // the resources entries
  RefArray<ResView> core, specific, constraint, callbacks;

  Ref<WidNameView> widNameView;
  Ref<WidManageView> widManageView;
  Ref<WidDescriptionView> widDescriptionView;
  Ref<WidQuickHelpView> widQuickHelpView;
  Ref<WidHelpNodeView> widHelpNodeView;

  // function to create a resources entry
  ResView *createResView( Lresource *lres, Widget parent, Cardinal r);

  // sets the current category label
  void setCategoryLabel(char *msg);

protected:

  // the callback, invoked by base class
  virtual void do_load(Widget,XtPointer);
  virtual void do_apply(Widget,XtPointer);
  virtual void do_close(Widget,XtPointer);
  virtual void do_viewChanged(Widget,XtPointer);
  virtual void do_automaticLoad(Widget,XtPointer);
  virtual void do_withSource(Widget,XtPointer);
  virtual void do_onHelp(Widget,XtPointer);
  virtual void do_onContext(Widget,XtPointer);
  virtual void do_help(Widget,XtPointer);

  // the window managers send WM_DELETE
  void wmDelete() { do_close(NULL, NULL); }

  // data for this view
  Lwidget *model;

  // to implement the view behavior
  static RefArray<WidResEditor> allViews;
  static Ref<WidResEditor> automaticLoadView;
  
  // constructor PROTECTED
  WidResEditor(Lwidget *lwidget);

  // update the name in title bar
  void update(unsigned long flags);

  // set the current model
  void setWidget(Lwidget *m);

  // change the view of resources
  void switchTo( PropertyWin pw );

  // if something has changed in the resource entries, return TRUE
  Boolean somethingChanged();

  // apply changes
  Boolean apply();

public:
  
  // my little interface
  static void showView(Lwidget *lwidget);
  ~WidResEditor();

  Boolean saveSize() { return TRUE; }
  char *getName() { return "WidgetResourceEditor"; }
};


#endif /* Don't add stuff after this #endif */
