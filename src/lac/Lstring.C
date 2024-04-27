/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: Lstring.C,v $
 *  $Date: 1999/08/27 15:29:45 $
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
 * $Log: Lstring.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:29:45  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:46  lazy
 * Imported to CVS
 *
 * Revision 1.3  1997/12/14  19:18:24  lazy
 * *** empty log message ***
 *
 * Revision 1.2  1997/12/14  16:06:58  lazy
 * Changed to const char*
 *
 * Revision 1.1  1997/07/25  19:32:19  lazy
 * Initial revision
 *
 */

#include "Lstring.h"
#include <string.h>

Lstring::Lstring(const char *v)
{
  value = NULL;
  len = 0;
  copy(v, strlen(v)+1);
}

Lstring::Lstring(const Lstring &s)
{
  value = NULL;
  len = 0;
  copy(s.value, s.len);
}

Lstring::~Lstring()
{
  delete value;
}


void Lstring::copy(const char *v, size_t len)
{
  if(len > this->len) {
    if(value)
      delete value;
    value = new char[len];
    this->len = len;
  }
  strcpy(value, v);
}

Lstring::operator char*() const
{
  return value;
}

Lstring & Lstring::operator=(const Lstring &s)
{
  copy(s.value, s.len);
  return *this;
}

Lstring & Lstring::operator+=(const Lstring &s)
{
  char tmp[len + s.len];
  strcpy(tmp, value);
  strcat(tmp, s.value);

  copy(tmp, len+s.len);

  return *this;
}

int Lstring::operator==(const Lstring &s) const
{
  return strcmp(value, s.value) == 0;
}

unsigned char 
Lstring::hash() const
{
  unsigned char result = 0;
  for(unsigned int i=0; i<len; i++) {
    result ^= value[i];
  }
  return result;
}

// -----------------------
//      compare()
// -----------------------

int Lstring::compare( const void *r1, const void *r2 )
{
  return strcmp(((Lstring**)r1)[0]->value,  
		((Lstring**)r2)[0]->value);
}
