#include <iostream>
#include <unistd.h>
#include <string.h>
#include "parser.hpp"
#include "ast.hpp"
#include "builtins.hpp"
#include "interpreter.hpp"

extern int yyparse();
extern FILE *yyin;

using namespace std;
int main(int argc, char *argv[]) {
    yyin = fopen(argv[1], "r");
    ast::Block * ast_root;
    if (yyparse(&ast_root) != 0) {
        cout << "\tParsing failed!" << endl;
        return 1;
    }
    // Parse was successful
    ast_root->print(std::cout);
    interpreter::Interpreter inter(ast_root);
    inter.run();
    return 0;
}
