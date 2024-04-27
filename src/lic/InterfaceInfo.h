/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: InterfaceInfo.h,v $
 *  $Date: 1999/08/27 15:31:09 $
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
 * $Log: InterfaceInfo.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:31:09  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:14  lazy
 * Imported to CVS
 *
 * Revision 1.2  1998/03/30  19:08:19  lazy
 * *** empty log message ***
 *
 * Revision 1.1  1997/07/25  20:26:36  lazy
 * Initial revision
 *
 */

// -------------------------------
// InterfaceInfo.h
//
// (C) Dirk Laessig
// -------------------------------

#ifndef _INTERFACEINFO_H_
#define _INTERFACEINFO_H_

#include <lac/Lobject.h>
#include <lac/RefArray.h>
#include <lac/Ref.h>
#include <lac/Lstring.h>

// ---- Forward declarations ----
class Lresource;
class Lwidget;
class Linterface;
class Ltmpl;
class LtmplList;

#ifndef MAX_NAME_LEN
#define MAX_NAME_LEN 32
#endif

// ----  HeaderInfo  ----

class HeaderInfo : public Lobject {
private:
  char *header;
public:
  HeaderInfo( char *h ) { header = h; }
  char *getHeader() { return header; }
  void fillout( Ltmpl *tmpl );
};

// ----  LocalHeaderInfo  ----

class LocalHeaderInfo : public Lobject {
private:
  char *header;
public:
  LocalHeaderInfo( char *h ) { header = new char[strlen(h)+1];
			       strcpy(header,h);
			     }
  ~LocalHeaderInfo() { delete header; }
  char *getHeader() { return header; }
  void fillout( Ltmpl *tmpl );
};

// ---- Linked Objects ----

class LinkInfo : public Lobject {
private:
  char linkedClass[256];
public:
  LinkInfo( char *lClass ) { strcpy(linkedClass, lClass); }
  char *getLinkedClass() { return linkedClass; }
  void fillout( Ltmpl *tmpl );
};


// ----  CallbackInfo  ----

class CallbackInfo : public Lobject {
private:
  Boolean isManageCB;
  char manageName[64];
  char widgetIdentifier[64];
  char *name;
  char method[256];
  Lstring interface;

  Boolean isLink;
public:
  CallbackInfo(Lwidget *w,char *n,char *m);
  char *getMethod() { return method; }
  void setInterfaceName(char *str) { interface = str; }
  void fillout( Ltmpl *tmpl );
};


// ----  ResourceInfo ----

class ResourceInfo : public Lobject {
private:
  char *resource_name;
  char *resource_type;
  char *code_string;
  Lstring valueString;

public:
  ResourceInfo(Lresource *lresource);
  ~ResourceInfo() { delete code_string; }
  void fillout( Ltmpl *tmpl );
};


// ----  ResourceFileInfo  ----

class ResourceFileInfo : public Lobject {
private:
  char *interfaceName;

  char *string;
  unsigned long len;
  
public:
  ResourceFileInfo(char *interfaceName);
  ~ResourceFileInfo() { delete string; }
  void addLine(char *widgetName, char *name, char *value);
  void fillout( Ltmpl *tmpl );

  char * getString() { return string; }
};



// ----  WidgetInfo  ----

class WidgetInfo : public Lobject {
private:
  char *name;
  char type[64];
  char identifier[64];
  char parent[64];
  char creation[256];
  Boolean manage;
  Boolean isLink;
  Boolean isPopupMenu;
  Boolean useCreateFunction;

  InterfaceInfo *interfaceInfo;
  char interface[256];
  char helpId[64];
  char *description;    // only a reference
  Lstring widgetclass;
  Lstring widgetclassName;
  Lstring createFunction;

  RefArray<ResourceInfo> resources;
public:
  WidgetInfo(Lwidget *, InterfaceInfo *interfaceInfo);
  ~WidgetInfo();
  void addResource( Lresource *lresource );

  void fillout( Ltmpl *tmpl );
  void fillOutResources( Ltmpl *tmpl, char *var );

  char *getCreation(){ return creation; }
  char *getIdentifier() { return identifier; }
//  char *getResources(){ return resources; }
};


// ----  RelationInfo  ----

class RelationInfo : public Lobject {
private:
  char sourceWidget[MAX_NAME_LEN];
  char resourceName[MAX_NAME_LEN];
  char destWidget[MAX_NAME_LEN];
  Boolean sourceIsLink;
  Boolean destIsLink;
  Lstring interface;

public:
  RelationInfo(Lwidget *sw, char *rn, Lwidget *dw);
  void setInterfaceName(char *str) { interface = str; }
  void fillout( Ltmpl *tmpl );
};


// ----  MethodInfo  ----

class MethodInfo : public Lobject {
private:
  char method[64];
  char *interface;
public:
  MethodInfo(char *method, char *in) 
    { strcpy(this->method, method); interface = in; }
  char *getMethod() { return method; }
  void fillout( Ltmpl *tmpl );
};



// ----  InterfaceInfo  ----

class InterfaceInfo : public Lobject {
private:
  char *name;
  char user[256];
  char date[256];
  char version[256];
  WidgetInfo *shellWidget;
  RefArray<WidgetInfo> widgets;
  RefArray<HeaderInfo> headers;
  RefArray<LocalHeaderInfo> localHeaders;
  RefArray<CallbackInfo> callbacks;
  RefArray<RelationInfo> relations;
  RefArray<MethodInfo> methods;
  RefArray<LinkInfo> links;
  Ref<ResourceFileInfo> resourceFile;

public:
  InterfaceInfo(Linterface *interface);
  ~InterfaceInfo();

  void addWidget( Lwidget *lwidget );
  void addHeader( char *header );
  void addLocalHeader( char *header );
  void addCallback( Lwidget *w, char *name, char *method );
  void addRelation(Lwidget *sourceWidget, char *resourceName, 
		   Lwidget *destionationWidget);
  void addResourceLine(char *widgetName, char *resourceName, char *value);

  void fillout( Ltmpl *tmpl );
  char *getName() { return name; }

  Boolean hasResourceFile() {return resourceFile->getString() ? TRUE : FALSE;}
};

#endif
