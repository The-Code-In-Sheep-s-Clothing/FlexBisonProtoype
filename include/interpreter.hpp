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
            std::string display;
            PieceObj();
            PieceObj(int, std::string, std::string);
    };
    class GamePiece {
        public:
            int owner;
            std::shared_ptr<PieceObj> desc;
            GamePiece();
            GamePiece(int, std::shared_ptr<PieceObj>);
    };
    class GameState {
        public:
            int current_player;
            std::vector<std::vector<std::shared_ptr<GamePiece>>> board;
            std::vector<std::vector<std::shared_ptr<PieceObj>>> pieces;
    };
    class Interpreter {
        std::shared_ptr<ast::Block> ast;

        std::string game;
        int players;
        GameState state;
        void game_loop();
        void make_board(std::shared_ptr<ast::BoardStatement>);
        void make_pieces(std::vector<std::shared_ptr<ast::PieceStatement>>);
        bool check_end();
        public:
            Interpreter();
            Interpreter(ast::Block *);

            void run();
    };
}
#endif
