#ifndef __AST_H
#define __AST_H

struct ast_node_number {
	long value;
};

struct ast_node_string {
	char *value;
};

struct ast_node_identifier {
	char *value;
};

union ast_node_atom {
	struct ast_node_number     *number;
	struct ast_node_string     *string;
	struct ast_node_identifier *identifier;
};

union ast_node_sexp;
struct ast_node_list {
	union ast_node_sexp **list;
};

union ast_node_sexp {
	union ast_node_atom *atom;
	struct ast_node_list *list;
};

#endif // __AST_H
