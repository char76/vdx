/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: misc.C,v $
 *  $Date: 1999/08/27 15:32:40 $
 *  $Revision: 1.2.2.1 $
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
 * $Log: misc.C,v $
 * Revision 1.2.2.1  1999/08/27 15:32:40  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.2  1998/06/02 16:52:11  lazy
 * Fix getPath() for trailing slash.
 *
 * Revision 1.1.1.1  1998/04/24 23:45:15  lazy
 * Imported to CVS
 *
 * Revision 1.3  1998/03/26 00:31:23  lazy
 * Check for empty string.
 *
 * Revision 1.2  1997/08/31 19:41:59  lazy
 * include <Xm/Xm.h> inserted.
 *
 * Revision 1.1  1997/07/25  20:38:56  lazy
 * Initial revision
 *
 */

// -----------------------------------
// misc.C
//
// Some helpful functions
// (C) Dirk Laessig
// -----------------------------------

#include "misc.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <Xm/Xm.h>
#include <Xm/DragDrop.h>
#include <Xm/Text.h>
#include <Xm/TextF.h>
#include <limits.h>
#include <sys/stat.h>
#include <errno.h>

// --------------------------------------
// withSuffix()
// --------------------------------------

void 
withSuffix(char *buffer, unsigned long len, char *suffix)
{
  if(buffer) {
    int i;
    i = strlen(buffer)-1;                  // index des letzten Zeichens
    while( i>0 ) {                        // rueckwaerts zaehlen
      if(buffer[i] == '.') {
	if(!strcmp(&buffer[i+1], suffix))  // suffix haengt schon 'dran
	  return;
	break;
      }
      if(buffer[i] == '/') 
	break;
      i--;
    }
    if(strlen(buffer)+1+strlen(suffix)+1 <= len) {
      strcat(buffer,".");
      strcat(buffer,suffix);
    }
  }
}


// -------------------------------------------------------------------
// getSuffix()
// -------------------------------------------------------------------

void 
getSuffix(char *buffer, char *suffix, unsigned long &len)
{
  unsigned int l = strlen(buffer);

  for(int i = l-1; i>=0; i--) {
    if(buffer[i] == '/')
      break;
    if(buffer[i] == '.') {
      if(suffix == NULL) {
	len = strlen(&(buffer[i+1]))+1;
	return;
      }
      strcpy(suffix, &(buffer[i+1]));
      return;
    }
  }
  if(suffix == NULL) {
    len = 1;
    return;
  }
  strcpy(suffix, "");
}


// --------------------------------------
// changeSuffix()
// --------------------------------------

void 
changeSuffix(char *buffer, unsigned long len, char *suffix)
{
  if(buffer) {
    int i;
    i = strlen(buffer)-1;                  // index des letzten Zeichens
    while( i>0 ) {                        // rueckwaerts zaehlen
      if(buffer[i] == '.') {
	buffer[i] = 0;
	break;
      }
      if(buffer[i] == '/') 
	break;
      i--;
    }
    if(strlen(buffer)+1+strlen(suffix)+1 <= len) {
      strcat(buffer,".");
      strcat(buffer,suffix);
    }
  }
}


// --------------------------------------
// withoutSuffix()
// --------------------------------------

void 
withoutSuffix(char *buffer)
{
  if(buffer) {
    int i;
    i = strlen(buffer)-1;                  // index des letzten Zeichens
    while( i>0 ) {                        // rueckwaerts zaehlen
      if(buffer[i] == '.') {
	buffer[i] = 0;
	break;
      }
      if(buffer[i] == '/') 
	break;
      i--;
    }
  }
}


// --------------------------------------
// getBasename()
// --------------------------------------

void 
getBasename(char *buffer)
{
  char tmp[strlen(buffer)+1];
  if(buffer) {
    int i;
    i = strlen(buffer)-1;                  // index des letzten Zeichens
    strcpy(tmp, buffer);
    while( i>0 ) {                        // rueckwaerts zaehlen
      if(buffer[i] == '/') {
	strcpy(tmp, &buffer[i+1]);
	break;
      }
      i--;
    }
    strcpy(buffer,tmp);
  }
}


// -----------------------------
// getPath()
// -----------------------------

