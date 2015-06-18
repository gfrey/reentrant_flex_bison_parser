%define api.pure full
%lex-param {void *scanner}
%parse-param {void *scanner}

%{
#include <stdio.h>
#include "ast.h"
#include "parser.tab.h"
#include "scanner.h"

void yyerror (yyscan_t *locp, char const *msg);
%}

%define api.value.type union /* Generate YYSTYPE from these types:  */
%token <struct ast_node_number*>     NUMBER     "number"
%token <struct ast_node_string*>     STRING     "string"
%token <struct ast_node_identifier*> IDENTIFIER "identifier"

%token TEOF 0 "end of file"
%token LPAREN "("
%token RPAREN ")"

%type <union ast_node_sexp*> sexp
%type <union ast_node_atom*> atom
%type <struct ast_node_list*> list

%%
%start sexps;

sexps:
  %empty                {}
| sexp                  {}

sexp:
  atom                  {}
| "(" list ")"          {};

list:
  %empty                {}
| sexp list             {};

atom:
  "number"              {}
| "identifier"          {}
| "string"              {};

%%

void yyerror (yyscan_t *locp, char const *msg) {
	fprintf(stderr, "%s\n", msg);
}

