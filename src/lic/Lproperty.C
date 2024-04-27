/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: Lproperty.C,v $
 *  $Date: 1999/08/27 15:31:20 $
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
 * $Log: Lproperty.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:31:20  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:13  lazy
 * Imported to CVS
 *
 * Revision 1.2  1998/03/30 19:08:29  lazy
 * *** empty log message ***
 *
 * Revision 1.1  1997/07/25  20:28:04  lazy
 * Initial revision
 *
 */

// -----------------------------------
//
// Lproperty
// 
// -----------------------------------

#include "Lproperty.h"

#include "Lresource.h"
#include "Lproject.h"
#include "Lwidget.h"
#include "InterfaceInfo.h"
#include <lac/TArray.h>

// ------------------------------
//      Lproperty()
// ------------------------------
Lproperty::Lproperty(Lwidget *papi,
		     WidgetClass widgetClass, 
		     WidgetClass parentClass,
		     YResource   *first_res )
{
  XtResourceList resList = NULL;
  Cardinal numRes, numSecRes, i, n;
  Lresource *tmp;
  XmSecondaryResourceData *secRes;

  TSortArray<Lresource> sortCore, sortSpecific, sortConstraint, sortCallbacks;

  lwidget = papi;
  this->parentWidgetClass = parentWidgetClass;
  filled = FALSE;

  // Die Ressource holen

  XtGetResourceList( widgetClass, &resList, &numRes );
  for( i=0; i<numRes; i++ ) {
    tmp = createLresource( resList[i], lwidget );
    if( tmp ) {
      if(tmp->isCore()) {
	sortCore.add(tmp);
	if(!strcmp(resList[i].resource_name,"width")) 
	  width = tmp;
	else if(!strcmp(resList[i].resource_name,"height")) 
	  height = tmp;
      } else if(!strcmp(tmp->getClassName(),"LresCallback"))
	sortCallbacks.add(tmp);
      else
	sortSpecific.add(tmp);
      if(!strcmp(resList[i].resource_type,"UnitType")) 
	unitType = tmp;
    } 
  }
  XtFree( (char*)resList );

  // Motif kann die Resources erweitern
  // Fuer Shell-Widgetklassen sehr wichtig

  numSecRes = XmGetSecondaryResourceData(widgetClass, &secRes);
  for( n=0; n<numSecRes; n++ ) {
    for( i=0; i<secRes[n]->num_resources; i++ ) {
      tmp = createLresource( secRes[n]->resources[i], lwidget );
      if( tmp ) {
	if(tmp->isCore())
	  sortCore.add(tmp);
	else if(!strcmp(tmp->getClassName(),"LresCallback"))
	  sortCallbacks.add(tmp);
	else
	  sortSpecific.add(tmp);
	if(!strcmp(secRes[n]->resources[i].resource_type,"UnitType")) 
	  unitType = tmp;
      } 
    }
  }

  // Die Contraint-Ressourcen holen

  if( parentClass ) {
    XtGetConstraintResourceList( parentClass, &resList, &numRes );
    for( i=0; i<numRes; i++ ) {
      tmp = createLresource( resList[i], lwidget );
      if( tmp ) {
	parentConstraints.add(tmp);
	if(!strcmp(tmp->getClassName(),"LresCallback"))
	  sortCallbacks.add(tmp);
	else
	  sortConstraint.add(tmp);
      }
    }
    XtFree( (char*)resList );
  }

  // sorting the arrays
  sortCore.sort();
  sortSpecific.sort();
  sortConstraint.sort();
  sortCallbacks.sort();

  for( i=0; i<sortCore.getSize(); i++ )
    core.add( sortCore[i] );
  for( i=0; i<sortSpecific.getSize(); i++ )
    specific.add( sortSpecific[i] );
  for( i=0; i<sortConstraint.getSize(); i++ )
    constraint.add( sortConstraint[i] );
  for( i=0; i<sortCallbacks.getSize(); i++ )
    callbacks.add( sortCallbacks[i] );

  if( first_res ) {
    YResource *res = first_res;
    while( res ) {
      if( !setResource( res->name, res->value, res->attrib ) ) {
	fprintf(stderr, "Resource_name %s not found.\n", 
		res->name );
      }
      res = res->next;
    }
  }

}

