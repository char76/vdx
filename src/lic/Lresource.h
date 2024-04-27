/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: Lresource.h,v $
 *  $Date: 1999/08/27 15:31:27 $
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
 * $Log: Lresource.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:31:27  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:13  lazy
 * Imported to CVS
 *
 * Revision 1.3  1998/03/30 19:08:32  lazy
 * *** empty log message ***
 *
 * Revision 1.2  1997/12/14  19:10:07  lazy
 * Configuration by extarnal file (resource.cf)
 *
 * Revision 1.1  1997/07/25  20:28:25  lazy
 * Initial revision
 *
 */

// --------------------------------------------
// Class Lresource and derived classes
//
// (C) Dirk Laesssig
// --------------------------------------------

#ifndef _LRESOURCE_H_
#define _LRESOURCE_H_

#include <lac/Model.h>
#include <lac/View.h>
#include <X11/IntrinsicP.h>
#include <X11/CoreP.h>
#include "parse.h"
#include <Xm/Xm.h>
#include <lac/Lstring.h>
#include <lac/LHashDictionary.h>

class Lwidget;
class WidgetView;

// --------- LresAttribute ------------
// Class to handle the Attributes member
// in Lresource;

class LresAttribute {
  const char *string;
  LresAttribute(const char *s) { string = s; }
public:
  const char *getString() const { return string; }
  
  static LresAttribute attrPublic;
  static LresAttribute attrPrivate;
  static LresAttribute attrMethod;
  static LresAttribute attrManage;
  static LresAttribute attrInclude;
  static LresAttribute attrLoad;
  static LresAttribute attrInterface;
};

// ----------------------- Lresource ---------------------

#define VALUE_CHANGED (USER_CHANGED << 1)

class Lresource : public Model {
private:

  static LHashDictionary<Lstring> config;        // The config file contents
  static void readConfig(char *filename = NULL); // Read the config file       
  static Boolean defaultConfigRead;

protected:	
  XtResource res;         // Copy des Ressource-Rec 
  Boolean _hasChanged;     
  Boolean _isDefault;
  XtArgVal value;         // Argument

  LresAttribute *currentAttribute;
  TArray<LresAttribute> possibleAttributes;

  Lwidget *widget;

public:
  Lresource(XtResource &r, Lwidget *widget);       
  Lresource(const Lresource &copy);
  YResource *createYResource();

  ~Lresource();

  // set _isDefault true
  void setAsDefault( XtArgVal val );              

  // If derived class has a to string convertion
  virtual Boolean needDefault() { return True; }

  // Needed for get values
  virtual XtArgVal *getAddrOfValue() { return &value; }

  virtual void applyToValue() {}

  char *getName() { return res.resource_name; }   // resource_name
  char *getType() { return res.resource_type; }   // resource_type
  Boolean isDefault() { return _isDefault; }   
  void setDefault( Boolean v ) { _isDefault = v; }
  Boolean hasChanged() { return _hasChanged; }
  Boolean isCore();

  void setValues( ArgList argList, Cardinal& count );
  XtArgVal getValue() { return value; }
  // Packt Value in ArgList und erhoeht count

  virtual void setString( char *string ) = 0;             // Konvertierung
  virtual char *getString( char *buffer, unsigned int &len ) = 0;
  virtual void setValue( XtArgVal value ) = 0;            // setzen
  virtual char *getClassName() = 0;

  virtual Boolean isRelation() { return FALSE; }

  // ------------- Attributes -----------
  TArray<LresAttribute> getPossibleAttributes() const 
    { return possibleAttributes; }
  const LresAttribute *getAttribute() const { return currentAttribute; }
  void setAttribute(char *name);

  // ------------- code creation ------------
  virtual void getCodeString( char *, unsigned int &len ) { len = 0; }

  // ------------- to sort the resource lists --------------
  static int compare( const void *r1, const void *r2 );


  // ------------- find a resource_type in the config file
  static const Lstring& findType(const char *type);

};



