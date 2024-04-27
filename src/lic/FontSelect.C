/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: FontSelect.C,v $
 *  $Date: 1999/08/27 15:30:57 $
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
 * $Log: FontSelect.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:30:57  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:15  lazy
 * Imported to CVS
 *
 * Revision 1.2  1998/03/30 19:08:15  lazy
 * *** empty log message ***
 *
 * Revision 1.1  1997/07/25 20:25:57  lazy
 * Initial revision
 *
 */

// ------------------------------ 
// FontSelect.C                      
// Do not edit
// ------------------------------

#include "FontSelect.h"
#include <Xm/Text.h>
#include <Xm/List.h>
#include <Xm/PushB.h>
#include <lac/TArray.h>
#include "lic.h"

#define RES_CONVERT(r,s) XtVaTypedArg,r,XtRString,s,strlen(s)+1
#define MAX_FONTNAME 256
#define DEFAULTPATTERN "-*-*-*-*-*-*-*-*-*-*-*-*-*-*"

char **FontSelect::fonts = NULL;
unsigned int FontSelect::count = 0;

// --------------------------------
//        FontSelect()
// --------------------------------

FontSelect::FontSelect(ValueView *th)
:FontSelect_base(NULL,NULL,0), textResView(th, this)
{
  unsigned long len;
  unsigned int i;
  char msg[1024];
  
  TArray<char> companies;
  TArray<char> families;
  TArray<char> sizes;

  setWaitCursor(TRUE);        
  quickHelpLabel = quickHelp;

  msgCat->getMsg(msg, SAMPLE_FONT_TEXT);
  XmTextSetString(sampleText, msg);

  textResView->getText(NULL,len);
  char t[len];
  textResView->getText(t,len);
  
  XmTextSetString(fontSelection,t);
  
  setFont(t);

  readFonts(DEFAULTPATTERN);                // alle Fonts lesen

  if(fonts) {
    
    queryFromFonts(companies,families,sizes);  // die Namen aufloesen

    for(i=0; i<companies.getSize(); i++) {
      XtCreateManagedWidget(companies[i], 
			    xmPushButtonWidgetClass, 
			    companyMenu, NULL, 0 );
    }
    for(i=0; i<families.getSize(); i++) {
      XtCreateManagedWidget(families[i], 
			    xmPushButtonWidgetClass, 
			    familyMenu, NULL, 0 );
    }
    for(i=0; i<sizes.getSize(); i++) {
      XtVaCreateManagedWidget(sizes[i], 
			      xmPushButtonWidgetClass, 
			      sizeMenu, 
			      XmNmarginHeight, 0,
			      XmNmarginWidth, 0,
			      NULL);
    }

  }

  for(i=0; i<companies.getSize(); i++)
    delete companies[i];
  for(i=0; i<families.getSize(); i++)
    delete families[i];
  for(i=0; i<sizes.getSize(); i++)
    delete sizes[i];

  setWaitCursor(FALSE);
}

// --------------------------------
//   ~FontSelect()
// --------------------------------

FontSelect::~FontSelect()
{
}

// --------------------------------
//    readFonts()
// --------------------------------

void FontSelect::readFonts(char *pattern)
{
  int ret;
  unsigned int i;

  XtUnmanageChild(fontList);

  if(!fonts) {
    fonts = XListFonts(XtDisplay(fontList),DEFAULTPATTERN,10000,&ret);
    count = ret;
  }

  XmListDeleteAllItems(fontList);

  if(fonts) {
    showedFonts.empty();
    for(i=0; i<count; i++) {
      if(matchPattern(fonts[i], pattern)) {
	XmString xms;

	showedFonts.add(fonts[i]);
	xms = XmStringCreateLtoR(fonts[i], XmSTRING_DEFAULT_CHARSET);
	XmListAddItemUnselected(fontList, xms, 0);
	
	XmStringFree(xms);
      }
    }
  }
  XtManageChild(fontList);
}

// --------------------------------
//        setFont()
// --------------------------------

void FontSelect::setFont(char *t) 
{
  if(t) {
    XtArgVal v;
    XrmValue from, to;
    
    from.addr = (XPointer)t;
    from.size = strlen(t)+1;
    to.addr = (XPointer)&v;
    to.size = sizeof(v);
    
    if( XtConvertAndStore(sampleText, XtRString, &from, 
			  "FontList", &to) ) {
      XtVaSetValues(sampleText,
		    XmNfontList, v,
		    NULL);
    } else {
      printf("Can't convert font %s.\n", t);
    }
  }
}

// -------------------------
// delNotify()
// -------------------------

void FontSelect::delNotify(BaseRef *)
{
  delete this;
}

// --------------------------------------
// Not used
// --------------------------------------
  
