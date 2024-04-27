/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
// ----------------------------------------
// Main programm 
// 
// This file was automaticly generated.
// ----------------------------------------

#include <stdio.h>

#include "TextWindow.h"

char *fallback = 
#include "Textedit_res.h"
;

// ---------------------------
//      main()
// ---------------------------

main(int argc, char **argv)
{
  VcView::init("Textedit", argc, argv, fallback);    // init X-Toolkit

  if(argc > 2) {
    fprintf(stderr, "usage: %s [filename]\n", argv[0]);
    exit(1);
  }

  TextWindow *mw = new TextWindow();          // build startup interface
  mw->open();                                 // show it

  if(argc == 2) {
    // there is a parameter on the command line
    mw->loadFile(argv[1]);
  }

  VcView::run();                             // run Application mainloop
}
