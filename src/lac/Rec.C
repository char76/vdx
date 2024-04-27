/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: Rec.C,v $
 *  $Date: 1999/08/27 15:30:03 $
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
 * $Log: Rec.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:30:03  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:45  lazy
 * Imported to CVS
 *
 * Revision 1.1  1995/09/27  21:11:18  lazy
 * Initial revision
 *
 */

/* -----------------------------------
     Class Rec

     (C) Dirk Laessig
   ----------------------------------- */


#include <lac/Rec.h>

// ----------------------------
//     zoom()
// ----------------------------
void Rec::zoom( Position z )
{
  if( z > 0 ) {
    x = x*z;
    y = y*z;
    width = width*z;
    height = height*z;
    return;
  } 
  if( z < 0 ) {
    z = -z;
    x = x/z;
    y = y/z;
    width = width/z;
    height = height/z;
    return;
  }
  // Wenn z==0, dann laeuft er durch
}

// -------------------------------
//     gridX()
// -------------------------------
void Rec::gridX( Dimension g )
{
  x = x + ( ( x%g > g/2 ) ? (g - x%g) : -(x%g) );
}

// -------------------------------
//     gridY()
// -------------------------------
void Rec::gridY( Dimension g )
{
  y = y + ( ( y%g > g/2 ) ? (g - y%g) : -(y%g) );
}

// -------------------------------
//     gridWidth()
// -------------------------------
void Rec::gridWidth( Dimension g )
{
  width = width + ( ( width%g > g/2 ) ? (g - width%g) : -(width%g) );
}

// -------------------------------
//     gridHeight()
// -------------------------------
void Rec::gridHeight( Dimension g )
{
  height = height + ( ( height%g > g/2 ) ? (g - height%g) : -(height%g) );
}

// -------------------------------
//    isIn()
// -------------------------------
Boolean Rec::isIn( Position px, Position py )
{
  return ( px >= x && px <= x+width && py >= y && py <= y+height );
}
