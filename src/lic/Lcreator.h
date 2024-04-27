/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: Lcreator.h,v $
 *  $Date: 1999/08/27 15:31:14 $
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
 * $Log: Lcreator.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:31:14  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:13  lazy
 * Imported to CVS
 *
 * Revision 1.2  1998/02/10  01:02:42  lazy
 * - add compare method to WidClassCategory
 * - move LClassInfo to vdxlib
 *
 * Revision 1.1  1997/07/25  20:26:49  lazy
 * Initial revision
 *
 */

// ---------------------------------------------
// Lcreator.h - Definition of class Lcreator
// (C) Dirk Laessig
// ---------------------------------------------
#ifndef _LCREATOR_H_
#define _LCREATOR_H_

#include <X11/IntrinsicP.h>
#include <X11/CoreP.h>
#include <lac/IconView.h>
#include <lac/LicView.h>
#include <lac/ConModel.h>

#include <vdxlib/LClassInfo.h>

#include <lac/LHashDictionary.h>

class Lwidget;


// -----------------------------------------
// Lcreator - Presents a WidgetClass
// -----------------------------------------

class Lcreator : public Iconable {
private:
  friend class WidClasses;
  friend class WidClassCategory;

  static Container<Lcreator> classes;            // All classes
  static Container<Lcreator> shellClasses;      
  static Container<Lcreator> managerClasses;    
  static Container<Lcreator> primitiveClasses;
  static Container<Lcreator> dialogClasses;

  LClassInfo &ci;
  String class_name;
  String pixmap;
  WidgetClass widget_class;
  Lstring description;             // Description String

  char *shortName;

  Cardinal created;                  // count the instances of this class
  Boolean shell;

  Widget dummy;                      // used for query default resources
  static char *defaultShellName;
  static char *linkContainer;        // normal XmFrame

  // resources
  TArray<char> possibleResources;     // all possible importent resources
  TArray<char> importentResources;    // for LresEditor
  
public:
  Lcreator( LClassInfo &ci);
  ~Lcreator()  {}

  WidgetClass getWidgetClass() { return ci.widget_class ? ci.widget_class : XtClass(dummy); }
  String getWidgetClassStr() { return ci.widget_class_str; }
  String getCreateFuncStr() { return ci.create_func_str; }
  String getHeader() { return ci.header_file; }
  ManagePolicy getManagePolicy() { return ci.managePolicy; }
  UpdatePolicy getUpdatePolicy() { return ci.updatePolicy; }
  Boolean getDefaultSize() { return ci.defaultSize; }
  char *getShortName() { return shortName; }

  Lwidget *createLwidget( Lwidget *parent );
  Widget createWidget(Widget parent, char* name, ArgList args, Cardinal n);

  TArray<char> getPossibleResources() { return possibleResources; }
  void setPossibleResources(TArray<char> &r) { possibleResources = r; }
  TArray<char> getImportentResources() { return importentResources; }
  void setImportentResources(TArray<char> &r) { importentResources = r; }

  Boolean isShell();
  Boolean asChildOk(Lcreator *toCheck);

  // Query some informations
  static Lcreator *getClass( char *name );
  static Lcreator *getDefaultShell() { return getClass(defaultShellName); }
  static void setDefaultShell(Lcreator *shell) 
    { defaultShellName = shell->class_name; }
  static Lcreator *getLinkContainer() { return getClass(linkContainer); }
  
  char *getName() { return class_name; }
  char *getDescription();
  char *getPixmapFile() { return pixmap; }
  char *getClassName() { return "Lcreator"; }

  // Return TRUE if this subclasses widgetClass
  Boolean isSubclass(WidgetClass widgetClass);

  // Save the resources that are not handled by VDX
  LHashDictionary<Lstring> unhandledResources;

