/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: Model.C,v $
 *  $Date: 1999/08/27 15:29:55 $
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
 * $Log: Model.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:29:55  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:45  lazy
 * Imported to CVS
 *
 * Revision 1.3  1997/09/07  13:32:34  lazy
 * Destructor of Model changed. RefArray's RemoveOnDelete
 * feature used.
 *
 * Revision 1.2  1997/07/25  19:49:50  lazy
 * *** empty log message ***
 *
 * Revision 1.1  1995/09/27  21:09:53  lazy
 * Initial revision
 *
 */

/* ------------------------------------
   Model        Implementation
   Selectable   Implemantation

   (C) Dirk Laessig
   ------------------------------------ */

#include <lac/View.h>
#include <lac/Model.h>
#include <ctype.h>
#include <lac/CallbackMethod.h>

#define MAX_VIEW_DATA_ITEM 256

/* #################################################################

                              Model

   ################################################################# */

// -----------------------------
//   Destruktor Model
// -----------------------------
Model::~Model()
{
  depend.setRemoveOnDelete(FALSE);
  for(unsigned int i = 0; i<depend.getSize(); i++)
    if(!depend[i].isNil() && depend[i]->destroyFromModel())
      depend[i].Delete();
  depend.setRemoveOnDelete(TRUE);
  for( unsigned int i=0; i<viewData.getSize(); i++ )
    delete viewData[i];
  if(viewDataString)
    delete viewDataString;
}

// -----------------------------
//   changed()
// -----------------------------
void Model::changed( unsigned long flags )
{
  if(flags != SELECTION_CHANGED)
    changedFlag = TRUE;

  for( unsigned int i=0; i<depend.getSize(); i++ )
    depend[i]->updateFromModel( flags );
}

// -----------------------------
//   view_opened()
// -----------------------------
void Model::view_opened( View *newView )
{
  depend.add( newView );
}

// -----------------------------
//   view_closed()
// -----------------------------
void Model::view_closed( View *rm )
{
  depend.remove( rm );
}

// -----------------------------
//   view_with_name()
// -----------------------------
RefArray<View> Model::view_with_name( char *name )
{
  RefArray<View> ret;
  for( unsigned int i=0; i<depend.getSize(); i++ )
    if( !strcmp( name, depend[i]->getName() ) )
      ret.add( depend[i] );

  return ret;
}

// --------------------------------------------
//  ViewData access
// --------------------------------------------

// -----------------------
// findViewData()
// -----------------------

Model::ViewData *Model::findViewData(View *view, char *dataName, ViewDataType type)
{
  ViewData *ret;

  for( unsigned int i=0; i<viewData.getSize(); i++ )
    if((ret=viewData[i])->dataType == type &&
       !strcmp( ret->dataName, dataName ) &&
       !strcmp( ret->viewName, view->getName() ) )
      return ret;

  return NULL;
}

// ------------------------
// ViewData::ViewData()
// ------------------------

Model::ViewData::ViewData(const char *viewName, 
			  char *dataName, ViewDataType type)
{
  this->viewName = new char[strlen(viewName)+1];
  strcpy(this->viewName,viewName);
  this->dataName = new char[strlen(dataName)+1];
  strcpy(this->dataName,dataName);
  this->dataType = type;
  this->dataSize = 0;
  this->data = 0;    
}

// --------------------- get-Functions ----------------

Boolean Model::getVDBoolean(View *view, char *name, Boolean &ret)
{
  ViewData *vd = findViewData(view,name,VD_BOOLEAN);
  if(!vd)
    return FALSE;
  ret = (Boolean)vd->data;
  return TRUE;
}

Boolean Model::getVDLong(View *view, char *name, long &ret)
{
  ViewData *vd = findViewData(view,name,VD_LONG);
  if(!vd)
    return FALSE;
  ret = (long)vd->data;
  return TRUE;
}


Boolean Model::getVDString(View *view, char *name, char *ret, unsigned long &size)
{
  ViewData *vd = findViewData(view,name,VD_STRING);
  if(!vd)
    return FALSE;
  if(!ret) {
    size = vd->dataSize;
  } else {
    if( size < vd->dataSize )
      return FALSE;
    strcpy(ret,(char*)vd->data);
  }
  return TRUE;
}


Boolean Model::getVDBytes(View *view, char *name, void *ret, unsigned long &size)
{
  ViewData *vd = findViewData(view,name,VD_BYTES);
  if(!vd)
    return FALSE;
  if(!ret) {
    size = vd->dataSize;
  } else {
    if( size < vd->dataSize )
      return FALSE;
    memcpy(ret,(void*)vd->data,size);
  }
  return TRUE;
}

// --------------------- set-Functions ----------------

void Model::setVDBoolean(View *view, char *name, Boolean set)
{
  ViewData *vd = findViewData(view,name,VD_BOOLEAN);
  if(!vd) {
    vd = new ViewData(view->getName(),name,VD_BOOLEAN);
    viewData.add(vd);
  }
  vd->data = (long)set;
}

void Model::setVDLong(View *view, char *name, long set)
{
  ViewData *vd = findViewData(view,name,VD_LONG);
  if(!vd) {
    vd = new ViewData(view->getName(),name,VD_LONG);
    viewData.add(vd);
  }
  vd->data = set;
}

