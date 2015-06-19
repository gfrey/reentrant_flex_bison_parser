#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ast.h"

struct ast_node_list *
new_list_node()
{
	struct ast_node_list *node = (struct ast_node_list *) malloc(sizeof(struct ast_node_list));
	node->length = 0;
	node->capacity = 16;
	node->list = (ast_node_sexp **) malloc(16*sizeof(ast_node_sexp *));
	printf("--> creating new list node\n");
	return node;
}

void
add_node_to_list(struct ast_node_list *list, ast_node_sexp *node)
{
	printf("===> %d %d\n", list->length, list->capacity);
	print_node_sexp(node);
	printf("---------\n");
   	if (list->length == list->capacity) {
		// TODO should allocate some more space
	}
	list->list[list->length] = node;
	list->length++;
}

void
print_node_list(struct ast_node_list *node)
{
	int i = 0;
	printf("list node with %d elements\n", node->length);
	for (i = 0; i < node->length; i++) {
		print_node_sexp(node->list[i]);
	}
}

struct ast_node_number *
new_number_node(long v)
{
	struct ast_node_number *res = (struct ast_node_number *) malloc(sizeof(struct ast_node_number));
	res->value = v;
	return res;
}

struct ast_node_identifier *
new_identifier_node(char *v)
{
	struct ast_node_identifier *res = (struct ast_node_identifier *) malloc(sizeof(struct ast_node_identifier));
	res->value = (char *) malloc(strlen(v));
	strcpy(res->value, v);
	return res;
}

struct ast_node_string *
new_string_node(char *v)
{
	struct ast_node_string *res = (struct ast_node_string *) malloc(sizeof(struct ast_node_string));
	res->value = (char *) malloc(strlen(v));
	strcpy(res->value, v);
	return res;
}

ast_node_atom *
new_atom_node()
{
	return (ast_node_atom *) malloc(sizeof(ast_node_atom));
}

void
print_node_atom(ast_node_atom *node)
{
	printf("--> node type: %d %d\n", node->type, AT_NUMBER);
	if (node->type == AT_IDENTIFIER) {
		printf("identifier\n");
		printf("identifier node: %s\n", node->value.identifier->value);
	} else if (node->type == AT_STRING) {
		printf("string\n");
		printf("string node: %s\n", node->value.string->value);
	} else if (node->type == AT_NUMBER) {
		printf("number\n");
		printf("number node: %ld\n", node->value.number->value);
	} else {
		printf("unknown atom node");
	}
}

void
print_node_sexp(ast_node_sexp *node)
{
	if (node->type == ST_ATOM) {
		printf("node is an atom\n");
		print_node_atom(node->value.atom);
	} else if (node->type == ST_LIST) {
		printf("node is a list\n");
		print_node_list(node->value.list);
	} else {
		printf("node is a what?\n");
	}
}
