/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: IconView.h,v $
 *  $Date: 1999/08/27 15:29:34 $
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
 * $Log: IconView.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:29:34  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:46  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/25  19:32:02  lazy
 * Initial revision
 *
 */

#ifndef _IconView_H_
#define _IconView_H_

#include <lac/Model.h>
#include <lac/SensitiveView.h>
#include <lac/ConModel.h>

// ----------------------------------------
//         Icon
// This define an icon ;-)
// ----------------------------------------
class IconView;

class Icon : public SensitiveRec {
private:
  Iconable *m;              // the model
  IconView *iconView;

  Dimension offset;         // Text offset in OneRow-Mode
  Dimension width, height;

  Ref<PixmapRecView> pixmap;
  Ref<TextRecView>   text;

public:
  Icon(Iconable *am, IconView *iv);
  Icon();                           // creates a dummy icon
  ~Icon();

  void draw(Boolean asSelected = FALSE);
  void update( unsigned long flags );
  void configure();

  void setPosition( Position x, Position y );
  Dimension getWidth();
  Dimension getHeight();
  Boolean isIn( Position x, Position y );
  Boolean isBefore(Position x, Position y);
  void highlightBefore(Boolean state);

  void edit(Position x, Position y, Boolean state);

  virtual Icon* copy( Iconable *am, IconView *iv);

  char *getName() { return "IconView"; }
};

// -----------------------------------------
//           IconView
// -----------------------------------------

class IconView : public SensitiveContainer {
private:
  ContainerBase *m;

  Dimension spacing;              // space between icons
  Dimension shadow;               // icons with shadows
  Boolean names;                  // icons with names
  Boolean oneRow;                 // one row geometry
  Boolean withIcons;              // show icons
  Boolean withSmallIcons;         // show small icons

  Ref<Icon> icon;

  void calculate();               // calc the icon positions
  Dimension getMinWidth();        // max width of icons
  Dimension getParentWidth();     // return scrolledWindow Size

public:
  IconView( ContainerBase *cm, Widget p, Icon *icon=NULL );
  ~IconView();
  void setModel(ContainerBase *m);

  void update( unsigned long flags );
  void act( char *){}
  
  void configure();               // fit icons to window size

  // visiblility attributes

  Boolean getWithNames() { return names; }
  void setWithNames( Boolean wn ) { names=wn; update(CONTAINER_CHANGED); }

  Boolean getWithIcons() { return withIcons; }
  void setWithIcons(Boolean b) 
  { withIcons = b; update(CONTAINER_CHANGED); }

  Boolean getWithSmallIcons() { return withSmallIcons; }
  void setWithSmallIcons(Boolean b) 
  { withSmallIcons = b; update(CONTAINER_CHANGED); }

  void setSpacing( Dimension space ) { spacing=space; configure(); }
  Dimension getSpacing() { return spacing; }

  void setShadow( Dimension sh ) { shadow=sh; update(CONTAINER_CHANGED); }
  Dimension getShadow() { return shadow; }

  void setOneRow( Boolean r ) { oneRow = r; configure(); }
  Boolean getOneRow() { return oneRow; }
};



#endif
