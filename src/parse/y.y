%{
/* ------------------------------------------------------- */
/*                 y.y or y.tab.c                          */
/*   parsing algorithm for LIC				   */
/*   (C) Dirk Laessig, 1994                                */
/* ------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include "parse.h"                      /* global definitions */
#define YYSTYPE char* 	                /* $1,.. are character pointers */
#define YYERROR_VERBOSE 1
#define YYDEBUG 1

extern YYSTYPE yytext;

YResource 	*a_res = NULL;          /* current resource */
YWidget 	*a_widget = NULL;       /* current widget */
YWidget		*root_widget = NULL;    /* root widget of the tree */
YWidget		*parent_widget = NULL;  /* parent widget of the current */
YMethod		*first_method = NULL;   /* beginning of global linked list */
YMethod		*current_method = NULL; /* current method */
YInterface	*first_interface = NULL;/* beginning of global linked list*/
YInterface	*current_interface = NULL; /* current interface */
YModule  	*first_module = NULL;   /* beginning of global linked list*/
YModule 	*current_module = NULL; /* current module */

YResult		*current_result = NULL; /* the return of parsing */
/* char palette[PATH_MAX];
char lang[LIC_LANG_MAX];
char startup[PATH_MAX];
char helpfile[PATH_MAX];
char sourcedir[PATH_MAX]; */

char parseError[256];
char *buffer;      

/* -------------------- */
/* Forward declarations */
/* -------------------- */

void bracket_open();       /* adding a tree node in a widget tree          */
void bracket_close();      /* restore parameters for the parent            */
void add_resource();       /* add resource to the linked list 
			      of the current widget                        */
void add_method();         /* add method to global linked list for methods */
void add_interface();	   /* add a interface to global data               */
void add_module();	   /* add a module to global data                  */
YResource *new_resource(); /* allocate structure and initialize it to zero */
YWidget *new_widget();     
YMethod *new_method();
YInterface *new_interface();
YModule *new_module();
void browse_widget( YWidget * );    /* debuging function                   */
void free_YWidget( YWidget *wg );   /* recursive function to free 
					a widget tree                      */

%}    /* end of C-declaration */



%token WIDGET
%token NAME
%token STRING
%token CLASS
%token INTERFACE
%token MODULE
%token STARTUP
%token RES_NAME
%token BRACKET_OPEN
%token BRACKET_CLOSE
%token CODE
%token PALETTE
%token LANG
%token MANAGED
%token QUICKHELP
%token PALETTE_INFO
%token VIEWDATA
%token HELPID
%token HELPFILE
%token SOURCEDIR
%token METHOD

%token APPL_CLASS
%token EXEC_FILE
%token MORE_SOURCE
%token EXTRA_CC_OPTIONS
%token EXTRA_LD_OPTIONS
%token EXTRA_LIBRARIES
%token DESCRIPTION
%token GLOBAL_RESOURCES

%token COMBI
%token NOBRACK

%%
input:	interfacefile
	| palette_root
	| projectfile       /* project file      */
;

interfacefile:   widget methods
;

methods: method
	| methods method
;

method: |
	METHOD		{ add_method(); }
	string		{ strcpy(current_method->name, buffer); }
	string		{ current_method->code = strdup(buffer); }
;

projectfile:	palette 
		items 
		lang 
		startup 
		helpfile 
		sourcedir 
		appl_class
		exec_file
		more_source 
		extra_cc_options 
		extra_ld_options
		extra_libraries
		project_description
		global_resources
;

appl_class: |
	APPL_CLASS string { strcpy(current_result->appl_class, buffer); }

exec_file: |
	EXEC_FILE string { strcpy(current_result->exec_file, buffer); }

more_source: |
	MORE_SOURCE string { m_strcpy(&current_result->more_source, buffer); }

extra_cc_options: |
	EXTRA_CC_OPTIONS string { m_strcpy(&current_result->extra_cc_options, buffer); }

extra_ld_options: |
	EXTRA_LD_OPTIONS string { m_strcpy(&current_result->extra_ld_options, buffer); }

extra_libraries: |
	EXTRA_LIBRARIES string { m_strcpy(&current_result->extra_libraries, buffer); }

project_description: |
	DESCRIPTION string { m_strcpy(&current_result->description, buffer); }

global_resources: |
	GLOBAL_RESOURCES string { m_strcpy(&current_result->global_resources, buffer); }

helpfile: |
	  HELPFILE string { strcpy(current_result->helpfile, buffer); }

sourcedir: |
	  SOURCEDIR string { strcpy(current_result->sourcedir, buffer); }

items:	|
	| item
	| items item
;

item:	interface_name
	| module
;

module:	MODULE	{ add_module(); }
	string  { strcpy(current_module->filename,buffer); }
;

palette: | 
	PALETTE	 string 	{ strcpy(current_result->palette,buffer); }
;

lang:    |
	LANG  string 	{ strcpy(current_result->lang,buffer); }
;

