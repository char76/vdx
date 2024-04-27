/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: TemplateView.h,v $
 *  $Date: 1999/08/27 15:31:55 $
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
 * $Log: TemplateView.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:31:55  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:17  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/25  20:30:47  lazy
 * Initial revision
 *
 */

// ----------------------------
// TemplateView.h
// ----------------------------

#ifndef _TemplateView_H_
#define _TemplateView_H_

#include "TemplateView_base.h"
#include "Lwidget.h"
#include "ControllerImpl.h"
#include <lac/RefArray.h>
#include <lac/IconView.h>

class Lpalette;
class WidgetIconView;

class TemplateView : public TemplateView_base {
protected:
  virtual void do_save(Widget,XtPointer);
  virtual void do_close(Widget,XtPointer);
  virtual void do_smallIcon(Widget,XtPointer);
  virtual void do_withIcon(Widget,XtPointer);
  virtual void do_withClassName(Widget,XtPointer);
  virtual void do_widgetMenuMap(Widget,XtPointer);
  virtual void do_pasteToTemplate(Widget,XtPointer);
  virtual void do_clickOnCreate(Widget,XtPointer);
  virtual void do_onHelp(Widget,XtPointer);
  virtual void do_onContext(Widget,XtPointer);
  virtual void do_help(Widget,XtPointer);
  virtual void do_saveAs(Widget,XtPointer);
  virtual void do_mapSaveAsDialog(Widget,XtPointer);


  TemplateView(Lpalette *model);
  
  void dropSiteRegister();
  static void dropProc(Widget wg, XtPointer client, XtPointer call);
  static void transferProc(Widget w, XtPointer closure, 
			   Atom *seltype, Atom *type,
			   XtPointer value, unsigned long *length, 
			   int *format);
  static Lpalette *findPalette(Widget dropOver);

  virtual Boolean saveSize() { return TRUE; }

  void wmDelete();
  void update(unsigned long);

  ControllerImpl controllerImpl;

  Lpalette *model;
  static RefArray<TemplateView> allViews;
  WidgetIconView *iconView;
  Boolean createOnClickMode;

public:
  static void showView(Lpalette *model);
  ~TemplateView();

  char *getName() { return "TemplateView"; }

  Boolean getCreateOnClick() { return createOnClickMode; }
};


// ############# PaletteIcon ##########
class PaletteIcon : public Icon {
private:
  Lwidget *lwidget;
public:
  PaletteIcon( Lwidget *am, IconView *iv )
    : Icon( am, iv ) { lwidget=am; }
  PaletteIcon() : Icon() {}
  Icon *copy( Iconable *am, IconView *iv )
    { 
      PaletteIcon *icon = new PaletteIcon((Lwidget*)am, iv); 
      icon->templateView = templateView;
      return icon;
    }

  // action on left mouse button
  void select( Boolean multi, Position x, Position y);

  // ref to parent view
  TemplateView *templateView;
};


#endif /* Don't add stuff after this #endif */