  // Get Widgets
  static Container<Lcreator> &getContainer() { return classes; }
  static Container<Lcreator> &getShells() { return shellClasses; }
  static Container<Lcreator> &getManager() { return managerClasses; }
  static Container<Lcreator> &getPrimitives() { return primitiveClasses; }
  static Container<Lcreator> &getDialogs() { return dialogClasses; }

  // ------------- to sort the classes --------------
  static int compare( const void *r1, const void *r2 );
};


//
// WidClassCategory - Named Container for Lcreator objects
//

class WidClassCategory : public Iconable {
private:
  Container<Lcreator> creators;
  Lstring name;

public:
  WidClassCategory(Lstring name);
  ~WidClassCategory();
  
  char *getName() { return name; }
  Container<Lcreator> &getCreators() { return creators; }
  char *getClassName() { return "WidClassCategory"; }

  void sort();

  // ------------- to sort the classes --------------
  static int compare( const void *r1, const void *r2 );
};

//
// WidClasses - Container to initialize Lcreator objects
//

class WidClasses : public Model {
private:
  Container<WidClassCategory> categories;
public:
  WidClasses();
  ~WidClasses();
  Container<WidClassCategory> &getCategories() { return categories; }
  char *getClassName() { return "WidClasses"; }

  void sort();
};

/* #############################################
         WidgetCreator
   ############################################# */

class WidgetCreator : public LicView {
private:
  WidgetRef form;
  WidgetRef optionMenu;
  WidgetRef menu;

  Container<Lcreator> *classes;   // the model to view
  IconView *classesIconView;

  Container<Lcreator> *shellClasses; // the shell -> toggle default shell

  void act( char *action );
  
public:
  WidgetCreator();
  ~WidgetCreator();

  void open() {LicView::open();classesIconView->update(CONTAINER_CHANGED);}

  void update( unsigned long ){}
};


/* #############################################
           LcreatorController()
   ############################################# */
class LcreatorController : public Controller {
private:
  Lcreator *lcreator;
  void createMenuEntries();
public:
  LcreatorController(Lcreator *am, View *icon);
  void act(MenuEntry *me);
  void actOnce(MenuEntry *me);
};

// ------------------- LcreatorIconView ---------------------

class LcreatorIconView : public IconView {
  Boolean createOnClick;
  Boolean asChildOfSelected;
public:
  LcreatorIconView(ContainerBase *cm, Widget p, Icon *icon=NULL )
    :IconView(cm,p,icon) 
  { 
    createOnClick = TRUE; 
    asChildOfSelected = FALSE;
  }

  Controller *getController(SensitiveRec *v) {
    return new LcreatorController((Lcreator*)v->getModel(),v);
  }

  XmString createXmString(Iconable *m);

  void setCreateOnClick(Boolean b) { createOnClick = b; }
  Boolean getCreateOnClick() { return createOnClick; }
  void setAsChildOfSelected(Boolean b) { asChildOfSelected = b; }
  Boolean getAsChildOfSelected() { return asChildOfSelected; }
  
};

/* #############################################
           LcreatorIcon
   ############################################# */
class LcreatorIcon : public Icon {
private:
  LcreatorIconView *iconView;
  Lcreator *lcreator;
  Atom exports[3];

public:
  LcreatorIcon( Lcreator *am, LcreatorIconView *iv)
    : Icon( am, iv) { lcreator=am; exports[0] = 0; iconView = iv; }
  LcreatorIcon() : Icon() {}
  Icon *copy( Iconable *am, IconView *iv)
    { return new LcreatorIcon((Lcreator*)am, (LcreatorIconView*)iv); }

  // action on left mouse button
  void select( Boolean multi, Position x, Position y );


  // drag and drop
  virtual void dragQueryExports(Atom *&exportTargets, 
				Cardinal &numExportTargets,
				Widget &icon);
  virtual Boolean convert(Widget w, Atom *selection, 
			  Atom *target,Atom *type,
			  XtPointer *value, unsigned long *length,
			  int *format);

};

#endif /* DON'T .. */