FontSelect::FontSelect(Widget wg, ArgList args, Cardinal n)
:FontSelect_base(wg,args,n) 
{
  // do nothing
}
FontSelect *createFontSelect(Widget parent, ArgList args, Cardinal n)
{
  return new FontSelect(parent,args,n);
}


// --------------------------
//      fontSelectOk()
// --------------------------

void FontSelect::fontSelectOk(Widget , XtPointer )
{
  char *t;
  
  t = XmTextGetString(fontSelection);
  
  textResView->setText(t);

  XtFree(t);
  delete this;
}


// --------------------------
//      fontSelectCancel()
// --------------------------

void FontSelect::fontSelectCancel(Widget , XtPointer )
{
  delete this;
}


// --------------------------
//      fontSelectHelp()
// --------------------------

void FontSelect::fontSelectHelp(Widget, XtPointer )
{
  getHelp(HID_FONT_CHOOSER);
}


// --------------------------
//      fontTextChanged()
// --------------------------

void FontSelect::fontTextChanged(Widget , XtPointer )
{
  char *t;

  t = XmTextGetString(fontSelection);
  
  setFont(t);
  
  readFonts(t);
  
  XtFree(t);
}


// --------------------------
//      fontSelected()
// --------------------------

void FontSelect::fontSelected(Widget , XtPointer )
{
  int *positions = NULL, count;

  XmListGetSelectedPos(fontList, &positions, &count);
  if(count == 1) {
    setFont(showedFonts[positions[0]-1]);
    XmTextSetString(fontSelection, showedFonts[positions[0]-1]);
  }
  if(positions)
    XtFree((char*)positions);
}


// --------------------------
//      companyChanged()
// --------------------------

void FontSelect::companyChanged(Widget , XtPointer callbackData)
{
  XmRowColumnCallbackStruct *cbs = (XmRowColumnCallbackStruct*)callbackData;

  setWaitCursor(TRUE);

  XtVaSetValues(companyOptionMenu, XmNmenuHistory, cbs->widget, NULL);
  updateOptionMenus();

  setWaitCursor(FALSE);
}



// --------------------------
//      familyChanged()
// --------------------------

void FontSelect::familyChanged(Widget , XtPointer callbackData)
{
  XmRowColumnCallbackStruct *cbs = (XmRowColumnCallbackStruct*)callbackData;

  setWaitCursor(TRUE);

  XtVaSetValues(familyOptionMenu, XmNmenuHistory, cbs->widget, NULL);
  updateOptionMenus();

  setWaitCursor(FALSE);
}



// --------------------------
//      sizeChanged()
// --------------------------

void FontSelect::sizeChanged(Widget , XtPointer callbackData)
{
  XmRowColumnCallbackStruct *cbs = (XmRowColumnCallbackStruct*)callbackData;

  setWaitCursor(TRUE);

  XtVaSetValues(sizeOptionMenu, XmNmenuHistory, cbs->widget, NULL);
  updateOptionMenus();

  setWaitCursor(FALSE);
}


// --------------------------
//    updateOptionMenus()
// --------------------------

void FontSelect::updateOptionMenus()
{
  unsigned int i, j;

  char *company, *family, *size;
  Widget dummy;
  WidgetList children;
  Cardinal numChildren;
  char pattern[MAX_FONTNAME];
  Boolean found;

  XtVaGetValues(companyOptionMenu, XmNmenuHistory, &dummy, NULL);
  company = XtName(dummy);
  XtVaGetValues(familyOptionMenu, XmNmenuHistory, &dummy, NULL);
  family = XtName(dummy);
  XtVaGetValues(sizeOptionMenu, XmNmenuHistory, &dummy, NULL);
  size = XtName(dummy);

  if(!strcmp(company,"companyDontCare")) 
    company = "*";
  if(!strcmp(family,"familyDontCare")) 
    family = "*";
  if(!strcmp(size,"sizeDontCare")) 
    size = "*";

  if(company[0]=='*' && family[0]=='*' && size[0]=='*') {
    strcpy(pattern,DEFAULTPATTERN);
  } else {
    sprintf(pattern, "-%s-%s-*-*-*-*-%s-*-*-*-*-*-*-*", company, family, size);
  }
  readFonts(pattern);
  
  XtVaGetValues(companyMenu,
		XmNchildren, &children,
		XmNnumChildren, &numChildren,
		NULL);
  for(i=0; i<numChildren; i++) {
    if(strcmp(XtName(children[i]),"companyDontCare")) {
      sprintf(pattern, "-%s-%s-*-*-*-*-%s-*-*-*-*-*-*-*", 
	      XtName(children[i]), family, size);
      for(j=0, found = FALSE; j<count && !found; j++) {
	found = matchPattern(fonts[j],pattern);
      }
      XtSetSensitive(children[i], found);
    }
  }

  XtVaGetValues(familyMenu,
		XmNchildren, &children,
		XmNnumChildren, &numChildren,
		NULL);
  for(i=0; i<numChildren; i++) {
    if(strcmp(XtName(children[i]),"familyDontCare")) {
      sprintf(pattern, "-%s-%s-*-*-*-*-%s-*-*-*-*-*-*-*", 
	      company, XtName(children[i]), size);
      for(j=0, found = FALSE; j<count && !found; j++) {
	found = matchPattern(fonts[j],pattern);
      }
      XtSetSensitive(children[i], found);
    }
  }

  XtVaGetValues(sizeMenu,
		XmNchildren, &children,
		XmNnumChildren, &numChildren,
		NULL);
  for(i=0; i<numChildren; i++) {
    if(strcmp(XtName(children[i]),"sizeDontCare")) {
      sprintf(pattern, "-%s-%s-*-*-*-*-%s-*-*-*-*-*-*-*", 
	      company, family, XtName(children[i]));
      for(j=0, found = FALSE; j<count && !found; j++) {
	found = matchPattern(fonts[j],pattern);
      }
      XtSetSensitive(children[i], found);
    }
  }
}


