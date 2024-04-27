/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: TextEdit.C,v $
 *  $Date: 1999/08/27 15:31:59 $
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
 * $Log: TextEdit.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:31:59  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:15  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/25  20:31:01  lazy
 * Initial revision
 *
 */

#include <Xm/Text.h>
#include <Xm/ToggleB.h>

#include "lic.h"
#include "TextEdit.h"
#include "LresEditor.h"

RefArray<TextEdit> TextEdit::allViews;

// ---------------------------------
//        TextEdit()
// ---------------------------------

TextEdit::TextEdit(ValueView *trv) 
:TextEdit_base(NULL,NULL,0), textResView(NULL,this)
{
  unsigned long len;

  LicView::quickHelpLabel = quickHelpLabel;
  allViews.add(this);
  textResView = trv;
  
  textResView->getText(NULL, len);
  char str[len];
  textResView->getText(str,len);
  
  XmTextSetString(text,str);
}


// ---------------------------------
//        delNotify()
// ---------------------------------

void TextEdit::delNotify(BaseRef*)
{
  delete this;
}


// ---------------------------------
//        saveAndExit()
// ---------------------------------

void TextEdit::saveAndExit(Widget, XtPointer)
{
  char *str;

  str = XmTextGetString(text);
  if(str) {
    textResView->setText(str);
    XtFree(str);
  }

  delete this;
}


// ---------------------------------
//        cutText()
// ---------------------------------

void TextEdit::cutText(Widget, XtPointer)
{
  XmTextCut(text, CurrentTime);
}


// ---------------------------------
//        copyText()
// ---------------------------------

void TextEdit::copyText(Widget, XtPointer)
{
  XmTextCopy(text, CurrentTime);
}


// ---------------------------------
//        pasteText()
// ---------------------------------

void TextEdit::pasteText(Widget, XtPointer)
{
  XmTextPaste(text);
}


// ---------------------------------
//        helpMe()
// ---------------------------------

void TextEdit::helpMe(Widget, XtPointer)
{
  getHelp(HID_TEXT_EDITOR);
}


// ---------------------------------
//        quickHelpChanged()
// ---------------------------------

void TextEdit::quickHelpChanged(Widget, XtPointer)
{

}


// ---------------------------------
//        doExit()
// ---------------------------------

void TextEdit::doExit(Widget, XtPointer)
{
  delete this;
}


// ---------------------------------
//        helpCallback()
// ---------------------------------

void TextEdit::helpCallback(Widget wg, XtPointer)
{
  printf("Callback TextEdit::helpCallback called by widget '%s'.\n",
         XtName(wg));
}


// ---------------------------------
//        importFile()
// ---------------------------------

void TextEdit::importFile(Widget wg, XtPointer)
{
  XmString xmstr;
  char *filename;

  XtVaGetValues(wg, 
		XmNtextString, &xmstr,
		NULL );
  XmStringGetLtoR( xmstr, XmSTRING_DEFAULT_CHARSET, &filename );
  
  if(filename) {
    FILE *fp;
    char *t;
    size_t size;
    
    fp = fopen(filename, "r");
    if( fp ) {
      fseek( fp, 0, SEEK_END );          // a kind of getting file size
      size = ftell(fp);
      rewind(fp);
      
      t = new char[size+1];                    // create buffer and read
      fread(t, sizeof(char), size, fp);
      t[size]=0;
      fclose(fp);
      
      XmTextInsert(text, XmTextGetCursorPosition(text), t);
      delete t;
    } else
      printf("Can't open file '%s' for reading.\n", filename);
  }
}


// ---------------------------------
//        exportFile()
// ---------------------------------

void TextEdit::exportFile(Widget wg, XtPointer)
{
  XmString xmstr;
  char *filename;
  char title[256];
  char msg[1024];
  char *t;
  FILE *fp;
  Boolean confirm = TRUE;

  XtVaGetValues(wg, 
		XmNtextString, &xmstr,
		NULL );
  XmStringGetLtoR( xmstr, XmSTRING_DEFAULT_CHARSET, &filename );
  
  if(filename) {
    t = XmTextGetString(text);
    if(t) {
      fp = fopen(filename, "r");
      if(fp) {
	msgCat->getMsg( title, QUERY_OVERWRITE_TITLE );
	msgCat->getMsg( msg, QUERY_OVERWRITE, filename );
	
	if( MSGBOX_OK == LicView::MsgBox(title, msg, MSGBOX_STYLE_YESNO))
	  confirm = TRUE;
	else
	  confirm = FALSE;

	fclose(fp);
      }
      fp = fopen(filename, "w");
      if( fp && confirm ) {
	fwrite(t, sizeof(char), strlen(t), fp);
	fclose(fp);
      } else
	printf("Can't open file '%s' for writing.\n", filename);
      XtFree(t);
    }
  }
}


void 
TextEdit::do_onHelp(Widget, XtPointer)
{
  getHelp(HID_USING_HELP);
}

void 
TextEdit::do_onContext(Widget, XtPointer)
{
  contextHelp();
}

