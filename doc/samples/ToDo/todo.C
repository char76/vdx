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

#include "MainWindow.h"
#include "ToDoList.h"

char *fallback = 
#include "Todo_res.h"
;

// ---------------------------
//      main()
// ---------------------------

main(int argc, char **argv)
{
  ToDoList toDoList;

  VcView::init("Todo", argc, argv, fallback);    // init X-Toolkit

  MainWindow *mw = new MainWindow(toDoList);    // build startup interface
  mw->open();                                 // show it

  VcView::run();                             // run Application mainloop
}
