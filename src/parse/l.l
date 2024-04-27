%{
#include "y.tab.h"
#include "parse.h"
extern int yyerror(char *);

#ifndef YY_FATAL_ERROR
#define YY_FATAL_ERROR(s) yyerror(s)
#endif

#ifndef yywrap
int yywrap()
{
	return 1;
}
#endif

%}

%s IN_STRING

%%
WIDGET			return( WIDGET );     /* keywords */
NAME			return( NAME );
CLASS			return( CLASS );
INTERFACE		return( INTERFACE );
MODULE   		return( MODULE );
METHOD   		return( METHOD );
STARTUP  		return( STARTUP );
LANG			return( LANG );
PALETTE			return( PALETTE );
PALETTE_INFO		return( PALETTE_INFO );
QUICKHELP		return( QUICKHELP );
MANAGED			return( MANAGED );
VIEWDATA		return( VIEWDATA );
HELPFILE		return( HELPFILE );
HELPID			return( HELPID );
SOURCEDIR		return( SOURCEDIR );
"{"			return( BRACKET_OPEN );
"}"			return( BRACKET_CLOSE );
APPL_CLASS		return( APPL_CLASS );
EXEC_FILE		return( EXEC_FILE );
MORE_SOURCE		return( MORE_SOURCE );
EXTRA_CC_OPTIONS	return( EXTRA_CC_OPTIONS );
EXTRA_LD_OPTIONS	return( EXTRA_LD_OPTIONS );
EXTRA_LIBRARIES		return( EXTRA_LIBRARIES );
DESCRIPTION		return( DESCRIPTION );
GLOBAL_RESOURCES	return( GLOBAL_RESOURCES );
\"[^\"]*\"     		if(yytext[yyleng-2] == '\\' ) {
				yyless(yyleng-1);
				yymore();
			} else {
				yylval = (int)cpyAndReplace(yytext, "\\\"", "\""); 
				return(STRING);
			}

[a-zA-Z][a-zA-Z0-9]*+	yylval = (int)yytext; return(RES_NAME);
"!".*			; /* a comment is beginning with a '!' and end with \n */
[ \n\t]			; /* the spaces */



