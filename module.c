#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "module.h"
#include "parser.tab.h"
#include "scanner.h"

module *
new_module_from_stdin(const char *prompt)
{
	module *mod = (module *) malloc(sizeof(module));
	mod->f = stdin;
        mod->prompt = NULL;
        //mod->f = NULL;
        //mod->prompt = prompt;
        mod->avail = 0;
        mod->src = NULL;
	return mod;
}

module *
new_module_from_file(const char *filename)
{
	module *mod = (module *) malloc(sizeof(module));
	mod->f = fopen(filename, "r");
        mod->prompt = NULL;
        mod->src = NULL;
	return mod;
}

module *
new_module_from_string(char *src)
{
	module *mod = (module *) malloc(sizeof(module));
	mod->src = mod->pos = strdup(src);
        mod->avail = strlen(src)+1;
        mod->prompt = NULL;
        mod->f = NULL;
	return mod;
}

void
delete_module(module *mod)
{
	if (mod->root != NULL) {
		delete_sexp_node(mod->root);
	}
        if(mod->src != NULL) {
            free(mod->src);
        } else if(mod->f != NULL) {
            fclose(mod->f);
        }
	free(mod);
}

int
parse_module(module *mod)
{
	yyscan_t sc;
	int res;

	yylex_init(&sc);
        yyset_extra(mod, sc);
        if(mod->f != NULL) {
            yyset_in(mod->f, sc);
        }
	res = yyparse(sc, mod);
	yylex_destroy(sc);

	if (res == 0) {
		print_node_sexp(mod->root);
	}

	return res;
}


