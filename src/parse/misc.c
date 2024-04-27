/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/***************************************
 * Little helpful functions
 **************************************/

#include "parse.h"
#include <string.h>
#include <stdlib.h>

char *cpyAndReplace(const char *toCopy, char *find, char *replace) 
{
  size_t currentLen, newLen, replaceLen, findLen;
  const char *ptr, *source;
  char *target;
  static char *holdStr = NULL;

  currentLen = strlen(toCopy);
  replaceLen = strlen(replace);
  findLen = strlen(find);

  ptr = toCopy;
  newLen = currentLen;
  while((ptr = strstr(ptr, find))) {   /* query the new size of the string */
    newLen += replaceLen;
    newLen -= findLen;
    ptr += findLen;
  }
  
  if(holdStr) 
    free(holdStr);
  holdStr = (char*)malloc(sizeof(char)*newLen + 1);

  source = toCopy;
  target = holdStr;
  while((ptr = strstr(source, find))) {           /* do the working */
    memcpy(target, source, ptr-source);
    target += ptr-source;
    memcpy(target, replace, replaceLen);
    target += replaceLen;
    source = ptr + findLen;
  }
  ptr = toCopy + currentLen;                      /* the last character */
  memcpy(target, source, ptr-source);             /* copy the tail      */
  target += ptr-source;
  *target = '\0';

  return holdStr;
}
