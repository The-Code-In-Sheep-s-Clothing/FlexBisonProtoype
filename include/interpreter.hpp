#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP
#include <memory>
#include <vector>
#include "ast.hpp"
namespace interpreter {
    class PieceObj {
        public:
            int num;
            std::string name;
            std::vector<std::string> display;
            PieceObj();
            PieceObj(int, std::string, std::vector<std::string>);
    };
    class GamePiece {
        public:
            int owner;
            std::string name;
            GamePiece();
            GamePiece(int, std::string);
    };
    class Interpreter {
        std::shared_ptr<ast::Block> ast;
        std::string game;
        int players;
        std::vector<std::vector<GamePiece>> board;
        std::vector<PieceObj> pieces;

        void game_loop();
        void setup();
        void make_board(std::shared_ptr<ast::BoardStatement>);
        public:
            Interpreter();
            Interpreter(ast::Block *);

            void run();
    };
}
#endif