// ----------------------------------------------
// createLresource()
// ----------------------------------------------

Lresource *createLresource(XtResource &r, Lwidget *);




// ----------------- LresNumber --------------------

class LresNumber : public Lresource {
private:
  enum { CHAR_VALUE, SHORT_VALUE, INT_VALUE, LONG_VALUE } valueType;
  char charValue;
  short shortValue;
  int intValue;
  long longValue;

public:
  LresNumber(XtResource &r, Lwidget *widget, const Lstring &internalType);

  void setString( char *string );   
  char *getString( char *buffer, unsigned int &len );            
  void setValue( XtArgVal value );
  static Boolean isValid( char *resource_type );
  char *getClassName() { return "LresNumber"; }

  virtual XtArgVal *getAddrOfValue();
  virtual void applyToValue();

  void getCodeString( char *buffer, unsigned int &len );
};


// ----------------- LresXmString --------------------

class LresXmString : public Lresource {
private:
  Boolean cvtXmStringToString(XmString xmString, 
			      char *buf, unsigned long size);

public:
  LresXmString(XtResource &r, Lwidget *widget) : Lresource(r, widget) 
    { 
      possibleAttributes.add(&LresAttribute::attrPrivate);
      possibleAttributes.add(&LresAttribute::attrPublic);
    }
  void setString( char *string );   
  char *getString( char *buffer, unsigned int &len );            
  void setValue( XtArgVal value );
  static Boolean isValid( char *resource_type );
  char *getClassName() { return "LresXmString"; }
};

// ----------------- LresBoolean --------------------

class LresBoolean : public Lresource {
private:
  Boolean booleanValue;

public:
  LresBoolean(XtResource &r, Lwidget *widget) : Lresource(r, widget) 
    { 
      possibleAttributes.add(&LresAttribute::attrPrivate);
      possibleAttributes.add(&LresAttribute::attrPublic);
    }
  void setString( char *string );   
  char *getString( char *buffer, unsigned int &len );            
  void setValue( XtArgVal value );
  static Boolean isValid( char *resource_type );
  char *getClassName() { return "LresBoolean"; }

  // to set resource values
  XtArgVal *getAddrOfValue() { return (XtArgVal*)&booleanValue; }
  void applyToValue() { 
    setAsDefault(booleanValue); 
  }

  void getCodeString( char *buffer, unsigned int &len );
};

// ----------------- LresEnum --------------------

class LresEnum : public Lresource {
private:

  struct EnumValue {
    char *identifier;     
    XtArgVal value;
  };

  struct EnumType {
    TArray<EnumValue> values;
  };

  static LHashDictionary<EnumType*> types;
  static void readConfig();

  EnumType *type;
  EnumValue *eValue;

  unsigned char charValue;

public:
  LresEnum(XtResource &r, Lwidget *widget);

  void setString( char *string );   
  char *getString( char *buffer, unsigned int &len );            
  void setValue( XtArgVal value );
  static Boolean isValid( char *resource_type );
  char *getClassName() { return "LresEnum"; }

  // to set resource values
  XtArgVal *getAddrOfValue() { return (XtArgVal*)&charValue; }
  void applyToValue() { setAsDefault(charValue); }

  char **getPossibleIdentifiers( char ** ids, unsigned int &len );

  void getCodeString( char *buffer, unsigned int &len );
};


// ----------------- LresCallback --------------------

class LresCallback : public Lresource {
private:
  char method[256];
  XtCallbackRec callbackList[2];

  static void testCallback(Widget,XtPointer,XtPointer);

public:
  LresCallback(XtResource &r, Lwidget *widget);

  void setString( char *string );   
  char *getString( char *buffer, unsigned int &len );            
  void setValue( XtArgVal value );
  char *getClassName() { return "LresCallback"; }

  static Boolean isValid( char *resource_type );
};


// ----------------- LresRelation --------------------

