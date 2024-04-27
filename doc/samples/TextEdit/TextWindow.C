/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
// ------------------------------ 
// TextWindow.C                      
// ------------------------------


#include "TextWindow.h"
#include <stdio.h>

// needed by stat()
#include <sys/stat.h>
#include <unistd.h>

// needed by XmText* functions of Motif
#include <Xm/Text.h>

// needed by XmInternAtom() and XmAddWMProtocolCallback() 
#include <Xm/Protocols.h>


// ------------------------------
// createTextWindow()
// ------------------------------

TextWindow *createTextWindow(Widget parent, ArgList args, Cardinal n)
{
  return new TextWindow(parent,args,n);
}


// ------------------------------
// TextWindow()
// ------------------------------

TextWindow::TextWindow(Widget wg, ArgList args, Cardinal n)
:TextWindow_base(wg,args,n) 
{
  Atom atom;

  hasChanged = FALSE;
  strcpy(filename, "");
  updateTitleBar();

  // If a user closes the window by window mananger menu 
  // (WM_DELETE_WINDOW), we should be notified.

  // Tell the shell widget that we will handle the WM_DELETE_WINDOW.
  XtVaSetValues(popupShell,
		XmNdeleteResponse, XmDO_NOTHING,
		NULL);

  // To understand the window manager we have to ask the XServer:
  // what is the id (Atom) of string "WM_DELETE_WINDOW"
  atom = XmInternAtom(XtDisplay(popupShell), "WM_DELETE_WINDOW", TRUE);
  if(!atom)
    printf("Fatal Error: Can't find WM_DELETE_WINDOW\n");

  // Now we add a window manager callback to get the notify if
  // the WM message arrives
  XmAddWMProtocolCallback(popupShell, atom, wmDelete, this);
}


// -------------------------
// wmDelete() - WM callback
// -------------------------
void TextWindow::wmDelete(Widget, XtPointer client_data, XtPointer)
{
  ::TextWindow *self = (::TextWindow*)client_data;
  
  // show the exit dialog
  XtManageChild(self->exitDialog);
}

// -------------------------
// do_save()
// -------------------------

void TextWindow::do_save(Widget, XtPointer)
{
  if(filename[0]) {
    saveFile(filename);
  } else {
    XtManageChild(fileSaveAsDialog);
  }
}


// -------------------------
// do_cut()
// -------------------------

void TextWindow::do_cut(Widget, XtPointer)
{
  XmTextCut(textWidget, CurrentTime);
}


// -------------------------
// do_copy()
// -------------------------

void TextWindow::do_copy(Widget, XtPointer)
{
  XmTextCopy(textWidget, CurrentTime);
}


// -------------------------
// do_paste()
// -------------------------

void TextWindow::do_paste(Widget, XtPointer)
{
  XmTextPaste(textWidget);
}


// -------------------------
// text_changed()
// -------------------------

void TextWindow::text_changed(Widget, XtPointer)
{
  if(!hasChanged) {
    hasChanged = TRUE;
    updateTitleBar();
  }
}


// -------------------------
// do_exit()
// -------------------------

void TextWindow::do_exit(Widget, XtPointer)
{
  exit(0);
}


// -------------------------
// do_open()
// -------------------------

void TextWindow::do_open(Widget, XtPointer)
{
  char buf[MY_PATH_MAX];

  getFSBfilename(fileOpenDialog, buf);
  if(buf[0]) {
    loadFile(buf);
  }
}


// -------------------------
// do_saveAs()
// -------------------------

void TextWindow::do_saveAs(Widget, XtPointer)
{
  char buf[MY_PATH_MAX];

  getFSBfilename(fileSaveAsDialog, buf);
  if(buf[0]) {
    saveFile(buf);
  }
}


// ####### 

// -------------------------
// updateTitleBar()
// -------------------------

void TextWindow::updateTitleBar()
{
  char str[MY_PATH_MAX+1];

  if(filename[0] == 0) {   // empty filename
    strcpy(str, "untitled.txt");
  } else {
    strcpy(str, filename);
  }
  if(hasChanged)
    strcat(str, "*");
  XtVaSetValues(getTop(), XmNtitle, str, NULL);
}

// -------------------------
// loadFile()
// -------------------------

Boolean TextWindow::loadFile(char *fname)
{
  struct stat st;
  FILE *fp;
  Boolean readOnly;

  if(stat(fname, &st) < 0) {
    perror("stat");
    return FALSE;
  }

  char buf[st.st_size + 1];

  if(access(fname, W_OK) < 0) {
    readOnly = TRUE;
  } else {
    readOnly = FALSE;
  }

  fp = fopen(fname, "r");
  if(fp == NULL) {
    perror("fopen");
    return FALSE;
  }
  
  if((size_t)st.st_size > fread(buf, sizeof(char), st.st_size, fp)) {
    perror("fread");
    fclose(fp);
    return FALSE;
  }

  buf[st.st_size] = 0;
  XmTextSetString(textWidget, buf);
  XtVaSetValues(textWidget, XmNeditable, !readOnly, NULL);
  XtSetSensitive(saveButton, !readOnly);
  XtSetSensitive(saveAsButton, !readOnly);
  XtSetSensitive(cutButton, !readOnly);
  XtSetSensitive(pasteButton, !readOnly);
  fclose(fp);

  strcpy(filename, fname);
  hasChanged = FALSE;
  updateTitleBar();
  return TRUE;
}

// ------------------------
// saveFile()
// ------------------------

Boolean TextWindow::saveFile(char *fname)
{
  char *str;
  size_t len;
  FILE *fp;

  str = XmTextGetString(textWidget);
  len = strlen(str);

  fp = fopen(fname, "w");
  if(fp == NULL) {
    perror("fopen");
    XtFree(str);
    return FALSE;
  }

  if(len > fwrite(str, sizeof(char), len, fp)) {
    perror("fwrite");
    XtFree(str);
    fclose(fp);
    return FALSE;
  }

  XtFree(str);

  if(fclose(fp) == EOF) {
    perror("fclose");
    return FALSE;
  }
  return TRUE;
}


// ------------------------
// getFSBfilename()
// ------------------------

void TextWindow::getFSBfilename(Widget wg, char buf[MY_PATH_MAX])
{
  char *str;
  XmString xms = NULL;

  XtVaGetValues(wg, XmNtextString, &xms, NULL);

  strcpy(buf, "");
  if(xms) {
    XmStringGetLtoR(xms, XmSTRING_DEFAULT_CHARSET, &str);
    if(str) {
      if(strlen(str) < MY_PATH_MAX) {
	strcpy(buf, str);
      }
      XtFree(str);
    }
    XmStringFree(xms);
  }
}
