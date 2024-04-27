/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: LresEditor.h,v $
 *  $Date: 1999/08/27 15:31:24 $
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
 * $Log: LresEditor.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:31:24  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:13  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/25  20:28:13  lazy
 * Initial revision
 *
 */

// ------------------------------------------------
// LresEditor
// Classes LresEditor (View of Lwidget) and 
// Component classes ResView (View of Lresource)
//                    - TextResView
//                      - ColorResView
//                      - FontResView
//                    - EnumResView
// ------------------------------------------------
#ifndef _LRESEDITOR_H_
#define _LRESEDITOR_H_

#include <Xm/Text.h>

#include "Lwidget.h"
#include "lic.h"

#include <lac/View.h>
#include <lac/LicView.h>


// -------------- LresEditor ---------
// View of Lwidget

class ResView;

class LresEditor : public LicView {
private:
  
  // a little helpful class

  class HelpNodeView : public View {
  private:
    Ref<HelpNode> helpNode;
    Widget textWidget;
    void update(unsigned long int) {
      if(helpNode.isNil())
	XmTextSetString(textWidget, "");
      else
	XmTextSetString(textWidget, helpNode->getName());
    }
    Boolean destroyFromModel() { return FALSE; }
  public:
    HelpNodeView(Widget wg, HelpNode *hn = NULL): View(hn), helpNode(hn, this)
      {
	textWidget = wg;
	update(0);
      }
    HelpNode *getHelpNode() { return helpNode; }
  };

  static RefArray<LresEditor> allViews;      // store all views
  
  Lwidget *lwidget;
  Widget shell, scrolledW;
  Widget coreW, specificW, constraintW, callbacksW, extraW;
  Widget quickHelpLabel;
  Widget applyB, closeB, helpB;
 
  Widget nameLabelW, manageLabelW, quickHelpLabelW;
  Widget nameTextW, manageToggleW, quickHelpTextW;
  Widget helpNodeLabelW, helpNodeTextW, helpNodeButtonW;
  HelpNodeView *hnView;

  RefArray<ResView> core, specific, constraint, callbacks;

  Widget autoLoadToggle;
  static Ref<LresEditor> autoLoad;
  static void autoLoadCallback( Widget, XtPointer, XtPointer );

  enum PropertyWin {
    PW_CORE, PW_SPECIFIC, PW_CONSTRAINT, PW_CALLBACKS, PW_EXTRA
    };
  
  PropertyWin currentPropertyWin;

  void fillExtra();
  
  LresEditor( Lwidget* model );
  void switchTo( PropertyWin pw );
  void setNewLwidget( Lwidget *lwidget );
  static LresEditor* getAutoLoad() { return autoLoad; } 
  Boolean somethingChanged();

  void helpNodeDropSiteRegister();
  static void helpNodeDropProc(Widget wg, XtPointer client, XtPointer call);
  static void helpNodeTransferProc(Widget w, XtPointer closure, 
				   Atom *seltype, Atom *type,
				   XtPointer value, unsigned long *length, 
				   int *format);
  static void configureEvent(Widget, XtPointer clientData, 
			     XEvent* event, Boolean*);

  void linkWithHelpNode(HelpNode *helpNode);


  // the help callback
  static void helpCallback(Widget, XtPointer, XtPointer) {
    LicView::getHelp(HID_WIDGET_RESOURCE_EDITOR);
  }

public:
  ~LresEditor();

  Boolean apply();
  void update( unsigned long flags );
  void act( char * action );

  ResView *createResView( Lresource *lres, Widget parent, Cardinal r);

  static LresEditor *showEditor(Lwidget *lwidget);    // prefer this 
  static void withLibLac(Boolean);
};


// ------------- ValueView ------------
// View to any value of the model 
// abstract base class

class ValueView : public WinView {
protected:
  Boolean changed;               // true if valueChangedCallback 

public:
  ValueView( Model *model ) : WinView(model) { changed = FALSE; }
  
  virtual Boolean apply() = 0;
  Boolean isChanged() { return changed; }

  virtual void getText(char *, unsigned long &) {}
  virtual void setText(char *) {}
};

// ------------- ResView ---------------
// View of Lresource

class ResView : public ValueView {
protected:
  LicView *pView;             // parent view
  Lresource *lresource;          // the model
  Widget table;                    // the XlCellTable widget as parent
  Widget label;                  // name of the resource
  //  Widget toResize;               // Widget for resize
  //  Widget beforeMenu;             // widget before the attrMenu
  Widget attrMenu;               // attr menu

  Cardinal r;                    // row index

  static void valueChangedCallback( Widget, XtPointer self, XtPointer );
                                 // should added by derived classes
                                 // clientData is a pointer to instance
  void createAttributeMenu();    // called in constructor of derived class

public:
  ResView( Lresource *model, Widget parent, LicView *pView, Cardinal r);
  ~ResView();                    // destroy row
  Boolean apply();               // put value in model
                                 // return true if value chnaged to default

  virtual void getStringValue( char *buffer, unsigned int &len ) = 0;
                                 // buffer == NULL -> len returns string len
                                 // buffer allocated -> len = sizeof buffer

  void update( unsigned long flags );
                                 // reset the changed flag 

  void setNewLresource( Lresource * );  // change the model
  //  void setWidth(Dimension w);
};


