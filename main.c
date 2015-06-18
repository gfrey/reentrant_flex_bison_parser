#include "parser.tab.h"
#include "scanner.h"

int main() {
	yyscan_t myscanner;

	yylex_init(&myscanner);
	yyparse(myscanner);
	yylex_destroy(myscanner);
}