void 
getPath(char *fullPath, char *path, unsigned long len)
{
  char tmp[strlen(fullPath)+1];
  if(fullPath) {
    int i;
    strcpy(tmp, fullPath);
    i = strlen(tmp)-1;                  // index des letzten Zeichens
    if(tmp[i] == '/') {
      tmp[i] = 0;
      i--;
    }
    while( i>=0 ) {                        // rueckwaerts zaehlen
      if(tmp[i] == '/') {
	tmp[i+1] = 0;
	break;
      }
      i--;
    }
    if(i<0) 
      tmp[0] = 0;

    if(strlen(tmp)+1 > len) {
      fprintf(stderr,"Warning: getPath()\n");
      return;
    }
    strcpy(path,tmp);
  }
}



// ---------------------------------------
// dropSiteFix()
// ---------------------------------------

void 
dropSiteFix(Widget wg, Boolean activate)
{
#ifndef hpux  
  if(XmIsText(wg) || XmIsTextField(wg)) {
    Arg args[3];
    Cardinal n=0;
    XRectangle rect;

    if(activate) {
      rect.x = 0;
      rect.y = 0;
      XtVaGetValues(wg,
		    XmNwidth, &rect.width,
		    XmNheight, &rect.height,
		    NULL);
      XtSetArg(args[n], XmNdropSiteActivity, XmDROP_SITE_ACTIVE); n++;
      XtSetArg(args[n], XmNnumDropRectangles, 1); n++;
      XtSetArg(args[n], XmNdropRectangles, &rect); n++;
    } else {
      XtSetArg(args[n], XmNdropSiteActivity, XmDROP_SITE_INACTIVE); n++;
      XtSetArg(args[n], XmNnumDropRectangles, 0); n++;
      XtSetArg(args[n], XmNdropRectangles, NULL); n++;
    }
    XmDropSiteUpdate(wg, args, n);
  } else {
    if(XtIsComposite(wg)) {
      WidgetList children;
      Cardinal numChildren, i;
      
      XtVaGetValues(wg,
		    XmNchildren, &children,
		    XmNnumChildren, &numChildren,
		    NULL);
      for( i=0; i<numChildren; i++)
	dropSiteFix(children[i],activate);
    }
  }
#endif
}



// ---------------------------------------
// replaceForRF()
// ---------------------------------------

void 
replaceForRF(char *src, char *dest, unsigned long &len)
{
  char *ptr1, *ptr2;
  unsigned long retLen = 0;
  ptr1 = src;
  ptr2 = dest;
  
  while(*ptr1) {
    switch(*ptr1) {
    case '\n':
      if(ptr2) {
	ptr1++;
	*ptr2++ = '\\';
	*ptr2++ = 'n';
      } else {
	retLen += 2;
	ptr1++;
      }
      break;
    default:
      if(ptr2) {
	*ptr2++ = *ptr1++;
      } else {
	retLen++;
	ptr1++;
      }
      break;
    }
  }
  if(ptr2)
    *ptr2 = 0;
  else
    len = retLen+1;
}


// -------------------------------------------------------------------
//
// getUserName(char *buf, size_t buffer_size);
//
// --------------------------------------------------------------------

void 
getUserName(char *buf, size_t &buffer_size)
{
  uid_t uid;
  struct passwd *pwent;
  char tmp[16];

  uid = getuid();
  pwent = getpwuid(uid);

  if(pwent == NULL || pwent->pw_name == NULL)
    sprintf(tmp, "%d", uid);

  if(buf == NULL) {
    if(pwent && pwent->pw_name)
      buffer_size = strlen(pwent->pw_name)+1;
    else
      buffer_size = strlen(tmp)+1;
  } else {
    if(pwent && pwent->pw_name)
      strcpy(buf, pwent->pw_name);
    else
      strcpy(buf, tmp);
    buffer_size = strlen(buf)+1;
  }
}

// -------------------------------------------------------------------
//
// createPath(file)
//
// file - to filename for that the path should be created
// return errno on failure or zero on success
//
// --------------------------------------------------------------------

int 
createPath(char *file)
{
  char path[PATH_MAX];
  int ret = 0;
  struct stat s;

  if(file[0] == 0) {
    return ENOENT;
  } 

  getPath(file, path, sizeof(path));
  
  if(stat(path, &s) < 0) {
    if(errno == ENOENT) {
      if(mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO) < 0) {
	if(errno == ENOENT) {
	  ret = createPath(path);
	  if(ret == 0) {
	    if(mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO) < 0)
	      ret = errno;
	  }
	} else {
	  ret = errno;
	}
      }
    } else {
      ret = errno;
    }
  } else {
    if(!S_ISDIR(s.st_mode))
      ret = ENOTDIR;
  }
  
  return ret;
}
