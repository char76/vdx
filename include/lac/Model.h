/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: Model.h,v $
 *  $Date: 1999/08/27 15:29:56 $
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
 * $Log: Model.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:29:56  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:45  lazy
 * Imported to CVS
 *
 * Revision 1.2  1997/07/25  19:49:53  lazy
 * *** empty log message ***
 *
 * Revision 1.1  1995/09/27  21:10:04  lazy
 * Initial revision
 *
 */

// --------------------------------
// Class Model and Selectable
//
// (C) Dirk Laessig
// --------------------------------

#ifndef _MODEL_H_
#define _MODEL_H_

#include <lac/Lobject.h>
#include <lac/RefArray.h>
#include <X11/Intrinsic.h>
#include <lac/TArray.h>
#include <lac/CallbackMethod.h>

class View;
class CallbackList;

/* ----------------------------------------------------

                        Model

   ---------------------------------------------------- */

#define SELECTION_CHANGED        0x00000001
#define NAME_CHANGED             0x00000002
#define CONTAINER_CHANGED        0x00000004
#define VD_WITH_CHILDREN_CHANGED 0x00000008
#define VIEWDATA_CHANGED         0x00000010
#define USER_CHANGED      VIEWDATA_CHANGED

class Model : public Lobject {
private:

  RefArray<View> depend; 
  void view_opened( View *newView );         // packt View in die Liste
  void view_closed( View *rm );

  enum ViewDataType {
    VD_BOOLEAN, VD_LONG, VD_STRING, VD_BYTES
    };

  class ViewData {
  public:
    ViewData(const char *viewName, char *dataName, ViewDataType type);
    ~ViewData(){ delete viewName; delete dataName; 
		 if(data && dataSize) free((void*)data);}
    char *viewName;
    char *dataName;
    ViewDataType dataType;
    unsigned long dataSize;      // wichtig fuer VD_STRING und VD_BYTES
    long data;                   // direkt oder Zeiger auf Daten
  };

  TArray<ViewData> viewData;   
  char *viewDataString;

  ViewData *findViewData(View *view, char *dataName, ViewDataType type);

  Boolean changedFlag;

public:
  Model(){ viewDataString=NULL; changedFlag = FALSE; }
  virtual ~Model();                          // loescht Views und ViewData
  virtual void changed( unsigned long flags ); // ruft update fuer alle Views
  RefArray<View> view_with_name( char *name ); // gibt views mit namen

  // ViewData Zugriff
  Boolean getVDBoolean(View *view, char *name, Boolean &ret);
  Boolean getVDLong(View *view, char *name, long &ret);
  Boolean getVDString(View *view, char *name, char *ret, unsigned long &size);
  Boolean getVDBytes(View *view, char *name, void *ret, unsigned long &size); 

  void setVDBoolean(View *view, char *name, Boolean set);
  void setVDLong(View *view, char *name, long set);
  void setVDString(View *view, char *name, char *set);
  void setVDBytes(View *view, char *name, void *set, unsigned long size); 

  void parseViewData(char *toParse);
  char *getViewData();

  // changed
  virtual Boolean getChangedFlag() { return changedFlag; }
  virtual void resetChangedFlag() { changedFlag = FALSE; }

  // Die View-Klasse hat zugriff
  friend class View;
};


/* -----------------------------------------------------

                   Selectable

   ----------------------------------------------------- */

class Selectable : public Model {
private:
  Boolean set;
  static char *currentClass;
  static RefArray<Selectable> selection;

public:
  Selectable();
  ~Selectable();     // loescht Selectable aus Liste

  void select( Boolean multi = FALSE );
  Boolean isSelected() { return set; }

  virtual char *getClassName() = 0;
  virtual void selected() { changed( SELECTION_CHANGED ); }
  virtual void unselected() { changed( SELECTION_CHANGED ); }
  static RefArray<Selectable> getSelection() { return selection; }

  static char *getCurrentClass() { return currentClass; }

  // Private Selection
  virtual RefArray<Selectable> & getPrivateSelection(Boolean &pri);

  // if global selection changes, callbacks are invoked
  static CallbackList selectionCallbacks;
};


// -------------------------------------------
//          Iconable
// 
// If you want to have an icon 
// for a model, you have to derive from 
// this class
// -------------------------------------------

class Iconable : public Selectable {
public:
  Iconable(){};

  virtual char *getName(){ return NULL; }
  virtual char *getDescription() { return getName(); }
  virtual char *getPixmapFile(){ return NULL; }
  virtual Boolean setName(char *) { return FALSE; }
  virtual Boolean nameChangeable() { return FALSE; }
};



#endif /* DON'T ADD ... */
