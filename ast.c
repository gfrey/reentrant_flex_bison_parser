#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ast.h"

ast_node_list *
new_list_node()
{
	ast_node_list *node = (ast_node_list *) malloc(sizeof(ast_node_list));
	node->length = 0;
	node->capacity = 16;
	node->list = (ast_node_sexp **) malloc(16*sizeof(ast_node_sexp *));
	return node;
}

void
delete_list_node(ast_node_list *node)
{
	int i;
	for (i = 0; i < node->length; i++) {
		delete_sexp_node(node->list[i]);
	}
	free(node->list);
	free(node);
}

void
add_node_to_list(ast_node_list *list, ast_node_sexp *node)
{
	if (list->length == list->capacity) {
		// TODO should allocate some more space
	}
	list->list[list->length] = node;
	list->length++;
}

void
print_node_list(ast_node_list *node)
{
	int i = 0;
	printf("list node with %d elements\n", node->length);
	for (i = 0; i < node->length; i++) {
		print_node_sexp(node->list[i]);
	}
}

ast_node_atom *
new_atom_node(enum atom_types type, void *v)
{
	ast_node_atom *node = (ast_node_atom *) malloc(sizeof(ast_node_atom));
	node->type = type;
	switch (type) {
		case AT_IDENTIFIER:
		case AT_STRING:
			node->value.string = (char *) malloc(strlen((char *) v)+1);
			strcpy(node->value.string, (char *) v);
			break;
		case AT_NUMBER:
			node->value.number = *((long *) v);
			break;
	}
	return node;
}

void
delete_atom_node(ast_node_atom *node)
{
	switch (node->type) {
		case AT_IDENTIFIER:
		case AT_STRING:
			free(node->value.string);
			break;
		case AT_NUMBER:
			break;
	}
	free(node);
}

void
print_node_atom(ast_node_atom *node)
{
	if (node->type == AT_IDENTIFIER) {
		printf("identifier node: %s\n", node->value.string);
	} else if (node->type == AT_STRING) {
		printf("string node: %s\n", node->value.string);
	} else if (node->type == AT_NUMBER) {
		printf("number node: %ld\n", node->value.number);
	} else {
		printf("unknown atom node");
	}
}

ast_node_sexp *
new_sexp_node(enum sexp_types type, void *v)
{
	ast_node_sexp *node = (ast_node_sexp *) malloc(sizeof(ast_node_sexp));

	node->type = type;
	switch (type) {
		case ST_ATOM:
			node->value.atom = (ast_node_atom *) v;
			break;
		case ST_LIST:
			node->value.list = (ast_node_list *) v;
			break;
	}
	return node;
}

void
delete_sexp_node(ast_node_sexp *node)
{
	switch (node->type) {
		case ST_ATOM:
			delete_atom_node(node->value.atom);
			break;
		case ST_LIST:
			delete_list_node(node->value.list);
			break;
	}
	free(node);
}

void
print_node_sexp(ast_node_sexp *node)
{
	if (node->type == ST_ATOM) {
		printf("node is an atom: ");
		print_node_atom(node->value.atom);
	} else if (node->type == ST_LIST) {
		printf("node is a list\n");
		print_node_list(node->value.list);
	} else {
		printf("node is a what?\n");
	}
}