startup: |
	STARTUP  string 	{ strcpy(current_result->startup,buffer); }
;

palette_root: 	WIDGET
		BRACKET_OPEN 		{ bracket_open(); }
		children	
		BRACKET_CLOSE 		{ bracket_close(); }
;	

interface_name: INTERFACE 	{ add_interface(); }
           string     	{ strcpy(current_interface->filename,buffer); }
;

widget: WIDGET
	BRACKET_OPEN 		{ bracket_open(); }	
	parameters 
	BRACKET_CLOSE 		{ bracket_close(); }
;

parameters:  	naming 
		| naming resources
		| naming resources children
		| naming children
;

children: widget
	| children widget
;

resources: 	resource
		| resources resource
;

naming:  NAME 
	 string 	{ strcpy( a_widget->name, buffer ); }
	 CLASS
	 string 	{ strcpy( a_widget->widget_class, buffer ); }
	 MANAGED
	 string		{ strcpy( a_widget->managed, buffer ); }
	 QUICKHELP
	 string		{ strcpy( a_widget->quickhelp, buffer ); }
	 helpid
	 VIEWDATA
	 string		{ m_strcpy( &a_widget->viewData, buffer ); }
	 widget_description
;

widget_description: |
	DESCRIPTION string { m_strcpy(&a_widget->description, buffer); }

helpid: |
	 HELPID
	 string		{ a_widget->helpId = atoi(buffer); }
;	

resource:		{ add_resource(); }
	 	name  	{ strcpy( a_res->name, buffer ); } 
		string  { m_strcpy( &a_res->value, buffer ); }
		name	{ strcpy( a_res->attrib, buffer ); }
;

name:	RES_NAME 	{ m_strcpy(&buffer,yytext);};
string: STRING 		{ m_strcpy(&buffer,yytext+1); buffer[strlen(buffer)-1]=0;};

%%

#include <stdio.h>
#include <ctype.h>

int yyerror( char * s ) {    /* is needed ????? */
  printf("%s\n", s );
  strcpy( parseError, s);

  yyclearin;
  return 0;
}

/* ------------------------------------- */
/*              new_resource()           */
/* ------------------------------------- */
YResource *new_resource()
{
	YResource *w;

	w = (YResource*)malloc(sizeof(YResource));
	memset( w, 0, sizeof(YResource));
	return w;
}

/* ------------------------------------- */
/*              new_widget()             */
/* ------------------------------------- */
YWidget *new_widget() 
{
	YWidget *w;

	w = (YWidget*)malloc(sizeof(YWidget));
	memset( w, 0, sizeof(YWidget) );
	w->helpId = -1;
	return w;
}


/* ------------------------------------- */
/*              new_method()             */
/* ------------------------------------- */
YMethod *new_method() 
{
	YMethod *w;

	w = (YMethod*)malloc(sizeof(YMethod));
	memset( w, 0, sizeof(YMethod) );
	return w;
}

/* ------------------------------------- */
/*              new_interface()          */
/* ------------------------------------- */
YInterface *new_interface() 
{
	YInterface *w;

	w = (YInterface*)malloc(sizeof(YInterface));
	memset( w, 0, sizeof(YInterface) );
	return w;
}

/* ------------------------------------- */
/*              new_module()             */
/* ------------------------------------- */
YModule *new_module() 
{
	YModule *w;

	w = (YModule*)malloc(sizeof(YModule));
	memset( w, 0, sizeof(YModule) );
	return w;
}


/* ------------------------------------- */
/*             bracket_open()            */
/* ------------------------------------- */
void bracket_open()
{ 
	YWidget *tmp;

	if( !a_widget ) { /* das erste Widget */
		a_widget = new_widget();
		parent_widget = a_widget;
		root_widget = a_widget;
	} else
		if( parent_widget && !parent_widget->first_child ) {  
		/* das erste Kind */
			a_widget = new_widget();
			parent_widget->first_child = a_widget;
			a_widget->parent = parent_widget;
			parent_widget = a_widget;
		} else {  			/* hat schon Kinder */
			if( parent_widget && parent_widget->first_child ) {    
				a_widget = new_widget();
				for( tmp = parent_widget->first_child;
					tmp->next ; tmp = tmp->next );
				tmp->next = a_widget;
				a_widget->parent = parent_widget;
				parent_widget = a_widget;
			} else {  /* kann nicht sein */
				printf("fatal error: no parent\n");
			}
		}
}

/* ----------------------------- */
/*       bracket_close()         */
/* ----------------------------- */
void bracket_close()
{
	parent_widget = parent_widget->parent;
}

/* ---------------------------- */
/*	    add_resource()	*/
/* ---------------------------- */
void add_resource()
{
	YResource *tmp;

	a_res = new_resource();
	if( a_widget->first_res ) {
		for( tmp = a_widget->first_res; tmp->next ; tmp = tmp->next );
		tmp->next = a_res;
	} else 
		a_widget->first_res = a_res;
}

