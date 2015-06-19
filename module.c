#include "module.h"
#include "parser.tab.h"
#include "scanner.h"

module *
new_module_from_stdin()
{
	module *mod = (module *) malloc(sizeof(module));
	mod->src = stdin;
	return mod;
}

module *
new_module_from_file(const char *filename)
{
	module *mod = (module *) malloc(sizeof(module));
	mod->src = fopen(filename, "r");
	return mod;
}

module *
new_module_from_string(char *src)
{
	module *mod = (module *) malloc(sizeof(module));
	mod->src = fmemopen(src, strlen(src)+1, "r");
	return mod;
}

void
delete_module(module *mod)
{
	if (mod->root != NULL) {
		delete_sexp_node(mod->root);
	}
	fclose(mod->src);
	free(mod);
}

int
parse_module(module *mod)
{
	yyscan_t sc;
	int res;

	yylex_init(&sc);
	yyset_in(mod->src, sc);
	res = yyparse(sc, mod);
	yylex_destroy(sc);

	if (res == 0) {
		print_node_sexp(mod->root);
	}

	return res;
}


