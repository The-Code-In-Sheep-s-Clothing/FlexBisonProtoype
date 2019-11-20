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
        this->state.current_player = 0;
    }
    void Interpreter::run() {
        // this->game_loop();
    }
    void Interpreter::game_loop() {

    }
    void Interpreter::make_board(std::shared_ptr<ast::BoardStatement> b) {
        std::vector<std::vector<std::shared_ptr<GamePiece>>> board = 
            std::vector<std::vector<std::shared_ptr<GamePiece>>>(b->x.get_value());
        for (int i = 0; i < b->x.get_value(); i++) {
            board[i] = std::vector<std::shared_ptr<GamePiece>>(b->y.get_value());
            for (int j = 0; j < b->y.get_value(); j++) {
                board[i][j] = NULL;
            }
        }
        this->state.board = board;
    }
    void Interpreter::make_pieces(std::vector<std::shared_ptr<ast::PieceStatement>> ps) {
        std::vector<std::vector<std::shared_ptr<PieceObj>>> pieces =
            std::vector<std::vector<std::shared_ptr<PieceObj>>>(ps.size());
        for (int i = 0; i < ps.size(); i ++)  {
            pieces[i] = std::vector<std::shared_ptr<PieceObj>>(this->players);
            for (int j = 0; j < this->players; j++) {
                pieces[i][j] = std::shared_ptr<PieceObj>(new PieceObj(
                    ps[i]->num.get_value(),
                    ps[i]->name.get_value(),
                    std::dynamic_pointer_cast<ast::StringNode>(ps[i]->display[j])->get_value()
                ));
            }
        }
        this->state.pieces = pieces;
    }
}
