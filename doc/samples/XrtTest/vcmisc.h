/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/* --------------------------------------- */
/* Helpfull functions for generated C-code */
/*                                         */
/* This file was automaticly generated by  */
/* View Designer/X                         */
/*                                         */
/* Don't edit this file, please!           */
/*                                         */
/* --------------------------------------- */
#ifndef VCMISC_H
#define VCMISC_H

#include <X11/Intrinsic.h>


/* --------------------------------------- */
/* getTopLevel() - return TopLevel widget  */
/* --------------------------------------- */

extern Widget getTopLevel(void);



/* --------------------------------------- */
/* manageWidget()                          */
/*                                         */
/* Callback for managing dialogs           */
/*                                         */
/* --------------------------------------- */

extern void manageWidget(Widget, XtPointer, XtPointer);


/* --------------------------------------- */
/* vcDestroyCallback()                     */
/*                                         */
/* Free interface structure                */
/*                                         */
/* --------------------------------------- */

extern void vcDestroyCallback(Widget, XtPointer, XtPointer );




/* --------------------------------------- */
/* createPixmapFromFile()                  */
/* --------------------------------------- */

extern Pixmap createPixmapFromFile(char *);


/* --------------------------------------- */
/* createPixmapFromData()                  */
/* --------------------------------------- */

extern Pixmap createPixmapFromData(char **);



/* --------------------------------------- */
/* vcinit()                                */
/* --------------------------------------- */

extern void vcinit (char *, Cardinal, char **, char *);



/* --------------------------------------- */
/* vcrun()                                 */
/* --------------------------------------- */

extern void vcrun(void);                           
				      

/* --------------------------------------- */
/* cvtResourceFromString()                 */
/* --------------------------------------- */
extern XtArgVal cvtResourceFromString(Widget wg, char *type, char *value);



/* --------------------------------------- */
/* addQuickHelp()                          */
/* --------------------------------------- */

extern void addQuickHelp(Widget);


/* --------------------------------------- */
/* addQuickHelpWidget()                    */
/* --------------------------------------- */

extern void addQuickHelpWidget(Widget);


/* --------------------------------------- */
/* addPopupMenuHandler()                   */
/* --------------------------------------- */

extern void addPopupMenuHandler(Widget menu, Widget parent);

#endif

