/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: LHashDictionary.h,v $
 *  $Date: 1999/08/27 15:29:36 $
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
 * $Log: LHashDictionary.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:29:36  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:46  lazy
 * Imported to CVS
 *
 * Revision 1.3  1998/03/30 19:09:06  lazy
 * *** empty log message ***
 *
 * Revision 1.2  1997/12/14  19:17:15  lazy
 * It works.
 *
 * Revision 1.1  1997/12/14  17:32:18  lazy
 * Initial revision
 *
 */

#ifndef LHASHDICTIONARY_H
#define LHASHDICTIONARY_H

#include <lac/TArray.h>
#include <lac/Lstring.h>

// -------------------------------------------------
// This template class stores pointers of
// element class. The key is always a Lstring
//
// ToDo: add() shound check the unique constrained
//       remove(const Lstring &)
// -------------------------------------------------
template <class T>
class LHashDictionaryIterator;

template <class T>
class LHashDictionary {
private:
  struct Item {                 // Nested Type Item to store the value
    Lstring key;
    T value;
  };

  TArray<Item> arrays[256];     // The Arrays

public:

  void add(const Lstring &key, const T &value) {  // Add a value by reference
    T foo;
    if(find(key, foo))
      return;
    Item *i = new Item;
    i->key = key;
    i->value = value;
    arrays[key.hash()].add(i);
  }

  int find(const Lstring &key, T &value) { // find a value and return the referance
    unsigned char h;
    h = key.hash();

    for(unsigned int i=0; i<arrays[h].getSize(); i++) {
      Item* item = arrays[h][i];
      if(item->key == key) {
	value = item->value;
	return 1;
      }
    }
    return 0;
  }

  friend class LHashDictionaryIterator<T>;
};



template <class T>
class LHashDictionaryIterator
{
private:
  unsigned int arraysIndex;
  unsigned int index;
  int valid;

  LHashDictionary<T> &dict;

public:
  LHashDictionaryIterator(LHashDictionary<T> &d) : dict(d) {
    valid = 0;
    for(unsigned int i=0; i<256; i++) {
      if(dict.arrays[i].getSize()) {
	arraysIndex = i;
	index = 0;
	valid = 1;
	break;
      }
    }
  }

  int isValid() { return valid; }

  int operator() () {
    index++;
    for(unsigned int i = arraysIndex; i<256; i++) {
      for(unsigned int j = index; j<dict.arrays[i].getSize(); j++) {
	arraysIndex = i;
	index = j;
	valid = 1;
	return valid;
      }
      index = 0;
    }
    valid = 0;
    return valid;
  }

  int get(Lstring &key, T &value) {
    if(valid) {
      key = dict.arrays[arraysIndex][index]->key;
      value = dict.arrays[arraysIndex][index]->value;
      return valid;
    }
    return valid;
  }
};

#endif
