#ifndef __AST_H
#define __AST_H

typedef struct {
	long value;
} ast_node_number;
ast_node_number *new_number_node(long v);

typedef struct {
	char *value;
} ast_node_string;
ast_node_string *new_string_node(const char *v);

typedef struct {
	char *value;
} ast_node_identifier;
ast_node_identifier *new_identifier_node(const char *v);

enum atom_types { AT_NUMBER, AT_STRING, AT_IDENTIFIER };

typedef struct {
	enum atom_types type;
	union {
		ast_node_number     *number;
		ast_node_string     *string;
		ast_node_identifier *identifier;
	} value;
} ast_node_atom;

ast_node_atom *new_atom_node(enum atom_types type, void *v);
void print_node_atom(ast_node_atom *node);

struct _ast_node_sexp;
typedef struct _ast_node_sexp ast_node_sexp;
typedef struct {
	ast_node_sexp **list;

	unsigned int length;
	unsigned int capacity;
} ast_node_list;

ast_node_list *new_list_node();
void print_node_list(ast_node_list *node);
void add_node_to_list(ast_node_list *list, ast_node_sexp *node);

enum sexp_types { ST_ATOM, ST_LIST };
struct _ast_node_sexp {
	enum sexp_types type;
	union {
		ast_node_atom *atom;
		ast_node_list *list;
	} value;
};
void print_node_sexp(ast_node_sexp *node);
ast_node_sexp *new_sexp_node(enum sexp_types type, void *v);

#endif // __AST_H
