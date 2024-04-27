/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: Lwidget.C,v $
 *  $Date: 1999/08/27 15:31:33 $
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
 * $Log: Lwidget.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:31:33  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:13  lazy
 * Imported to CVS
 *
 * Revision 1.3  1998/03/30 19:08:33  lazy
 * *** empty log message ***
 *
 * Revision 1.2  1997/09/07  15:00:12  lazy
 * display a popup menu in test mode.
 *
 * Revision 1.1  1997/07/25  20:29:02  lazy
 * Initial revision
 *
 */

/* --------------------------------------------------------------------
   (C) Dirk Laessig 1994

   Lwidget.C
   Class Lwidget WidgetView & WidgetMenu

   -------------------------------------------------------------------- */

#include "lic.h"
#include "Lwidget.h"
#include "Lwhere.h"
#include "Lcreator.h"
#include "Lproject.h"
#include "Lpalette.h"
#include "InterfaceInfo.h"
#include "MenuEdit.h"
#include "MainWindow.h"
#include "WidBrowseView.h"
#include "WidResEditor.h"
#include "AttachmentEditor.h"
#include "TransformDialog.h"

#include <X11/ShellP.h>

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <Xm/RowColumn.h>
#include <Xm/Label.h>
#include <Xm/PushB.h>
#include <Xm/ScrolledW.h>
#include <Xm/Form.h>
#include <Xm/PanedW.h>
#include <Xm/ToggleB.h>
#include <Xm/Separator.h>

#include <X11/Shell.h>
#include <X11/ObjectP.h>
#include <X11/IntrinsicP.h>
#include <X11/CoreP.h>
#include <X11/CompositeP.h>


#include "noSource.xbm"
#include "noSource_mask.xbm"

#define MAX_ARGS 300                // max argument list
#define MAX_NAME_LEN   32
#define DUMMY_NAME     "widget"     // if no name is valid, try this

#define STATE_ICON_OFFSET_X -20
#define STATE_ICON_OFFSET_Y -8

#define VD_SHOW_DIALOG "showDialog"

#define ITALIC_FONT "italic"
#define BOLD_FONT "bold"

Boolean WidgetView::testMode = False;
Button1Mode WidgetView::button1Mode;
Container<Lwidget> Lwidget::clipboard;


extern "C" void _XtDoPhase2Destroy(XtAppContext, int);


/* ######################################################

   Lwidget        - a Model of a widget

   ###################################################### */

// ------------------------------------------
//       Lwidget()  - Kontruktor
// ------------------------------------------
Lwidget::Lwidget( Lcreator *aclass, char *name, const Lwhere &wo )
{
  parent = NULL;
  properties = NULL;
  this->aclass = aclass;
  manage = (aclass->getManagePolicy() == NORMAL_MANAGE);
  quickhelp = NULL;

  description = new char[strlen(aclass->getName())+1];
  strcpy(description, aclass->getName());

  this->name = new char[strlen(name)+1];
  strcpy(this->name, name);
  setParent(wo.getparent());
  if( parent )
    parent->children.add(this);

  WidgetClass widgetClass, parentClass = NULL;
  widgetClass = aclass->getWidgetClass();
  if( parent )
    parentClass = parent->aclass->getWidgetClass();
  properties = new Lproperty( this, widgetClass, parentClass );

  if(parent) {
    // Wir haben noch keine default in den properties -> pappi convertiert
    int x,y;
    parent->getProperties()->convertFromPixel(wo.getx(), wo.gety(), x, y);
    properties->setResource("x", x);
    properties->setResource("y", y);
  }
  if(wo.getwidth() && wo.getheight() && parent) {
    int width, height;
    parent->getProperties()->convertFromPixel(wo.getwidth(), wo.getheight(),
					      width, height);
    properties->setResource("width", width);
    properties->setResource("height", height);
  }
  
  isLink = FALSE;
  nameOfLinkedInterface = NULL;
}

// ------------------------------------------
//       Lwidget()  - Kontruktor
//                    Erzeugen eines Links
// ------------------------------------------
Lwidget::Lwidget(Lwidget *parent, char *linked, char *name )
{
  this->parent = NULL;
  properties = NULL;
  manage = TRUE;
  quickhelp = NULL;

  this->aclass = Lcreator::getLinkContainer(); // normaly XmFrame

  description = new char[strlen(linked)+1];
  strcpy(description, linked);

  this->name = new char[strlen(name)+1];
  strcpy(this->name, name);
  setParent(parent);

  this->linked = Lproject::current().getInterface( linked );
  nameOfLinkedInterface = new char[ strlen(linked)+1 ];
  strcpy( nameOfLinkedInterface, linked );

  parent->children.add(this);
  isLink = TRUE;

  WidgetClass widgetClass, parentClass = NULL;
  widgetClass = aclass->getWidgetClass();
  if( parent )
    parentClass = parent->aclass->getWidgetClass();
  properties = new Lproperty( this, widgetClass, parentClass );
}

// ------------------------------------------
//       Lwidget()  - Kontruktor
//                    Lesen aus Datei
// ------------------------------------------
Lwidget::Lwidget( YWidget *yWidget, Lwidget *parent )
{
  this->parent = NULL;
  properties = NULL;

  char *name = yWidget->name; 
  YWidget *child;

  isLink = FALSE;
  nameOfLinkedInterface = NULL;
  manage = TRUE;

  this->name = new char[strlen(name)+1];
  strcpy(this->name, name);
  setParent(parent);
  
  if( yWidget->widget_class[0] == '@' ) {
    // it's a link 
    isLink = TRUE;
    nameOfLinkedInterface = new char[ strlen(yWidget->widget_class) ];
    strcpy( nameOfLinkedInterface, &(yWidget->widget_class[1]) );
    linked = Lproject::current().getInterface( nameOfLinkedInterface );
    aclass = Lcreator::getLinkContainer();
  } else {
    aclass = Lcreator::getClass( yWidget->widget_class );
  }

  if(yWidget->description) {
    description = new char[strlen(yWidget->description)+1];
    strcpy(description, yWidget->description);
  } else {
    description = new char[strlen(aclass->getName())+1];
    strcpy(description, aclass->getName());
  }
  if(!strcmp(yWidget->managed, "TRUE") 
     && aclass->getManagePolicy() != NEVER_MANAGE) 
    manage = TRUE;
  else
    manage = FALSE;

  helpNode = Lproject::current().findHelpNode(yWidget->helpId);
  if(yWidget->quickhelp[0]) {
    quickhelp = new char[strlen(yWidget->quickhelp)+1];
    strcpy(quickhelp, yWidget->quickhelp);
  } else 
    quickhelp = NULL;

  parseViewData(yWidget->viewData);

  WidgetClass widgetClass, parentClass = NULL;
  widgetClass = aclass->getWidgetClass();
  if( parent )
    parentClass = parent->aclass->getWidgetClass();
  properties = new Lproperty( this, widgetClass, parentClass, yWidget->first_res );

  for( child=yWidget->first_child; child; child = child->next ) {
    if(Lcreator::getClass(child->widget_class) || 
       child->widget_class[0] == '@') {
      children.add( new Lwidget( child, this ));
    } else {
      fprintf(stderr, "Error: Widget class '%s' is not available.\n", 
	      child->widget_class);
    }
  }
}

// -----------------------------------------
//     createYWidget()
// -----------------------------------------
void Lwidget::setDescription(char *s)
{
  if(description)
    delete description;
  description = new char[strlen(s)+1];
  strcpy(description, s);
}

// -----------------------------------------
//     createYWidget()
// -----------------------------------------

YWidget *Lwidget::createYWidget()
{
  YWidget *ret, *child;
  
  ret = (YWidget*)malloc( sizeof(YWidget) );
  memset(ret, 0, sizeof(YWidget));
  
  strcpy(ret->name, name);
  m_strcpy(&ret->viewData, getViewData());
  if(manage) 
    strcpy(ret->managed, "TRUE");
  else
    strcpy(ret->managed, "FALSE");

  m_strcpy(&ret->description, description);

  if(helpNode.isNil())
    ret->helpId = -1;
  else 
    ret->helpId = helpNode->getId();

  ret->quickhelp[0] = 0;
  if(quickhelp)
    strcpy(ret->quickhelp, quickhelp);

  if( !isLink ) {
    strcpy(ret->widget_class, aclass->getName());
    
    ret->first_res = properties->createYResource();

    if( children.getSize() ) {
      ret->first_child = child = children[0]->createYWidget();
      if( children.getSize() > 1 )
	for( unsigned int i=1 ; i < children.getSize() ; i++ , child = child->next )
	  child->next = children[i]->createYWidget();
    }
  } else { // save the link
    strcpy( ret->widget_class, "@" );
    strcat( ret->widget_class, nameOfLinkedInterface);
    ret->first_res = properties->createYResource();
  }
  return ret;
}

// ------------------------------------------
//       ~Lwidget()  - De-Kontruktor
// ------------------------------------------

Lwidget::~Lwidget()
{
  if(description)
    delete description;
  if(quickhelp)
    delete quickhelp;
  if( properties )
    delete properties;
  if(name)
    delete name;
  if(nameOfLinkedInterface)
    delete nameOfLinkedInterface;
  for( unsigned int i=0; i<nameReferences.getSize(); i++ )
    nameReferences[i]->changeNameTo("");
}


// ------------------------------------------
//       setQuickhelp()
// ------------------------------------------

void Lwidget::setQuickhelp(char *qh)
{
  if(quickhelp) 
    delete quickhelp;
  quickhelp = new char[strlen(qh)+1];
  strcpy(quickhelp, qh);
}

// ------------------------------------------
//       find() 
// ------------------------------------------

Lwidget *Lwidget::find( Window )
{
  return NULL;
}


// ------------------------------------------
//       copyTo()
// ------------------------------------------

Lwidget *Lwidget::copyTo( Lwidget * )
{
  return NULL;
}

// ------------------------------------------
//       moveTo()
// ------------------------------------------

void Lwidget::moveTo( Lwidget *newParent )
{
  if( parent )
    parent->children.remove( this );
  parent = newParent;
  newParent->children.add( this );
  getProperties()->parentChanged();
}



// ------------------------------------------
//       existNamedWidget()
// ------------------------------------------

Boolean Lwidget::existNamedWidget( char *name )
{
  if( this->name && !strcmp(this->name,name))
    return TRUE;
  for( unsigned int i=0; i<children.getSize(); i++ )
    if( children[i]->existNamedWidget(name) )
      return TRUE;
  return FALSE;
}

// ------------------------------------------
//       getInterface()
// ------------------------------------------

Linterface *Lwidget::getInterface()
{
  if( parent )
    return parent->getInterface();

  // Wenn da kein Parent is, dann mut du shell sein
  return Lproject::current().getInterface( this );
}


