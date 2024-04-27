/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: Ltmpl.h,v $
 *  $Date: 1999/08/27 15:31:29 $
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
 * $Log: Ltmpl.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:31:29  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:14  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/25  20:28:51  lazy
 * Initial revision
 *
 */

// -------------------------
// Ltmpl.h 
// Definition of class Ltmpl
//
// (C) Dirk Laessig
// -------------------------

#ifndef _LTMPL_H_
#define _LTMPL_H_

#include <limits.h>
#include <lac/Lobject.h>

class Ltmpl {
private:
  char *text;
  char *filename;

  struct CacheData {
    char path[PATH_MAX];
    char *text;
  };
  static CacheData **cacheData;
  static unsigned int cacheSize;

  static char *findInCache( const  char *filename );
  static void addInCache( const char *filename, const char *text );

  static char *nextChar(char *ptr, char toFind);

public:
  Ltmpl( const char *filename );
  Ltmpl( Ltmpl &toCopy );
  ~Ltmpl();

  const char *getText() { return text; }

  // return false if there is no var
  int insertVariable( const char *var, const char *val );

  int doConditional( const char *var, unsigned char b );

  // search for $(VARIABLE,filename) and replace with $(VARIABLE)
  // buffer filename must be allocated (_POSIX_PATH_MAX)
  int cutFilenameVariable( const char *var, char *filename );


  static void resetCache();           // free all data
                               
};


class LtmplList {
private:
  Ltmpl tmpl;
  Ltmpl **all;
  long size;

  char *result;

public:
  LtmplList(Ltmpl &t);
  LtmplList(char *filename);
  ~LtmplList();
  Ltmpl *add();                      // create a new Ltmpl in all, return it
  char *getResult();                 // return the text of all Ltmpl
};


class Lfile : public Lobject {
private:
  Ltmpl tmpl;
  char filename[PATH_MAX];
  int careOverwrite;
  int fileClass;

public:
  Lfile(Ltmpl &tmpl, char *fName, int careOverwrite, int fileClass);
  char *getFilename() { return filename; }
  int getCareOverwrite() { return careOverwrite; }
  int getFileClass() { return fileClass; }
  int write();
  int fileExist();    
};

#endif /* Don't add stuff after this endif */