// --------------------------
//    queryFromFont()
// --------------------------

void FontSelect::queryFromFonts(TArray<char> &c,
				TArray<char> &f,
				TArray<char> &s)
{
  unsigned int i, j;
  if(fonts == NULL)
    return;

  for( i=0; i<count; i++) {
    char font[MAX_FONTNAME];
    char *company = NULL;
    char *family = NULL;
    char *size = NULL;
    char *str;

    memset(font, 0, sizeof(font));
    strcpy(font, fonts[i]);
    
    if(font[0] == '-' ) {
      str = strtok(font, "-");
      if(str) {
	company = str;
	str = strtok(NULL, "-");
	if(str) {
	  family = str;
	  for(j=0; j<5; j++) {
	    while(*str && *str!='-') str++;
	    str++;
	  }
	  if(str) {
	    size=str;
	    while(*str && *str!='-') str++;
	    *str = 0;
	  }
	}
      }
    }
    if(company) {
      if( c.getSize() == 0 ) {
	str = new char[strlen(company)+1];
	strcpy(str,company);
	c.add(str);
      } else {
	for(j=0; j<c.getSize(); j++) {
	  if(!strcmp(c[j], company))
	    break;
	  if( strcmp(c[j], company) > 0 ) {
	    str = new char[strlen(company)+1];
	    strcpy(str,company);
	    c.insert(str,c[j]);
	    break;
	  }
	}
	if( c.getSize() == j ) {
	  str = new char[strlen(company)+1];
	  strcpy(str,company);
	  c.add(str);
	}
      }
    }
    if(family) {
      if( f.getSize() == 0) {
	str = new char[strlen(family)+1];
	strcpy(str,family);
	f.add(str);
      } else {
	for(j=0; j<f.getSize(); j++) {
	  if(!strcmp(f[j], family))
	    break;
	  if( strcmp(f[j], family) > 0) {
	    str = new char[strlen(family)+1];
	    strcpy(str,family);
	    f.insert(str, f[j]);
	    break;
	  }
	}
	if( j==f.getSize() ) {
	  str = new char[strlen(family)+1];
	  strcpy(str,family);
	  f.add(str);
	}
      }
    }
    if(size) {
      if( s.getSize() == 0 ) {
	str = new char[strlen(size)+1];
	strcpy(str,size);
	s.add(str);
      } else {
	for(j=0; j<s.getSize(); j++) {
	  if(!strcmp(s[j], size))
	    break;
	  if( atoi(s[j]) > atoi(size) ) {    // anders als die anderen
	    str = new char[strlen(size)+1];
	    strcpy(str,size);
	    s.insert(str, s[j]);
	    break;
	  }
	}
	if( s.getSize() == j ) {
	  str = new char[strlen(size)+1];
	  strcpy(str,size);
	  s.add(str);
	}
      }
    }
  }   // end of for
}


// -----------------------------------
//      matchPattern()
// -----------------------------------
Boolean FontSelect::matchPattern(char *font, char *pattern)
{
  char *ptr1, *ptr2;

  ptr1 = font;
  ptr2 = pattern;

  while( *ptr1 && *ptr2 ) {
    if( *ptr2 == '?' ) {
      ptr1++;
      ptr2++;
      continue;
    }
    if( *ptr2 == '*' ) {
      while(*ptr2 && (*ptr2 == '*' || *ptr2 == '?')) ptr2++;
      if(*ptr2) {
	while(*ptr1 && *ptr1 != *ptr2) ptr1++;
	if(*ptr1 == 0)
	  return FALSE;
	ptr1++;
	ptr2++;
      }
      continue;
    }
    if( *ptr1 != *ptr2 ) {
      return FALSE;
    }
    ptr1++;
    ptr2++;
  }
  return TRUE;
}
