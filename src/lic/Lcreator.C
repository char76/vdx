/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: Lcreator.C,v $
 *  $Date: 1999/08/27 15:31:13 $
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
 * $Log: Lcreator.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:31:13  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:13  lazy
 * Imported to CVS
 *
 * Revision 1.5  1998/02/10  01:00:25  lazy
 * - Sort widget categories.
 * - move LCLassInfo to vdxlib
 *
 * Revision 1.4  1997/09/02  18:58:54  lazy
 * compares the getShortName()
 *
 * Revision 1.3  1997/08/31  20:42:41  lazy
 * Test fuer Karsten.
 *
 * Revision 1.2  1997/08/31  20:41:47  lazy
 * Test mit XrtWidgets.
 *
 * Revision 1.1  1997/07/25  20:26:47  lazy
 * Initial revision
 *
 */



/* ---------------------------------------------------------------------
   (C) Dirk Laessig 1994

   --------------------------------------------------------------------- */

#ifndef WITHOUT_LAC
#define USE_LWID
#endif

#include <lac/Model.h>
#include <lac/View.h>
#include <lac/IconView.h>

#include "lic.h"
#include "Lcreator.h"
#include "Lwhere.h"
#include "Lwidget.h"
#include "Lproject.h"

#include <Xm/PushB.h>
#include <Xm/Form.h>
#include <Xm/RowColumn.h>
#include <Xm/DrawingA.h>
#include <Xm/ToggleB.h>


// 
// Default width and height for widget, which don't have its own defaults
//

#define DEFAULT_WIDTH		100
#define DEFAULT_HEIGHT		100



#include <X11/StringDefs.h>

#include <X11/Shell.h>
#include <stdio.h>
#include <ctype.h>

#include <lac/TFuncSort.h>

// -------------------------
// Initialize class member 
// -------------------------

Container<Lcreator> Lcreator::classes;
Container<Lcreator> Lcreator::shellClasses;
Container<Lcreator> Lcreator::managerClasses;
Container<Lcreator> Lcreator::primitiveClasses;
Container<Lcreator> Lcreator::dialogClasses;

char * Lcreator::defaultShellName = "TopLevelShell";
char * Lcreator::linkContainer = "XmFrame";

// ###########################################################
// WidClasses
// ###########################################################

//---------------------------------------------
// WidClasses
//
// Create Lcreator object from LClassInfo
// put them into categories
//---------------------------------------------

WidClasses::WidClasses()
{
  Cardinal i;
  Lcreator *lcreator;
  
  // call libvdx.so

  LClassInfo *classinfo = getVdxClassInfo();

  // Create Lcreator objects from LClassInfo

  for(i = 0; classinfo[i].widget_class || classinfo[i].create_func; i++ ){
    WidClassCategory *cat = NULL;

    lcreator = new Lcreator(classinfo[i]);

    for(unsigned int j=0; j<categories.getSize(); j++) {
      if(!strcmp(categories[j]->getName(), classinfo[i].category)) {
	cat = categories[j];
	break;
      }
    }

    // Create a new category of not exist
    if(cat == NULL) {
      cat = new WidClassCategory(classinfo[i].category);
      categories.add(cat);
    }

    // save the lcreator in the category
    cat->getCreators().add(lcreator);

    // save the lcreator by sub class
    if(lcreator->shell) {
      Lcreator::shellClasses.add(lcreator);
    } else if( lcreator->ci.managePolicy == DIALOG_MANAGE ) {
      Lcreator::dialogClasses.add(lcreator);
    } else if(lcreator->isSubclass(compositeWidgetClass)) {
      Lcreator::managerClasses.add(lcreator);
    } else {
      Lcreator::primitiveClasses.add(lcreator);
    }
  }

  // Sort the containers in Lcreator
  tSort(Lcreator::shellClasses);
  tSort(Lcreator::primitiveClasses);
  tSort(Lcreator::managerClasses);
  tSort(Lcreator::dialogClasses);

  sort();   // Call sort to sort the contents

  printf("%d widget classes available\n", Lcreator::classes.getSize());
}

// -------------------------------------
// sort()
//
// Sort the array of widget categories
// -------------------------------------

void
WidClasses::sort()
{
  tSort(categories);
  for(unsigned int i=0; i<categories.getSize(); i++) {
    categories[i]->sort();
  }
}

// -------------------------------------
// ~WidClasses()
//
// Destructor
// -------------------------------------

WidClasses::~WidClasses()
{
  while(categories.getSize())
    delete categories[0];
}

// ################################################
// WidClassCategory
// ################################################

