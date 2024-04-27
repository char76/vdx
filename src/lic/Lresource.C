/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: Lresource.C,v $
 *  $Date: 1999/08/27 15:31:25 $
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
 * $Log: Lresource.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:31:25  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:14  lazy
 * Imported to CVS
 *
 * Revision 1.5  1998/04/06 17:25:16  lazy
 * Call changed() when setAsDefault() is called.
 *
 * Revision 1.4  1998/03/30 19:08:30  lazy
 * *** empty log message ***
 *
 * Revision 1.3  1997/12/14  19:07:40  lazy
 * Configuration of Resources by resource file.
 *
 * Revision 1.2  1997/09/10  18:46:12  lazy
 * Fixed after using purify.
 *
 * Revision 1.1  1997/07/25  20:28:23  lazy
 * Initial revision
 *
 */

// ------------------------
// Lresource
//
// (C) Dirk Laessig
// ------------------------

#include "Lresource.h"
#include "LApp.h"
#include "lic.h"
#include <string.h>
#include <stdlib.h>
#include <Xm/Xm.h>
#include "Lproject.h"
#include "Lwidget.h"
#include <lac/LicView.h>

// ------- LresAttributes -----------
LresAttribute LresAttribute::attrPrivate("private");
LresAttribute LresAttribute::attrPublic("public");
LresAttribute LresAttribute::attrMethod("method");
LresAttribute LresAttribute::attrManage("manage");
LresAttribute LresAttribute::attrInclude("include");
LresAttribute LresAttribute::attrLoad("load");
LresAttribute LresAttribute::attrInterface("interface");


// -------------------------
//  Lresource( XtResource )
// -------------------------
Lresource::Lresource(XtResource &r, Lwidget *widget)
{
  this->widget = widget;
  res = r;
  _hasChanged = FALSE;
  _isDefault = TRUE;
  currentAttribute = NULL;
  value = 0;
}

// -------------------------
//  Lresource(&copy )
// -------------------------
Lresource::Lresource( const Lresource &copy )
{
  widget = copy.widget;
  res = copy.res;
  _hasChanged = copy._hasChanged;
  _isDefault = copy._isDefault;

  possibleAttributes = copy.possibleAttributes;
  currentAttribute = copy.currentAttribute;
}

// -------------------------
//  createYResource()
// -------------------------
YResource *Lresource::createYResource()
{
  unsigned int len;
  YResource *r = (YResource*)malloc(sizeof(YResource));
  memset( r, 0, sizeof(YResource) );
  strcpy( r->name, res.resource_name );
  
  getString( NULL, len );
  char str[len];
  getString( str, len );
  m_strcpy( &r->value, str );

  if(currentAttribute) 
    strcpy(r->attrib, currentAttribute->getString());
  else if(possibleAttributes.getSize() > 0)
    strcpy(r->attrib, possibleAttributes[0]->getString());
  else
    strcpy(r->attrib, LresAttribute::attrPrivate.getString());

  return r;
}


// -------------------------
//  ~Lresource( )
// -------------------------
Lresource::~Lresource()
{
}

// -------------------------
//  setAsDefault()
// -------------------------
void Lresource::setAsDefault( XtArgVal val )
{
  setValue(val);
  _hasChanged = FALSE;
  _isDefault = TRUE;
  changed(VALUE_CHANGED);
}


// -------------------------
//  setValues()
// -------------------------
void Lresource::setValues( ArgList a, Cardinal& count )
{
  XtSetArg( a[count], res.resource_name, value );
  count++;
}


// -------------------------
//  setAttribute()
// -------------------------
void Lresource::setAttribute(char *name)
{
  Boolean found = FALSE;
  FOREACH(i,possibleAttributes) {
    if(!strcmp(name, possibleAttributes[i]->getString())) {
      found = TRUE;
      currentAttribute = possibleAttributes[i];
      break;
    }
  }
  if(!found) {
    if(possibleAttributes.getSize() > 0)
      currentAttribute = possibleAttributes[0];
    else
      currentAttribute = &LresAttribute::attrPrivate;

    // fprintf(stderr, "Fatal error: attribute %s not valid for resource %s!\n",
    //    	    name, res.resource_name);
  }
}

