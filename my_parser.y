%define api.pure full
%lex-param {void *scanner}
%parse-param {void *scanner}{module *mod}
%locations
%define parse.error verbose

%{
#include <stdio.h>
#include "module.h"
#include "ast.h"
#include "my_parser.h"
#include "my_scanner.h"

void my_error(YYLTYPE *, yyscan_t *locp, module *mod, char const *msg);
%}

%code requires
{
#include "module.h"
#include "ast.h"
}

/* declare tokens */
%token <l>     NUMBER
%token <str>   STRING
%token <str>   IDENTIFIER

%token TOK_EOF

%type <sexp> sexp
%type <atom> atom
%type <list> list

%union {
    long l;
    const char *str;
    ast_node_sexp *sexp;
    ast_node_atom *atom;
    ast_node_list *list;
}

%%
%start sexps;

sexps: sexp     { mod->root = $1; YYACCEPT; }
     | TOK_EOF  { YYABORT; }

sexp:
  atom          { $$ = new_sexp_node(ST_ATOM, $1); }
| '(' list ')'  { $$ = new_sexp_node(ST_LIST, $2); };

list:
  %empty        { $$ = new_list_node(); }
| list sexp     { $$ = $1; add_node_to_list($$, $2); };

atom:
  NUMBER        { $$ = new_atom_node(AT_NUMBER, (void *)(&$1)); }
| IDENTIFIER    { $$ = new_atom_node(AT_IDENTIFIER, (void *)$1); }
| STRING        { $$ = new_atom_node(AT_STRING, (void *)$1); };

%%

void my_error(YYLTYPE *llocp, yyscan_t *locp, module *mod, char const *msg) {
	fprintf(stderr, "--> %s\n", msg);
}

