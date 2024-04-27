/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: InterfaceInfo.C,v $
 *  $Date: 1999/08/27 15:31:08 $
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
 * $Log: InterfaceInfo.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:31:08  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:14  lazy
 * Imported to CVS
 *
 * Revision 1.3  1998/02/10  00:58:38  lazy
 * Add widgetClass to code gen interface.
 *
 * Revision 1.2  1997/09/10  18:47:35  lazy
 * Popup menu source code generation.
 * Fixed non-deleted shellWidget (purify is the best).
 *
 * Revision 1.1  1997/07/25  20:26:32  lazy
 * Initial revision
 *
 */

// ----------------------------
// InterfaceInfo.C
// (C) Dirk Laessig
// ----------------------------

#include "Ltmpl.h"
#include "Lproject.h"
#include "Lwidget.h"
#include "Lresource.h"
#include "InterfaceInfo.h"
#include "misc.h"
#include "lic.h"
#include <ctype.h>
#include <time.h>
#include <sys/utsname.h>

#define RES_CONVERT "RES_CONVERT(\"%s\", \"%s\")"

// -------------------------
// HeaderInfo
// -------------------------

void HeaderInfo::fillout( Ltmpl *tmpl )
{
  tmpl->insertVariable("HEADER",header);
}


// -------------------------
// LocalHeaderInfo
// -------------------------

void LocalHeaderInfo::fillout( Ltmpl *tmpl )
{
  tmpl->insertVariable("HEADER",header);
}


// -------------------------
// LinkInfo
// -------------------------

void LinkInfo::fillout( Ltmpl *tmpl )
{
  tmpl->insertVariable("LINK_CLASS", linkedClass);
}


// -------------------------
// ResourceInfo()
// -------------------------

ResourceInfo::ResourceInfo(Lresource *lresource)
{
  unsigned int len;

  resource_name = lresource->getName();
  resource_type = lresource->getType();
  lresource->getCodeString(NULL, len);
  
  if(len == 0) {
    char *string;
    lresource->getString(NULL, len);
    string = new char[len+1];
    lresource->getString(string, len);
    code_string = new char[strlen(string)+strlen(RES_CONVERT)
			   +strlen(resource_type)+1];
    sprintf(code_string, RES_CONVERT, resource_type, string);
    delete string;
  } else {
    code_string = new char[len+1];
    lresource->getCodeString(code_string, len);
  }
  lresource->getString(NULL, len);
  char aString[len+1];
  lresource->getString(aString, len);
  valueString = aString;
}


void ResourceInfo::fillout( Ltmpl *tmpl )
{
  tmpl->insertVariable("RESOURCENAME", resource_name);
  tmpl->insertVariable("RESOURCEVALUE", code_string);
  tmpl->insertVariable("VALUESTRING", valueString);
}

// -------------------------
// ResourceFileInfo
// -------------------------

ResourceFileInfo::ResourceFileInfo(char *interfaceName)
{
  this->interfaceName = interfaceName;
  string = NULL;
  len = 0;
}

void ResourceFileInfo::addLine(char *widgetName, char *name, char *value)
{
  unsigned long valLen;
  replaceForRF(value, NULL, valLen);
  char nValue[valLen];
  replaceForRF(value, nValue, valLen);
  
  char buf[strlen(interfaceName)+strlen(widgetName)
	   +strlen(name)+strlen(nValue)+10];
  if(!strcmp(interfaceName, widgetName)) {
    sprintf(buf,"*%s.%s: %s\n", interfaceName, name, nValue);
  } else {
    sprintf(buf,"*%s*%s.%s: %s\n", interfaceName, widgetName, name, nValue);
  }
  unsigned long stringLen, bufLen;
  if(string)
    stringLen = strlen(string);
  else
    stringLen = 0;
  bufLen = strlen(buf);
  if(len < stringLen+bufLen+1) {
    len = stringLen+bufLen+4096;
    char *tmp = new char[len];
    tmp[0] = 0;
    if(string) {
      strcpy(tmp,string);
      delete string;
    }
    string = tmp;
  }
  strcat(string,buf);
}

