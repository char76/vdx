/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/****************************************************************
 *
 *  $RCSfile: write.c,v $
 *  $Date: 1999/08/27 15:33:17 $
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
 * $Log: write.c,v $
 * Revision 1.1.1.1.2.1  1999/08/27 15:33:17  dirk
 * Transform the copyright to GPL
 *
 * Revision 1.1.1.1  1998/04/24 23:45:51  lazy
 * Imported to CVS
 *
 * Revision 1.2  1997/07/25  19:39:14  lazy
 * Header inserted.
 *
 */

/* -------------------------------------------- */
/* write.c - implementation of api writeFile()  */
/* (C) Dirk Laessig 1995                        */
/* -------------------------------------------- */

#include "parse.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

static int writeWidget( FILE *fp, YWidget *w, char *spaces );
static int writeResource( FILE *fp, YResource *r, char *spaces );
static int writeMethod( FILE *fp, YMethod *m );
static int writeInterface( FILE *fp, YInterface *i );
static int writeModule( FILE *fp, YModule *m );

#define DOIT(s) if(0 == s) { error = errno; return error; }
#define PREP(s) cpyAndReplace(s, "\"", "\\\"")

/* -------------------------------
   
         writeFile()

   ------------------------------- */

int writeFile( char *filename, YResult *toWrite )
{
  FILE *fp;
  int error = 0;

  if( !filename || !toWrite )
    return EINVAL;
  
  fp = fopen( filename, "w" );
  if(fp == NULL)
    return errno;

  if( toWrite->root_widget )
    error = writeWidget( fp, toWrite->root_widget, "" );
  if(error) return error;

  if( toWrite->first_method )
    error = writeMethod( fp, toWrite->first_method );
  if(error) return error;

  if( toWrite->palette[0] )
    DOIT(fprintf( fp, "PALETTE \"%s\"\n", PREP(toWrite->palette) ));

  
  if( toWrite->first_interface )
    error = writeInterface( fp, toWrite->first_interface );
  if(error) return error;
  
  if( toWrite->first_module )
    error = writeModule( fp, toWrite->first_module );
  if(error) return error;
  
  if( toWrite->lang[0] )
    DOIT(fprintf( fp, "LANG \"%s\"\n", PREP(toWrite->lang) ));

  if( toWrite->startup[0] )
    DOIT(fprintf( fp, "STARTUP \"%s\"\n", PREP(toWrite->startup) ));

  if( toWrite->helpfile[0] )
    DOIT(fprintf( fp, "HELPFILE \"%s\"\n", PREP(toWrite->helpfile) ));

  if( toWrite->sourcedir[0] )
    DOIT(fprintf( fp, "SOURCEDIR \"%s\"\n", PREP(toWrite->sourcedir) ));
  
  if( toWrite->appl_class[0] )
    DOIT(fprintf( fp, "APPL_CLASS \"%s\"\n", PREP(toWrite->appl_class) ));
  
  if( toWrite->exec_file[0] )
    DOIT(fprintf( fp, "EXEC_FILE \"%s\"\n", PREP(toWrite->exec_file) ));
  
  if( toWrite->more_source )
    DOIT(fprintf( fp, "MORE_SOURCE \"%s\"\n", PREP(toWrite->more_source) ));
  
  if( toWrite->extra_cc_options )
    DOIT(fprintf( fp, "EXTRA_CC_OPTIONS \"%s\"\n", PREP(toWrite->extra_cc_options) ));

  if( toWrite->extra_ld_options )
    DOIT(fprintf( fp, "EXTRA_LD_OPTIONS \"%s\"\n", PREP(toWrite->extra_ld_options) ));

  if( toWrite->extra_libraries )
    DOIT(fprintf( fp, "EXTRA_LIBRARIES \"%s\"\n", PREP(toWrite->extra_libraries) ));

  if( toWrite->description )
    DOIT(fprintf( fp, "DESCRIPTION \"%s\"\n", PREP(toWrite->description) ));

  if( toWrite->global_resources )
    DOIT(fprintf( fp, "GLOBAL_RESOURCES \"%s\"\n", PREP(toWrite->global_resources) ));

  if(fclose( fp ))
    return errno;
  return 0; /* ok */
}


/* ------------------------ 

       writeWidget()

   ------------------------ */
int writeWidget( FILE *fp, YWidget *w, char *spaces )
{
  char sp[256];
  int error = 0;

  strcpy( sp, spaces );
  strcat( sp, "  " );     /* add two spaces */

  DOIT(  fprintf( fp, "%sWIDGET {\n", spaces ));
  DOIT(  fprintf( fp, "%sNAME \"%s\"\n", sp, PREP(w->name) ));
  DOIT(  fprintf( fp, "%sCLASS \"%s\"\n", sp, PREP(w->widget_class) ));
  DOIT(  fprintf( fp, "%sMANAGED \"%s\"\n", sp, PREP(w->managed) ));
  DOIT(  fprintf( fp, "%sQUICKHELP \"%s\"\n", sp, PREP(w->quickhelp) ));
  DOIT(  fprintf( fp, "%sHELPID \"%d\"\n", sp, w->helpId ));
  DOIT(  fprintf( fp, "%sVIEWDATA \"%s\"\n",sp, PREP(w->viewData) ));
  if( w->description )
    DOIT(fprintf( fp, "%sDESCRIPTION \"%s\"\n", sp, PREP(w->description) ));


  if( w->first_res )
    error = writeResource( fp, w->first_res, sp );
  if(error) return error;

  if( w->first_child )
    error = writeWidget( fp, w->first_child, sp );
  if(error) return error;

  DOIT(fprintf( fp, "%s}\n", spaces ));

  if( w->next )
    error = writeWidget( fp, w->next, spaces );
  return error;
}


/* ------------------------ 

       writeMethod()

   ------------------------ */
int writeMethod( FILE *fp, YMethod *m )
{
  int error = 0;
  DOIT(  fprintf( fp, "METHOD\n" ));
  DOIT(  fprintf( fp, "\"%s\"\n", PREP(m->name) ));
  DOIT(  fprintf( fp, "\"%s\"\n", PREP(m->code) ));
  if( m->next )
    error = writeMethod( fp, m->next );
  return error;
}

/* ------------------------ 

       writeInterface()

   ------------------------ */
int writeInterface( FILE *fp, YInterface *i )
{
  int error = 0;
  DOIT(fprintf( fp, "INTERFACE \"%s\"\n", PREP(i->filename) ));
  if( i->next )
    error = writeInterface( fp, i->next );
  return error;
}

/* ------------------------ 

       writeModule()

   ------------------------ */
int writeModule( FILE *fp, YModule *m )
{
  int error = 0;
  DOIT(fprintf( fp, "MODULE \"%s\"\n", PREP(m->filename) ));
  if( m->next )
    error = writeModule( fp, m->next );
  return error;
}


/* ------------------------ 

       writeResource()

   ------------------------ */
int writeResource( FILE *fp, YResource *r, char *spaces )
{
  int error = 0;

  DOIT(fprintf( fp, "%s%s \"%s\" %s\n", spaces, r->name, PREP(r->value), r->attrib));
  if( r->next )
    error = writeResource( fp, r->next, spaces );
  return error;
}


/* -------------------

      m_strcpy()

   ------------------- */

void m_strcpy( char **destination, char *source )
{
  if( *destination ) 
    free( *destination );
  *destination = (char*)malloc(sizeof(char) * (strlen(source)+1));
  strcpy(*destination, source);
}