// -------------------------
//  isCore()
// -------------------------
Boolean Lresource::isCore() 
{
  if( !strcmp( res.resource_name, "ancestorSensitive" ) ||
      !strcmp( res.resource_name, "x" ) ||
      !strcmp( res.resource_name, "y" ) ||
      !strcmp( res.resource_name, "width" ) ||
      !strcmp( res.resource_name, "height" ) ||
      !strcmp( res.resource_name, "borderWidth" ) ||
      !strcmp( res.resource_name, "sensitive" ) ||
      !strcmp( res.resource_name, "screen" ) ||
      !strcmp( res.resource_name, "depth" ) ||
      !strcmp( res.resource_name, "colormap" ) ||
      !strcmp( res.resource_name, "background" ) ||
      !strcmp( res.resource_name, "backgroundPixmap" ) ||
      !strcmp( res.resource_name, "borderColor" ) ||
      !strcmp( res.resource_name, "borderPixmap" ) ||
      !strcmp( res.resource_name, "mappedWhenManaged" ) ||
      !strcmp( res.resource_name, "translations" ) ||
      !strcmp( res.resource_name, "accelerators" ) )
    return TRUE;
  return FALSE;
}

// -----------------------
//      compare()
// -----------------------

int Lresource::compare( const void *r1, const void *r2 )
{
  return strcmp(((Lresource**)r1)[0]->res.resource_name,  
		((Lresource**)r2)[0]->res.resource_name);
}


// Static Member config contains the resource_type mapping

LHashDictionary<Lstring> Lresource::config;
Boolean Lresource::defaultConfigRead = FALSE;


// -----------------------
//      readConfig()
// -----------------------

void 
Lresource::readConfig(char *filename)
{
  Lstring file;
  Boolean defaultConfig = FALSE;

  if(filename == NULL) {     // handle default config file
    file = app->getConfigPath();
    file += "/";
    file += "resource.cf";
    defaultConfig = TRUE;
  } else {
    file = filename;
  }

  FILE *fp;
  fp = fopen(file, "r");
  if(fp) {
    char line[BUFSIZ], s1[BUFSIZ], s2[BUFSIZ];

    while(fgets(line, sizeof(line), fp) != NULL) {
      if(line[0] != '!' && line[0] != ' ') {
	Lstring value;
	Boolean found = FALSE;

	sscanf(line, "%s %s", s1, s2);
	if(config.find(Lstring(s1), value))
	  found = TRUE;
	if(!found) {
	  config.add(s1, Lstring(s2));
	}
      }
    }
    fclose(fp);
  }

  if(defaultConfig)
    defaultConfigRead = TRUE;
}


// -----------------------
//      findType()
// -----------------------

const Lstring &
Lresource::findType(const char *type)
{
  static Lstring s = "undefined";
  static Lstring found;

  if(!defaultConfigRead)
    readConfig();
  
  if(config.find(type, found))
    return found;

  return s;
}


// ############################################
//
// LresNumber
//
// ############################################

void LresNumber::setString( char *string )
{
  XtArgVal v;
  v = (XtArgVal)strtol(string, NULL, 10);
  setValue( v );
}

char *LresNumber::getString( char *buffer, unsigned int &len )
{
  if( !buffer ) {
    len = 30;
    return NULL;
  }
  if( len != 0 )
    sprintf( buffer,"%ld", value );
  else
    return NULL;
  return buffer;
}

void LresNumber::setValue( XtArgVal v )
{
  value = v;
  _hasChanged = TRUE;
  _isDefault = FALSE;
  // changed( VALUE_CHANGED );
}

XtArgVal *LresNumber::getAddrOfValue()
{
  switch(valueType) {
  case CHAR_VALUE:
    return (XtArgVal*)&charValue;
    break;
  case SHORT_VALUE:
    return (XtArgVal*)&shortValue;
    break;
  case INT_VALUE:
    return (XtArgVal*)&intValue;
    break;
  case LONG_VALUE:
    return (XtArgVal*)&longValue;
    break;
  }
  return &value;
}

