#include <iostream>
#include "interpreter.hpp"
#include "builtins.hpp"
#include "ast.hpp"

namespace interpreter {
    PieceObj::PieceObj() {}
    PieceObj::PieceObj(int num, std::string name, std::vector<std::string> display) {
        this->num = num;
        this->name = name;
        this->display = display;
    }
    GamePiece::GamePiece() {}
    GamePiece::GamePiece(int owner, std::string name) {
        this->owner = owner;
        this->name = name;
    }
    Interpreter::Interpreter() {}
    Interpreter::Interpreter(ast::Block *ast) {
        this->ast = std::shared_ptr<ast::Block>(ast);
    }
    void Interpreter::run() {
        this->setup();
        // this->game_loop();
    }
    void Interpreter::setup() {
        this->make_board(ast::get_board(this->ast.get()));
        // this->players = ast::get_players(this->ast.get());
    }
    void Interpreter::game_loop() {

    }
    void Interpreter::make_board(std::shared_ptr<ast::BoardStatement> b) {
        this->board = std::vector<std::vector<GamePiece>>(b->x.get_value());
        for (int i = 0; i < b->x.get_value(); i++) {
            this->board[i] = std::vector<GamePiece>(b->y.get_value());
        }
    }
}
