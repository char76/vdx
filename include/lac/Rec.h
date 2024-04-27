/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: Rec.h,v $
 *  $Date: 1999/08/27 15:30:04 $
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
 * $Log: Rec.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:30:04  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:45  lazy
 * Imported to CVS
 *
 * Revision 1.1  1995/09/27  21:11:27  lazy
 * Initial revision
 *
 */

/* ---------------------------------------
     Class Rec

     (C) Dirk Laessig
   --------------------------------------- */

#ifndef _REC_H_
#define _REC_H_

#include <X11/Intrinsic.h>

class Rec {
private:
  Position x, y;
  Dimension width, height;

public:
  Rec() { x=0; y=0; width=0; height=0; }
  Rec( Position ax, Position ay, Dimension awidth = 0, Dimension aheight = 0 )
    { x=ax; y=ay; width=awidth; height=aheight; }

  void setPosition( Position ax, Position ay ) { x = ax; y = ay; }
  void setDimension( Dimension w, Dimension h ) { width = w; height = h; }

  Position getX() { return x; }
  Position getY() { return y; }
  Dimension getWidth() { return width; }
  Dimension getHeight() { return height; }

  void getPosition( Position &ax, Position &ay ) { ax = x; ay = y; }
  void getDimension( Dimension &w, Dimension &h ) { w = width; h = height; }
  
  void zoom( Position z );
  void gridX( Dimension g );
  void gridY( Dimension g );
  void gridWidth( Dimension g );
  void gridHeight( Dimension g );

  Boolean isIn( Position x, Position y );
}; /* end of class Rec */


#endif /* DON'T ADD ... */