void LresNumber::applyToValue()
{
  switch(valueType) {
  case CHAR_VALUE:
    setAsDefault(charValue);
    break;
  case SHORT_VALUE:
    setAsDefault(shortValue);
    break;
  case INT_VALUE:
    setAsDefault(intValue);
    break;
  case LONG_VALUE:
    setAsDefault(longValue);
    break;
  }
  setAsDefault(value);
}

LresNumber::LresNumber(XtResource &r, Lwidget *widget, const Lstring &internal)
: Lresource(r, widget) 
{
  possibleAttributes.add(&LresAttribute::attrPrivate);
  possibleAttributes.add(&LresAttribute::attrPublic);
  
  valueType = LONG_VALUE;
  if(internal == "SHORT")
    valueType = SHORT_VALUE;
  else if(internal == "INT")
    valueType = INT_VALUE;
  else if(internal == "CHAR")
    valueType = CHAR_VALUE;
}

Boolean LresNumber::isValid( char *resource_type )
{
  Lstring internal = findType(resource_type);
  if(internal == "SHORT") 
    return TRUE;
  else if(internal == "INT")
    return TRUE;
  else if(internal == "LONG")
    return TRUE;
  else if(internal == "CHAR")
    return TRUE;
  return FALSE;
}

void LresNumber::getCodeString( char *buffer, unsigned int &len )
{
  getString(buffer,len);
}


// ############################################
//
// LresXmString
//
// ############################################

void LresXmString::setString( char *string )
{
  XmString comString = XmStringCreateLtoR( string, XmSTRING_DEFAULT_CHARSET );
  setValue( (XtArgVal)comString );
}

Boolean LresXmString::cvtXmStringToString(XmString xmString, 
					  char *buf, unsigned long size)
{
  XmStringContext context;
  unsigned long currentLen = 0;

  if(buf == NULL)
    return FALSE;
  if(size < 1)
    return FALSE;

  strcpy(buf, "");
  currentLen += 1;

  if(XmStringInitContext(&context, xmString)) {
    XmStringCharSet charSet;
    XmStringDirection direction;
    Boolean separator;
    char *str;
    Boolean r;

    do {
      r = XmStringGetNextSegment(context, &str, &charSet, 
				 &direction, &separator);
 
      // ignore charSet and direction

      if(str) {                  // concat the segment
	if(strlen(str)+currentLen > size) {
	  XtFree(str);
	  XmStringFreeContext(context);
	  return FALSE;
	}
	strcat(buf, str);
	XtFree(str);
      }

      if(separator) {            // concat the separator
	if(currentLen+1 > size) {
	  XmStringFreeContext(context);
	  return FALSE;
	}
	strcat(buf, "\n");
      }

    } while(r);
    XmStringFreeContext(context);
    return TRUE;
  } 
  return TRUE;
}

char *LresXmString::getString( char *buffer, unsigned int &len )
{
  if( !buffer ) {
    if( value ) {
      for(unsigned long size = 256; size < (1<<19); size = (size<<1)) {
	char str[size];
	if(cvtXmStringToString((XmString)value, str, size)) {
	  len = strlen(str)+1;
	  break;
	}
      }
    } else
      len = 1;
    return NULL;
  }
  if( value ) {
    if(!cvtXmStringToString((XmString)value, buffer, len)) {
      buffer[0] = 0;
    }
  } else
    buffer[0]=0;
  return buffer;
}

void LresXmString::setValue( XtArgVal v )
{
  if( value ) {
    XmStringFree( (XmString)value );
    value = 0;
  }
  value = v;

  _hasChanged = TRUE;
  _isDefault = FALSE;
  // changed( VALUE_CHANGED );
}

Boolean LresXmString::isValid( char *resource_type )
{
  if(findType(resource_type) == "XMSTRING")
    return TRUE;
  return FALSE;
}

// ############################################
//
// LresBoolean
//
// ############################################

void LresBoolean::setString( char *string )
{
  XtArgVal v;
  v = (XtArgVal)strtol(string, NULL, 10);
  setValue( v );
}