// ------------------------------------------
//       getChildren()
// ------------------------------------------

RefArray<Lwidget>& Lwidget::getChildren() 
{ 
//  if( isLink && !linked.isNil() )
//    return linked->getChildren();

  return children; 
}


// ------------------------------------------
//       getClass()
// ------------------------------------------

Lcreator *Lwidget::getClass() { 
//  if( isLink && !linked.isNil() )
//    return linked->getClass();
  return aclass; 
} 


// ------------------------------------------
//       getProperties()
// ------------------------------------------

Lproperty *Lwidget::getProperties() { 
  return properties; 
}

// ------------------------------------------
//       changed()
// ------------------------------------------
void Lwidget::changed( unsigned long flags )
{

  if( !getParent() && flags & NAME_CHANGED ) {
    Linterface *li = getInterface();
    if(li)
      li->changed(NAME_CHANGED);
  }

  if( flags & NAME_CHANGED )
    for( unsigned i=0; i<nameReferences.getSize(); i++ )
      nameReferences[i]->changeNameTo(getName());

  Model::changed( flags );
}


// ------------------------------------------
//       fillInterfaceInfo()
// ------------------------------------------
void Lwidget::fillInterfaceInfo( InterfaceInfo *ii )
{
  unsigned int i;
  Lwidget *ref;

  ii->addWidget(this);
  ii->addHeader(getClass()->getHeader());

  // searching for callbacks

  for( i=0; i<getProperties()->getCallbacks().getSize(); i++ )
    if( !getProperties()->getCallbacks()[i]->isDefault() ) {
      unsigned int len;
      getProperties()->getCallbacks()[i]->getString(NULL,len);
      char method[len+1];
      if(getProperties()->getCallbacks()[i]->getAttribute() ==
	 &LresAttribute::attrMethod) {
	getProperties()->getCallbacks()[i]->getString(method,len);
      } else {
	method[0] = '$';
	getProperties()->getCallbacks()[i]->getString(method+1,len);
      }
      ii->addCallback(this, 
		      getProperties()->getCallbacks()[i]->getName(),
		      method );
    }

  // searching for relations in properties (core,specific,constraint)

  RefArray<Lresource> &res1( getProperties()->getCore() );
  for( i=0; i<res1.getSize(); i++ )
    if( !res1[i]->isDefault() && res1[i]->isRelation() ) {
      unsigned int len;
      res1[i]->getString(NULL,len);
      char destination[len];
      res1[i]->getString(destination,len);
      for(ref = this; ref->getParent(); ref = ref->getParent());
      ref = ref->findNamedWidget(destination);
      if( ref ) {
	ii->addRelation(this,res1[i]->getName(), ref );
      }
    }

  RefArray<Lresource> &res2( getProperties()->getSpecific() );
  for( i=0; i<res2.getSize(); i++ )
    if( !res2[i]->isDefault() && res2[i]->isRelation() ) {
      unsigned int len;
      res2[i]->getString(NULL,len);
      char destination[len];
      res2[i]->getString(destination,len);
      for(ref = this; ref->getParent(); ref = ref->getParent());
      ref = ref->findNamedWidget(destination);
      if( ref ) {
	ii->addRelation(this,res2[i]->getName(), ref );
      }
    }

  RefArray<Lresource> &res3( getProperties()->getConstraint() );
  for( i=0; i<res3.getSize(); i++ )
    if( !res3[i]->isDefault() && res3[i]->isRelation() ) {
      unsigned int len;
      res3[i]->getString(NULL,len);
      char destination[len];
      res3[i]->getString(destination,len);
      for(ref = this; ref->getParent(); ref = ref->getParent());
      ref = ref->findNamedWidget(destination);
      if( ref ) {
	ii->addRelation(this,res3[i]->getName(), ref );
      }
    }


  for( i=0; i<children.getSize(); i++ )
    children[i]->fillInterfaceInfo(ii);

}

// --------------------------
//  fillResourceFileInfo()
// --------------------------

void Lwidget::fillResourceFileInfo( ResourceFileInfo *)
{
}

// --------------------------
//      isNameValid()
// --------------------------
Boolean Lwidget::isNameValid( char *n )
{
  char *ptr;
  if( strlen(n) > MAX_NAME_LEN || isdigit(*n) )
    return FALSE;
  ptr = n;
  while( *ptr ) {
    if( !isalnum(*ptr) && *ptr!='_' )
      return FALSE;
    ptr++;
  }
  if( getInterface() )
    if( getInterface()->existNamedWidget(n) )
      return FALSE;
  return TRUE;
}

// --------------------------
//      setName()
// --------------------------
Boolean Lwidget::setName( char *n )
{
  if(!strcmp(name, n))
    return TRUE;

  if( !isNameValid(n) ) 
    return FALSE;

  delete name;
  name = new char[strlen(n)+1];
  strcpy(name,n);
  changed(NAME_CHANGED);

  return TRUE;
}


// --------------------------
//  nameReferenceAdd()
// --------------------------

void Lwidget::nameReferenceAdd( LresRelation *toAdd )
{
  nameReferences.add(toAdd);
}

// --------------------------
//  nameReferenceRemove()
// --------------------------

void Lwidget::nameReferenceRemove( LresRelation *toRemove )
{
  nameReferences.remove(toRemove);
}


// ------------------------------
//    findNamedWidget()
// ------------------------------

Lwidget *Lwidget::findNamedWidget( char *n )
{
  Lwidget *ret;

  if(!strcmp(n,getName()))
    return this;
  for(unsigned int i=0; i<children.getSize(); i++ )
    if( (ret = children[i]->findNamedWidget(n)) )
      return ret;

  return NULL;
}

// ------------------------------
//    copy()
// ------------------------------

Lwidget* Lwidget::copy()
{
  YResult *dummy;
  Lwidget *ret;

  dummy = (YResult*)malloc(sizeof(YResult));
  memset( dummy, 0, sizeof(YResult) );
  dummy->root_widget = createYWidget();

  ret = new Lwidget( dummy->root_widget );
  free_YResult(dummy);
  return ret;
}

// ------------------------------
//    setParent()
// ------------------------------

void Lwidget::setParent(Lwidget *newParent)
{
  char *oldName;
  int c=1;
  Lwidget *oldParent = parent;

  if(oldParent != newParent)
    TreeNode<Lwidget>::setParent(newParent);

  oldName = new char[strlen(name)+1];
  strcpy(oldName, name);

  while( !isNameValid(name) ) {           // looking for a good name
    if( strlen(name)<MAX_NAME_LEN ) {

      delete name;
      name = new char[strlen(oldName)+5];
      sprintf(name,"%s_%d",oldName,c++);

    } else {                   // Name zu lang

      delete name;
      name = new char[strlen(DUMMY_NAME)+1];
      strcpy(name,DUMMY_NAME);

      delete oldName;
      oldName = new char[strlen(DUMMY_NAME)+1];
      strcpy(oldName, DUMMY_NAME);
    }
  }
  delete oldName;

  FOREACH(i,children) {
    children[i]->setParent(this);
  }

  if( newParent && properties && oldParent != newParent ) {
    properties->parentChanged();
  }
}

// ------------------------------
//    asChildOk()
// ------------------------------

Boolean Lwidget::asChildOk(Lwidget* toCheck)
{
  return getClass()->asChildOk(toCheck->getClass());
}


// ------------------------------
//    getChangedFlag()
// ------------------------------

Boolean Lwidget::getChangedFlag()
{
  if(ContainerBase::getChangedFlag())
    return TRUE;
  return FALSE;
}


// ------------------------------
//    resetChangedFlag()
// ------------------------------

void Lwidget::resetChangedFlag()
{
  ContainerBase::resetChangedFlag();
}
 

 
/* ####################################################

   WidgetIconView, WidgetTreeView

   #################################################### */

void WidgetIconView::setWithClasses(Boolean b)
{
  withClasses = b;
  update(CONTAINER_CHANGED);
}

XmString WidgetIconView::createXmString(Iconable *m)
{
  XmString xms1, xms2, xms;
  char text[1024];
  
  if(withClasses) {
    sprintf(text, " (%s)", ((Lwidget*)m)->getClass()->getName());
    
    xms1 = XmStringCreate(m->getName(), BOLD_FONT);
    xms2 = XmStringCreate(text, ITALIC_FONT);
    xms = XmStringConcat(xms1, xms2);
    XmStringFree(xms1);
    XmStringFree(xms2);
  } else {
    xms = XmStringCreate(m->getName(), XmSTRING_DEFAULT_CHARSET);
  }
  return xms;
}

void WidgetTreeView::setWithClasses(Boolean b)
{
  withClasses = b;
  update(CONTAINER_CHANGED);
  refresh();
}

XmString WidgetTreeView::createXmString(Iconable *m)
{
  XmString xms1, xms2, xms;
  char text[1024];
  
  if(withClasses) {
    sprintf(text, " (%s)", ((Lwidget*)m)->getClass()->getName());
    
    xms1 = XmStringCreate(m->getName(), BOLD_FONT);
    xms2 = XmStringCreate(text, ITALIC_FONT);
    xms = XmStringConcat(xms1, xms2);
    XmStringFree(xms1);
    XmStringFree(xms2);
  } else {
    xms = XmStringCreate(m->getName(), XmSTRING_DEFAULT_CHARSET);
  }

  return xms;
}


/* ####################################################

   WidgetMenu - The popupmenu of a widget

   #################################################### */

// ----------------------
//   WidgetController
// ----------------------
WidgetController::WidgetController(Lwidget *am, View *v)
:Controller(am, v)
{
  lwidget = am;
}

