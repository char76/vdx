/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
// ------------------------------ 
// HelpView.C                      
// ------------------------------


#include "HelpView.h"
#include <stdio.h>
#include <Xm/Text.h>

HelpView *HelpView::helpView = NULL;

HelpView::HelpText HelpView::helpText[] = {
  { "MainWindow", "helpButton",
    "This is the ToDo List Application\n"},
  { "MainWindow", "form_1",
    "You have pressed key F1"},
  { "ItemView", "helpButton",
    "The Item View shows detail information of a todo list application.\n"},
  { "ItemView", "form_1",
    "The Item View shows detail information of a todo list application.\n"},
  { NULL, NULL, NULL }
};

// ------------------------------
// HelpView()
// ------------------------------

HelpView::HelpView()
:HelpView_base(NULL, NULL, 0) 
{
}


// -------------------------
// showHelp()
// -------------------------

void HelpView::showHelp(char *interface, char *widget)
{
  Boolean found = FALSE;

  if(helpView == NULL)
    helpView = new ::HelpView();
  for(unsigned int i=0; helpText[i].text; i++) {
    if(!strcmp(helpText[i].interface, interface) &&
       !strcmp(helpText[i].widget, widget)) {
      XmTextSetString(helpView->text, helpText[i].text);
      found = TRUE;
      break;
    }
  }
  if(!found) {
    char buf[64+strlen(interface)+strlen(widget)];
    sprintf(buf, "Warning: No help for widget '%s' of interface '%s'",
	    widget, interface);
    XmTextSetString(helpView->text, buf);
  }
  helpView->open();
}

// -------------------------
// close_window()
// -------------------------

void HelpView::close_window(Widget, XtPointer)
{
  close();
}





