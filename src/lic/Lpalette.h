/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: Lpalette.h,v $
 *  $Date: 1999/08/27 15:31:17 $
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
 * $Log: Lpalette.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:31:17  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:14  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/25  20:27:11  lazy
 * Initial revision
 *
 */

// -------------------------------
// Lpalette.h
// (C) Dirk Laessig
// Definition of class Lpalette
// -------------------------------

#ifndef _LPALETTE_H_
#define _LPALETTE_H_

#include "Lwidget.h"
#include <lac/IconView.h>
#include <lac/LicView.h>

#define PALETTE_DEFAULT_NAME "Templates.pal"

// ############# Lpalette #############

class Lpalette : public TreeNode<Lwidget> {
private:
  char name[PATH_MAX];
  Boolean aNew;

public:
  Lpalette();
  Lpalette(char* filename);

  Boolean save(char *filename = NULL);
  void myAdd(Lwidget *lw);

  char *getFilename() { return name; }
  void setFilename(char *n = NULL);

  Boolean isNew() { return aNew; }
  char *getClassName() { return "Lpalette"; }
};


#if(0)
// ############# PaletteView ##########

class PaletteView : public LicView {
private:
  Lpalette *lpalette;
  WidgetRef form;
  Ref<IconView> lwidgets;
  static RefArray<PaletteView> allViews;

  void dropSiteRegister();
  static void dropProc(Widget wg, XtPointer client, XtPointer call);
  static void transferProc(Widget w, XtPointer closure, 
			   Atom *seltype, Atom *type,
			   XtPointer value, unsigned long *length, 
			   int *format);
  
public:
  PaletteView( Lpalette *model );
  ~PaletteView();
  
  void act( char *action );
  void update( unsigned long ) {}

  static Lpalette *findPalette( Widget dropOver );

  virtual Boolean saveSize() { return TRUE; }
  char *getName() { return "PaletteView"; }

};


#endif

#endif /* DONT ADD STUFF .. */
