/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: TArray.C,v $
 *  $Date: 1999/08/27 15:30:14 $
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
 * $Log: TArray.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:30:14  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:45  lazy
 * Imported to CVS
 *
 * Revision 1.1  1995/09/27  21:12:31  lazy
 * Initial revision
 *
 */

// TArray.C


#include <stdio.h>

#include "TArray.h"

// -----------------------------
class View;
class Selectable;
class SensitiveRec;

TArray<View> vi;
TArray<Selectable> sl;
TArray<SensitiveRec> sv;