void ResourceFileInfo::fillout( Ltmpl *tmpl )
{
  tmpl->insertVariable("RESOURCEFILE", string ? string : "");
}

// ------------------
// MethodInfo
// ------------------
void MethodInfo::fillout( Ltmpl *tmpl )
{
  tmpl->insertVariable("METHOD",method);
  tmpl->insertVariable("INTERFACE",interface);
}


// ------------------
// CallbackInfo
// ------------------
CallbackInfo::CallbackInfo(Lwidget *w,char *n,char *m)
{ 
  isLink = w->isLinked();
  strcpy( widgetIdentifier, w->getName()); 
  name = n;
  if(m[0]=='$') {
    isManageCB = TRUE;
    strcpy(manageName, m+1);
    method[0]=0;
  } else {
    isManageCB = FALSE;
    strcpy( method, m );
    manageName[0] = 0;
  }
}

void CallbackInfo::fillout( Ltmpl *tmpl )
{
  tmpl->doConditional("IS_LINK", isLink);
  tmpl->doConditional("IS_MANAGE_CB", isManageCB);
  tmpl->insertVariable("NAME", name);
  tmpl->insertVariable("WIDGET_IDENTIFIER", widgetIdentifier);
  tmpl->insertVariable("METHOD", method);
  tmpl->insertVariable("WIDGET_TO_MANAGE", manageName);
  tmpl->insertVariable("INTERFACE", interface);
}


// ------------------
// RelationInfo
// ------------------
RelationInfo::RelationInfo(Lwidget *sw, char *rn, Lwidget *dw)
{
  sourceIsLink = sw->isLinked();
  destIsLink =dw->isLinked();
  strcpy(sourceWidget,sw->getName());
  strcpy(resourceName,rn);
  strcpy(destWidget,dw->getName());
}

void RelationInfo::fillout( Ltmpl *tmpl )
{
  tmpl->doConditional("SOURCE_ISLINK",sourceIsLink);
  tmpl->doConditional("DESTINATION_ISLINK",destIsLink);
  tmpl->insertVariable("SOURCEWIDGET",sourceWidget);
  tmpl->insertVariable("DESTINATIONWIDGET",destWidget);
  tmpl->insertVariable("RESOURCENAME",resourceName);
  tmpl->insertVariable("INTERFACE", interface);
}


// -------------------------
// WidgetInfo
// -------------------------

