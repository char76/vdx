/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: Lproperty.h,v $
 *  $Date: 1999/08/27 15:31:22 $
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
 * $Log: Lproperty.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:31:22  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:13  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/25  20:28:07  lazy
 * Initial revision
 *
 */

// --------------------------------------
// Lproperty - Class
// 
// (C) Dirk Laessig
// --------------------------------------

#ifndef _LPROPERTY_H_
#define _LPROPERTY_H_

#include <lac/RefArray.h>
#include <parse.h>
#include <X11/Intrinsic.h>
#include "Lresource.h"

class Lwidget;
class WidgetInfo;

class Lproperty {
private:
  Lwidget *lwidget;
  WidgetClass parentWidgetClass;

  RefArray<Lresource> parentConstraints;

  RefArray<Lresource> core;
  RefArray<Lresource> specific;
  RefArray<Lresource> constraint;

  RefArray<Lresource> callbacks;

  Boolean filled;
  Ref<Lresource> unitType;
  Ref<Lresource> width, height;

public:
  Lproperty(Lwidget *papi,
	    WidgetClass widgetClass, 
	    WidgetClass parentClass = NULL,
	    YResource   *first_res = NULL );
  Lproperty( Lproperty &toCopy );
  ~Lproperty();
  
  RefArray<Lresource> & getCore() { return core; }
  RefArray<Lresource> & getSpecific() { return specific; }
  RefArray<Lresource> & getConstraint() { return constraint; }
  RefArray<Lresource> & getCallbacks() { return callbacks; }

  YResource *createYResource();
  void apply( Widget widget );
  void fillWithDefaults( Widget widget );
  void getArgList( ArgList argList, Cardinal &count );

  Boolean setResource( char *resource_name, XtArgVal value );
  Boolean setResource( char *resource_name, char *str, char *attr=NULL );
  void setRelation( WidgetView * );

  XtArgVal getResource( char *resource_name );
  Lresource *getLresource(char *resource_name);

  Boolean isFilled() { return filled; }

  void parentChanged();

  Boolean convertFromPixel(int x, int y, int &rx, int &ry);

  // some infos for better working
  Boolean hasSpecSize();
};

#endif