/* ------------------------ */
/*    add_method()          */
/* ------------------------ */
void add_method()
{
	YMethod *tmp;
	
	tmp = current_method;
	current_method = new_method();
	if( tmp ) {                /* adding an entry */
		tmp->next = current_method;
	} else {                   /* the first entry */
		first_method = current_method;
	}
}

/* ------------------------ */
/*     add_interface()      */
/* ------------------------ */
void add_interface()
{
	YInterface *tmp;
	
	tmp = current_interface;
	current_interface = new_interface();
	if( tmp ) {                /* adding an entry */
		tmp->next = current_interface;
	} else {                   /* the first entry */
		first_interface = current_interface;
	}
}

/* ------------------------ */
/*     add_module()      */
/* ------------------------ */
void add_module()
{
	YModule *tmp;
	
	tmp = current_module;
	current_module = new_module();
	if( tmp ) {                /* adding an entry */
		tmp->next = current_module;
	} else {                   /* the first entry */
		first_module = current_module;
	}
}

/* ------------------------ */
/*        parse()           */
/* ------------------------ */
extern FILE *yyin;
YResult *parse( char *filename ) {
	YResult *ret;
	struct stat mystat;
	current_result = ret = (YResult *)malloc(sizeof(YResult));
	memset( ret, 0, sizeof(YResult) );

	if(stat(filename, &mystat) < 0) {
		ret->error = errno;
		return(ret);	
	}	
	if(S_ISDIR(mystat.st_mode)) {
		ret->error = EISDIR;
		return(ret);
	}
	yyin = fopen(filename, "r");
	if( !yyin ) {
		ret->error = errno;
		return(ret);	
	}

	parseError[0] = 0;
	a_res = NULL;         
	a_widget = NULL;      
	parent_widget = NULL; 
	current_method = NULL;
	current_interface = NULL; 
	current_module = NULL; 
	root_widget = NULL;
	first_method = NULL;
	first_interface = NULL;
/*	lang[0] = 0;
	palette[0] = 0;
	startup[0] = 0;
	helpfile[0] = 0;
	sourcedir[0] = 0; */

	yyparse();

	if(fclose(yyin))
		ret->error = errno;

	ret->root_widget = root_widget;
	ret->first_method = first_method;
	ret->first_interface = first_interface;
	ret->first_module = first_module;
/*
	strcpy( ret->palette, palette );
	strcpy( ret->lang, lang );
	strcpy( ret->startup, startup );
	strcpy( ret->helpfile, helpfile );
	strcpy( ret->parseError, parseError );
	strcpy( ret->sourcedir, sourcedir );
*/
	return(ret);
}

/* ---------------------------- */
/*       browse_widget()	*/
/* ---------------------------- */
void browse_widget( YWidget *wg )
{
	YResource *tmp;
	YWidget	  *twg;
	printf("Name:%s,Klasse:%s\n",wg->name,wg->widget_class);
	for( tmp=wg->first_res; tmp ; tmp = tmp->next )
		printf("\t%s,%s (%s)\n",tmp->name,tmp->value,tmp->attrib);
	printf("Beginne mit Kinder\n");
	for( twg=wg->first_child; twg; twg = twg->next )
		browse_widget( twg );
	printf("Ende der Kinder fuer '%s'\n",wg->name);
}

/* ----------------------------- */
/*         free_YWidget()        */
/* ----------------------------- */
void free_YWidget( YWidget *wg )
{
	YResource *tmp, *last;

	for( 	tmp = wg->first_res; 
		tmp; 
		last = tmp, tmp = tmp->next, 
		last->value ? free(last->value) : 0, free(last));
	if( wg->first_child )
		free_YWidget( wg->first_child );
	if( wg->next )
		free_YWidget( wg->next );	

	if( wg->viewData )
		free( wg->viewData );
	if( wg->description )
		free( wg->description );
	free( wg );
}
/* ----------------------------- */
/*         free_YResult()        */
/* ----------------------------- */
void free_YResult( YResult *res )
{
	YMethod *tmp, *last;
	YInterface *tin, *lin;
	YModule *tmo, *lmo;

	if( res->root_widget )
		free_YWidget( res->root_widget );

	for( 	tmp = res->first_method; 
		tmp; 
		last = tmp, tmp = tmp->next, free(last)) {
		if(tmp->code)
			free(tmp->code);
	}
	for( 	tin = res->first_interface; 
		tin; 
		lin = tin, tin = tin->next, free(lin));
	for( 	tmo = res->first_module; 
		tmo; 
		lmo = tmo, tmo = tmo->next, free(lmo));
	if(res->more_source)
		free(res->more_source);
	if(res->description)
		free(res->description);
	if(res->extra_cc_options)
		free(res->extra_cc_options);
	if(res->extra_ld_options)
		free(res->extra_ld_options);
	if(res->extra_libraries)
		free(res->extra_libraries);
	if(res->global_resources)
		free(res->global_resources);
	free( res );
}
