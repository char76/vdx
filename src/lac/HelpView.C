/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: HelpView.C,v $
 *  $Date: 1999/08/27 15:29:32 $
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
 * $Log: HelpView.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:29:32  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:46  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/25  19:31:48  lazy
 * Initial revision
 *
 * Revision 1.1  1995/09/27  21:03:51  lazy
 * Initial revision
 *
 */

// ----------------------------------------
// Main programm 
// 
// This file was generated by
// MLX View Composer (C) 1995 Dirk Laessig
// ----------------------------------------

#include <stdio.h>

#include "MLXHelp.h"


// ---------------------------
//      main()
// ---------------------------

main(int argc, char **argv)
{
  LicView::init("HelpView",argc,argv );    // init X-Toolkit

  if(argc > 2) {
    fprintf(stderr, "Usage: %s filename\n", argv[0]);
    exit(0);
  }

  MLXHelp *mw;
  if( argc == 2 )
    mw = new MLXHelp(argv[1]);          // build startup interface
  else 
    mw = new MLXHelp();       
  mw->open();                                  // show it

  LicView::run();                              // run Application mainloop
}