char *LresBoolean::getString( char *buffer, unsigned int &len )
{
  if( !buffer ) {
    len = 30;
    return NULL;
  }
  if( len != 0 )
    sprintf( buffer,"%ld", value );
  else
    return NULL;
  return buffer;
}

void LresBoolean::setValue( XtArgVal v )
{
  value = (XtArgVal)Boolean(v);
  _hasChanged = TRUE;
  _isDefault = FALSE;
  // changed( VALUE_CHANGED );
}

Boolean LresBoolean::isValid( char *resource_type )
{
  if(findType(resource_type) == "BOOL") {
    return TRUE;
  }
  return FALSE;
}

void LresBoolean::getCodeString( char *buffer, unsigned int &len )
{
  getString(buffer,len);
}


// ############################################
//
// LresCallback
//
// ############################################

LresCallback::LresCallback(XtResource &r, Lwidget *widget) 
: Lresource(r, widget) 
{
  method[0]=0;
  callbackList[0].callback = testCallback;
  callbackList[0].closure = this;
  callbackList[1].callback = NULL;
  callbackList[1].closure = NULL;
  
  possibleAttributes.add(&LresAttribute::attrMethod);
  possibleAttributes.add(&LresAttribute::attrManage);
}

void LresCallback::testCallback(Widget wg,XtPointer cl, XtPointer)
{
  char buffer[1024];
  WidgetView *wv;
  Widget toManage;
  LresCallback *self = (LresCallback*)cl;

  char *methodName = (char*)self->method;
  if(methodName) {
    if(self->currentAttribute == &LresAttribute::attrMethod){
      msgCat->getMsg(buffer,SAY_CALLBACK_CALLED,methodName,XtName(wg));
      puts(buffer);
    } else if(self->currentAttribute == &LresAttribute::attrManage) {
      wv = WidgetView::findWidget(wg);
      if(wv) {
	wv = wv->findTop();
	toManage = wv->findNamedWidget(methodName);
	if(toManage)
	  XtManageChild(toManage);
	else
	  fprintf(stderr,"Can't find Widget %s.\n",&methodName[1]);
      } else
	fprintf(stderr,"Can't find WidgetView with Widget %s.\n",XtName(wg));
    }
  }
}


void LresCallback::setString( char *string )
{
  strcpy(method,string);
  if( method[0] == 0 )
    setValue(0);
  else 
    setValue( (XtArgVal)callbackList );
}

char *LresCallback::getString( char *buffer, unsigned int &len )
{
  if( !buffer ) {
    len = strlen(method)+1;
    return NULL;
  }
  if( len >= strlen(method)+1 )
    strcpy( buffer, method );
  else
    return NULL;
  return buffer;
}

void LresCallback::setValue( XtArgVal v )
{
  value = v;
  _hasChanged = TRUE;
  _isDefault = FALSE;
  // changed( VALUE_CHANGED );
}

Boolean LresCallback::isValid( char *resource_type )
{
  if(findType(resource_type) == "CALLBACK") {
    return TRUE;
  }
  return FALSE;
}

// ############################################
//
// LresEnum
//
// ############################################

LHashDictionary<LresEnum::EnumType*> LresEnum::types;

LresEnum::LresEnum(XtResource &r, Lwidget *widget) 
: Lresource(r, widget) 
{
  type = NULL;
  eValue = NULL;
  types.find(r.resource_type, type);
  //  for( unsigned int i=0; i<types.getSize(); i++ ) 
  //    if( !strcmp( types[i]->name, r.resource_type ) ) {
  //      type = types[i];
  //    }
  eValue = type->values[0];
  possibleAttributes.add(&LresAttribute::attrPrivate);
  possibleAttributes.add(&LresAttribute::attrPublic);
}


void LresEnum::setString( char *string )
{
  for( unsigned int i=0; i<type->values.getSize(); i++ ) {
    if(!strcmp( type->values[i]->identifier, string ) ) {
      eValue = type->values[i];
      setValue( type->values[i]->value );
      return;
    }
  } 
  fprintf(stderr,"can not convert string %s to enum\n", string);
}