// -------------------------------------
// WidClassCategory
//
// Constructor
// -------------------------------------

WidClassCategory::WidClassCategory(Lstring n)
  :name(n)
{}
 
// -------------------------------------
// sort()
//
// sort the creators
// -------------------------------------

void
WidClassCategory::sort()
{
  tSort(creators);
}
 
// -------------------------------------
// compare()
// -------------------------------------

int 
WidClassCategory::compare(const void *r1, const void *r2) 
{
  return strcmp(((WidClassCategory **)r1)[0]->name, 
		((WidClassCategory **)r2)[0]->name);
} 

// -------------------------------------
// ~WidClassCategory
//
// Destructor
// -------------------------------------

WidClassCategory::~WidClassCategory()
{
  while(creators.getSize())
    delete creators[0];
}

// #########################################################
// Lcreator - identifies a widget class
// #########################################################

// --------------------------------------------------
//   Lcreator - Contructor
// --------------------------------------------------

Lcreator::Lcreator(LClassInfo &aCI)
:ci(aCI)
{
  static Widget dummyParent = NULL;

  pixmap = new char[PATH_MAX];
  strcpy(pixmap, ci.pixmap);
  
  classes.add(this);
  created = 0;

  if(dummyParent == NULL) {
    dummyParent = XmCreateDrawingArea(LicView::getTopLevel(),
				      "dummyParent",NULL,0);
    XtManageChild(dummyParent);
  }
  if(ci.widget_class) {
    XtInitializeWidgetClass(ci.widget_class);
    dummy = NULL;
  } else {
    dummy = createWidget(dummyParent,"LcreatorDummy",NULL,0);
  }


  if(dummy && ci.managePolicy == NORMAL_MANAGE) XtManageChild(dummy);
  shell = isSubclass(shellWidgetClass);

  if(ci.widget_class) {
    class_name = ci.widget_class->core_class.class_name;
  } else {
    class_name = ci.create_func_str;
  }


  char name[strlen(class_name)+1];
  char *ptr;
  unsigned int clen, nlen;
  const char *create = "Create";
  
  strcpy(name, class_name);
  ptr = name;
  clen = strlen(create);
  nlen = strlen(ptr);

  if(nlen > 1 && name[0] == 'X' && name[1] == 'm') {
    ptr += 2;
    if(nlen > clen+1 && !strncmp(ptr, create, clen))
      ptr += clen;
  } 
  shortName = new char[strlen(ptr)+1];
  strcpy(shortName, ptr);

}
  


Boolean Lcreator::isSubclass(WidgetClass widgetClass)
{
  Boolean result = FALSE;
  WidgetClass wc;
  
  for (wc = getWidgetClass(); wc != NULL; wc = wc->core_class.superclass)
        if (wc == widgetClass) {
            result = TRUE;
            break;
        }
  
  return result;
}



#if(0)
// --------------------------------------------------
//   InitClasses() 
//   name_buffer=NULL -> count == Groesse der Arrays
//   -> String name_buffer[count] -> und nochmal 
//   InitClasses( name_buffer, count ); 
// --------------------------------------------------

void Lcreator::InitClasses( String *name_buffer, Cardinal *count )
{
  Cardinal i, maxClasses;
  Lcreator *lcreator;

  for(maxClasses = 0 ; 
      classinfo[maxClasses].widget_class || classinfo[maxClasses].create_func; 
      maxClasses++ );
  if( name_buffer == NULL ) {
    *count = maxClasses;
    return;
  }

  if( *count < maxClasses ) {
    *count = 0;
    return;
  }

  TSortArray<Lcreator> shellClasses;
  TSortArray<Lcreator> managerClasses;
  TSortArray<Lcreator> primitiveClasses;
  TSortArray<Lcreator> dialogClasses;

  for( i = 0 ; 
      classinfo[i].widget_class || classinfo[i].create_func; 
      i++ ){
    lcreator = new Lcreator( classinfo[i] );    
    name_buffer[i] = lcreator->class_name;

    if( lcreator->shell )
      shellClasses.add(lcreator);
    else if( lcreator->ci.managePolicy == DIALOG_MANAGE )
      dialogClasses.add(lcreator);
    else if(lcreator->isSubclass(compositeWidgetClass))
      managerClasses.add(lcreator);
    else
      primitiveClasses.add(lcreator);
  }
  
  shellClasses.sort();
  primitiveClasses.sort();
  managerClasses.sort();
  dialogClasses.sort();

  for(i=0; i<shellClasses.getSize(); i++)
    Lcreator::shellClasses.add(shellClasses[i]);
  for(i=0; i<primitiveClasses.getSize(); i++)
    Lcreator::primitiveClasses.add(primitiveClasses[i]);
  for(i=0; i<managerClasses.getSize(); i++)
    Lcreator::managerClasses.add(managerClasses[i]);
  for(i=0; i<dialogClasses.getSize(); i++)
    Lcreator::dialogClasses.add(dialogClasses[i]);

}
#endif

