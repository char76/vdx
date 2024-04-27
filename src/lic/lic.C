/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: lic.C,v $
 *  $Date: 1999/08/27 15:32:32 $
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
 * $Log: lic.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:32:32  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:13  lazy
 * Imported to CVS
 *
 * Revision 1.2  1998/03/30 19:08:53  lazy
 * *** empty log message ***
 *
 * Revision 1.1  1997/07/25  20:37:50  lazy
 * Initial revision
 *
 */

/* ------------------------------------
   lic.C
   
   Main program of LIC
   (C) Dirk Laessig, 1994
   ------------------------------------ */

//#define __USE_BSD

#include <stdio.h>
#include <locale.h>
#include <unistd.h>
#include <errno.h>

#include "Lproject.h"
#include "LApp.h"
#include "MainWindow.h"
#include "lic.h"
#include "Lcreator.h"
#include "Converter.h"
#include "AgreeWindow.h"
#include <lac/Lstring.h>
#include "MegaPipe.h"
#include "lic_gen.h"

#ifdef CDE_WIDGETS
#include <Dt/Term.h>
#endif

// -------------------------
//   Globale Variable
// -------------------------

LApp *app;
MsgCat *msgCat;
MainWindow *mainWindow;
int rd_fd;
FILE *oldout;

char *fallback_resources =
#include "fallback.h"
;

// -------------------------
//   sig_handler()
// -------------------------
void
sig_handler(int s)
{
  if(oldout)
    fprintf(oldout, "Signal %d received. Closing application.\n", s);
  if(app)
    app->exit();
}

// -------------------------
//   errorHandler()
// -------------------------
int 
errorHandler(Display *display, XErrorEvent *errorEvent)
{
  char msg[1024];
  XGetErrorText(display, errorEvent->error_code, msg, sizeof(msg));
  fprintf(stderr, "Xlib-Error: %s\n",msg);
  return 0;
}


// ---------------------------
//      main()
// ---------------------------

int main(int argc, char **argv)
{
  struct sigaction saction;

  checkForGenerateMode(argc, argv);

  oldout = fdopen(dup(fileno(stdout)), "w");
  rd_fd = redirectOutput();

  saction.sa_handler = (void (*)(int))sig_handler;
  saction.sa_flags = 0;
  sigemptyset(&saction.sa_mask);
  sigaction(SIGINT, &saction, NULL);
  sigaction(SIGTERM, &saction, NULL);
  sigaction(SIGHUP, &saction, NULL);

#ifdef CDE_WIDGETS
  DtTermInitialize();
#endif


  Widget topLevel =                  // init X-Toolkit
    LicView::init( APPL_CLASS,argc,argv, fallback_resources ); 
  XSetErrorHandler(errorHandler);

  addConverter(topLevel);

  setlocale(LC_ALL, "");
  XtSetLanguageProc(XtWidgetToApplicationContext(topLevel), NULL, NULL);

  msgCat = new MsgCat(XtDisplay(LicView::getTopLevel()));

  app = new LApp(argc, argv);             // make new Application

  if(app->firstExecution()) {
    AgreeWindow agree;
    agree.close();
  }

  if(app->isDemo()) {
    char msg[1024];
    char title[256];
    
    msgCat->getMsg(title, "DEMO_DIALOG_TITLE");
    msgCat->getMsg(msg  , "DEMO_DIALOG_MSG");
    
    LicView::MsgBox(title, msg, MSGBOX_STYLE_OK);
  }

  mainWindow = new MainWindow( app );  // build startup interface
  mainWindow->open();                                      // show it

  LicView::run();                           // run Application mainloop

}


#if 0
extern "C" void exit(int status)
{
  if(status == 0)
    _exit(0);
  printf("exit(%d)\n", status);
}
#endif