char *LresEnum::getString( char *buffer, unsigned int &len )
{
  if( !buffer ) {
    if( eValue )
      len = strlen( eValue->identifier )+1;
    else
      len = 0;
    return NULL;
  }
  if( eValue && len >= strlen(eValue->identifier)+1 )
    strcpy( buffer, eValue->identifier );
  else
    return NULL;
  return buffer;
}

void LresEnum::setValue( XtArgVal v )
{
  unsigned char tmp = (unsigned char)v;
  value = tmp;
  _hasChanged = TRUE;
  _isDefault = FALSE;
  for( unsigned int i=0; i<type->values.getSize(); i++ )
    if( value == type->values[i]->value )
      eValue = type->values[i];
  // changed( VALUE_CHANGED );
}

// ---------------------------------------------------------
// readConfig() - static method
//                read all enum from a file
// ---------------------------------------------------------
  
void LresEnum::readConfig()
{
  char path[PATH_MAX];
  FILE *fd;
  char str[1024];
  EnumType *readType;
  EnumValue *readValue;

  strcpy(path, app->getConfigPath());
  if( path[strlen(path)-1]!='/' )
    strcat(path, "/");
  strcat(path, "enums.cf");
  fd = fopen( path, "r" );
  if( fd ) {
    while( !feof(fd) ) {
      str[0] = 0;
      fscanf( fd, "%s", str );
      if(str[0] != 0) {
	readType = new EnumType();
	Lstring key(str);
	//	readType->name = new char[strlen(str)+1];
	//	strcpy( readType->name, str );
	while( !feof(fd) ) {
	  fscanf(fd, "%s", str );
	  if( !strcmp(str,"end") )
	    break;
	  readValue = new EnumValue();
	  readValue->identifier = new char[strlen(str)+1];
	  strcpy(readValue->identifier, str);
	  readValue->value = 0;
	  fscanf(fd, "%ld", &readValue->value);
	  readType->values.add( readValue );
	} // end while

	types.add(key, readType);

      } // end if
    } // end while
    fclose(fd);
  } else {
    fprintf(stderr,"Fatal error: can't find config file %s\n",path);
  }
}

char **LresEnum::getPossibleIdentifiers( char ** ids, unsigned int &len )
{
  if( !ids ) {
    len = type->values.getSize();
    return NULL;
  }
  if( len >= type->values.getSize() ) {
    for( unsigned int i=0; i< type->values.getSize(); i++ ) {
      ids[i] = type->values[i]->identifier;
    }
    return ids;
  }
  return NULL;
}


Boolean LresEnum::isValid( char *resource_type )
{
  EnumType *val;
  static int init = 0;
  if( init == 0 ) { 
    readConfig();
    init = 1;
  }
  
  if(types.find(resource_type, val))
    return TRUE;

  return FALSE;
}


void LresEnum::getCodeString( char *buffer, unsigned int &len )
{
  char buf[16];
  unsigned int tmp = (unsigned char)value;
  sprintf(buf, "%d", tmp);
  if(buffer) {
    strncpy(buffer, buf, len);
  } else {
    len = strlen(buf)+1;
  }
}


// ############################################
//
// LresRelation
//
// ############################################

void LresRelation::setString( char *string )
{
  Lwidget *lw, *shell=NULL;

  if(strlen(string)<sizeof(widgetName)) {
    if( widgetName[0] ) {
      for( shell = partOf; shell->getParent(); shell = shell->getParent() ); 
      lw = shell->findNamedWidget(widgetName);
      if(lw)
	lw->nameReferenceRemove(this);
    }
    if(!shell)
      for( shell = partOf; shell->getParent(); shell = shell->getParent() ); 
    lw = shell->findNamedWidget(string);
    if( lw ) {
      lw->nameReferenceAdd(this);
      connected = TRUE;
    }
    strcpy(widgetName,string);
    _hasChanged = TRUE;
    _isDefault = FALSE;
    // changed(VALUE_CHANGED);
  }
}

char *LresRelation::getString( char *buffer, unsigned int &len )
{
  if( !buffer ) {
    len = strlen(widgetName)+1;
    return NULL;
  }
  if( len > strlen(widgetName) )
    strcpy(buffer,widgetName);
  else
    return NULL;
  return buffer;
}

