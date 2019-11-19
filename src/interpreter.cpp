#include <iostream>
#include "interpreter.hpp"
#include "builtins.hpp"
#include "ast.hpp"

namespace interpreter {
    PieceObj::PieceObj() {}
    PieceObj::PieceObj(int num, std::string name, std::string display) {
        this->num = num;
        this->name = name;
        this->display = display;
    }
    GamePiece::GamePiece() {}
    GamePiece::GamePiece(int owner, std::shared_ptr<PieceObj> desc) {
        this->owner = owner;
        this->desc = desc;
    }
    Interpreter::Interpreter() {}
    Interpreter::Interpreter(ast::Block *ast) {
        this->ast = std::shared_ptr<ast::Block>(ast);
        this->players = ast::get_players(this->ast.get())->num.get_value();
        this->make_board(ast::get_board(this->ast.get()));
        this->make_pieces(ast::get_pieces(this->ast.get()));
    }
    void Interpreter::run() {
        // this->game_loop();
    }
    void Interpreter::game_loop() {

    }
    void Interpreter::make_board(std::shared_ptr<ast::BoardStatement> b) {
        this->board = std::vector<std::vector<std::shared_ptr<GamePiece>>>(b->x.get_value());
        for (int i = 0; i < b->x.get_value(); i++) {
            this->board[i] = std::vector<std::shared_ptr<GamePiece>>(b->y.get_value());
            for (int j = 0; j < b->y.get_value(); j++) {
                this->board[i][j] = NULL;
            }
        }
    }
    void Interpreter::make_pieces(std::vector<std::shared_ptr<ast::PieceStatement>> ps) {
        this->pieces = std::vector<std::vector<std::shared_ptr<PieceObj>>>(ps.size());
        for (int i = 0; i < ps.size(); i ++)  {
            this->pieces[i] = std::vector<std::shared_ptr<PieceObj>>(this->players);
            for (int j = 0; j < this->players; j++) {
                this->pieces[i][j] = std::shared_ptr<PieceObj>(new PieceObj(
                    ps[i]->num.get_value(),
                    ps[i]->name.get_value(),
                    std::dynamic_pointer_cast<ast::StringNode>(ps[i]->display[j])->get_value()
                ));
            }
        }
    }
}