// ----------------------
//   createMenuEntries()
// ----------------------
void WidgetController::createMenuEntries()
{
  MenuEntry *me;

  me = new MenuEntry(this, ME_PUSHBUTTON, LWIDGET_EDIT, FALSE);
  me->setKeyBinding(0, "e");
  entries.add(me);

  me = new MenuEntry(this, ME_PUSHBUTTON, LWIDGET_BROWSE, FALSE);
  me->setKeyBinding(0, "b");
  entries.add(me);

  if(!strcmp(view->getName(), "TreeNodeView") ||
     !strcmp(view->getName(), "IconView"))
     {
       me =  new MenuEntry(this, ME_PUSHBUTTON, LWIDGET_RENAME, TRUE);
       me->setKeyBinding(0, "r");
       entries.add(me);
     }
     
  if( MenuEdit::isOfValidClass(lwidget) ) {
    me = new MenuEntry(this, ME_PUSHBUTTON, LWIDGET_MENUEDIT,FALSE);
    me->setKeyBinding(0, "m");
    entries.add(me);
  }
  
  if( AttachmentEditor::isOfValidClass(lwidget) ) {
    me = new MenuEntry(this, ME_PUSHBUTTON, LWIDGET_ATTACHMENTS,FALSE);
    me->setKeyBinding(0, "a");
    entries.add(me);
  }
  
  me = new MenuEntry(this, ME_PUSHBUTTON, LWIDGET_TRANSFORM,FALSE);
  me->setKeyBinding(0, "t");
  entries.add(me);

  if(!strcmp(view->getName(), "WidgetView")) {
    Boolean multi;
    MenuEntry *subMenu;

    multi = (selection.getSize() > 1);   // multiple widget -> sensitive

    
    subMenu = new MenuEntry(this, ME_SUBMENU, "Align", TRUE);
    entries.add(subMenu);
    
    me = new MenuEntry(this, ME_PUSHBUTTON, LWIDGET_ALIGNLEFT, 
		       TRUE, subMenu);
    me->setSensitive(multi);
    entries.add(me);

    me = new MenuEntry(this, ME_PUSHBUTTON, LWIDGET_ALIGNRIGHT, 
		       TRUE, subMenu);
    me->setSensitive(multi);
    entries.add(me);
    
    me = new MenuEntry(this, ME_PUSHBUTTON, LWIDGET_ALIGNTOP, 
		       TRUE, subMenu);
    me->setSensitive(multi);
    entries.add(me);
    
    me = new MenuEntry(this, ME_PUSHBUTTON, LWIDGET_ALIGNBOTTOM, 
		       TRUE, subMenu);
    me->setSensitive(multi);
    entries.add(me);

    me = new MenuEntry(this, ME_PUSHBUTTON, LWIDGET_ALIGNHCENTER, 
		       TRUE, subMenu);
    me->setSensitive(multi);
    entries.add(me);

    me = new MenuEntry(this, ME_PUSHBUTTON, LWIDGET_ALIGNVCENTER, 
		       TRUE, subMenu);
    me->setSensitive(multi);
    entries.add(me);

    me = new MenuEntry(this, ME_PUSHBUTTON, LWIDGET_ALIGNWIDTH, 
		       TRUE, subMenu);
    me->setSensitive(multi);
    entries.add(me);

    me = new MenuEntry(this, ME_PUSHBUTTON, LWIDGET_ALIGNHEIGHT, 
		       TRUE, subMenu);
    me->setSensitive(multi);
    entries.add(me);
  }

  entries.add( new MenuEntry(this, ME_SEPARATOR, "Sep" ,FALSE));
  
  me = new MenuEntry(this, ME_PUSHBUTTON, LWIDGET_CUT, TRUE);     // cut
  me->setKeyBinding(0, "x");
  entries.add(me);

  me = new MenuEntry(this, ME_PUSHBUTTON, LWIDGET_COPY, TRUE);    // copy 
  me->setKeyBinding(0, "c");
  entries.add(me);

  me = new MenuEntry(this, ME_PUSHBUTTON, LWIDGET_PASTE, FALSE);  // paste 
  me->setKeyBinding(0, "v");
  if(Lwidget::clipboard.getSize() == 0)
    me->setSensitive(FALSE);
  else {
    Boolean asChildOk = TRUE;
    for(unsigned int i=0; i<Lwidget::clipboard.getSize(); i++) {
      if(!lwidget->asChildOk(Lwidget::clipboard[i])) {
	asChildOk = FALSE;
	break;
      }
    }
    me->setSensitive(asChildOk);
  }
  entries.add(me);

  if( WidgetView::findWidget(lwidget)) {
    entries.add( new MenuEntry(this, ME_SEPARATOR, "Sep" ,FALSE));
    
    if(lwidget->getClass()->getManagePolicy() == DIALOG_MANAGE) {
      me = new MenuEntry(this, ME_TOGGLEBUTTON, LWIDGET_VISIBILITY ,
			 FALSE);
      Boolean state;
      if(!lwidget->getVDBoolean(WidgetView::findWidget(lwidget), 
				VD_SHOW_DIALOG, state))
	state = TRUE;
      me->setToggleButtonValue(state);
      entries.add(me);
    }

    me = new MenuEntry(this, ME_PUSHBUTTON, LWIDGET_REFRESH,FALSE);
    me->setKeyBinding(0,"f");
    entries.add(me);
  }
  
  entries.add( new MenuEntry(this, ME_SEPARATOR, "Sep" ,FALSE));
  
  me = new MenuEntry(this, ME_PUSHBUTTON, LWIDGET_DELETE,FALSE);
  me->setKeyBinding(0, "osfDelete");
  entries.add(me);

}

// ----------------------
//    defaultAction()
// ----------------------
void WidgetController::defaultAction()
{
  WidResEditor::showView(lwidget);
}

// ----------------------
//       actOnce()
// ----------------------

void WidgetController::actOnce(MenuEntry* me)
{
  // #####################################################################
  //                      Rename
  
  if(me->match(LWIDGET_RENAME)) {
    SensitiveRec *sr = ((SensitiveRec*)(View*)view);
    sr->getContainer()->edit(sr, 0, 0, TRUE);
  }

  // #####################################################################
  //                      CLIPBOARD

  if(me->match(LWIDGET_COPY) || me->match(LWIDGET_CUT)) {
    while(Lwidget::clipboard.getSize())
      delete Lwidget::clipboard[0];

    RefArray<Lwidget> sel;
    sel.setRemoveOnDelete(FALSE);

    for(unsigned int i=0; i<selection.getSize(); i++) {
      Controller *c = selection[i];
      sel.add(((WidgetController*)c)->lwidget);
    }
    for(unsigned int i=0; i<sel.getSize(); i++) {
      if(!sel[i].isNil()) {
	Lwidget::clipboard.add(sel[i]->copy());
	if(me->match(LWIDGET_CUT))
	  sel[i].Delete();
      }
    }
  }

  // #####################################################################
  //                      ALIGNMENTS

  if(me->match(LWIDGET_ALIGNLEFT)) {                        // Align Left
    Position x;
    x = lwidget->getProperties()->getResource("x");

    for(unsigned int i=0; i<selection.getSize(); i++) {
      Controller *c = selection[i];
      ((WidgetController*)c)->lwidget->getProperties()->setResource("x", x);
    }
    for(unsigned int i=0; i<selection.getSize(); i++) {
      Controller *c = selection[i];
      ((WidgetController*)c)->lwidget->changed(RESOURCE_CHANGED);
    }
  }

  if(me->match(LWIDGET_ALIGNTOP)) {                        // Align Top
    Position y;
    y = lwidget->getProperties()->getResource("y");

    for(unsigned int i=0; i<selection.getSize(); i++) {
      Controller *c = selection[i];
      ((WidgetController*)c)->lwidget->getProperties()->setResource("y", y);
    }
    for(unsigned int i=0; i<selection.getSize(); i++) {
      Controller *c = selection[i];
      ((WidgetController*)c)->lwidget->changed(RESOURCE_CHANGED);
    }
  }

  if(me->match(LWIDGET_ALIGNBOTTOM)) {                        // Align Bottom
    Position y, iy;
    Dimension height, iHeight;

    y = lwidget->getProperties()->getResource("y");
    height = lwidget->getProperties()->getResource("height");

    for(unsigned int i=0; i<selection.getSize(); i++) {
      Controller *c = selection[i];
      Lwidget *lw = ((WidgetController*)c)->lwidget;
      
      iHeight = lw->getProperties()->getResource("height");
      iy = y - (iHeight-height);
      lw->getProperties()->setResource("y", iy);
    }
    for(unsigned int i=0; i<selection.getSize(); i++) {
      Controller *c = selection[i];
      ((WidgetController*)c)->lwidget->changed(RESOURCE_CHANGED);
    }
  }

  if(me->match(LWIDGET_ALIGNRIGHT)) {                        // Align Right
    Position x, ix;
    Dimension width, iWidth;

    x = lwidget->getProperties()->getResource("x");
    width = lwidget->getProperties()->getResource("width");

    for(unsigned int i=0; i<selection.getSize(); i++) {
      Controller *c = selection[i];
      Lwidget *lw = ((WidgetController*)c)->lwidget;
      
      iWidth = lw->getProperties()->getResource("width");
      ix = x - (iWidth-width);
      lw->getProperties()->setResource("x", ix);
    }
    for(unsigned int i=0; i<selection.getSize(); i++) {
      Controller *c = selection[i];
      ((WidgetController*)c)->lwidget->changed(RESOURCE_CHANGED);
    }
  }

  if(me->match(LWIDGET_ALIGNHCENTER)) {              // Align Horizontal Center
    Position x, ix;
    Dimension width, iWidth;

    x = lwidget->getProperties()->getResource("x");
    width = lwidget->getProperties()->getResource("width");

    for(unsigned int i=0; i<selection.getSize(); i++) {
      Controller *c = selection[i];
      Lwidget *lw = ((WidgetController*)c)->lwidget;
      
      iWidth = lw->getProperties()->getResource("width");
      ix = x - (iWidth-width)/2;
      lw->getProperties()->setResource("x", ix);
    }
    for(unsigned int i=0; i<selection.getSize(); i++) {
      Controller *c = selection[i];
      ((WidgetController*)c)->lwidget->changed(RESOURCE_CHANGED);
    }
  }

  if(me->match(LWIDGET_ALIGNVCENTER)) {               // Align Vertical Center
    Position y, iy;
    Dimension height, iHeight;

    y = lwidget->getProperties()->getResource("y");
    height = lwidget->getProperties()->getResource("height");

    for(unsigned int i=0; i<selection.getSize(); i++) {
      Controller *c = selection[i];
      Lwidget *lw = ((WidgetController*)c)->lwidget;
      
      iHeight = lw->getProperties()->getResource("height");
      iy = y - (iHeight-height)/2;
      lw->getProperties()->setResource("y", iy);
    }
    for(unsigned int i=0; i<selection.getSize(); i++) {
      Controller *c = selection[i];
      ((WidgetController*)c)->lwidget->changed(RESOURCE_CHANGED);
    }
  }

  if(me->match(LWIDGET_ALIGNWIDTH)) {                        // Align Width
    Dimension width;
    width = lwidget->getProperties()->getResource("width");

    for(unsigned int i=0; i<selection.getSize(); i++) {
      Controller *c = selection[i];
      ((WidgetController*)c)->lwidget->getProperties()->setResource("width", 
								    width);
    }
    for(unsigned int i=0; i<selection.getSize(); i++) {
      Controller *c = selection[i];
      ((WidgetController*)c)->lwidget->changed(RESOURCE_CHANGED);
    }
  }

  if(me->match(LWIDGET_ALIGNHEIGHT)) {                        // Align Height
    Dimension height;
    height = lwidget->getProperties()->getResource("height");

    for(unsigned int i=0; i<selection.getSize(); i++) {
      Controller *c = selection[i];
      ((WidgetController*)c)->lwidget->getProperties()->setResource("height", 
								    height);
    }
    for(unsigned int i=0; i<selection.getSize(); i++) {
      Controller *c = selection[i];
      ((WidgetController*)c)->lwidget->changed(RESOURCE_CHANGED);
    }
  }

}

