/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: Lstring.h,v $
 *  $Date: 1999/08/27 15:29:46 $
 *  $Revision: 1.1.1.1.2.2 $
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
 * $Log: Lstring.h,v $
 * Revision 1.1.1.1.2.2  1999/08/27 15:29:46  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1.2.1  1998/07/01 18:31:39  lazy
 * Patches gcc 2.8
 *
 * Revision 1.1.1.1  1998/04/24 23:45:46  lazy
 * Imported to CVS
 *
 * Revision 1.3  1997/12/14  19:18:05  lazy
 * Insert header.
 *
 */

#ifndef _Lstring_H_
#define _Lstring_H_

#include <stdlib.h>

class Lstring {
private:
  char *value;
  size_t len;

  void copy(const char *value, size_t len);

public:
  Lstring(const char *v = "");
  Lstring(const Lstring &);
  ~Lstring();

  size_t getLen() { return len-1; }
  operator char*() const;
  Lstring & operator=(const Lstring &);
  Lstring & operator+=(const Lstring &);
  int operator==(const Lstring &) const;
  int operator==(const char *r) const { return operator==(Lstring(r)); }

  unsigned char hash() const;

  // ------------- to sort --------------
  static int compare( const void *r1, const void *r2 );
};



#endif
