/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: VersionControl.h,v $
 *  $Date: 1999/08/27 15:32:11 $
 *  $Revision: 1.1.1.1.2.1 $
 *
 *  Copyright 1997, Dirk Laessig
 *  ALL RIGHTS RESERVED
 *  See the file Copyright for more information
 *
 *  Dirk Laessig
 *  Goettingstr. 5
 *  38106 Braunschweig
 *  Germany
 ****************************************************************/
/*
 * $Log: VersionControl.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:32:11  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:16  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/09/02  18:21:21  lazy
 * Initial revision
 *
 */

Boolean 
openFileHook(char *file);

Boolean
saveFileHook(char *file);

Boolean
closeFileHook(char *file);