// ------------------------------------------
//               act()
// ------------------------------------------

void WidgetController::act(MenuEntry *me)
{
  // ----------------- Clipboard Paste -----------

  if(me->match(LWIDGET_PASTE)) {
    for(unsigned int i=0; i<Lwidget::clipboard.getSize(); i++) {
      Lwidget *lw;
      lw = Lwidget::clipboard[i]->copy();
      lwidget->add(lw);
    }
    lwidget->changed(CONTAINER_CHANGED);
  }

  
  if(me->match(LWIDGET_DELETE)) {
    if( lwidget->getChildren().getSize() > 0 ) {
      char title[256];
      char msg[1024];
      msgCat->getMsg( title, QUERY_WIDGET_DELETE_TITLE );
      msgCat->getMsg( msg, QUERY_WIDGET_DELETE_MSG, lwidget->getName() );
      if( MSGBOX_OK == LicView::MsgBox(title, msg, MSGBOX_STYLE_YESNO) )
	delete lwidget;
    } else 
      delete lwidget;
  }
  if(me->match(LWIDGET_EDIT)) {
    LicView::setWaitCursor(TRUE);
    WidResEditor::showView(lwidget);
    LicView::setWaitCursor(FALSE);
  }
  if(me->match(LWIDGET_BROWSE)) {
    LicView::setWaitCursor(TRUE);
    WidBrowseView::showView(lwidget);
    LicView::setWaitCursor(FALSE);
  }
  if(me->match(LWIDGET_VISIBILITY)) {
    Boolean state;
    state = me->getToggleButtonValue();
    lwidget->setVDBoolean(WidgetView::findWidget(lwidget), 
			  VD_SHOW_DIALOG, state);
    lwidget->changed(VIEWDATA_CHANGED);
  }
  if(me->match(LWIDGET_REFRESH)) {
    lwidget->changed(RESOURCE_CHANGED);
  }

  if(me->match(LWIDGET_MENUEDIT)) {
    MenuEdit::showEditor( lwidget );
  }
  if(me->match(LWIDGET_ATTACHMENTS)) {
    AttachmentEditor::showView( lwidget );
  }
  if(me->match(LWIDGET_TRANSFORM)) {
    TransformDialog::showView( lwidget );
  }
}



/* ####################################################

   WidgetView    -   the wysisyg view of a widget

   #################################################### */


RefArray<WidgetView> WidgetView::allViews;
WidgetView::DragInfo WidgetView::draggedObject;
XContext WidgetView::uniqueContext;
Boolean WidgetView::optimalRefresh = TRUE;
RefArray<Controller> WidgetView::controllers;

Widget WidgetView::updateParent;
int WidgetView::position;       


// -----------------------------------
//     WidgetView()
// -----------------------------------
WidgetView::WidgetView( Lwidget *model, WidgetView *parent )
:WinView(model)
{
  widget = NULL;
  lwidget = model;
  this->parent = parent;
  gc = 0;
  linkOk = TRUE;

  display = XtDisplay(Lproject::current().getTopLevel());

  original = TRUE;
  if(lwidget->isLinked()) 
    original = FALSE;
  if(parent && !parent->original)
    original = FALSE;


  if( parent && parent->widget )   // only if parent has a real widget
    createWidget();                // create the widget with no populate
  else 
    if( !parent )
      createWidget();              // create the widget with no populate

  allViews.add(this);
  
  if( lwidget->isLinked() ) { 
    Linterface *interface = 
      Lproject::current().getInterface(lwidget->getNameOfLinkedInterface());
    if(interface)
      children.add( new WidgetView((interface->getShell()->getChildren())[0],
				   this));
    else
      linkOk = FALSE;
  } else {
    // no link
    for( unsigned int i=0; i<model->getChildren().getSize(); i++ ) {
      children.add( new WidgetView((model->getChildren())[i],this) );
    }
  }
}

// ----------------------------------
//        ~WidgetView()
// ----------------------------------
WidgetView::~WidgetView()
{
  Widget tmp = widget;
  if( widget && !((Object)widget)->object.being_destroyed ) {
//    XmDropSiteUnregister(widget);
    widgetDestroyed();
    XtDestroyWidget(tmp);
  }

  while( children.getSize() )
    children[0].Delete();

  if(gc)
    XFreeGC(display, gc);

}

// --------------------------------------------------------------
//   SetTestMode()
// 
//   Im Testmode verhalten sich die Widgets die von 
//   Lwidget erzeugt werden wie normal
//   Ist der Testmode aus, dann koennen sie editiert werden
// --------------------------------------------------------------

void WidgetView::SetTestMode( Boolean b )
{
  testMode = b;

  if( strcmp( Selectable::getCurrentClass(), "Lwidget" ) )
    return;
  RefArray<Selectable> selection = Selectable::getSelection();
  for(Cardinal i=0; i<selection.getSize(); i++ )
    selection[i]->changed( SELECTION_CHANGED );
}


// ------------------------------------------
//       ButtonPressEvent() 
// ------------------------------------------

void WidgetView::ButtonPressEvent(Widget, XtPointer this_class, 
				  XEvent *event, Boolean *b )
{
  WidgetView *self = (WidgetView*)this_class;

  static Time lastTime = 0;
  Boolean doubleClick = FALSE;
  Time thisTime = ((XButtonEvent*)event)->time;
  if(thisTime - lastTime < 300)
    doubleClick = TRUE;
  
  *b = testMode;

  Window retRoot, retChild;
  int retRootX, retRootY, retX, retY;
  unsigned int retKey;
  XQueryPointer( XtDisplay((Widget)self->widget), 
		XtWindow((Widget)self->widget), 
		&retRoot, &retChild,
		&retRootX, &retRootY,
		&retX, &retY,
		&retKey );
  
  if(testMode) {
    if( retKey & Button3Mask ) {
      for(unsigned int i=0; i<self->children.getSize(); i++) {
	if(!strcmp(self->children[i]->lwidget->getClass()->getName(),
		   "XmCreatePopupMenu")) {
	  XButtonEvent *be = (XButtonEvent*)event;
	  XmMenuPosition(self->children[i]->widget, be);
	  XtManageChild(self->children[i]->widget);
	  break;
	}
      }
    }
    return;
  }
  if( retKey & Button3Mask ) {
    while(controllers.getSize() != 0)
      controllers[0].Delete();
    if(self->lwidget->isSelected()) {
      RefArray<Selectable> s(Selectable::getSelection());
      for(unsigned int i=0; i<s.getSize(); i++) {
	Lwidget *lw = (Lwidget*)(Selectable*)s[i];
	controllers.add(new WidgetController(lw, self));
      }
    } else {
      controllers.add(new WidgetController(self->lwidget, self));
    }
    Window dummy;
    int x, y;
    Widget w = self->findTop()->widget;
    XTranslateCoordinates(XtDisplay(self->widget), XtWindow(self->widget), 
			  XtWindow(w), retX, retY, &x, &y, &dummy );

    controllers[0]->popupMenu(w, x, y, controllers);
    XtUngrabButton(w, Button3, ShiftMask|ControlMask);
    return;
  }
  
  if(retKey & Button2Mask) {
    self->startDrag(event, retX, retY);
    return;
  }
  if(retKey & Button1Mask) {
    lastTime = thisTime;
    if(doubleClick) {
      while(controllers.getSize() != 0)
	controllers[0].Delete();
      if(self->lwidget->isSelected()) {
	RefArray<Selectable> s(Selectable::getSelection());
	for(unsigned int i=0; i<s.getSize(); i++) {
	  Lwidget *lw = (Lwidget*)(Selectable*)s[i];
	  controllers.add(new WidgetController(lw, self));
	}
      } else {
	controllers.add(new WidgetController(self->lwidget, self));
      }
      LicView::setWaitCursor(TRUE);
      for(unsigned int i=0; i<controllers.getSize(); i++) 
	controllers[i]->defaultAction();
      LicView::setWaitCursor(FALSE);
    }
    Lwhere where(Lproject::current(), self->widget);
    if( where.isCanceled() )
      return;
    if( where.isSelected() ) {
      self->lwidget->select((retKey & ControlMask) == ControlMask);
      return;
    }
    // Dat ding muss wo anders hin 
    int x,y,width,height;
    Lproperty *prop = self->lwidget->getProperties();

    prop->convertFromPixel(where.getx(), where.gety(), x, y);
    prop->convertFromPixel(where.getwidth(), where.getheight(), width, height);
						     
    if(!strcmp(self->lwidget->getClass()->getName(), "XmCreateScrolledText") ||
       !strcmp(self->lwidget->getClass()->getName(), "XmCreateScrolledCSText") ||
       !strcmp(self->lwidget->getClass()->getName(), "XmCreateScrolledList")) {
      Widget w = XtParent(self->widget);
      Position mx, my;
      XtVaGetValues(w, XmNx, &mx, XmNy, &my, NULL);
      x += mx;
      y += my;
    }    
    prop->setResource( "x", x);
    prop->setResource( "y", y);
    prop->setResource("width", width);
    prop->setResource("height", height);
    self->lwidget->changed(RESOURCE_CHANGED | GEOMETRY_CHANGED);
  }
}



// ------------------------------------------
//       ButtonReleaseEvent() 
// ------------------------------------------


void WidgetView::ButtonReleaseEvent(Widget, XtPointer ,
				  XEvent *, Boolean *b )
{

  *b = testMode;
  if(testMode)
    return;

#if(0)
  if(bEvent->state & Button1Mask) {  /* Selected this Widget */

    switch( button1Mode ) {
    case WV_EDIT:
      LresEditor *e = LresEditor::getAutoLoad();
      if( e )
	e->setNewLwidget(self->lwidget);
      else 
	e = new LresEditor(self->lwidget);
      e->open();
      break;

    case WV_SELECT:
      self->lwidget->select();
      break;

    case WV_RESIZE:
      break;
    }
  }
#endif
}


// ------------------------------------------
//       Button2MotionEvent() 
// ------------------------------------------


void WidgetView::Button2MotionEvent(Widget , XtPointer,
				  XEvent *, Boolean *b )
{
  *b = testMode;
  if(testMode)
    return;
}



// ------------------------------------------
//       TrashEvent() 
// ------------------------------------------


