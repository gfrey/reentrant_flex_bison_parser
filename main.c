#include "module.h"

int
main(int argc, char **argv) 
{
	module *mod;
	int i, res;

	/*mod = new_module_from_string("(add 1 2 (\"test\" 3 4) 5)");
	res = parse_module(mod);
	delete_module(mod);
	return res;*/

	if (argc == 1) {
		mod = new_module_from_stdin("> ");
		res = parse_module(mod);
                delete_module(mod);
                printf("\n");
                return res;
	}

	for (i = 1; i < argc; i++) {
                FILE *f = fopen(argv[i], "r");
                if(f == NULL) {
                    fprintf(stderr, "Error opening '%s'\n", argv[i]);
                    break;
                }
		mod = new_module_from_file(f);
		res = parse_module(mod);
                delete_module(mod);
                fclose(f);
		if (res != 0 ) {
			return res;
		}
	}
	return 0;
}
