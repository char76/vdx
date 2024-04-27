/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
/* --------------------------------------------- */
/*  parse.h    -   Interface zum Parsen von      */
/*                 Dateien                       */
/*  Projekt: LIC                                 */
/*  (C) Dirk Laessig, 1994                       */
/* --------------------------------------------- */
#ifndef _PARSE_H_
#define _PARSE_H_

#ifdef __cplusplus
extern "C" {
#endif

#define LIC_LANG_MAX      64
#define LIC_NAME_MAX      64
#define LIC_ATTRIB_MAX    16
#define LIC_MANAGED_MAX   16
#define LIC_QUICKHELP_MAX 256

#include <limits.h>

/* YResource is a item in a linked list */

typedef struct _YResource {
  char name[LIC_NAME_MAX];      /* resource_name */
  char *value;              /* resource_value in string presentation  */
  char attrib[LIC_ATTRIB_MAX];  /* public/private                         */
  struct _YResource *next;      /* pointer to next element of linked list */
} YResource; 



/* YWidget is a node of a tree */

typedef struct _YWidget {
  char name[LIC_NAME_MAX];          /* the widget name                */
  char widget_class[LIC_NAME_MAX];  /* the widget class               */
  char managed[LIC_MANAGED_MAX];    /* TRUE or FALSE                  */
  char quickhelp[LIC_QUICKHELP_MAX];/* quickhelp text                 */
  int helpId;                       /* associated help id             */
  char *description;                /* description of a widget        */
  struct _YResource *first_res;     /* linked list of resources       */
  struct _YWidget   *first_child;   /* linked list of children        */
  struct _YWidget   *next;          /* pointer to next child          */
  struct _YWidget   *parent;        /* hold the parent 
				       ( only nessesary for parsing ) */
  char *viewData;                   /* view depended data   (->Model) */
} YWidget;


/* YMethod is a structure for a method in the interface */

typedef struct _YMethod {
  char name[LIC_NAME_MAX];   /* name and signature of the method */
  char *code;                /* code of the method               */
  struct _YMethod *next;     /* next item in the linked list     */
} YMethod;


/* YInterface is a item in a linked list */

typedef struct _YInterface {
  char filename[PATH_MAX];
  struct _YInterface *next;
} YInterface;


/* YModule is a item in a linked list */

typedef struct _YModule {
  char filename[PATH_MAX];
  struct _YModule *next;
} YModule;


/* YPalette */

typedef struct _YPalette {
  char name[LIC_NAME_MAX];        
  struct _YWidget *first_widget; 
} YPalette; 


/* YResult is a structure, that is created while parsing a file */

typedef struct _YResult {
  YWidget *root_widget;             /* the root of the widget tree         */
  YMethod *first_method;            /* first item of method list           */
  YInterface *first_interface;      /* first item of a linked list         */
  char palette[PATH_MAX];           /* palette                             */
  char helpfile[PATH_MAX];          /* help resources                      */
  char lang[LIC_LANG_MAX];          /* language of project                 */
  YModule *first_module;            /* first item of a linked list         */
  char startup[PATH_MAX];           /* startup interface                   */
  char parseError[256];             /* if the first character is   
				       not zero then parsing failed        */
  char sourcedir[PATH_MAX];         /* the directory in which the source is
				       generated 			   */
  char appl_class[PATH_MAX];        /* application class of project        */
  char exec_file[PATH_MAX];         /* name of the executable              */
  char *more_source;                /* additional source code              */
  char *extra_cc_options;           /* additional compiler options         */
  char *extra_ld_options;           /* additional linker options           */
  char *extra_libraries;            /* additional libraries                */
  char *description;                /* project description                 */
  char *global_resources;           /* resources like font, bg, ...        */
  int error;                        /* the errno, on success == 0          */
} YResult;


/* ------------------------ */
/*       API functions      */
/* ------------------------ */
YResult *parse( char *filename );      /* parse the file and return result */
int writeFile( char *filename, YResult *toWrite );
                                       /* write parseable file */
void free_YResult( YResult * );        /* free allocated memory */
void m_strcpy( char **destination, char *source ); 
                                       /* strcpy() with free & malloc */

/* copy the string in a static char* and replaces all matching substrings
   'find' with the substring 'replace'                                    */
 
char *cpyAndReplace(const char *toCopy, char *find, char *replace);

#ifdef __cplusplus
}
#endif

#endif