WidgetInfo::WidgetInfo(Lwidget *lw, InterfaceInfo *interfaceInfo)
{
  useCreateFunction = TRUE;

  name = lw->getName();
  description = lw->getDescription();
  isPopupMenu = FALSE;
  if(!strcmp(lw->getClass()->getName(), "XmCreatePopupMenu")) {
    isPopupMenu = TRUE;
  }
  this->interfaceInfo = interfaceInfo;
  strcpy( interface, interfaceInfo->getName() );
  strcpy( identifier, name );

  if( lw->getParent() ) {
    strcpy( parent, lw->getParent()->getName() );
  } else
    strcpy( parent, "getTopLevel()");

  isLink = FALSE;
  if( lw->isLinked() ) {
    isLink = TRUE;
    sprintf(creation, "create%s(parent,\n\t\t\targs, n)",
	    lw->getNameOfLinkedInterface());
    strcpy( type, lw->getNameOfLinkedInterface() );
    strcat( type, "*" );
    widgetclass = "NULL";
  } else {
    strcpy(type, "Widget" );
    if( lw->getClass()->getWidgetClassStr() ) {

      useCreateFunction = FALSE;
      widgetclassName = lw->getClass()->getName();

      if( lw->getParent() ) {
	sprintf(creation, "XtCreateWidget(\"%s\", %s,\n\t\t\tparent, args, n)",
		name, lw->getClass()->getWidgetClassStr() );
      } else {
	sprintf(creation, "XtCreatePopupShell(\"%s\", %s,\n\t\t\tparent, args, n)",
		name, lw->getClass()->getWidgetClassStr() );
      }
      widgetclass = lw->getClass()->getWidgetClassStr();
    } else {

      useCreateFunction = TRUE;
      createFunction = lw->getClass()->getName();

      if( lw->getClass()->getCreateFuncStr() ) {
	sprintf(creation, "%s( parent, \"%s\", args, n)",
		lw->getClass()->getCreateFuncStr(), name );
	widgetclass = "NULL";
      }
    }
  }


  unsigned int i;
  RefArray<Lresource> &core(lw->getProperties()->getCore());
  RefArray<Lresource> &specific(lw->getProperties()->getSpecific());
  RefArray<Lresource> &constraint(lw->getProperties()->getConstraint());


  for( i=0; i<core.getSize(); i++ )
    if( !core[i]->isDefault() && !core[i]->isRelation() )
      addResource( core[i] );

  for( i=0; i<specific.getSize(); i++ )
    if( !specific[i]->isDefault() && !specific[i]->isRelation() )
      addResource( specific[i] );

  for( i=0; i<constraint.getSize(); i++ )
    if( !constraint[i]->isDefault() && !constraint[i]->isRelation() )
      addResource( constraint[i] );

  if(lw->getQuickhelp() && *lw->getQuickhelp()) {
    interfaceInfo->addResourceLine(lw->getName(), 
				   "quickHelpLabel", lw->getQuickhelp());
  }
  if( lw->getParent() && lw->toManage())
    manage = TRUE;
  else
    manage = FALSE;

  if(lw->getHelpNode())
    sprintf(helpId, "%d", lw->getHelpNode()->getId());
  else
    strcpy(helpId, "-1");
}

WidgetInfo::~WidgetInfo()
{
  while(resources.getSize())
    resources[0].Delete();
}

void WidgetInfo::addResource( Lresource *lresource )
{
  if(lresource->getAttribute() == &LresAttribute::attrPublic) {
    unsigned int len;
    lresource->getString(NULL, len);
    char r[len];
    lresource->getString(r, len);
    interfaceInfo->addResourceLine(name, lresource->getName(), r);
  } else if(lresource->getAttribute() == &LresAttribute::attrInclude) {
    unsigned int len;
    lresource->getString(NULL, len);
    char r[len];
    lresource->getString(r, len);
    interfaceInfo->addLocalHeader(r);
    resources.add(new ResourceInfo(lresource));
  } else
    resources.add(new ResourceInfo(lresource));
}


void WidgetInfo::fillOutResources( Ltmpl *tmpl, char *var )
{
  char fName[PATH_MAX];
  char fullPath[PATH_MAX];

  while(tmpl->cutFilenameVariable(var,fName)) {
    strcpy( fullPath, app->getConfigPath() );
    strcat( fullPath, "/" );
    strcat( fullPath, fName );
    
    LtmplList tl(fullPath);
    
    for( unsigned int i=0; i<resources.getSize(); i++ ) {
      Ltmpl *t = tl.add();
      resources[i]->fillout(t);
    }
    tmpl->insertVariable(var,tl.getResult());
  }
}


void WidgetInfo::fillout( Ltmpl *tmpl )
{
  tmpl->doConditional("ISLINK",isLink);
  tmpl->doConditional("MANAGE",manage);
  tmpl->doConditional("IS_POPUPMENU", isPopupMenu);

  tmpl->doConditional("USE_CREATEFUNCTION", useCreateFunction);

  tmpl->insertVariable("NAME",name);
  tmpl->insertVariable("PARENT",parent);
  tmpl->insertVariable("IDENTIFIER",identifier);
  tmpl->insertVariable("TYPE",type);
  tmpl->insertVariable("CREATION",creation);
  tmpl->insertVariable("INTERFACE",interface);
  tmpl->insertVariable("HELPID",helpId);
  tmpl->insertVariable("DESCRIPTION",description);
  tmpl->insertVariable("WIDGETCLASS", widgetclass);

  tmpl->insertVariable("WIDGETCLASSNAME", widgetclassName);
  tmpl->insertVariable("CREATEFUNCTION", createFunction);

  fillOutResources(tmpl,"RESOURCES");
}