// -----------------------
//      getDescription()
// -----------------------

char *Lcreator::getDescription()
{
  if(description == "") {
    char buf[1024];
    msgCat->getMsg(buf, LCREATOR_DESCRIPTION, getName());
    description = buf;
  }
  return description;
}

// -----------------------
//      compare()
// -----------------------

int Lcreator::compare( const void *r1, const void *r2 )
{
  return strcmp(((Lcreator**)r1)[0]->getShortName(),  
		((Lcreator**)r2)[0]->getShortName());
}

// ------------------------
//  createWidget()
// ------------------------

Widget Lcreator::createWidget(Widget parent, 
			      char* name, 
			      ArgList args, 
			      Cardinal n)
{
  if( ci.widget_class ) {
    if( parent ) 
      return XtCreateWidget( name, ci.widget_class, parent, args, n );
    else 
      return XtCreatePopupShell(name, 
				ci.widget_class,
				Lproject::current().getTopLevel(),
				args, n );
  }
  if( ci.create_func ) {
    return ci.create_func( parent, name, args, n );
  }
  fprintf(stderr,"Fatal Error: no method to create the widget. (Lcreator)\n");
  return NULL;

}


// -----------------------
//     createLwidget()
// -----------------------

Lwidget * Lcreator::createLwidget( Lwidget *parent )
{
  char wg_name[256];
  Linterface *ainterface;
  Lwidget *lw;
  Boolean flag = FALSE;
  Lwhere where;

  if(parent == NULL) {
    where = Lwhere(Lproject::current());    // grab pointer and query geometry
    if( where.isCanceled() )
      return NULL;
    parent = where.getparent();
  } else {
    where.setparent(parent);
  }
  ainterface = NULL;
  if( parent == NULL ) {                              // create new Interface

    if(getManagePolicy()==DIALOG_MANAGE) {    // Don't create
      char msg[1024];
      char title[1024];
      msgCat->getMsg( title, ERROR_TITLE );
      msgCat->getMsg( msg, ERROR_CREATE_DIALOG );
      LicView::MsgBox(title, msg, MSGBOX_STYLE_OK);
      return NULL;
    }

    flag = TRUE;
    if( isShell() )                                  
      ainterface = Lproject::current().addInterface(this);
    else
      ainterface = Lproject::current().addInterface();
    parent = ainterface->getShell();
    where.setparent(parent);
  } else {
    ainterface = parent->getInterface();
  }

  if( (flag && !isShell()) || !flag ) {
    char buf[256];
    if(!strncmp(class_name,"XmCreate",strlen("XmCreate"))) {
      strcpy(buf, &class_name[strlen("XmCreate")]);
    } else {
      if(!strncmp(class_name,"Xm",strlen("Xm"))) {
	strcpy(buf, &class_name[strlen("Xm")]);
      } else {
	strcpy(buf,class_name);
      }
    }
    buf[0] = tolower(buf[0]);
    sprintf( wg_name, "%s_%d", buf, ++created );
    while( ainterface->existNamedWidget(wg_name) )
      sprintf( wg_name, "%s_%d", buf, ++created );
      
    if(where.getheight() == 0 && where.getwidth() == 0 && ci.defaultSize) {
      where.setwidth(DEFAULT_WIDTH);
      where.setheight(DEFAULT_HEIGHT);
    }
    
    lw = new Lwidget( this, wg_name, where );             // create Lwidget
    lw->select();
  }
  
  if( flag ) {
    ainterface->moveTo(where.getx(),where.gety());
    ainterface->setSize(where.getwidth(), where.getheight());
  } else 
    parent->changed( CONTAINER_CHANGED );

  if( ainterface ) 
    ainterface->show();

  return lw;
}


// -----------------------
//  getClass()
// -----------------------

Lcreator *Lcreator::getClass( char *name )
{
  for( unsigned int i=0 ; i<classes.getSize() ; i++ )
    if( !strcmp(name, classes[i]->class_name) )
      return classes[i];
  return NULL;
}


// -----------------------
//  isShell()
// -----------------------

Boolean Lcreator::isShell()
{
  return shell;
}

// -----------------------
//  asChildOk()
// -----------------------

