#include "parser.tab.h"
#include "scanner.h"
#include "ast.h"

int main() {
    ast_node_sexp root;
	yyscan_t myscanner;
	int res;

	yylex_init(&myscanner);
	res = yyparse(myscanner, &root);
	yylex_destroy(myscanner);

	print_node_sexp(&root);

	return res;
}
