#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "module.h"
#include "my_parser.h"
#include "my_scanner.h"

yyscan_t my_scanner_ctor(module *mod);

module *
new_module_from_stdin(const char *prompt)
{
	module *mod = (module *) malloc(sizeof(module));
        mod->f = NULL;
        mod->prompt = prompt;
        mod->avail = 0;
        mod->src = NULL;
	return mod;
}

module *
new_module_from_file(FILE *f)
{
	module *mod = (module *) malloc(sizeof(module));
	mod->f = f;
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
        }
	free(mod);
}

int
parse_module(module *mod)
{
	int res;
        yyscan_t sc = my_scanner_ctor(mod);

        if(mod->f != NULL) {
            my_set_in(mod->f, sc);
        }
        while( (res = my_parse(sc, mod)) == 0) {
            print_node_sexp(mod->root);
        }
        my_lex_destroy(sc);

	return res;
}