Boolean Lcreator::asChildOk(Lcreator *toCheck)
{
  unsigned char type;
  Boolean isHom, radioBox;
  WidgetClass entryClass;

  if(toCheck->isSubclass(shellWidgetClass)) {     // Shell allways
    return TRUE;
  }
  if(toCheck->dummy &&
     XtParent(toCheck->dummy) &&      // Convenient Widget inserts shell
     XtParent(toCheck->dummy) != LicView::getTopLevel() &&
     XtIsShell(XtParent(toCheck->dummy))) {
    return TRUE;
  }

  if(isSubclass(compositeWidgetClass)) {     
    if(dummy && XmIsRowColumn(dummy)) {
      XtVaGetValues(dummy,
		    XmNradioBehavior, &radioBox,
		    XmNisHomogeneous, &isHom,
		    XmNentryClass, &entryClass,
		    NULL );
      if(isHom && entryClass == toCheck->getWidgetClass())
	return TRUE;
      if(!isHom)
	return TRUE;
      if(radioBox && toCheck->isSubclass(xmToggleButtonWidgetClass))
	return TRUE;
    } else 
      return TRUE;
  }
  if(toCheck->dummy && XmIsRowColumn(toCheck->dummy)) {
    XtVaGetValues(toCheck->dummy,
		  XmNrowColumnType, &type,
		  NULL);
    if(type != XmWORK_AREA )     // dann ist es ein Menu
      return TRUE;
  }
  return FALSE;
}


/* ##########################################################
                  WidgetCreator - A View class
   ########################################################## */

#define LCREATOR_SETDEFAULTSHELL "SetDefaultShell"

// -------------------------
//   WidgetCreator()
// -------------------------

WidgetCreator::WidgetCreator()
:LicView(&Lcreator::getContainer()) , classes(&Lcreator::getContainer())
{
  Widget menu, defaultS, button;
  Arg args[10]; Cardinal n=0;

  shellClasses = &Lcreator::getShells();

  popupShell = XtVaCreatePopupShell ("WidgetCreatorShell", 
				     topLevelShellWidgetClass,
				     topLevel,
				     NULL );
  form = XtVaCreateManagedWidget("WidgetCreatorForm",
				 xmFormWidgetClass,
				 popupShell,
				 NULL);

  menu = XmCreatePulldownMenu(form, "DefaultShell", (Arg*)NULL, 0 ); 
  for( unsigned int i=0; i<shellClasses->getSize(); i++ ) {
    char *name = Lcreator::getShells()[i]->getName();
    button = XtVaCreateManagedWidget(name,xmPushButtonWidgetClass, menu, NULL);
    addAction(button, LCREATOR_SETDEFAULTSHELL);
    if( !strcmp(name,Lcreator::getDefaultShell()->getName()) )
      defaultS = button;
  }
  n=0;
  XtSetArg( args[n], XmNmenuHistory, defaultS ); n++;
  XtSetArg( args[n], XmNsubMenuId, menu ); n++;
  XtSetArg( args[n], XmNleftAttachment, XmATTACH_FORM ); n++;
  XtSetArg( args[n], XmNleftOffset, 5 ); n++;
  XtSetArg( args[n], XmNtopAttachment, XmATTACH_FORM ); n++;
  XtSetArg( args[n], XmNtopOffset, 5 ); n++;
  optionMenu = XmCreateOptionMenu( form, "OptionMenu", args, n );
  XtManageChild( optionMenu );

  classesIconView =       
    new IconView( classes, form , new LcreatorIcon() );
  classesIconView->setWithNames(FALSE);

  XtVaSetValues( classesIconView->getWidget(),
		XmNleftAttachment, XmATTACH_FORM,
		XmNleftOffset, 5,
		XmNtopAttachment, XmATTACH_WIDGET,
		XmNtopOffset, 5,
		XmNtopWidget, Widget(optionMenu),
		XmNrightAttachment, XmATTACH_FORM,
		XmNrightOffset, 5,
		XmNbottomAttachment, XmATTACH_FORM,
		XmNbottomOffset, 5,
		NULL );
  classes->changed( CONTAINER_CHANGED );
}

// -------------------------
//   ~WidgetCreator()
// -------------------------

WidgetCreator::~WidgetCreator()
{
  delete classesIconView;
}



// -------------------------
//   act()
// -------------------------

void WidgetCreator::act( char *action )
{
  Widget w;
  if(!strcmp(action,LCREATOR_SETDEFAULTSHELL)) {
    if(optionMenu) {
      XtVaGetValues(optionMenu,XmNmenuHistory,&w,NULL);
      Lcreator *lc = Lcreator::getClass(XtName(w));
      if( lc )
	Lcreator::setDefaultShell(lc);
    }
  }
}