void WidgetView::TrashEvent(Widget, XtPointer client, XEvent *event, Boolean *b )
{
  WidgetView *self = (WidgetView*)client;
  *b = testMode;

  if(testMode)
    return;

  if(event->type == KeyPress) {
    XKeyEvent *keyEvent = (XKeyEvent*)event;
    KeySym sym;
    Modifiers ret_mod;

    XmTranslateKey(keyEvent->display, keyEvent->keycode, keyEvent->state,
		   &ret_mod, &sym);

    while(controllers.getSize() != 0)
      controllers[0].Delete();
    RefArray<Selectable> s(Selectable::getSelection());
    if(!strcmp(Selectable::getCurrentClass(), "Lwidget")) {
      for(unsigned int i=0; i<s.getSize(); i++) {
	Lwidget *lw = (Lwidget*)(Selectable*)s[i];
	controllers.add(new WidgetController(lw, self));
      } 
      
      if(controllers.getSize() > 0)
	controllers[0]->processKey(keyEvent->state,
				   XKeysymToString(sym), controllers);
    }
  }
}

// ------------------------------------------
//       ExposeEvent() 
// ------------------------------------------

void WidgetView::ExposeEvent(Widget, XtPointer this_class,
			  XEvent *event, Boolean * )
{
  XExposeEvent *exevent = (XExposeEvent*)event;
  WidgetView *self = (WidgetView*)this_class;
  if( !testMode && exevent->count==0 && self->lwidget->isSelected() ) 
    self->draw_selected();
  if(exevent->count==0 && self->lwidget->isLinked() )
    self->testLink();
}
  
// ------------------------------------------
//       ConfigureEvent
// ------------------------------------------

void WidgetView::ConfigureEvent(Widget wg, XtPointer this_class,
				XEvent *event, Boolean * )
{
  if( event->type == ConfigureNotify ) {
    WidgetView *self = (WidgetView*)this_class;

    if(!self->original && !self->lwidget->isLinked()) 
                                        // nur frame im Link erlaubt
      return;

    if(!self->widget)
      return;

    Dimension width, height;
    XtVaGetValues(self->widget,
		  "width", &width,
		  "height", &height,
		  NULL );
  
    // Beim Pushbutton machen wir eine Ausnahme, da Motif hier 
    // einen Bug hat.

    if( strcmp(self->lwidget->getClass()->getName(), "XmPushButton") ) {
      // Set the width end height resource, if it is default
      Lresource *lres;
      unsigned int i;
    
      for( i=0; i<self->lwidget->getProperties()->getCore().getSize(); i++ ) {
	lres = self->lwidget->getProperties()->getCore()[i];
	if(!strcmp(lres->getName(),"width")) {
	  if(!lres->isDefault())
	    lres->setValue(width);
	  else
	    lres->setAsDefault(width);
	}
	if(!strcmp(lres->getName(),"height")) {
	  if(!lres->isDefault())
	    lres->setValue(height);
	  else
	    lres->setAsDefault(height);
	}
      }
    }

    if(!self->parent) {           // shell widget moechte position wissen
      Position x, y;
      XtVaGetValues(self->widget,
		    XmNx, &x,
		    XmNy, &y,
		    NULL);
      self->lwidget->getInterface()->moveTo(x,y,TRUE);
    }
    self->refresh();
  }

  if( event->type == MapNotify ) {

    WidgetView *self = (WidgetView*)this_class;

    XSaveContext(XtDisplay(wg),XtWindow(wg),getContext(),(XPointer)self);

    if(!self->widget)
      return;

    if( self->gc == 0 ) {
      XGCValues gcValues;
      Pixel bg;

      XtVaGetValues(self->widget, XmNbackground, &bg, NULL);
      if(bg != BlackPixelOfScreen(XtScreen(self->widget))) {
	gcValues.foreground = BlackPixelOfScreen(XtScreen(self->widget));
      } else {
	gcValues.foreground = WhitePixelOfScreen(XtScreen(self->widget));
      }
      gcValues.background = 0;
      gcValues.line_width = 3;
      gcValues.subwindow_mode = IncludeInferiors;
      gcValues.graphics_exposures = True;
      self->gc = XCreateGC( XtDisplay(self->widget),XtWindow(self->widget), 
			   GCForeground | GCGraphicsExposures |
			   GCBackground | GCLineWidth | GCSubwindowMode,
			   &gcValues );
      XFlushGC( XtDisplay(self->widget), self->gc );
    }
  }
  if( event->type == UnmapNotify ) {
    XDeleteContext(XtDisplay(wg),XtWindow(wg),getContext());
  }
}
  
// ------------------------------------------
//       getContext()
// ------------------------------------------

XContext WidgetView::getContext()
{
  if(!uniqueContext)
    uniqueContext = XUniqueContext();
  return uniqueContext;
}

// ------------------------------------------
//       draw_selected() 
// ------------------------------------------

void WidgetView::draw_selected()
{
  Window dummy;
  int x, y;
  unsigned int width, height, bwidth, depth, size;
  RefArray<Selectable> selection = Selectable::getSelection();

  if( gc != 0 ) {
    XGetGeometry(display, XtWindow(widget), &dummy, 
		 &x, &y, &width, &height,
		 &bwidth, &depth);
    
    size = 6;

    XDrawRectangle(XtDisplay((Widget)widget), XtWindow((Widget)widget), gc,
		   0, 0, width-1, height-1 );
    
    if((selection.getSize() > 1) && selection[0] == lwidget) {
      XDrawRectangle(XtDisplay((Widget)widget), XtWindow((Widget)widget), gc,
		     0, 0, size, size );
      XDrawRectangle(XtDisplay((Widget)widget), XtWindow((Widget)widget), gc,
		     0, height-size, size, size );
      XDrawRectangle(XtDisplay((Widget)widget), XtWindow((Widget)widget), gc,
		     width-size, height-size, size, size );
      XDrawRectangle(XtDisplay((Widget)widget), XtWindow((Widget)widget), gc,
		     width-size, 0, size, size );

      XDrawRectangle(XtDisplay((Widget)widget), XtWindow((Widget)widget), gc,
		     (width>>1)-(size>>1), 0, size, size );
      XDrawRectangle(XtDisplay((Widget)widget), XtWindow((Widget)widget), gc,
		     0, (height>>1)-(size>>1), size, size );
      XDrawRectangle(XtDisplay((Widget)widget), XtWindow((Widget)widget), gc,
		     width-size, (height>>1)-(size>>1), size, size );
      XDrawRectangle(XtDisplay((Widget)widget), XtWindow((Widget)widget), gc,
		     (width>>1)-(size>>1), height-size , size, size );
    } else {
      XFillRectangle(XtDisplay((Widget)widget), XtWindow((Widget)widget), gc,
		     0, 0, size, size );
      XFillRectangle(XtDisplay((Widget)widget), XtWindow((Widget)widget), gc,
		     0, height-size, size, size );
      XFillRectangle(XtDisplay((Widget)widget), XtWindow((Widget)widget), gc,
		     width-size, height-size, size, size );
      XFillRectangle(XtDisplay((Widget)widget), XtWindow((Widget)widget), gc,
		     width-size, 0, size, size );

      XFillRectangle(XtDisplay((Widget)widget), XtWindow((Widget)widget), gc,
		     (width>>1)-(size>>1), 0, size, size );
      XFillRectangle(XtDisplay((Widget)widget), XtWindow((Widget)widget), gc,
		     0, (height>>1)-(size>>1), size, size );
      XFillRectangle(XtDisplay((Widget)widget), XtWindow((Widget)widget), gc,
		     width-size, (height>>1)-(size>>1), size, size );
      XFillRectangle(XtDisplay((Widget)widget), XtWindow((Widget)widget), gc,
		     (width>>1)-(size>>1), height-size , size, size );
    }
  }
}

// ------------------------------------------
//       refresh() 
// ------------------------------------------

void WidgetView::refresh(Window win)
{
  
  if(gc && widget && XtWindow(widget)) {
    Window my, root, p, *childW;
    int x, y;
    unsigned int i;

    unsigned int width, height, bwidth, depth, numChildW;

    my = win ? win : XtWindow(widget);

    childW = NULL;
    XQueryTree(display, my, &root, &p, &childW, &numChildW);
    for( i=0; childW && i<numChildW; i++ ) 
      refresh(childW[i]);
    if(childW)
      XFree(childW);

    XGetGeometry(display, my, &root, &x, &y, &width, &height,
		 &bwidth, &depth);
    XClearArea(display, my, 0, 0, width, height, TRUE);
  }
}


// ------------------------------------------
//       testLink()
// ------------------------------------------

void WidgetView::testLink()
{
  Dimension width, height;
  Linterface *interface = 
    Lproject::current().getInterface(lwidget->getNameOfLinkedInterface());
  if( !interface ) {
    linkOk = FALSE;
    if( gc == 0 ) {
      XGCValues gcValues;
      Pixel bg;

      XtVaGetValues(widget, XmNbackground, &bg, NULL);
      if(bg != BlackPixelOfScreen(XtScreen((Widget)widget))) {
	gcValues.foreground = BlackPixelOfScreen(XtScreen((Widget)widget));
      } else {
	gcValues.foreground = WhitePixelOfScreen(XtScreen((Widget)widget));
      }
      gcValues.subwindow_mode = IncludeInferiors;
      gcValues.background = 0;
      gcValues.line_width = 3;
      gcValues.graphics_exposures = True;
      gc = XCreateGC( XtDisplay((Widget)widget), XtWindow((Widget)widget), 
		     GCForeground | GCGraphicsExposures |
		     GCBackground | GCLineWidth | GCSubwindowMode,
		     &gcValues );
      XFlushGC( XtDisplay((Widget)widget), gc );
    }
    XtVaGetValues( widget,
		  "width", &width,
		  "height", &height,
		  NULL );
    XDrawLine(XtDisplay((Widget)widget),XtWindow((Widget)widget),gc,0,0,width,height);
    XDrawLine(XtDisplay((Widget)widget),XtWindow((Widget)widget),gc,width,0,0,height);
  } else {
    if( !linkOk ) {
      children.add( new WidgetView((interface->getShell()->getChildren())[0],
				   this));
      linkOk = TRUE;
    }
  }
}



// ---------------------------------
//       findWidget()
// ---------------------------------

WidgetView *WidgetView::findWidget( Widget wg )
{
  WidgetView *self=NULL;
  if(!XFindContext(XtDisplay(wg),XtWindow(wg),getContext(),(char**)(&self)))
    return self;
  for( unsigned int i=0 ; i<allViews.getSize(); i++ )
    if( allViews[i]->widget == wg )
      return allViews[i];
  return NULL;
}

WidgetView *WidgetView::findWidget(Lwidget *lwidget)
{
  for( unsigned int i=0 ; i<allViews.getSize(); i++ )
    if(allViews[i]->lwidget == lwidget && 
       (allViews[i]->original || allViews[i]->lwidget->isLinked()))
      return allViews[i];
  return NULL;
}


