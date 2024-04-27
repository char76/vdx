/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: TFuncSort.h,v $
 *  $Date: 1999/08/27 15:30:17 $
 *  $Revision: 1.1.1.1.2.1 $
 *
 *  Copyright 1997 1998, Dirk Laessig
 *  ALL RIGHTS RESERVED
 *  See the file Copyright for more information
 *
 *  Dirk Laessig
 *  Muehlenpfordtstr. 5
 *  38106 Braunschweig
 *  Germany
 ****************************************************************/
/*
 * $Log: TFuncSort.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:30:17  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:46  lazy
 * Imported to CVS
 *
 * Revision 1.1  1998/02/10  01:03:50  lazy
 * Initial revision
 *
 */

#include <lac/TArray.h>
#include <lac/ConModel.h>
#include <lac/RefArray.h>

// ---------------------------------------
// Template function to sort an RefArray
//
// Use the funtion at the end of this file
// ---------------------------------------

template <class ContainerClass, class ItemClass> void 
tSort(ContainerClass &array, TSortArray<ItemClass> &tmp)
{
  // Transfer item pointers to tmp

  for(unsigned int i=0; i<array.getSize(); i++) {
    tmp.add(array[i]);
  }

  // make array empty 

  array.empty();

  // sort the tmp array

  tmp.sort();

  // Transfer contents back

  for(unsigned int i=0; i<tmp.getSize(); i++) {
    array.add(tmp[i]);
  }
}


//
// Sort a RefArray
// 

template <class ItemClass> void
tSort(RefArray<ItemClass> &array)
{
  TSortArray<ItemClass> tmp;
  tSort(array, tmp);
}


// 
// Sort a container
//

template <class ItemClass> void
tSort(Container<ItemClass> &array)
{
  TSortArray<ItemClass> tmp;
  tSort(array, tmp);
}



