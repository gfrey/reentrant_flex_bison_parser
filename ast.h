#ifndef __AST_H
#define __AST_H


enum atom_types { AT_NUMBER, AT_STRING, AT_IDENTIFIER };

typedef struct {
	enum atom_types type;
	union {
		long number;
		char *string;
	} value;
} ast_node_atom;

ast_node_atom *new_atom_node(enum atom_types type, void *v);
void delete_atom_node(ast_node_atom *node);
void print_node_atom(ast_node_atom *node);

struct _ast_node_sexp;
typedef struct _ast_node_sexp ast_node_sexp;
typedef struct {
	ast_node_sexp **list;

	unsigned int length;
	unsigned int capacity;
} ast_node_list;

ast_node_list *new_list_node();
void delete_list_node(ast_node_list *node);
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
void delete_sexp_node(ast_node_sexp *node);

#endif // __AST_H