// ------------------------------
//      Lproperty(Lproperty &)
// ------------------------------
Lproperty::Lproperty( Lproperty & )
{
  filled = FALSE;
}

// ------------------------------
//      ~Lproperty
// ------------------------------
Lproperty::~Lproperty()
{
  while( core.getSize() )
    core[0].Delete();
  while( constraint.getSize() )
    constraint[0].Delete();
  while( specific.getSize() )
    specific[0].Delete();
  while( callbacks.getSize() )
    callbacks[0].Delete();
}
	  

// ------------------------------
//      createYResource()
// ------------------------------
YResource *
Lproperty::createYResource()
{
  unsigned int i;

  YResource *ret, *ptr, *last;
  ret = ptr = last = NULL;

  for( i=0; i<core.getSize(); i++ )
    if( !core[i]->isDefault() ) {
      ptr = core[i]->createYResource();
      if( !ret )
	ret = ptr;
      if( last )
	last->next = ptr;
      last = ptr;
    }

  for( i=0; i<specific.getSize(); i++ )
    if( !specific[i]->isDefault() ) {
      ptr = specific[i]->createYResource();
      if( !ret )
	ret = ptr;
      if( last )
	last->next = ptr;
      last = ptr;
    }

  for( i=0; i<constraint.getSize(); i++ )
    if( !constraint[i]->isDefault() ) {
      ptr = constraint[i]->createYResource();
      if( !ret )
	ret = ptr;
      if( last )
	last->next = ptr;
      last = ptr;
    }

  for( i=0; i<callbacks.getSize(); i++ )
    if( !callbacks[i]->isDefault() ) {
      ptr = callbacks[i]->createYResource();
      if( !ret )
	ret = ptr;
      if( last )
	last->next = ptr;
      last = ptr;
    }

  return ret;
}

// ------------------------------
//        apply()
// ------------------------------
void 
Lproperty::apply( Widget widget )
{
  Cardinal count = 300;
  Arg argList[count];
  getArgList( argList, count );
  XtSetValues( widget, argList, count );
}


// ------------------------------
//     getArgList()
// ------------------------------
void 
Lproperty::getArgList( ArgList argList, Cardinal &count )
{
  Cardinal i;
  count = 0;

  for( i=0; i<core.getSize(); i++ )
    if( !core[i]->isDefault() && !core[i]->isRelation() )
      core[i]->setValues( argList, count );

  for( i=0; i<specific.getSize(); i++ )
    if( !specific[i]->isDefault() && !specific[i]->isRelation() )
      specific[i]->setValues( argList, count );

  for( i=0; i<constraint.getSize(); i++ )
    if( !constraint[i]->isDefault() && !constraint[i]->isRelation() )
      constraint[i]->setValues( argList, count );

  for( i=0; i<callbacks.getSize(); i++ )
    if( !callbacks[i]->isDefault() && !callbacks[i]->isRelation() )
      callbacks[i]->setValues( argList, count );
}


// ------------------------------
//        setResource()
// ------------------------------
Boolean 
Lproperty::setResource( char *resource_name, XtArgVal value )
{
  unsigned int i;
  
  for( i=0; i<core.getSize() ; i++ )
    if( !strcmp( core[i]->getName(), resource_name )) {
      core[i]->setValue( value );
      core[i]->changed(VALUE_CHANGED);
      return TRUE;
    }
  for( i=0; i<specific.getSize() ; i++ )
    if( !strcmp( specific[i]->getName(), resource_name )) {
      specific[i]->setValue( value );
      specific[i]->changed(VALUE_CHANGED);
      return TRUE;
    }
  for( i=0; i<constraint.getSize() ; i++ )
    if( !strcmp( constraint[i]->getName(), resource_name )) {
      constraint[i]->setValue( value );
      constraint[i]->changed(VALUE_CHANGED);
      return TRUE;
    }
  return FALSE;
}


