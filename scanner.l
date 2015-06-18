%{
#include "parser.tab.h"
%}

%option reentrant bison-bridge noyywrap

id     [+\-\*/]|([a-zA-Z][a-zA-Z_0-9]*)
int    [0-9]+
blank  [ \t]
string \"[^\"\n]*\"

%%

{blank}+   ;
[\n]+      ;

"("        return LPAREN;
")"        return RPAREN;

{int}      return NUMBER;

{id}       return IDENTIFIER;
{string}   return STRING;
<<EOF>>    return TEOF;