void LresRelation::setValue( XtArgVal v )
{
  value = v;
  _hasChanged = TRUE;
  _isDefault = FALSE;
  // changed( VALUE_CHANGED );
}

Boolean LresRelation::isValid( char *resource_type )
{
  if(findType(resource_type) == "WIDGET")
    return TRUE;
  return FALSE;
}

void LresRelation::getCodeString( char *buffer, unsigned int &len )
{
  getString(buffer,len);
}

void LresRelation::apply( WidgetView *wv )
{
  Lwidget *shell, *lw;
  Widget dest;
  if( wv->getParent() && widgetName[0] ) {
    if( !connected ) {                        // now try to connect
      for( shell = partOf; shell->getParent(); shell = shell->getParent() ); 
      lw = shell->findNamedWidget(widgetName);
      if( lw ) {
	lw->nameReferenceAdd(this);
	connected = TRUE;
      }
    }
    dest = wv->getParent()->findNamedWidget(widgetName);
    if( dest ) {
      XtVaSetValues(wv->getWidget(),res.resource_name,dest,NULL);
    } else {
      fprintf(stderr,"Can't find Widget '%s' \n",widgetName);
    }
  }
}

void LresRelation::changeNameTo(char *newName)
{
  strcpy(widgetName,newName);
  changed(VALUE_CHANGED);
}


// ############################################
//
// LresPixmap
//
// ############################################

LresPixmap::LresPixmap(XtResource &r, Lwidget *widget) 
: Lresource(r, widget) 
{
  pixmapName[0]=0;
  display = XtDisplay(Lproject::current().getTopLevel());
  root = XRootWindowOfScreen(XtScreen(Lproject::current().getTopLevel()));

  possibleAttributes.add(&LresAttribute::attrLoad);
  possibleAttributes.add(&LresAttribute::attrInclude);
}

void LresPixmap::setString( char *string )
{
  Pixmap pix, mask;
  XpmAttributes attr;
  Lstring path;
  char *tmp = NULL;
  Boolean allocated = FALSE;

  memset(&attr,0,sizeof(attr));
  attr.valuemask = XpmReturnPixels;
  
  strcpy(pixmapName,string);
  if(currentAttribute == &LresAttribute::attrLoad) {
    tmp = XtResolvePathname(display, "pixmaps", pixmapName, "", NULL,
			     NULL, 0, NULL);
    if(tmp == NULL) {
      path = app->getProject()->getSourcePath();
      path += "/";
      path += pixmapName;
    } else {
      path = tmp;
      allocated = TRUE;
      XtFree(tmp);
    }
  } else {
    path = app->getProject()->getSourcePath();
    path += "/";
    path += pixmapName;
  }

  if(path.getLen() > 0) {
    if(XpmReadFileToPixmap(display, root, path, &pix, &mask, &attr))
      pix = XmUNSPECIFIED_PIXMAP;
  } else
    pix = XmUNSPECIFIED_PIXMAP;
  
  if( pixmapName[0] == 0 ) {
    if(value!=0 && value!=XmUNSPECIFIED_PIXMAP)
      XFreePixmap(display,(Pixmap)value);
    setValue(XmUNSPECIFIED_PIXMAP);
  } else {
    if(value!=0 && value!=XmUNSPECIFIED_PIXMAP)
      XFreePixmap(display,(Pixmap)value);
    setValue(pix);
  }
}

char *LresPixmap::getString( char *buffer, unsigned int &len )
{
  if( !buffer ) {
    len = strlen(pixmapName)+1;
    return NULL;
  }
  if( len >= strlen(pixmapName)+1 )
    strcpy(buffer, pixmapName);
  else
    return NULL;
  return buffer;
}

void LresPixmap::setValue( XtArgVal v )
{
  value = v;
  _hasChanged = TRUE;
  _isDefault = FALSE;
  // changed( VALUE_CHANGED );
}

