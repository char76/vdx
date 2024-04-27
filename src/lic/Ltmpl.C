/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: Ltmpl.C,v $
 *  $Date: 1999/08/27 15:31:28 $
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
 * $Log: Ltmpl.C,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:31:28  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:13  lazy
 * Imported to CVS
 *
 * Revision 1.1  1997/07/25  20:28:48  lazy
 * Initial revision
 *
 */

// -----------------------------
// Ltmpl.h 
// Implementation of class Ltmpl
//
// (C) Dirk Laessig
// -----------------------------

#include <stdio.h>
#include <string.h>
#include "Ltmpl.h"
#include <errno.h>
#include "misc.h"

#ifndef SEEK_END
#define SEEK_END 2
#endif

Ltmpl::CacheData **Ltmpl::cacheData = NULL;
unsigned int Ltmpl::cacheSize = 0;

// -----------------------------------
//        Ltmpl()
// -----------------------------------
Ltmpl::Ltmpl( const char *filename )
{
  FILE *fp;
  char *cacheHit = NULL;
  long size;

  text = NULL;
  this->filename = new char[strlen(filename)+1];
  strcpy(this->filename, filename);

  if( (cacheHit = findInCache(filename)) ) {
    text = new char[strlen(cacheHit)+1];
    strcpy(text,cacheHit);
  } else {
    fp = fopen( filename, "r" );                // open the file
    if( !fp ) {
      text = new char[1];    
      *text = 0;
      return;
    }
    fseek( fp, 0, SEEK_END );                   // a kind of getting file size
    size = ftell(fp);
    rewind(fp);
    
    text = new char[size+1];                    // create buffer and read
    fread( text, sizeof(char), size, fp );
    text[size]=0;

    fclose(fp);
//    addInCache(filename,text);
  }
}

// -----------------------------------
//        Ltmpl( Ltmpl& )
// -----------------------------------
Ltmpl::Ltmpl( Ltmpl &toCopy )
{
  this->filename = new char[strlen(toCopy.filename)+1];
  strcpy(this->filename, toCopy.filename);

  if(toCopy.text) {
    this->text = new char[strlen(toCopy.text)+1];
    strcpy(this->text, toCopy.text);
  } else {
    this->text = NULL;
  }
}


// -----------------------------------
//        ~Ltmpl()
// -----------------------------------
Ltmpl::~Ltmpl()
{
  delete filename;
  delete text;
}

// -----------------------------------
//      insertVariable()
// -----------------------------------
int Ltmpl::insertVariable( const char *var, const char *val )
{
  register char *ptr;
  char *end, *cpy;

  ptr = text;
  while(*ptr) {
    if( *ptr == '$' ) {
      ptr++;
      if( *ptr && *ptr == '(' ) {
	ptr++;
	if( *ptr && !strncmp(ptr, var, strlen(var))) {
	  end = ptr + strlen(var);
	  if( *end && *end == ')' ) {   // ok, found
	    ptr -=2 ;
	    end++;
	    cpy = new char[strlen(text)-strlen(var)-3+strlen(val)+1];
	    memcpy( cpy, text, ptr-text );  // copy the first part
	    cpy[ptr-text] = 0;
	    strcat( cpy, val );     // copy the value of variable
	    ptr = cpy+strlen(cpy);  // new search
	    strcat( cpy, end );     // copy the end
	    delete text;            // deallocate the old buffer
	    text = cpy;             // set instance variable
	  } else
	    ptr++;
	} else
	  ptr++;
      } else
	ptr++;
    } else 
      ptr++;
  }
  return 1;
}

// -----------------------------------
//      nextChar()
// -----------------------------------

char *Ltmpl::nextChar(char *aPtr, char toFind)
{
  int count=0, flag=0;
  char *ptr = aPtr;
  
  while( *ptr ) {
    if(!flag) {
      if(toFind == *ptr && count == 0) 
	return ptr;
      switch(*ptr) {
      case '\\': 
	flag = 1; break;
      case '(':
	count++; break;
      case ')':
	count--; break;
      }
    } else
      flag = 0;
    ptr++;
  }
  return NULL;
}


// -----------------------------------
//      doConditional()
// -----------------------------------
int Ltmpl::doConditional( const char *var, unsigned char b )
{
  register char *ptr, *ptr2;
  char *end, *cpy, *begin, *first, *last ;
  int newSize;

  ptr = text;
  while(*ptr) {
    if( *ptr == '$' ) {
      first = ptr;
      ptr++;
      if( *ptr && *ptr == '(' ) {
	ptr++;
	if( *ptr && !strncmp(ptr, var, strlen(var))) {
	  ptr += strlen(var);
	  if( *ptr && *ptr == ',' ) {   // ok, found
	    if( b ) {                  // erster Zweig
	      if(*(ptr+1)) 
		begin = ptr + 1;
	      else
		return 1;
	      end = nextChar(begin,',');
	      if(!end)
		return 1;
	      end--;
	      last = nextChar(end+1,')');
	      if(!last || !*(last+1))
		return 1;
	      last++;
	    } else {
	      if(*(ptr+1)) 
		ptr++;
	      else
		return 1;
	      begin = nextChar(ptr,',');
	      if(!begin || !*(begin+1))
		return 1;
	      begin++;
	      end = nextChar(begin,')');
	      if(!end)
		return 1;
	      last = end+1;
	      end--;
	    }
	    newSize = first-text +end-begin+1 +text+strlen(text)+1-last +1;
	    cpy = new char[newSize];
	    memset(cpy, 0, newSize);
	    ptr = text;
	    ptr2 = cpy;
	    strncpy(ptr2, ptr, first-text);
	    if(end>=begin) {
	      newSize = end-begin+2;
	      char buf[newSize];
	      memset(buf,0,newSize);
	      ptr = begin;
	      ptr2 = buf;
	      while(ptr<=end) {
		if(*ptr=='\\')
		  ptr++;
		if(ptr>end)
		  break;
		*ptr2 = *ptr;
		ptr2++;
		ptr++;
	      }
	      strcat(cpy,buf);
	    }
	    ptr = cpy + strlen(cpy);
	    strcat(cpy,last);
	    delete text;
	    text = cpy;
	  } else
	    ptr++;
	} else
	  ptr++;
      } else
	ptr++;
    } else 
      ptr++;
  }
  return 1;
}



