#include <iostream>
#include <unistd.h>
#include <string.h>
#include "parser.hpp"
#include "ast.hpp"
#include "builtins.hpp"

extern int yyparse();
std::shared_ptr<ast::BoardStatement> board;
std::shared_ptr<ast::PlayersStatement> players;

using namespace std;
int main(int argc, char *argv[]) {
    ast::Block * ast_root;
    if (yyparse(&ast_root) != 0) {
        cout << "\tParsing failed!" << endl;
        return 1;
    }
    // Parse was successful
    ast_root->print(std::cout);
    board = ast::get_board(ast_root);
    players = ast::get_players(ast_root);
    if (board)
        board->print(std::cout);
    if (players)
        players->print(std::cout);

    return 0;
}
