%{
#include "parser.tab.h"
%}

%option reentrant bison-bridge noyywrap

id     [a-zA-Z][a-zA-Z_0-9]*
int    [0-9]+
blank  [ \t]
string \"[^\"\n]*\"

%%

{blank}+   ;
[\n]+      ;

"("        return TOK_LPAREN;
")"        return TOK_RPAREN;

{int}      { yylval->NUMBER = atol(yytext); return NUMBER; }

{id}       { yylval->IDENTIFIER = yytext; return IDENTIFIER; }
{string}   { yylval->STRING = yytext; return STRING; }

<<EOF>>    return TOK_EOF;