/* ##########################################
        LcreatorController
   ########################################## */

#define LCREATOR_CREATE "LcreatorCreate"

LcreatorController::LcreatorController(Lcreator *am, View *icon)
:Controller(am,icon)
{
  lcreator = am;
}

void LcreatorController::actOnce(MenuEntry *)
{

}

void LcreatorController::createMenuEntries()
{
  entries.add( new MenuEntry(this, ME_PUSHBUTTON, LCREATOR_CREATE, FALSE));
}


// -----------------------
//    act()
// -----------------------
void LcreatorController::act(MenuEntry *me)
{
  if(me->match(LCREATOR_CREATE)) {
    lcreator->createLwidget(NULL);
  }
}


// ###################################
// LcreatorIconView
// ###################################

XmString 
LcreatorIconView::createXmString(Iconable *m)
{
  XmString xms;

  xms = XmStringCreate(((Lcreator*)m)->getShortName(), 
		       XmSTRING_DEFAULT_CHARSET);

  return xms;
}


// ###################################
// LcreatorIcon
//
// select()
// ###################################

void LcreatorIcon::select( Boolean b, Position x, Position y)
{
  if(iconView->getCreateOnClick()) {
    if(iconView->getAsChildOfSelected()) {
      RefArray<Selectable> selection(Selectable::getSelection());
      RefArray<Lwidget> parents;

      if(!strcmp(Selectable::getCurrentClass(), "Lwidget")
	 && selection.getSize() > 0) {
	for(unsigned int i=0; i<selection.getSize(); i++) {
	  Lwidget *lwidget = (Lwidget*)(Selectable*)selection[0];
	  parents.add(lwidget);
	}
      }
      
      for(unsigned int i=0; i<parents.getSize(); i++) {
	if(parents[i]->getClass()->asChildOk(lcreator)) {
	  lcreator->createLwidget(parents[i]);
	} else {
	  printf("Can't create %s as child of %s(%s)\n", 
		 lcreator->getName(), parents[i]->getName(),
		 parents[i]->getClass()->getName());
	}
      }

    } else {
      lcreator->createLwidget(NULL);
    }
    pressed = FALSE;
    expose();
  } else {
    SensitiveRec::select(b, x, y);
  }
}


// -----------------------------
// dragQueryExports()
// -----------------------------

void LcreatorIcon::dragQueryExports(Atom *&exportTargets, 
				    Cardinal &numExportTargets,
				    Widget &sourceIcon)
{
  SensitiveRec::dragQueryExports(exportTargets, numExportTargets, sourceIcon);
  
  if(exports[0] == 0) {
    exports[0] = XmInternAtom(XtDisplay(parent),"COMPOUND_TEXT",False);
    exports[1] = XmInternAtom(XtDisplay(parent),lcreator->getClassName(),False);
    exports[2] = XmInternAtom(XtDisplay(parent),"Lwidget",False);
  }
  exportTargets = exports;
  numExportTargets = 3;

}

// -----------------------------
// convert()
// -----------------------------

Boolean LcreatorIcon::convert(Widget w, Atom *a, 
			      Atom *target,Atom *type,
			      XtPointer *value, unsigned long *length,
			      int *format)
{
  if(SensitiveRec::convert(w, a, target, type, value, length, format))
    return TRUE;
  
  if(*target == exports[2]) {
    Lwhere where;
    char buf[256];

    if(lcreator->getDefaultSize()) {
      where.setwidth(DEFAULT_WIDTH);
      where.setheight(DEFAULT_HEIGHT);
    }

    if(!strncmp(lcreator->getName(),"XmCreate",strlen("XmCreate"))) {
      strcpy(buf, &(lcreator->getName()[strlen("XmCreate")]));
    } else {
      if(!strncmp(lcreator->getName(),"Xm",strlen("Xm"))) {
	strcpy(buf, &(lcreator->getName()[strlen("Xm")]));
      } else {
	strcpy(buf,lcreator->getName());
      }
    }
    buf[0] = tolower(buf[0]);

    Iconable **ptr;
    *length = 1;
    *format = sizeof(Iconable*)*8;
    ptr = (Iconable**)XtMalloc(sizeof(Iconable*)*(*length));
    *ptr = new Lwidget(lcreator, buf, where);   // if this is a copy, 
                                            // the memory will not be freed
    *value = (XtPointer)ptr;
    *type = exports[2];
    return TRUE;
  }
  return FALSE;
}