// ------------------------------
//        setResource( string )
// ------------------------------
Boolean 
Lproperty::setResource( char *resource_name, char *string, char *attr )
{
  unsigned int i;
  
  for( i=0; i<core.getSize() ; i++ )
    if( !strcmp( core[i]->getName(), resource_name )) {
      core[i]->setString( string );
      if(attr)
	core[i]->setAttribute(attr);
      core[i]->changed(VALUE_CHANGED);
      return TRUE;
    }
  for( i=0; i<specific.getSize() ; i++ )
    if( !strcmp( specific[i]->getName(), resource_name )) {
      specific[i]->setString( string );
      if(attr)
	specific[i]->setAttribute(attr);
      specific[i]->changed(VALUE_CHANGED);
      return TRUE;
    }
  for( i=0; i<constraint.getSize() ; i++ )
    if( !strcmp( constraint[i]->getName(), resource_name )) {
      constraint[i]->setString( string );
      if(attr)
	constraint[i]->setAttribute(attr);
      constraint[i]->changed(VALUE_CHANGED);
      return TRUE;
    }
  for( i=0; i<callbacks.getSize() ; i++ )
    if( !strcmp( callbacks[i]->getName(), resource_name )) {
      callbacks[i]->setString( string );
      if(attr)
	callbacks[i]->setAttribute(attr);
      callbacks[i]->changed(VALUE_CHANGED);
      return TRUE;
    }
  return FALSE;
}



// ------------------------------
//        fillWithDefaults
// ------------------------------
void 
Lproperty::fillWithDefaults( Widget widget )
{
  Cardinal i, count;
  count = 0;
  Arg argList[300];
  Lresource *lres[300];

  for(i = 0; i < core.getSize(); i++ ) {
    if(core[i]->isDefault() && core[i]->needDefault()) {
      argList[count].name = core[i]->getName();
      argList[count].value = (XtArgVal)core[i]->getAddrOfValue();
      lres[count] = core[i];
      count++;
    }
  }

  for(i = 0; i < specific.getSize(); i++ ) {
    if(specific[i]->isDefault() && specific[i]->needDefault()) {
      argList[count].name = specific[i]->getName();
      argList[count].value = (XtArgVal)specific[i]->getAddrOfValue();
      lres[count] = specific[i];
      count++;
    }
  }

  for(i = 0; i < constraint.getSize(); i++ ) {
    if(constraint[i]->isDefault() && constraint[i]->needDefault()) {
      argList[count].name = constraint[i]->getName();
      argList[count].value = (XtArgVal)constraint[i]->getAddrOfValue();
      lres[count] = constraint[i];
      count++;
    }
  }

  filled = TRUE;
  XtGetValues( widget, argList, count );
  for(i=0; i<count; i++) {
    lres[i]->applyToValue();
  }
}


// ---------------------
//  parentChanged()
// ---------------------

void 
Lproperty::parentChanged()
{
  XtResourceList resList = NULL;
  Cardinal numRes, i;
  Lresource *tmp;
  Lwidget *parent;

  TSortArray<Lresource> sortCallbacks, sortConstraint;

  parent = lwidget->getParent();
  
  if( !parent || strcmp(parent->getClassName(),"Lwidget"))
    return;

  if( parent && parentWidgetClass == parent->getClass()->getWidgetClass() )
    return;

  parentWidgetClass = parent->getClass()->getWidgetClass();
  while(parentConstraints.getSize()) 
    parentConstraints[0].Delete();

  if( parent ) {
    XtGetConstraintResourceList( parentWidgetClass, &resList, &numRes );
    for( i=0; i<numRes; i++ ) {
      tmp = createLresource( resList[i], lwidget );

      if( tmp ) {
	parentConstraints.add(tmp);
	if(!strcmp(tmp->getClassName(),"LresCallback"))
	  sortCallbacks.add(tmp);
	else
	  sortConstraint.add(tmp);
      }
    }
    XtFree( (char*)resList );


    // sorting of resources

    sortCallbacks.sort();
    sortConstraint.sort();

    for( i=0; i<sortConstraint.getSize(); i++ )
      constraint.add( sortConstraint[i] );
    for( i=0; i<sortCallbacks.getSize(); i++ )
      callbacks.add( sortCallbacks[i] );

  }

  lwidget->changed(CONSTRAINTS_CHANGED);
}