// ------------------------
// InterfaceInfo
// ------------------------

InterfaceInfo::InterfaceInfo(Linterface *interface)
{
  char *atime;
  size_t len;
  time_t atime_t;
  struct utsname utsname;

  name = interface->getName();

  len = sizeof(user);
  getUserName(user, len);

  if(uname(&utsname) == 0) {
    if(strlen(user) + strlen(utsname.nodename) + 2 < sizeof(user)) {
      strcat(user, "@");
      strcat(user, utsname.nodename);
    }
  }

  atime_t = time(NULL);
  atime = ctime(&atime_t);
  if(atime && strlen(atime) < sizeof(date)) {
    strcpy(date, atime);
    if(date[strlen(date)-1] == '\n')
      date[strlen(date)-1] = 0;
  } else {
    strcpy(date, "ctime() failed :-(");
  }

  msgCat->getMsg(version, VDX_VERSION);

  shellWidget = NULL;
  resourceFile = new ResourceFileInfo(name);
  interface->getShell()->fillInterfaceInfo(this);
}

InterfaceInfo::~InterfaceInfo()
{
  while(widgets.getSize())
    widgets[0].Delete();
  while(headers.getSize())
    headers[0].Delete();
  while(localHeaders.getSize())
    localHeaders[0].Delete();
  while(callbacks.getSize())
    callbacks[0].Delete();
  while(methods.getSize())
    methods[0].Delete();
  while(relations.getSize())
    relations[0].Delete();
  resourceFile.Delete();
  if(shellWidget)
    delete shellWidget;
}  

void InterfaceInfo::addWidget( Lwidget *lwidget )
{
  if(lwidget->isLinked()) {
    char *n = lwidget->getNameOfLinkedInterface();
    links.add( new LinkInfo(n) );
  }
  if(lwidget->getParent())
    widgets.add( new WidgetInfo(lwidget, this) );
  else
    shellWidget = new WidgetInfo(lwidget, this);
}

void InterfaceInfo::addHeader( char *header )
{
  unsigned int i;
  for( i=0; i<headers.getSize(); i++ )
    if( !strcmp(headers[i]->getHeader(),header) )
      break;
  if( i == headers.getSize() )
    headers.add( new HeaderInfo(header) );
}

void InterfaceInfo::addLocalHeader( char *header )
{
  unsigned int i;
  for( i=0; i<localHeaders.getSize(); i++ )
    if( !strcmp(localHeaders[i]->getHeader(),header) )
      break;
  if( i == localHeaders.getSize() )
    localHeaders.add( new LocalHeaderInfo(header) );
}

void InterfaceInfo::addCallback( Lwidget *widget, char *name, char *method )
{
  unsigned int i;
  CallbackInfo *cbi;

  cbi = new CallbackInfo(widget,name,method);
  cbi->setInterfaceName(this->name);
  callbacks.add(cbi);

  for( i=0; i<methods.getSize(); i++ )
    if( !strcmp(methods[i]->getMethod(),method) )
      break;
  if( method[0] != '$' && i == methods.getSize() )
    methods.add( new MethodInfo(method,this->name) );
}


void InterfaceInfo::addRelation(Lwidget *sw, char *rn, Lwidget *dw)
{
  RelationInfo *ri;
  ri = new RelationInfo(sw,rn,dw);
  ri->setInterfaceName(this->name);
  relations.add(ri);
}