// --------------------------------------
//           updateFrom()
// --------------------------------------

WidgetView *WidgetView::updateFrom()
{
  if(parent && optimalRefresh) {
    if(parent->lwidget->getClass()->getUpdatePolicy() == ON_CHILD_UPDATE ||
       parent->lwidget->isLinked())
      return parent->updateFrom();
    else
      return this;
  }
  return this;
}

// --------------------------------------
//           update()
// --------------------------------------
void WidgetView::update( unsigned long flags )
{
  WidgetView *from, *shell;
  unsigned int i;
  
  if( flags & CONTAINER_CHANGED ) {
    from = updateFrom();

    shell = from;
    while(shell->parent) {
      shell = shell->parent;     // von dem obersten Widget (Shell)
    }
    if(from->widget) {
      XtDestroyWidget(from->widget);
      from->widgetDestroyed();          // set widget to NULL
      //      _XtDoPhase2Destroy(context, 0);
    }
    while( children.getSize() )          // update the children
      children[0].Delete();
    for( i=0; i<lwidget->getChildren().getSize(); i++ )  // update children
      children.add( new WidgetView((lwidget->getChildren())[i],this) );

    from->createWidget(TRUE);                 // populate

    if( !from->parent ) {        // it's an interface
      Linterface *li = lwidget->getInterface();
      li->show();
    }

    shell->setRelation();
    shell->manageDialogs();

#if(0)
    if(XtIsComposite(from->widget) && 
       ((CompositeWidgetClass)XtClass(from->widget))
       ->composite_class.change_managed) {
      ((CompositeWidgetClass)XtClass(from->widget))->
	composite_class.change_managed(from->widget);
      
    }
#endif
  }

  if( flags & (RESOURCE_CHANGED | NAME_CHANGED) && 
                             // Wenn oben schon durch, dann hier nicht
     (flags & CONTAINER_CHANGED) != CONTAINER_CHANGED) {  

    from = updateFrom();   // Widget herausfinden, von dem der update laeuft
    shell = from;
    while(shell->parent) {
      shell = shell->parent;     // von dem obersten Widget (Shell)
    }

    if((from->parent == shell) &&
       (flags & GEOMETRY_CHANGED)) {       // top non shell widget
      from = shell;
    }

    XtDestroyWidget(from->widget);
    from->widgetDestroyed();          // set widget to NULL
    //    _XtDoPhase2Destroy(context, 0);

    from->createWidget(TRUE);         // recursive widget creation
    updateParent = NULL;

    if( !from->getParent() ) {        // it's an interface
      Linterface *li = lwidget->getInterface();
      li->show();
    }
    
    shell->setRelation();
#if(0)
    if(XtIsComposite(from->widget) && 
       ((CompositeWidgetClass)XtClass(from->widget))
       ->composite_class.change_managed) {
      ((CompositeWidgetClass)XtClass(from->widget))->
	composite_class.change_managed(from->widget);
      
    }
#endif
    shell->manageDialogs();
    
  }

  if( flags & SELECTION_CHANGED ) {
    RefArray<Selectable> selection = Selectable::getSelection();
    for(i=0; i<selection.getSize(); i++) {
      WidgetView *wv;
      Lwidget *lw = (Lwidget*)(Selectable*)selection[i];
      wv = findWidget(lw);
      if(wv)
	wv->refresh();
    }
    if(!lwidget->isSelected())
      refresh();
  }

  if( flags & VIEWDATA_CHANGED ) {
    if( lwidget->getClass()->getManagePolicy() == DIALOG_MANAGE ) {
      Boolean showIt;
      if(!lwidget->getVDBoolean(this, VD_SHOW_DIALOG, showIt))
	XtManageChild(widget);
      if(showIt)
	XtManageChild(widget);
      else
	XtUnmanageChild(widget);
    }
  }
}

// --------------------------------------
//           createWidget()
// --------------------------------------
void WidgetView::createWidget( Boolean populate )
{
  unsigned int i;
  Cardinal count = MAX_ARGS;
  Arg args[count];
  Cardinal numChildren = 0, numChildrenAfter = 0;

  isPopup = FALSE;

  if(parent && parent->widget)            // Wieviel Kinder vor dem create
    XtVaGetValues(parent->widget,
		  XmNnumChildren, &numChildren,
		  NULL);

  lwidget->getProperties()->getArgList( args, count );

  if( !lwidget->isLinked() ) {
    widget = lwidget->getClass()->createWidget(parent ? parent->widget
					       :(Widget)NULL,
					       lwidget->getName(), 
					       args, count );
  } else {
    widget = lwidget->getClass()->createWidget(parent ? parent->widget 
					       :(Widget)NULL,
					       lwidget->getName(), 
					       args, count );
  }

  updateParent = NULL;

  if(parent && parent->widget) {           // Wieviel Kinder nach dem create
    XtVaGetValues(parent->widget,
		  XmNnumChildren, &numChildrenAfter,
		  NULL);
    if(numChildren == numChildrenAfter)
      isPopup = TRUE;
  }

  lwidget->getProperties()->fillWithDefaults( widget );

  // Hack for BulletinBord, Form, ...
  if(lwidget->getProperties()->hasSpecSize()) {  // don't allow resize
    XtVaSetValues(widget, XmNresizePolicy, XmRESIZE_NONE, NULL);
  } else {
    XtVaSetValues(widget, XmNresizePolicy, XmRESIZE_ANY, NULL);
  }

  if(XtIsShell(widget))
    XtVaSetValues(widget, XmNallowShellResize, TRUE, NULL);


  prepareWidget(widget);

  // Add HelpCallback
  if(lwidget->getHelpNode()) {
    XtAddCallback(widget, XmNhelpCallback, helpCallback, this);
  }


  if(lwidget->getClass()->getManagePolicy()==DIALOG_MANAGE) {
    XtVaSetValues(XtParent(widget),                // flackert sonst
		  XmNallowShellResize, FALSE,
		  NULL);
    XtAddCallback(XtParent(widget), XmNpopdownCallback, dialogPopdown, this);
  }

  if( populate ) {
    for( i=0; i<children.getSize(); i++ )
      children[i]->createWidget(TRUE);
  }

  if( parent != NULL ) {
    if(lwidget->getClass()->getManagePolicy() != NEVER_MANAGE &&
       lwidget->toManage()) {
      XtManageChild(widget);
    } else {
      if(lwidget->getClass()->getManagePolicy() == DIALOG_MANAGE) {
	Boolean showIt;
	if(!lwidget->getVDBoolean(this, VD_SHOW_DIALOG, showIt))
	  showIt = lwidget->toManage();
	if(showIt)
	  XtManageChild(widget);
      }
    }
  }
}


// -----------------------
//     prepareWidget()
// -----------------------

void 
WidgetView::prepareWidget(Widget wg)
{
  WidgetView *self = this;
  if(!original) {
    WidgetView *tmp = findTop();
    if(tmp->parent) 
      self = tmp->parent;
  }
  
  if(original && !lwidget->getClass()->isShell())
    registerDropSite(wg);              // enable dropping over new widget
  else if(!original && !lwidget->getClass()->isShell()) {
    XmDropSiteUnregister(wg);    // disable dropping over text widgets
  }

  XtAddEventHandler(wg, ButtonPressMask, 
		    False, ButtonPressEvent, self);
  XtAddEventHandler(wg, ButtonReleaseMask, 
		    False, ButtonReleaseEvent, self);
  XtAddEventHandler(wg, Button2MotionMask, 
		    False, Button2MotionEvent, self);
  XtAddEventHandler(wg, 
		    KeyPressMask | KeyReleaseMask | EnterWindowMask |
		    LeaveWindowMask| Button2MotionMask| 
		    Button3MotionMask, 
		    False, TrashEvent, self);
  XtInsertEventHandler(wg, ExposureMask,  False, 
		       ExposeEvent, this, XtListTail );
  XtInsertEventHandler(wg, StructureNotifyMask, 
		       TRUE, ConfigureEvent, this, XtListTail );


  if(XtIsConstraint(wg)) {
    Cardinal numChildren = 0;
    WidgetList widgetList;

    XtVaGetValues(wg, 
		  XmNchildren, &widgetList,
		  XmNnumChildren, &numChildren,
		  NULL );
    for(Cardinal i=0; i<numChildren; i++ ) {
      if(XtIsWidget(widgetList[i]) &&
	 !((Object)widgetList[i])->object.being_destroyed ) {
	prepareWidget(widgetList[i]);
      }
    }
  }
}

// -----------------------
//     setRelation()
// -----------------------

void WidgetView::setRelation()
{
  unsigned int i;

  lwidget->getProperties()->setRelation(this);

  for( i=0; i<children.getSize(); i++ )
    children[i]->setRelation();

}

// -----------------------
//     dialogPopdown()
// -----------------------

void WidgetView::dialogPopdown(Widget, XtPointer clientData, XtPointer)
{
  WidgetView *self = (WidgetView*)clientData;
  
  self->lwidget->setVDBoolean(self, VD_SHOW_DIALOG, FALSE);
  self->lwidget->changed(VIEWDATA_CHANGED);
}

// -----------------------
//     manageDialogs()
// -----------------------

void WidgetView::manageDialogs()
{
  unsigned int i;

  if(lwidget->getClass()->getManagePolicy() == DIALOG_MANAGE &&
     !XtIsManaged(widget)) {
    Boolean showIt;
    if(!lwidget->getVDBoolean(this, VD_SHOW_DIALOG, showIt))
      XtManageChild(widget);
    if(showIt)
      XtManageChild(widget);
  }
  for( i=0; i<children.getSize(); i++ )
    children[i]->manageDialogs();
}

// -----------------------
//     findNamedWidget()
// -----------------------

Widget WidgetView::findNamedWidget(char *name)
{
  unsigned int i;

  if(!strcmp(name, lwidget->getName()))
    return widget;
     
  for( i=0; i<children.getSize(); i++ ) {
    Widget wg;
    wg = children[i]->findNamedWidget(name);
    if( wg )
      return wg;
  }
  return NULL;
}

// -----------------------
//     findTop()
// -----------------------
WidgetView *WidgetView::findTop()
{
  WidgetView *ret = this;

  while( ret->parent && !ret->parent->lwidget->isLinked() )
    ret = ret->parent;

  return ret;
}

// -----------------------
//     widgetDestroyed()
// -----------------------

void WidgetView::widgetDestroyed()
{
  widget = NULL;
  for(unsigned int i=0; i<children.getSize(); i++ )
    children[i]->widgetDestroyed();
}

// ####################  Drag & Drop Facilities ###################

// -----------------------
//     registerDropSite()
// -----------------------

