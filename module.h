#ifndef __MODULE_H
#define __MODULE_H

#include <stdio.h>
#include "ast.h"

typedef struct {
	FILE          *src;
	ast_node_sexp *root;
} module;

module *new_module_from_stdin();
module *new_module_from_file(const char *filename);
module *new_module_from_string(char *src);
void delete_module(module *mod);

int parse_module(module *mod);


#endif // __MODULE_H
