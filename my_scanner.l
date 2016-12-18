%option reentrant bison-bridge

%{
#include <editline/readline.h>
#include "my_parser.h"
#include "module.h"

#define YY_EXTRA_TYPE module *
#define YY_INPUT(buf,result,max_size) { \
    result = read_next(yyextra, buf, max_size); }

size_t read_next(module *, char *, size_t);
%}

%x COMMENT

U      [\x80-\xbf]
UALPHA   [A-Za-z]|\xc2[\x80-\x84\x86-\x9f\xa1-\xbf]|[\xc3-\xdf]{U}|[\xe0-\xe1]{U}{U}|[\xe3-\xef]{U}{U}|\xe2(\x80[\x8b-\xad\xb0-\xbf]|\x81[\x80-\x9e\xa0-\xbf]|[\x82-\xbf]{U})
INFIX   [_#'`.+*/%$~^&@|<>=!:-]
SPECIAL [_#?'`]
NAME_END [0-9]|{SPECIAL}|{UALPHA}

EXP      ([Ee][-+]?[0-9]+)

id     (({UALPHA}|{SPECIAL})({NAME_END})*|{INFIX}+)
oct    0[0-7]*
int    [1-9][0-9]*
hex    0[Xx][0-9a-fA-F]+
blank  ([ \t\x0b-\x0d]|\xc2[\x85\xa0]|\xe2(\x80[\x80-\x8a\xaf]|\x81\x9f))
string \"([^"\\]|\\['"?\\abfnrtv]|\\[0-7]{1,3}|\\[Xx][0-9a-fA-F]+)*\"

%%

"/*"       { BEGIN(COMMENT); }

{blank}+ |
[\n\0]+   {}

"(" |
")"        { return yytext[0]; }

{oct}      { char *end; yylval->NUMBER = strtol(yytext, &end, 8);
             return NUMBER; }
{int}      { char *end; yylval->NUMBER = strtol(yytext, &end, 10);
             return NUMBER; }
{hex}      { char *end; yylval->NUMBER = strtol(yytext+2, &end, 16);
             return NUMBER; }

[0-9]*\.[0-9]+{EXP}?[flFL]? |
[0-9]+{EXP}[flFL]? |
0[Xx]([0-9a-fA-F]*\.[0-9a-fA-F]+|[0-9a-fA-F]+\.?)[Pp][-+]?[0-9]+[flFL]? {
             yylval->NUMBER = 1; return NUMBER; }

{id}       { yylval->IDENTIFIER = yytext; return IDENTIFIER; }
{string}   { yylval->STRING = yytext; return STRING; }

<<EOF>>    { return TOK_EOF; }

<COMMENT>"*/"   { BEGIN(INITIAL); }
<COMMENT><<EOF>>        { printf("Unterminated comment\n");
                          return TOK_EOF; }
<COMMENT>[^/]   {}
<COMMENT>\/[^*] {}

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
      } else {
          ret = YY_NULL;
      }
      return ret;
}