// ---------------------- TexResView ----------------------
// View of Lresource
// A TextWidget contains the string presentation of
// the resource value
//
// derive the class, if you want to have extra button 
// to activate another editor (font-chooser, color-edit)

class TextResView : public ResView {
protected:
  Widget textWidget;

  void activateCallback(Widget, XtPointer, XtPointer);

public:
  TextResView( Lresource *model, Widget parent, LicView *pView, Cardinal r);
  
  void getStringValue( char *buffer, unsigned int &len );
  void update( unsigned long flags );


  void getText(char *text, unsigned long &len);
  void setText(char *text);

  void act( char * ) {}
};

// ------------------ FontResView ---------------------
class FontSelect;

class FontResView : public TextResView {
private:
  Widget button;
  Ref<FontSelect> fontSelect;

  static void fontSelectCallback(Widget,XtPointer,XtPointer);

public:
  FontResView(Lresource *model, Widget parent, LicView *pView, Cardinal r);

};


// ------------------ ColorResView ---------------------
class ColorSelect;

class ColorResView : public TextResView {
private:
  Widget button;
  Ref<ColorSelect> colorSelect;

  static void colorSelectCallback(Widget,XtPointer,XtPointer);

public:
  ColorResView(Lresource *model, Widget parent, LicView *pView, Cardinal r);

};


// ------------------ MultiTextResView ---------------------
class TextEdit;

class MultiTextResView : public TextResView {
private:
  Widget button;
  Ref<TextEdit> textEdit;

  static void multiTextCallback(Widget,XtPointer,XtPointer);

public:
  MultiTextResView(Lresource *model, Widget parent, LicView *pView, 
		   Cardinal r);

};


// ---------------------- BooleanResView ----------------------
// View of Lresource
// A ToggleButton shows the value
//

class BooleanResView : public ResView {
protected:
  Widget toggleWidget;

public:
  BooleanResView( Lresource *model, Widget parent, LicView *aView, 
		  Cardinal r);
  
  void getStringValue( char *buffer, unsigned int &len );
  void update( unsigned long flags );

  void act( char * ) {}
};

// ---------------------- EnumResView ----------------------
// View of Lresource
// A EnumButton shows the value
//

class EnumResView : public ResView {
protected:
  Widget menu;

public:
  EnumResView( Lresource *model, Widget parent, LicView *pView, Cardinal r);
  
  void getStringValue( char *buffer, unsigned int &len );
  void update( unsigned long flags );

  void act( char * ) {}
};



// --------------------- WidNameView ---------------------
// Widget Name View

class WidNameView : public ValueView {
private:
  Widget label;
  Widget text;
  Lwidget *model;

  static void valueChangedCallback( Widget, XtPointer self, XtPointer );

public:
  WidNameView( Lwidget *model, Widget parent, LicView *pView, Cardinal r);
  
  Boolean apply();
  void update(unsigned long flags);

  void setNewLwidget(Lwidget *model);
  
  void act(char *) {}
};


// --------------------- WidDescriptionView ---------------------
// Widget Name View

class WidDescriptionView : public ValueView {
private:
  Widget label;
  Widget text;
  Lwidget *model;

  static void valueChangedCallback( Widget, XtPointer self, XtPointer );

public:
  WidDescriptionView( Lwidget *model, Widget parent, LicView *pView, Cardinal r);
  
  Boolean apply();
  void update(unsigned long flags);

  void setNewLwidget(Lwidget *model);
  
  void act(char *) {}
};


// --------------------- WidQuickHelpView ---------------------
// Widget Name View

class WidQuickHelpView : public ValueView {
private:
  Widget label;
  Widget text;
  Lwidget *model;

  static void valueChangedCallback( Widget, XtPointer self, XtPointer );

public:
  WidQuickHelpView( Lwidget *model, Widget parent, LicView *pView, Cardinal r);
  
  Boolean apply();
  void update(unsigned long flags);

  void setNewLwidget(Lwidget *model);
  
  void act(char *) {}
};


// --------------------- WidHelpNodeView ---------------------
// Widget Name View

class WidHelpNodeView : public ValueView {
private:
  Widget label;
  Widget text;
  Widget clearButton;
  Lwidget *model;
  Ref<HelpNode> helpNode;

  static void valueChangedCallback( Widget, XtPointer self, XtPointer );

  void dropSiteRegister();
  static void dropProc(Widget wg, XtPointer client, XtPointer call);
  static void transferProc(Widget w, XtPointer closure, 
			   Atom *seltype, Atom *type,
			   XtPointer value, unsigned long *length, 
			   int *format);

  static RefArray<WidHelpNodeView> allViews;
public:
  WidHelpNodeView( Lwidget *model, Widget parent, LicView *pView, Cardinal r);
  
  Boolean apply();
  void update(unsigned long flags);

  void setNewLwidget(Lwidget *model);
  
  void act(char *);
};


// --------------------- WidManageView ---------------------
// Widget Manage View

class WidManageView : public ValueView {
private:
  Widget label;
  Widget toggle;
  Lwidget *model;

  static void valueChangedCallback( Widget, XtPointer self, XtPointer );

public:
  WidManageView( Lwidget *model, Widget parent, LicView *pView, Cardinal r);
  
  Boolean apply();
  void update(unsigned long flags);

  void setNewLwidget(Lwidget *model);
  
  void act(char *) {}
};


#endif /* DON'T .. */

