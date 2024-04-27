/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
// ----------------------------------------
// Main programm 
// 
// This file was automaticly generated.
// ----------------------------------------

/*



*/

#include <stdio.h>

#include "ToolBoxSample.h"

char *fallback = 
#include "Xfetest_res.h"
;

// ---------------------------
//      main()
// ---------------------------

main(int argc, char **argv)
{
  VcView::init("Xfetest", argc, argv, fallback);    // init X-Toolkit


  ToolBoxSample *mw = new ToolBoxSample();          // build startup interface
  mw->open();                                 // show it

  VcView::run();                             // run Application mainloop
}