// -----------------------------------
//      catFilenameVariable()
// -----------------------------------
int Ltmpl::cutFilenameVariable( const char *var, char *filename )
{
  char *ptr, *end, *cpy;
  
  ptr = text;
  while(*ptr) {
    if( *ptr == '$' ) {
      ptr++;
      if( *ptr && *ptr == '(' ) {
	ptr++;
	if( *ptr && !strncmp(ptr, var, strlen(var))) {
	  ptr = ptr + strlen(var);

	  if( *ptr && *ptr == ',' ) {   // ok, found

	    for(end = ptr; *end && *end != ')' ; end++ );  // find the end
	    if( !*end )
	      return 0;

	    strncpy(filename,ptr+1,end-ptr-1);   // save the filename
	    filename[end-ptr-1] = 0;

	    cpy = new char[strlen(text)-(end-ptr)+1];
	    memcpy( cpy, text, ptr-text );  // copy the first part
	    cpy[ptr-text] = 0;
	    strcat( cpy, end );     // copy the end
	    delete text;            // deallocate the old buffer
	    text = cpy;             // set instance variable

	    return 1;

	  } else
	    ptr++;
	} else
	  ptr++;
      } else
	ptr++;
    } else 
      ptr++;
  }
  return 0;
}


// -----------------------------------
//      resetCache()
// -----------------------------------
void Ltmpl::resetCache()
{
  for( unsigned int i=0; i<cacheSize; i++ ) {
    delete cacheData[i]->text;
    delete cacheData[i];
  }
  delete cacheData;
  cacheSize = 0;
  cacheData = NULL;
}

// -----------------------------------
//      findInCache()
// -----------------------------------
char *Ltmpl::findInCache( const char *filename )
{
  for( unsigned int i=0; i<cacheSize; i++ ) {
    if( !strcmp( cacheData[i]->path, filename ) )
      return cacheData[i]->text;
  }
  return NULL;
}

// -----------------------------------
//      addInCache()
// -----------------------------------
void Ltmpl::addInCache( const char *filename, const char *text )
{
  CacheData **old = cacheData;
  unsigned int i;
  cacheSize++;
  cacheData = new CacheData*[cacheSize];
  for( i=0; i<cacheSize-1; i++ ) {
    cacheData[i] = old[i];
  }
  cacheData[i] = new CacheData;
  strcpy(cacheData[i]->path,filename);
  cacheData[i]->text = new char[strlen(text)+1];
  strcpy(cacheData[i]->text,text);
}


// ###############################################                           
//              LtmplList
// ###############################################

// -----------------------------------
//      LtmplList()
// -----------------------------------
LtmplList::LtmplList(Ltmpl &t)
:tmpl(t)
{
  all = NULL;
  result = NULL;
  size = 0;
}

// -----------------------------------
//      LtmplList()
// -----------------------------------
LtmplList::LtmplList(char *filename)
:tmpl(filename)
{
  all = NULL;
  result = NULL;
  size = 0;
}

// -----------------------------------
//      LtmplList()
// -----------------------------------
LtmplList::~LtmplList()
{
  for( int i=0; i<size; i++ )
    delete all[i];
  delete all;
  delete result;
}

// -----------------------------------
//      add()
// -----------------------------------
Ltmpl *LtmplList::add()
{
  int i;
  Ltmpl **old = all;

  size++;
  all = new Ltmpl*[size];
  for( i=0; i<size-1; i++ )
    all[i] = old[i];
  all[i] = new Ltmpl(tmpl);
  delete old;
  return all[i];
}

// -----------------------------------
//      getResult()
// -----------------------------------
char *LtmplList::getResult()
{
  int i;
  unsigned long bufferSize = 0;
  delete result;
  
  for( i=0; i<size; i++ )                        // query size of all texts
    bufferSize += strlen( all[i]->getText() );
  bufferSize++;                                  // zero terminated
  result = new char[bufferSize];
  result[0] = 0;
  for( i=0; i<size; i++ )
    strcat( result, all[i]->getText() );         // fill the buffer
  return result;
}
  


// -----------------------------------
//      Lfile()
// -----------------------------------
Lfile::Lfile(Ltmpl &t, char *fName, int careOverwrite, int fileClass)
:tmpl(t)
{
  this->fileClass = fileClass;
  this->careOverwrite = careOverwrite;
  strcpy(filename, fName);
}

// -----------------------------------
//      write()
// -----------------------------------
int Lfile::write()
{
  FILE *fp;
  int ret;

  ret = createPath(filename);
  if(ret != 0)
    return ret;

  fp = fopen(filename, "w");
  if(fp) {
    unsigned int len = strlen(tmpl.getText());
    if(fwrite(tmpl.getText(), 1, len, fp) < len) {
      int ret = errno;
      fclose(fp);
      return ret;
    }
    if(fclose(fp) != 0)
      return errno;
    return 0;
  }
  return errno;
}



// -----------------------------------
//      fileExist()
// -----------------------------------
int Lfile::fileExist()
{
  FILE *fp;

  fp = fopen(filename, "r");
  if(fp) {
    fclose(fp);
    return 1;
  }
  return 0;
}