void WidgetView::registerDropSite(Widget wg)
{
  imports[0] = XmInternAtom(display,lwidget->getClassName(),False);

  Arg args[10];
  Cardinal n = 0;
  XtSetArg(args[n], XmNimportTargets, imports); n++;
  XtSetArg(args[n], XmNnumImportTargets, 1); n++;
  XtSetArg(args[n], XmNdropSiteOperations, XmDROP_COPY|XmDROP_MOVE); n++;
  XtSetArg(args[n], XmNdropProc, dropProc); n++;
  XtSetArg(args[n], XmNdragProc, dragProc); n++;
  XtSetArg(args[n], XmNdropSiteType, XmDROP_SITE_COMPOSITE); n++;
  XtSetArg(args[n], XmNanimationStyle, XmDRAG_UNDER_NONE); n++;
  XmDropSiteUnregister(wg);
  XmDropSiteRegister(wg,args,n);
}

// -----------------------
//     startDrag()
// -----------------------

void WidgetView::startDrag(XEvent *event, Position x, Position y)
{
  Arg args[10];
  Cardinal n;

  static XtCallbackRec finishCBList[2];
  static XtCallbackRec topLevelEnterCBList[2];
  static XtCallbackRec topLevelLeaveCBList[2];

  finishCBList[0].callback = dropFinish;
  finishCBList[0].closure =  NULL;
  finishCBList[1].callback = NULL;
  finishCBList[1].closure =  NULL;

  topLevelEnterCBList[0].callback = topLevelEnter;
  topLevelEnterCBList[0].closure =  this;
  topLevelEnterCBList[1].callback = NULL;
  topLevelEnterCBList[1].closure =  NULL;

  topLevelLeaveCBList[0].callback = topLevelLeave;
  topLevelLeaveCBList[0].closure =  this;
  topLevelLeaveCBList[1].callback = NULL;
  topLevelLeaveCBList[1].closure =  NULL;

  exports[0] = XmInternAtom(display,"COMPOUND_TEXT",False);
  exports[1] = XmInternAtom(display,lwidget->getClassName(),False);

  draggedObject.dragged = this;
  draggedObject.offsetX = x;
  draggedObject.offsetY = y;

  n = 0;
  XtSetArg(args[n], XmNexportTargets, exports); n++;
  XtSetArg(args[n], XmNnumExportTargets, 2); n++;
  XtSetArg(args[n], XmNconvertProc, convertProc); n++;
  XtSetArg(args[n], XmNdropFinishCallback, finishCBList); n++;
  XtSetArg(args[n], XmNtopLevelEnterCallback, topLevelEnterCBList); n++;
  XtSetArg(args[n], XmNtopLevelLeaveCallback, topLevelLeaveCBList); n++;
  XtSetArg(args[n], XmNdragOperations, XmDROP_COPY | XmDROP_MOVE); n++;
  XmDragStart(widget, event, args, n);
}

// -----------------------
//     dropFinish()
// -----------------------

void WidgetView::dropFinish(Widget ,XtPointer clientData,XtPointer)
{
  if(clientData) {      // changed() ist nach dem Drop aufzurufen
    DropFinishInfo *pdfi = (DropFinishInfo*)clientData;
    if(pdfi->droppedOn)
      pdfi->droppedOn->changed(CONTAINER_CHANGED);
    if(pdfi->lwidget)
      pdfi->lwidget->changed(RESOURCE_CHANGED);
    if(pdfi->parent)
      pdfi->parent->changed(CONTAINER_CHANGED);
  } else {
    draggedObject.dragged = NULL;
  }
}

void WidgetView::topLevelEnter(Widget wg,XtPointer clientData,
			       XtPointer callData)
{
  char *dummy;
  Widget sourceIcon;
  WidgetView *self = (WidgetView*)clientData;

  XmTopLevelEnterCallback cb = (XmTopLevelEnterCallback)callData;

  if(!XFindContext(XtDisplay(wg), cb->window, getContext(), &dummy)) {
    
    sourceIcon = WinView::getIconFromBits(Lproject::current().getTopLevel(), 
					  noSource_bits,
					  noSource_width,
					  noSource_height,
					  noSource_mask_bits,
					  noSource_mask_width,
					  noSource_mask_height,
					  0, 0);
    XtVaSetValues(wg,
		  XmNsourceCursorIcon, sourceIcon,
		  NULL);
  } else {
    sourceIcon = WinView::getIconFromPixmapName(
                               Lproject::current().getTopLevel(), 
			       self->lwidget->getPixmapFile());
    XtVaSetValues(wg,
		  XmNsourceCursorIcon, sourceIcon,
		  NULL);
  }
}

void WidgetView::topLevelLeave(Widget, XtPointer, XtPointer)
{
}

// -----------------------
//     convertProc()
// -----------------------

Boolean WidgetView::convertProc(Widget w, Atom *, 
			   Atom *target, Atom *type,
			   XtPointer *value, unsigned long *length, 
			   int *format, unsigned long *,
			   XtPointer, XtRequestId *)
{
  XmString xmstr;
  char *ctext;
  char *passtext;
  WidgetView *self = draggedObject.dragged;
  
  if(*target == XmInternAtom(XtDisplay(w),"DELETE",False)) {
    *value = NULL;
    *type = XmInternAtom(XtDisplay(w), "NULL", False);
    *length = 0;
    *format = 8;
    return True;
  }

  if(!self)
    return False;

  if(*target == self->exports[0]) {
    xmstr = XmStringCreateLocalized(self->lwidget->getName());
    ctext = XmCvtXmStringToCT(xmstr);
    passtext = XtMalloc(strlen(ctext)+1);
    memcpy(passtext, ctext, strlen(ctext)+1);
    *value = (XtPointer) passtext;
    *length = strlen(passtext);
    *type = self->exports[0];
    *format = 8;
  } else {
    if(*target == self->exports[1]) {
      Lwidget **ptr;
      *length = 1;
      *format = sizeof(Lwidget*)*8;
      ptr = (Lwidget**)XtMalloc(sizeof(Lwidget*)*(*length));
      *ptr = self->lwidget;
      *value = (XtPointer)ptr;
      *type = self->exports[1];
    } else
      return False;
  }

  return TRUE;
}


// -----------------------
//     drawXorRec()
// -----------------------

void WidgetView::drawXorRec(Rec &rec)
{
  static GC gc=0;
  Position x,y;
  Dimension width, height;
  char buf[64];
  int direction, ascent, descent;
  XCharStruct charStruct;
  XGCValues gcValues;
  Dimension tWidth, tHeight;

  if( !gc ) {
    
    XGCValues gcValues;
    Font fid;

    fid = XLoadFont(display, app->getLwhereFont());
    if(!fid) {
      fid = XLoadFont(display, "fixed");
    }
    Pixel bg;

    XtVaGetValues(widget, XmNbackground, &bg, NULL);
    if(bg != BlackPixelOfScreen(XtScreen((Widget)widget))) {
      gcValues.foreground = BlackPixelOfScreen(XtScreen((Widget)widget)) ^ bg;
    } else {
      gcValues.foreground = WhitePixelOfScreen(XtScreen((Widget)widget)) ^ bg;
    }
    gcValues.function = GXxor;
    gcValues.subwindow_mode = IncludeInferiors;
    gcValues.background = 0;
    gcValues.line_width = 1;
    gcValues.font = fid;
    gc = XCreateGC( display, XtWindow(widget), 
		   GCFunction | GCForeground | GCFont |
		   GCBackground | GCLineWidth | GCSubwindowMode,
		   &gcValues );
    XFlushGC(display, gc);
  }
  rec.getPosition(x,y);
  rec.getDimension(width,height);
  XDrawRectangle(display,XtWindow(widget),gc, 
		 x, y, width, height);
  
  sprintf(buf,"%+d%+d", x, y);
  
  XGetGCValues(display, gc, GCFont, &gcValues );
  XQueryTextExtents(display, gcValues.font, 
		    buf, strlen(buf),
		    &direction, &ascent, &descent, &charStruct );
  tWidth = charStruct.lbearing+charStruct.rbearing;
  tHeight = charStruct.ascent+charStruct.descent;
  
  XDrawString(display, XtWindow(widget), gc, 
	      x + width/2 - tWidth/2, 
	      y + height/2 + tHeight/2, 
	      buf, strlen(buf));

}

// -----------------------
//     getWindowRec()
// -----------------------

Rec WidgetView::getWindowRec()
{
  Window root;
  int x, y;
  unsigned int width, height, borderWidth, depth;
  XGetGeometry(display, XtWindow(widget), &root,
	       &x, &y, &width, &height, &borderWidth, &depth);
  return Rec(x, y, width, height);
}

// -----------------------
//     dropProc()
// -----------------------

void WidgetView::dropProc(Widget wg, XtPointer, XtPointer callData)
{
  WidgetView *self=findWidget(wg);
  static XmDropTransferEntryRec transList[1];
  static DropInfo dropInfo;

  Arg args[10];
  Cardinal n=0;
  XmDropProcCallback dd = (XmDropProcCallback)callData;


  dropInfo.widgetView = self;
  dropInfo.x = dd->x;
  dropInfo.y = dd->y;
  dropInfo.operation = dd->operation;
  dropInfo.dfi.droppedOn = NULL;
  dropInfo.dfi.parent = NULL;
  dropInfo.dfi.lwidget = NULL;
  XtAddCallback(dd->dragContext, XmNdestroyCallback, 
		dropFinish, &dropInfo.dfi);

  

  transList[0].target = self->imports[0];
  transList[0].client_data = (XtPointer)&dropInfo;
  XtSetArg(args[n], XmNdropTransfers, transList); n++;
  XtSetArg(args[n], XmNnumDropTransfers, 1); n++;
  XtSetArg(args[n], XmNtransferProc, transferProc); n++;
  XmDropTransferStart(dd->dragContext,args,n);
}


// -----------------------
//     dragProc()
// -----------------------