class LresRelation : public Lresource {
private:
  Boolean connected;
  Lwidget *partOf;
  char widgetName[32];
public:
  LresRelation(XtResource &r, Lwidget *widget) : Lresource(r, widget) 
    { 
      connected = FALSE; partOf = widget; widgetName[0]=0;
      possibleAttributes.add(&LresAttribute::attrPrivate);
    }
  void setString( char *string );   
  char *getString( char *buffer, unsigned int &len );            
  void setValue( XtArgVal value );
  static Boolean isValid( char *resource_type );
  char *getClassName() { return "LresRelation"; }

  void apply(WidgetView*);
  Boolean isRelation() { return TRUE; }

  void getCodeString( char *buffer, unsigned int &len );

  void changeNameTo(char *newName);
};


// ----------------- LresPixmap --------------------

class LresPixmap : public Lresource {
private:
  char pixmapName[256];
  Display *display;
  Window root;
  
public:
  LresPixmap(XtResource &r, Lwidget *widget);

  void setString( char *string );   
  char *getString( char *buffer, unsigned int &len );            
  void setValue( XtArgVal value );
  char *getClassName() { return "LresPixmap"; }

  void getCodeString( char *buffer, unsigned int &len );

  static Boolean isValid( char *resource_type );
};

// ----------------- LresPixel --------------------

class LresPixel : public Lresource {
private:
  char colorName[256];
public:
  LresPixel(XtResource &r, Lwidget *widget) : Lresource(r, widget) 
    { 
      colorName[0]=0; 
      possibleAttributes.add(&LresAttribute::attrPrivate);
      possibleAttributes.add(&LresAttribute::attrPublic);
    }
  void setString( char *string );   
  char *getString( char *buffer, unsigned int &len );            
  void setValue( XtArgVal value );
  static Boolean isValid( char *resource_type );
  char *getClassName() { return "LresPixel"; }

};



// ----------------- LresFontList --------------------

class LresFontList : public Lresource {
private:
  char fontName[256];
public:
  LresFontList(XtResource &r, Lwidget *widget) : Lresource(r, widget) { 
    possibleAttributes.add(&LresAttribute::attrPrivate);
    possibleAttributes.add(&LresAttribute::attrPublic);
    fontName[0]=0; }
  void setString( char *string );   
  char *getString( char *buffer, unsigned int &len );            
  void setValue( XtArgVal value );
  static Boolean isValid( char *resource_type );
  char *getClassName() { return "LresFontList"; }

};


// ----------------- LresString --------------------

class LresString : public Lresource {
private:
  char *string;
public:
  LresString(XtResource &r, Lwidget *widget) : Lresource(r, widget) 
    { 
      string=NULL; 
      possibleAttributes.add(&LresAttribute::attrPrivate);
      possibleAttributes.add(&LresAttribute::attrPublic);
    }
  ~LresString() { if(string) delete string; }
  void setString( char *string );   
  char *getString( char *buffer, unsigned int &len );            
  void setValue( XtArgVal value );
  static Boolean isValid( char *resource_type );
  char *getClassName() { return "LresString"; }

  void getCodeString( char *buffer, unsigned int &len );

};


// ----------------- LresCvtFromString --------------------

class LresCvtFromString : public Lresource {
private:
  char *string;            // String presentation
  double dbl;              // Xrt3dDouble (buffer to convert)

public:
  LresCvtFromString(XtResource &r, Lwidget *widget) : Lresource(r, widget) { 
    string=NULL; 
    possibleAttributes.add(&LresAttribute::attrPrivate);
    possibleAttributes.add(&LresAttribute::attrPublic);
  }

  ~LresCvtFromString() { if(string) delete string; }

  // set and get the string
  void setString(char *string);   
  char *getString( char *buffer, unsigned int &len );            

  void setValue( XtArgVal value );
  static Boolean isValid(char *resource_type);

  // Return the class name
  char *getClassName() { return "LresCvtFromString"; }

  // this class has no to string convertion
  virtual Boolean needDefault() { return False; }

};


#endif /* DONT ADD STUFF AFTER THIS #endif */
