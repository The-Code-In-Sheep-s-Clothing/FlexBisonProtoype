#include <iostream>
#include "parser.hpp"
#include "ast.hpp"

extern int yyparse();

using namespace std;
int main() {
    ast::Block * ast_root;
    if (yyparse(&ast_root) != 0) {
        cout << "Broke" << endl;
        return 1;
    }
    // Parse was successful
    ast_root->print(std::cout);
    return 0;
}
