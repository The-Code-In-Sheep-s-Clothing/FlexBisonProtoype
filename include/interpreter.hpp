#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP
#include <memory>
#include <vector>
#include "ast.hpp"
#include "builtins.hpp"

namespace interpreter {
    class Interpreter {
        std::shared_ptr<ast::Block> ast;
        std::string game;
        int players;
        builtins::GameState state;

        void game_loop();
        void make_board(std::shared_ptr<ast::BoardStatement>);
        void make_pieces(std::vector<std::shared_ptr<ast::PieceStatement>>);
        bool check_end();
        int get_winner();
        void take_turn();
        void print_board();
        public:
            Interpreter();
            Interpreter(ast::Block *);

            void run();
    };
}
#endif
