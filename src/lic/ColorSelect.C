/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: ColorSelect.C,v $
 *  $Date: 1999/08/27 15:30:45 $
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
 * $Log: ColorSelect.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:30:45  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:15  lazy
 * Imported to CVS
 *
 * Revision 1.2  1998/03/30 19:08:08  lazy
 * *** empty log message ***
 *
 * Revision 1.1  1997/07/25 20:25:08  lazy
 * Initial revision
 *
 */

// ------------------------------ 
// ColorSelect.C                      
// Do not edit
// ------------------------------

#include "ColorSelect.h"
#include "LresEditor.h"
#include <Xm/Scale.h>
#include <Xm/Text.h>
#include <Xm/List.h>
#include <ctype.h>

#define MAX_VALUE 255
#define DEFAULT_COLOR "black"
#define MAX_COLOR_NAME 255
#define RGB_TXT "rgb.txt"

TSortArray<Lstring> ColorSelect::colorDB;
Boolean ColorSelect::init;

// -------------------------------
// ColorSelect
// -------------------------------

ColorSelect::ColorSelect(ValueView *t)
:ColorSelect_base(NULL,NULL,0), textResView(t,this)
{
  unsigned long len;

  quickHelpLabel = quickHelp;
  display = XtDisplay(sampleColor);
  XtVaGetValues(sampleColor,
		XmNcolormap, &cmap,
		NULL);

  textResView->getText(NULL, len);
  if(len == 0 || len == 1) 
    len = strlen(DEFAULT_COLOR);
  char str[len];
  textResView->getText(str,len);
  if(!str[0])
    strcpy(str, DEFAULT_COLOR);

  unsigned long pixels[1];
  if(!XAllocColorCells(display, cmap, FALSE, NULL, 0, pixels, 1)) {
    useCvt = TRUE;    // If we have TrueColor use Converters
  } else {
    useCvt = FALSE;
  }

  xcolor.pixel = pixels[0];
  xcolor.flags = DoRed | DoBlue | DoGreen;

  if(!useCvt) {
    XStoreNamedColor(display, cmap, str, xcolor.pixel , xcolor.flags);
  } else {
    XtVaSetValues(sampleColor, 
		  XtVaTypedArg, XmNbackground, XtRString, str, strlen(str)+1, 
		  NULL);
    XtVaGetValues(sampleColor, XmNbackground, &xcolor.pixel, NULL);
  }

  XQueryColor(display, cmap, &xcolor);

  XtVaSetValues(sampleColor,
		XmNbackground, xcolor.pixel,
		NULL);

  XColor dummy;
  dummy.pixel = XWhitePixelOfScreen(XtScreen(sampleColor));
  dummy.flags = DoRed | DoBlue | DoGreen;
  XQueryColor(display, cmap, &dummy);

  maxRedValue = dummy.red;
  maxGreenValue = dummy.green;
  maxBlueValue = dummy.blue;

  XtVaSetValues(redScale, XmNmaximum, MAX_VALUE, NULL);
  XtVaSetValues(blueScale, XmNmaximum, MAX_VALUE, NULL);
  XtVaSetValues(greenScale, XmNmaximum, MAX_VALUE, NULL);

  XmScaleSetValue(redScale, (xcolor.red*MAX_VALUE)/maxRedValue);
  XmScaleSetValue(blueScale, (xcolor.blue*MAX_VALUE)/maxBlueValue);
  XmScaleSetValue(greenScale, (xcolor.green*MAX_VALUE)/maxGreenValue);

  if(init == 0) 
    initColorDB();

  for(unsigned int i=0; i<colorDB.getSize(); i++) {
    XmString xms;
    xms = XmStringCreate(*(colorDB[i]), XmSTRING_DEFAULT_CHARSET);
    XmListAddItem(colorList, xms, 0);
    XmStringFree(xms);
  }

  valueChanged(NULL,NULL);
}

ColorSelect::~ColorSelect()
{
  XFreeColors(display, cmap, &xcolor.pixel, 1, 0);
}

// -------------------------------
// delNotify()
// -------------------------------
void 
ColorSelect::delNotify(BaseRef *)
{
  delete this;
}

// -------------------------------
// not used
// -------------------------------

ColorSelect *createColorSelect(Widget parent, ArgList args, Cardinal n)
{
  return new ColorSelect(parent,args,n);
}
ColorSelect::ColorSelect(Widget wg, ArgList args, Cardinal n)
:ColorSelect_base(wg,args,n) 
{
  // do nothing
}