void InterfaceInfo::fillout( Ltmpl *tmpl )
{
  char fName[PATH_MAX];
  char fullPath[PATH_MAX];

  tmpl->insertVariable("DATE", date);
  tmpl->insertVariable("USER", user);
  tmpl->insertVariable("VDX_VERSION", version);

  resourceFile->fillout(tmpl);

  if(shellWidget) {
    tmpl->insertVariable("SHELLCREATION",shellWidget->getCreation());
    tmpl->insertVariable("SHELLIDENTIFIER",shellWidget->getIdentifier());
    shellWidget->fillOutResources(tmpl,"SHELLRESOURCES");
  }

  tmpl->insertVariable("NAME",name);
  while(tmpl->cutFilenameVariable("LINKS",fName)) {
    strcpy( fullPath, app->getConfigPath() );
    strcat( fullPath, "/" );
    strcat( fullPath, fName );
    
    LtmplList tl(fullPath);
    
    for( unsigned int i=0; i<links.getSize(); i++ ) {
      Ltmpl *t = tl.add();
      links[i]->fillout(t);
    }
    tmpl->insertVariable("LINKS",tl.getResult());
  }
  while(tmpl->cutFilenameVariable("WIDGETS",fName)) {
    strcpy( fullPath, app->getConfigPath() );
    strcat( fullPath, "/" );
    strcat( fullPath, fName );
    
    LtmplList tl(fullPath);
    
    for( unsigned int i=0; i<widgets.getSize(); i++ ) {
      Ltmpl *t = tl.add();
      widgets[i]->fillout(t);
    }
    tmpl->insertVariable("WIDGETS",tl.getResult());
  }
  while(tmpl->cutFilenameVariable("METHODS",fName)) {
    strcpy( fullPath, app->getConfigPath() );
    strcat( fullPath, "/" );
    strcat( fullPath, fName );
    
    LtmplList tl(fullPath);
    for( unsigned int i=0; i<methods.getSize(); i++ ) {
      Ltmpl *t = tl.add();
      methods[i]->fillout(t);
    }
    tmpl->insertVariable("METHODS",tl.getResult());
  }
  while(tmpl->cutFilenameVariable("CALLBACKS",fName)) {
    strcpy( fullPath, app->getConfigPath() );
    strcat( fullPath, "/" );
    strcat( fullPath, fName );
    
    LtmplList tl(fullPath);
    
    for( unsigned int i=0; i<callbacks.getSize(); i++ ) {
      Ltmpl *t = tl.add();
      callbacks[i]->fillout(t);
    }
    tmpl->insertVariable("CALLBACKS",tl.getResult());
  }
  while(tmpl->cutFilenameVariable("RELATIONS",fName)) {
    strcpy( fullPath, app->getConfigPath() );
    strcat( fullPath, "/" );
    strcat( fullPath, fName );
    
    LtmplList tl(fullPath);
    
    for( unsigned int i=0; i<relations.getSize(); i++ ) {
      Ltmpl *t = tl.add();
      relations[i]->fillout(t);
    }
    tmpl->insertVariable("RELATIONS",tl.getResult());
  }
  while(tmpl->cutFilenameVariable("HEADERS",fName)) {
    strcpy( fullPath, app->getConfigPath() );
    strcat( fullPath, "/" );
    strcat( fullPath, fName );
    
    LtmplList tl(fullPath);
    
    for( unsigned int i=0; i<headers.getSize(); i++ ) {
      Ltmpl *t = tl.add();
      headers[i]->fillout(t);
    }
    tmpl->insertVariable("HEADERS",tl.getResult());
  }
  while(tmpl->cutFilenameVariable("LOCALHEADERS",fName)) {
    strcpy(fullPath, app->getConfigPath() );
    strcat(fullPath, "/" );
    strcat(fullPath, fName );
    
    LtmplList tl(fullPath);
    
    for( unsigned int i=0; i<localHeaders.getSize(); i++ ) {
      Ltmpl *t = tl.add();
      localHeaders[i]->fillout(t);
    }
    tmpl->insertVariable("LOCALHEADERS",tl.getResult());
  }
  resourceFile->fillout(tmpl);
}

// -------------------------
// addResourceLine()
// -------------------------

void InterfaceInfo::addResourceLine(char *widgetName, 
				    char *resourceName, char *value)
{
  resourceFile->addLine(widgetName,resourceName,value);
}