// ---------------------------
//    setRelation()
// ---------------------------

void 
Lproperty::setRelation( WidgetView *wv )
{
  unsigned int i;

  for( i=0; i<core.getSize() ; i++ )
    if( core[i]->isRelation() ) {
      LresRelation *lrel = ((LresRelation*)(Lresource*)core[i]);
      lrel->apply(wv);
    }
  for( i=0; i<specific.getSize() ; i++ )
    if( specific[i]->isRelation() ) {
      LresRelation *lrel = ((LresRelation*)(Lresource*)specific[i]);
      lrel->apply(wv);
    }
  for( i=0; i<constraint.getSize() ; i++ )
    if( constraint[i]->isRelation() ) {
      LresRelation *lrel = ((LresRelation*)(Lresource*)constraint[i]);
      lrel->apply(wv);
    }
}


// ---------------------------
//    getResource()
// ---------------------------

XtArgVal 
Lproperty::getResource( char *resource_name )
{
  unsigned int i;
  
  for( i=0; i<core.getSize() ; i++ )
    if( !strcmp( core[i]->getName(), resource_name )) {
      return core[i]->getValue();
    }
  for( i=0; i<specific.getSize() ; i++ )
    if( !strcmp( specific[i]->getName(), resource_name )) {
      return specific[i]->getValue();
    }
  for( i=0; i<constraint.getSize() ; i++ )
    if( !strcmp( constraint[i]->getName(), resource_name )) {
      return constraint[i]->getValue();
    }
  for( i=0; i<callbacks.getSize() ; i++ )
    if( !strcmp( callbacks[i]->getName(), resource_name )) {
      return callbacks[i]->getValue();
    }
  return 0;
}

// ---------------------------
//    convertFromPixel()
// ---------------------------

Boolean 
Lproperty::convertFromPixel(int x, int y, int &rx, int &ry)
{
  int type;
  if(unitType.isNil() || !filled) 
    type = XmPIXELS;
  else
    type = (int)unitType->getValue();

  rx = XmCvtFromHorizontalPixels(XtScreen(Lproject::current().getTopLevel()), x, type);
  ry = XmCvtFromVerticalPixels(XtScreen(Lproject::current().getTopLevel()), y, type);
  return True;
}

// ---------------------------
//    hasSpecSize()
// ---------------------------

Boolean 
Lproperty::hasSpecSize()
{
  // if width or height is set

  if(!width.isNil() && !width->isDefault())
    return TRUE;
  if(!height.isNil() && !height->isDefault())
    return TRUE;
  return FALSE;
}


// ---------------------------
//    getLresource()
// ---------------------------

Lresource *
Lproperty::getLresource(char *resource_name)
{
  unsigned int i;
  
  for( i=0; i<core.getSize() ; i++ )
    if( !strcmp( core[i]->getName(), resource_name )) {
      return core[i];
    }
  for( i=0; i<specific.getSize() ; i++ )
    if( !strcmp( specific[i]->getName(), resource_name )) {
      return specific[i];
    }
  for( i=0; i<constraint.getSize() ; i++ )
    if( !strcmp( constraint[i]->getName(), resource_name )) {
      return constraint[i];
    }
  for( i=0; i<callbacks.getSize() ; i++ )
    if( !strcmp( callbacks[i]->getName(), resource_name )) {
      return callbacks[i];
    }
  return NULL;
}

