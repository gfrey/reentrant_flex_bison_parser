%option reentrant bison-bridge

%{
#include <editline/readline.h>
#include "parser.tab.h"
#include "module.h"

#define YY_EXTRA_TYPE module *
#define YY_INPUT(buf,result,max_size) { \
    result = read_next(yyextra, buf, max_size); }

size_t read_next(module *, char *, size_t);
%}

id     [a-zA-Z][a-zA-Z_0-9]*
int    [0-9]+
blank  [ \t]
string \"[^\"\n]*\"

%%

{blank}+ |
[\n\0]+   {}

"(" |
")"        { return yytext[0]; }

{int}      { yylval->NUMBER = atol(yytext); return NUMBER; }

{id}       { yylval->IDENTIFIER = yytext; return IDENTIFIER; }
{string}   { yylval->STRING = yytext; return STRING; }

<<EOF>>    { return TOK_EOF; }

%%

int yywrap() {
    return 1;
}

size_t read_next(module *mod, char *buf, size_t max_size) {
      size_t ret;

      if(mod->prompt && !mod->avail) {
          if(mod->src != NULL) {
              free(mod->src);
              mod->src = NULL;
          } 

          mod->src = readline("> ");
          if(mod->src == NULL)
              return YY_NULL;
          mod->pos = mod->src;

          if(mod->src[0] != 0)
              add_history(mod->src);

          // Send along the trailing '\0' char.
          mod->avail = strlen(mod->src)+1;
      }

      if(mod->f != NULL) {
          ret = fread(buf, 1, max_size, mod->f);
      } else if(mod->avail > 0) {
          ret = mod->avail < max_size ? mod->avail : max_size;
          memcpy(buf, mod->pos, ret);
          mod->pos   += ret;
          mod->avail -= ret;
          printf("read_next: %ld\n", ret);
      } else {
          ret = YY_NULL;
      }
      return ret;
}