void LresPixmap::getCodeString( char *buffer, unsigned int &len )
{
  unsigned int l;
  char *createFunction;
  char parameter[strlen(pixmapName)+1];

  if(currentAttribute == &LresAttribute::attrInclude) {
    createFunction = "createPixmapFromData(%s)";
    strcpy(parameter, pixmapName);
    for(char *ptr=parameter; *ptr; ptr++)
      if(*ptr == '.') *ptr = '_';
  } else {
    createFunction = "createPixmapFromFile(\"%s\")";
    strcpy(parameter, pixmapName);
  }
  l = strlen(createFunction);
  l += strlen(parameter)+1;
  if(!buffer) {
    len = l;
    return;
  }
  if( len < l )
    return;
  sprintf(buffer, createFunction, parameter);
}

Boolean LresPixmap::isValid( char *resource_type )
{
  if(findType(resource_type) == "PIXMAP")
    return TRUE;
  return FALSE;
}

// ############################################
//
// LresPixel
//
// ############################################

void LresPixel::setString( char *string )
{
  XtArgVal v;
  XrmValue from, to;

  from.addr = (XPointer)string;
  from.size = strlen(string)+1;
  to.addr = (XPointer)&v;
  to.size = sizeof(v);

  if( XtConvertAndStore(Lproject::current().getTopLevel(), 
			XtRString, &from,
			res.resource_type, &to) ) {
    strcpy(colorName, string);
    setValue( v );
  } else {
    printf("Can't convert color %s.\n",string);
  }
}

char *LresPixel::getString( char *buffer, unsigned int &len )
{
  if( !buffer ) {
    len = strlen(colorName)+1;
    return NULL;
  }
  if( len != 0 )
    strcpy(buffer, colorName);
  else
    return NULL;
  return buffer;
}

void LresPixel::setValue( XtArgVal v )
{
  value = v;
  _hasChanged = TRUE;
  _isDefault = FALSE;
  // changed( VALUE_CHANGED );
}

Boolean LresPixel::isValid( char *resource_type )
{
  if(findType(resource_type) == "PIXEL")
    return TRUE;
  return FALSE;
}


// ############################################
//
// LresFontList
//
// ############################################

void LresFontList::setString( char *string )
{
  XtArgVal v;
  XrmValue from, to;

  from.addr = (XPointer)string;
  from.size = strlen(string)+1;
  to.addr = (XPointer)&v;
  to.size = sizeof(v);

  if( XtConvertAndStore(Lproject::current().getTopLevel(), 
			XtRString, &from,
			res.resource_type, &to) ) {
    strcpy(fontName, string);
    setValue( v );
  } else {
    printf("Can't convert font %s.\n",string);
  }
}

char *LresFontList::getString( char *buffer, unsigned int &len )
{
  if( !buffer ) {
    len = strlen(fontName)+1;
    return NULL;
  }
  if( len != 0 )
    strcpy(buffer, fontName);
  else
    return NULL;
  return buffer;
}

void LresFontList::setValue( XtArgVal v )
{
  value = v;
  _hasChanged = TRUE;
  _isDefault = FALSE;
  // changed( VALUE_CHANGED );
}

Boolean LresFontList::isValid( char *resource_type )
{
  if(findType(resource_type) == "FONTLIST")
    return TRUE;
  return FALSE;
}

// ############################################
//
// LresString
//
// ############################################

void LresString::setString( char *string )
{
  XtArgVal v;

  if(this->string) 
    delete this->string;
  this->string = new char[strlen(string)+1];
  strcpy(this->string, string);
  v = (XtArgVal)this->string;
  setValue( v );
}

char *LresString::getString( char *buffer, unsigned int &len )
{
  if( !buffer ) {
    if(string)
      len = strlen(string)+1;
    else
      len = 1;
    return NULL;
  }
  if( len != 0 ) {
    if(string)
      strcpy(buffer, string);
    else
      buffer[0]=0;
  } else
    return NULL;
  return buffer;
}

void LresString::setValue( XtArgVal v )
{
  value = v;
  _hasChanged = TRUE;
  _isDefault = FALSE;
  // changed( VALUE_CHANGED );
}

