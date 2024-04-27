/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: msgfile.h,v $
 *  $Date: 1999/08/27 15:30:33 $
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
 * $Log: msgfile.h,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:30:33  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:45  lazy
 * Imported to CVS
 *
 * Revision 1.1  1995/09/27  21:15:27  lazy
 * Initial revision
 *
 */

/* -------------------------------------------
   msgfile.h - Headerfile for parsing algorithm
   ------------------------------------------- */

#ifndef _MSGFILE_H_
#define _MSGFILE_H_

#define MAX_MSG       256

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _YMsg {
  int msgNr;
  char msg[MAX_MSG];
  struct _YMsg *next;
} LMessages;


/* API for parsing algorithm */

/* parse a file named filename and return a result */
LMessages *readMsgFile( char *filename );

/* after calling parse, result structure must be deallocated */
void free_LMessages( LMessages *toFree );

#ifdef __cplusplus
}
#endif

#endif