void 
ColorSelect::valueChanged(Widget , XtPointer)
{
  int red, green, blue;

  XmScaleGetValue(redScale, &red);
  XmScaleGetValue(greenScale, &green);
  XmScaleGetValue(blueScale, &blue);
  xcolor.red = red*maxRedValue/MAX_VALUE;
  xcolor.green = green*maxGreenValue/MAX_VALUE;
  xcolor.blue = blue*maxBlueValue/MAX_VALUE;

  char str[64];
  sprintf(str,"#%02x%02x%02x",red, green, blue);

  if(useCvt) {
    XtVaSetValues(sampleColor, 
		  XtVaTypedArg, XmNbackground, XtRString, str, strlen(str)+1, 
		  NULL);
  } else {
    XStoreColor(display,cmap,&xcolor);
  }

  /*
  for( int i=0; str[i]; i++ )
    if(str[i] == ' ')
      str[i]='0';
      */

  XmTextSetString(colorText,str);
}


void 
ColorSelect::textValueChanged(Widget , XtPointer )
{
  char *str = XmTextGetString(colorText);
  if(str) {
    if(useCvt) {
      XtVaSetValues(sampleColor, 
		    XtVaTypedArg, XmNbackground, 
		    XtRString, str, strlen(str)+1, 
		    NULL);
      XtVaGetValues(sampleColor, XmNbackground, &xcolor.pixel, NULL);
    } else {
      XStoreNamedColor(display, cmap, str,
		       xcolor.pixel, DoRed|DoGreen|DoBlue);
    }
    XQueryColor(display, cmap, &xcolor);


    XmScaleSetValue(redScale, (xcolor.red*MAX_VALUE)/maxRedValue);
    XmScaleSetValue(greenScale, (xcolor.green*MAX_VALUE)/maxGreenValue);
    XmScaleSetValue(blueScale, (xcolor.blue*MAX_VALUE)/maxBlueValue);
    XtFree(str);
  }
}


void 
ColorSelect::colorSelectOk(Widget , XtPointer )
{
  char *str = XmTextGetString(colorText);
  if(str) {
    textResView->setText(str);
    XtFree(str);
  }
  delete this;
}


void 
ColorSelect::colorSelectCancel(Widget , XtPointer )
{
  delete this;
}


void 
ColorSelect::colorSelectHelp(Widget, XtPointer )
{
  getHelp(HID_COLOR_SELECT);
}





void 
ColorSelect::do_browseSelection(Widget,XtPointer)
{
  int *selection;
  int num;

  if(XmListGetSelectedPos(colorList, &selection, &num)) {
    if(num == 1) {
      XmTextSetString(colorText, *(colorDB[selection[0]-1]));
      textValueChanged(NULL, NULL);
    }
    XtFree((char*)selection);
  }
}


void 
ColorSelect::initColorDB()
{
  if(colorDB.getSize() > 0) {
    for(unsigned int i=0; i<colorDB.getSize(); i++)
      delete colorDB[i];
    colorDB.empty();
  }

  char *path;
  path = XtResolvePathname(XtDisplay(colorList), "", RGB_TXT, "", NULL,
			   NULL, 0, NULL);
  if(path) {
    FILE *fp;
    char colorName[MAX_COLOR_NAME];
    char line[BUFSIZ], *ptr;

    fp = fopen(path, "r");
    if(fp) {
      while(!feof(fp)) {
	if(fgets(line, sizeof(line), fp) != 0) {
	  ptr = line;
	  while(isspace(*ptr) && *ptr) ptr++;
	  if(*ptr == '!' || *ptr == 0)             // comment or empty
	    continue;
	  while(!isspace(*ptr) && *ptr) ptr++;     // skip red
	  while(isspace(*ptr) && *ptr) ptr++;
	  while(!isspace(*ptr) && *ptr) ptr++;     // skip green
	  while(isspace(*ptr) && *ptr) ptr++;
	  while(!isspace(*ptr) && *ptr) ptr++;     // skip blue
	  while(isspace(*ptr) && *ptr) ptr++;
	  if(*ptr == 0)
	    continue;
	  memset(colorName, 0, sizeof(colorName));
	  strncpy(colorName, ptr, sizeof(colorName)-1);
	  
	  for(int i = strlen(colorName)-1; i >= 0; i--) { 
	    if(isspace(colorName[i])) {            // delete succeeding spaces
	      colorName[i] = 0;
	    } else {
	      break;
	    }
	  }
	  colorDB.add(new Lstring(colorName));
	}
      }
      fclose(fp);
    }
    XtFree(path);
  }
  init = 1;

  colorDB.sort();

}