Boolean LresString::isValid( char *resource_type )
{
  if(findType(resource_type) == "STRING")
    return TRUE;
  return FALSE;
}

void LresString::getCodeString( char *buffer, unsigned int &len )
{
  if(buffer == NULL) {
    if(string)
      len = strlen(string)+3;
    else
      len = 3;
    return;
  }
  strcpy(buffer,"\"");
  if(string)
    strcat(buffer,string);
  strcat(buffer,"\"");
}


// ############################################
//
// LresCvtFromString
//
// ############################################

void LresCvtFromString::setString( char *string )
{
  XtArgVal v;
  XrmValue from, to;

  from.addr = (XPointer)string;
  from.size = strlen(string)+1;

  // Work around for Xrt3dDouble :-(
  if(!strcmp(res.resource_type, "Xrt3dDouble")) {
    v = (XtArgVal)&dbl;
    to.addr = (XPointer)v;
    to.size = sizeof(dbl);
  } else {
    to.addr = (XPointer)&v;
    to.size = sizeof(v);
  }

  if(XtConvertAndStore(Lproject::current().getTopLevel(), 
		       XtRString, &from,
		       res.resource_type, &to) ) {
    if(this->string) {
      delete this->string;
    }
    this->string = new char[strlen(string)+1];
    strcpy(this->string, string);
    setValue(v);
  } else {
    printf("Can't convert %s to %s.\n",string, res.resource_type);
  }
}

char *LresCvtFromString::getString( char *buffer, unsigned int &len )
{
  if( !buffer ) {
    if(string)
      len = strlen(string)+1;
    else
      len = 1;
    return NULL;
  }
  if( len != 0 ) {
    if(string)
      strcpy(buffer, string);
    else
      buffer[0]=0;
  } else
    return NULL;
  return buffer;
}

void LresCvtFromString::setValue( XtArgVal v )
{
  value = v;
  _hasChanged = TRUE;
  _isDefault = FALSE;
  // changed( VALUE_CHANGED );
}

Boolean LresCvtFromString::isValid( char *resource_type )
{
  if(findType(resource_type) == "CONVERTER")
    return TRUE;
  return FALSE;
}

// ##################################################
//
// createLresource()
//
// ##################################################

Lresource *createLresource( XtResource &r, Lwidget *partOf )
{
  Lstring internalType;

  if(!strcmp(r.resource_name, "numChildren"))
    return NULL;

  internalType = Lresource::findType(r.resource_type);

  if(internalType == "XMSTRING")
    return new LresXmString(r, partOf);
  if(internalType == "BOOL")
    return new LresBoolean(r, partOf);
  if(internalType == "CALLBACK")
    return new LresCallback(r, partOf);
  if(internalType == "WIDGET")
    return new LresRelation(r, partOf);
  if(internalType == "PIXMAP")
    return new LresPixmap(r, partOf);
  if(internalType == "PIXEL")
    return new LresPixel(r, partOf);
  if(internalType == "FONTLIST")
    return new LresFontList(r, partOf);
  if(internalType == "STRING")
    return new LresString(r, partOf);
  if(internalType == "CONVERTER")
    return new LresCvtFromString(r, partOf);

  if(internalType == "SHORT" ||
     internalType == "INT" ||
     internalType == "LONG" ||
     internalType == "CHAR") 
    return new LresNumber(r, partOf, internalType);

  if(LresEnum::isValid(r.resource_type))
    return new LresEnum(r, partOf);

  partOf->getClass()->unhandledResources.add(r.resource_name,
  					     r.resource_type);

#if(0)
  if(!strcmp(r.resource_type, "Pointer"))
    return NULL;
  if(!strcmp(r.resource_type, "Function"))
    return NULL;
  if(!strcmp(r.resource_type, "Colormap"))
    return NULL;
  if(!strcmp(r.resource_type, "Screen"))
    return NULL;
  if(!strcmp(r.resource_type, "WidgetList"))
    return NULL;

  fprintf(stderr, "%s:\t%s \t%s\n", 
	  partOf->getClass()->getName(),
	  r.resource_name, r.resource_type);
#endif
  return NULL;
}