void WidgetView::dragProc(Widget wg, XtPointer, XtPointer callData)
{
  XmDragProcCallback dd = (XmDragProcCallback)callData;
  WidgetView *self=findWidget(wg);
  WidgetView *tmp;
  Lwidget *droppedOn = self->lwidget;
  Lwidget *lwidget = draggedObject.dragged ? 
    draggedObject.dragged->lwidget : (Lwidget*)NULL;
  Position x = dd->x;
  Position y = dd->y;
  Rec rec;

  
  if(self) {
    switch(dd->reason) {
    case XmCR_DROP_SITE_ENTER_MESSAGE:
//      XtVaGetValues(dd->dragContext,                // altes Icon speichern
//		    XmNstateCursorIcon, &oldStateIcon,
//		    NULL);
      if(draggedObject.dragged) {        // aus einem WidgetView 

	if(isDropValid(droppedOn, lwidget, dd->operation, x, y)) {
	  rec = draggedObject.dragged->getWindowRec();
	  rec.setPosition(x - draggedObject.offsetX, 
			  y - draggedObject.offsetY);
	  rec.gridX(app->getGrid() ? app->getGridValue() : 1);
	  rec.gridY(app->getGrid() ? app->getGridValue() : 1);
	  tmp = findWidget(droppedOn);
	  if(tmp) tmp->drawXorRec(rec);
	  draggedObject.lastDraw = rec;
	  draggedObject.lastDrawWidgetView = tmp;
	} else {
	  draggedObject.lastDrawWidgetView = NULL;
//	  XtVaSetValues(dd->dragContext, 
//			XmNstateCursorIcon, forbiddenIcon,
//			NULL);
	}
      }
      break;
    case XmCR_DROP_SITE_MOTION_MESSAGE:   // aus einem WidgetView 

      if(draggedObject.dragged && draggedObject.lastDrawWidgetView) {

	rec = draggedObject.lastDraw;
	draggedObject.lastDrawWidgetView->drawXorRec(rec);

	if(isDropValid(droppedOn, lwidget, dd->operation, x, y)) {
	  rec.setPosition(x - draggedObject.offsetX, 
			  y - draggedObject.offsetY);
	  rec.gridX(app->getGrid() ? app->getGridValue() : 1);
	  rec.gridY(app->getGrid() ? app->getGridValue() : 1);
	  tmp = findWidget(droppedOn);
	  if(tmp) tmp->drawXorRec(rec);
	  draggedObject.lastDraw = rec;
	  draggedObject.lastDrawWidgetView = tmp;
	} else {
	  draggedObject.lastDrawWidgetView = NULL;
	}	  

      }
      break;
    case XmCR_DROP_SITE_LEAVE_MESSAGE:           // aus einem WidgetView 
      if(draggedObject.dragged && draggedObject.lastDrawWidgetView) { 
	rec = draggedObject.lastDraw;
	draggedObject.lastDrawWidgetView->drawXorRec(rec);
      }
//      XtVaSetValues(dd->dragContext, 
//		    XmNstateCursorIcon, forbiddenIcon,
//		    NULL);
      break;
    }
  }
}

// -----------------------
//     isDropValid()
// -----------------------

Boolean WidgetView::isDropValid(Lwidget* &droppedOn, 
				Lwidget *lwidget,
				unsigned char operation,
				Position &x, Position &y)
{
  Lwidget *parent, *oldDroppedOn = droppedOn;

  if(!droppedOn->asChildOk(lwidget)) {
    if(droppedOn->getParent()) {
      droppedOn = droppedOn->getParent();
    } else {
      return False;
    }
  }
  if(operation == XmDROP_MOVE) {
    if(lwidget == droppedOn) {           // nicht auf sich selber fallen lassen
      if(droppedOn->getParent()) {
	droppedOn = droppedOn->getParent();
      } else {
	return False;
      }
    }
    for(parent = droppedOn; parent; parent = parent->getParent())
      if(parent == lwidget) {           // Keinen Knoten machen
	return False;
      }
  }
  if(!droppedOn->asChildOk(lwidget))
    return False;

  if(droppedOn != oldDroppedOn) {  // Koordinaten umrechnen
    WidgetView *droppedOnWidgetView = findWidget(droppedOn);
    WidgetView *oldDroppedOnWidgetView = findWidget(oldDroppedOn);
    unsigned long dummyLong;
    int ix, iy;

    if(droppedOnWidgetView && oldDroppedOnWidgetView) {
      Window sourceWindow = XtWindow(oldDroppedOnWidgetView->widget);
      Window destWindow = XtWindow(droppedOnWidgetView->widget);
      XTranslateCoordinates(XtDisplay(droppedOnWidgetView->widget), 
			    sourceWindow, destWindow, 
			    x, y, &ix, &iy, &dummyLong );
      x = ix; y = iy;
    }
  }
  
  return True;
}

// -----------------------
//     transferProc()
// -----------------------

void WidgetView::transferProc(Widget w, XtPointer closure, 
			      Atom *, Atom *,
			      XtPointer value, unsigned long *, 
			      int *)
{
  if(!value) {
    XtVaSetValues(w, XmNtransferStatus, XmTRANSFER_FAILURE, NULL);
    return;
  }
  DropInfo *dropInfo = (DropInfo*)closure;
  Lwidget *droppedOn = dropInfo->widgetView->lwidget;
  Lwidget **ptr = (Lwidget**)value;
  Lwidget *lwidget = *ptr;
  Lwidget *parent;
  Position x = dropInfo->x;
  Position y = dropInfo->y;


  if(!isDropValid(droppedOn, lwidget, dropInfo->operation, x, y)) {
    XtVaSetValues(w, XmNtransferStatus, XmTRANSFER_FAILURE, NULL);
    return;
  }
  if(draggedObject.dragged) {    // von WidgetView gedragged
    Rec rec(x - draggedObject.offsetX, y - draggedObject.offsetY);
    rec.gridX(app->getGrid() ? app->getGridValue() : 1);
    rec.gridY(app->getGrid() ? app->getGridValue() : 1);
    rec.getPosition(x,y);
  } else {                       // von woanders gedragged
    Rec rec(x, y);
    rec.gridX(app->getGrid() ? app->getGridValue() : 1);
    rec.gridY(app->getGrid() ? app->getGridValue() : 1);
    rec.getPosition(x,y);
  }

  // Wenn dies ein Move ist, dann Objekt beim Parent herausnehmen

  parent = NULL;                     // Bei Copy bleibt parent NULL
  if(dropInfo->operation == XmDROP_MOVE) {
    parent = lwidget->getParent();
    if(parent != NULL && parent != droppedOn) {  // wenn sich pappi aendert
      parent->remove(lwidget);
    }
  }

  // Wenn dies ein Copy ist, dann kopieren: toMove ist Prototype

  if( dropInfo->operation == XmDROP_COPY ) {
    Lwidget *copied;
    copied = lwidget->copy();
    if( !copied ) {
      XtVaSetValues(w, XmNtransferStatus, XmTRANSFER_FAILURE, NULL);
      return;
    }
    lwidget = copied;
  }

  // Beim neuen Parent einfuegen
  
  if(parent != droppedOn)    // wenn sich pappi aendert
    droppedOn->add(lwidget);

  int nx,ny;
  Lproperty *prop = lwidget->getProperties();

  if(!prop->convertFromPixel(x, y, nx, ny)) {
    droppedOn->getProperties()->convertFromPixel(x, y, nx, ny);
  }
  prop->setResource("x", nx);
  prop->setResource("y", ny);

  if(parent != droppedOn)
    dropInfo->dfi.droppedOn = droppedOn;
  else
    dropInfo->dfi.droppedOn = NULL;

  if(parent && parent == droppedOn && dropInfo->operation == XmDROP_MOVE)
    dropInfo->dfi.lwidget = lwidget;
  else
    dropInfo->dfi.lwidget = NULL;


  if(parent && parent != droppedOn && dropInfo->operation == XmDROP_MOVE)
    dropInfo->dfi.parent = parent;
  else
    dropInfo->dfi.parent = NULL;

}

// --------------------------------
//        insertPos()
// --------------------------------

int WidgetView::insertPos(Widget newWidget)
{
  Widget parent = XtParent(newWidget);
  Cardinal numChildren;

  XtVaGetValues(parent,
		XmNnumChildren, &numChildren,
		NULL);
  if(updateParent == parent) {
    return position;     // nicht beachten der Ressource XmNpositionIndex !!!
  } else {
    return numChildren;
  }
}


// --------------------------------
//        helpCallback()
// --------------------------------

void WidgetView::helpCallback(Widget, XtPointer clientData, XtPointer)
{
  WidgetView *self = (WidgetView*)clientData;
  if(self->lwidget->getHelpNode()) {
    Lproject::current().getHelp(self->lwidget->getHelpNode()->getId());
  }
}
  

// ##########################################################
//                   WidgetBrowse
// ##########################################################

RefArray<WidgetBrowse> WidgetBrowse::allViews;

#define BROWSE_CLOSE "BrowseClose"

WidgetBrowse::WidgetBrowse(Lwidget *am) 
: LicView(am) 
{
  Widget form, button;

  lwidget = am;

  allViews.add(this);

  popupShell = XtVaCreatePopupShell ("WidgetBrowse", 
				     topLevelShellWidgetClass,
				     topLevel,
				     NULL );
  form = XtVaCreateManagedWidget("Form", xmFormWidgetClass,
				 popupShell, NULL );

  button = XtVaCreateManagedWidget("Button", xmPushButtonWidgetClass,
				   form,
				   XmNbottomAttachment, XmATTACH_FORM,
				   XmNleftAttachment, XmATTACH_FORM,
				   XmNrightAttachment, XmATTACH_FORM,
				   NULL);
  addAction(button,BROWSE_CLOSE);

  tv = new WidgetTreeView( am, form );
  XtManageChild(tv->getTop());

  XtVaSetValues(tv->getTop(),
		XmNleftAttachment, XmATTACH_FORM,
		XmNtopAttachment, XmATTACH_FORM,
		XmNrightAttachment, XmATTACH_FORM,
		XmNbottomAttachment, XmATTACH_WIDGET,
		XmNbottomWidget, button,
		NULL);
  
  update(NAME_CHANGED);
}


// -----------------------------
// WidgetBrowse: ~WidgetBrowse()
// -----------------------------

WidgetBrowse::~WidgetBrowse() 
{ 
  close(); 
  if(!tv.isNil())
    tv.Delete(); 
  //  XtDestroyWidget(popupShell);
}

// ----------------------------
// WidgetBrowse: act()
// ----------------------------

WidgetBrowse *WidgetBrowse::showBrowser(Lwidget *lwidget)
{
  WidgetBrowse *ret = NULL;
  
  for(unsigned int i=0; i<allViews.getSize(); i++) {
    if(allViews[i]->lwidget == lwidget) {
      ret = allViews[i];
      break;
    }
  }
  
  if(ret == NULL) 
    ret = new WidgetBrowse(lwidget);

  ret->open();

  return ret;
}


// ----------------------------
// WidgetBrowse: act()
// ----------------------------

void WidgetBrowse::act(char* action)
{
  if(!strcmp(action,BROWSE_CLOSE)) {
    close();
    delete this;
  }
}

// ----------------------------
// WidgetBrowse: update
// ----------------------------
void WidgetBrowse::update( unsigned long flags )
{
  if( flags & NAME_CHANGED ) {
    char title[256];
    msgCat->getMsg(title, WIDGET_BROWSE_TITLE, 
		   lwidget->getName(), 
		   lwidget->getClass()->getName() );
    XtVaSetValues(popupShell, 
		  XmNtitle, title,
		  XmNiconName, title,
		  NULL );
  }
}