void Model::setVDString(View *view, char *name, char *set)
{
  ViewData *vd = findViewData(view,name,VD_STRING);
  if(!vd) {
    vd = new ViewData(view->getName(),name,VD_STRING);
    viewData.add(vd);
  }
  if( vd->data )
    free( (void*)vd->data );
  vd->dataSize = strlen(set)+1;
  vd->data = (long)malloc(vd->dataSize);
  strcpy((char*)vd->data, set);
}

void Model::setVDBytes(View *view, char *name, void *set, unsigned long size)
{
  ViewData *vd = findViewData(view,name,VD_BYTES);
  if(!vd) {
    vd = new ViewData(view->getName(),name,VD_BYTES);
    viewData.add(vd);
  }
  if( vd->data )
    free( (void*)vd->data );
  vd->dataSize = size;
  vd->data = (long)malloc(vd->dataSize);
  memcpy((void*)vd->data, set, vd->dataSize);
}

// ---------------- ViewData persistenz ---------------------

void Model::parseViewData(char *toParse)
{
  char *ptr = toParse;
  char type[32],vn[256],dn[256],value[64];
  long ld;
  unsigned int i;
  ViewData *vd=NULL;

  for( i=0; i<viewData.getSize(); i++ )
    delete viewData[i];

  while(*ptr) {
    while(*ptr && isspace(*ptr)) ptr++;
    if(!*ptr)
      return;
    sscanf(ptr,"%s",type);
    while(*ptr && !isspace(*ptr)) ptr++;
    while(*ptr && isspace(*ptr)) ptr++;
    if(!*ptr)
      return;
    if(!strcmp(type,"BOOLEAN")) {
      sscanf(ptr,"%s %s %s",vn,dn,value);
      viewData.add( vd = new ViewData(vn,dn,VD_BOOLEAN));
      if(!strcmp(value,"TRUE"))
	vd->data = (long)TRUE;
      else
	vd->data = (long)FALSE;
    } else {
      if(!strcmp(type,"LONG")) {
	sscanf(ptr,"%s %s %ld",vn,dn,&ld);
	viewData.add( vd = new ViewData(vn,dn,VD_LONG));
	vd->data = ld;
    } else 
      fprintf(stderr,"parse error: near %s\n",ptr);
    }
    while(*ptr && !isspace(*ptr)) ptr++;
    while(*ptr && isspace(*ptr)) ptr++;
    while(*ptr && !isspace(*ptr)) ptr++;
    while(*ptr && isspace(*ptr)) ptr++;
    while(*ptr && !isspace(*ptr)) ptr++;
  }
}

char *Model::getViewData()
{
  char buf[MAX_VIEW_DATA_ITEM];
  ViewData *vd;
  char *vds = NULL;
  size_t len;

  len = 2*MAX_VIEW_DATA_ITEM;
  vds = new char[len];

  vds[0] = 0;

  for( unsigned int i=0; i<viewData.getSize(); i++ ) {
    vd = viewData[i];
    switch(vd->dataType) {
    case VD_BOOLEAN:
      sprintf(buf,"BOOLEAN %s %s %s ",vd->viewName, vd->dataName, 
	      ((Boolean)vd->data) ? "TRUE" : "FALSE" );
      break;
    case VD_LONG:
      sprintf(buf,"LONG %s %s %ld ",vd->viewName, vd->dataName, vd->data);
      break;
    default:
      break;
    }
    while(strlen(vds)+strlen(buf)+1 > len) {
      len += MAX_VIEW_DATA_ITEM;
      char *tmp = new char[len];
      strcpy(tmp, vds);
      delete vds;
      vds = tmp;
    }
    strcat(vds, buf);
  }

  if(viewDataString)
    delete viewDataString;

  viewDataString = vds;

  return viewDataString;
}


/* #################################################################

                             Selectable

   ################################################################# */

RefArray<Selectable> Selectable::selection;
char *Selectable::currentClass = "Selectable";
CallbackList Selectable::selectionCallbacks;

// ----------------------------------
//    Konstruktor von Selectable
// ----------------------------------
Selectable::Selectable()
{
  set = False;
}
  
// ----------------------------------
//    Destruktor von Selectable
// ----------------------------------
Selectable::~Selectable()
{
  selection.remove( this );     // braeuchte eigentlich nicht sein
}
  
// ----------------------------------
//           select
// ----------------------------------
void Selectable::select( Boolean multi )
{
  unsigned int i;
  Boolean pri;

  // initialisiert mit globaler Selection oder privater
  RefArray<Selectable> &selection(getPrivateSelection(pri));

  if( multi && (pri || !strcmp(getClassName(),currentClass)) ) {
    if( !set ) {
      selection.add( this );
      set = True;
      selected();
    } else {
      selection.remove( this );
      set = False;
      unselected();
    }
  } else {

    RefArray<Selectable> tmp(selection);
    for( i=0; i<selection.getSize(); i++ )
      selection[i]->set = False;
    selection.empty();
    for( i=0; i<tmp.getSize(); i++ )
      tmp[i]->unselected();

    selection.add( this );
    if(!pri)
      currentClass = getClassName();
    set = True;
    selected();
  }
  selectionCallbacks.call();
}


// -------------------------------
//   getPrivateSelection()
// -------------------------------

RefArray<Selectable> &Selectable::getPrivateSelection(Boolean &pri)
{
  pri = FALSE;
  return Selectable::selection;
}
