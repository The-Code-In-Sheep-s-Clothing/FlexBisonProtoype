#include <iostream>
#include "interpreter.hpp"
#include "builtins.hpp"
#include "ast.hpp"

namespace interpreter {
    Interpreter::Interpreter() {}
    Interpreter::Interpreter(ast::Block *ast) {
        this->ast = std::shared_ptr<ast::Block>(ast);
        this->players = ast::get_players(this->ast.get())->num.get_value();
        this->make_board(ast::get_board(this->ast.get()));
        this->make_pieces(ast::get_pieces(this->ast.get()));
        this->state.current_player = 0;
    }
    void Interpreter::run() {
        this->game_loop();
    }
    void Interpreter::game_loop() {
        std::cout << "Playing Game" << std::endl;
        bool playing = true;
        while (playing) {
            for (int i = 0; i < this->players; i++) {
                this->print_board();
                this->state.current_player = i;    
                std::cout << "It is Player " << this->state.current_player << "'s turn." << std::endl;
                this->take_turn();
                if (this->check_end()) {
                    playing = false;
                    break;
                }
            }
        }
        std::cout << "Player " << this->get_winner() << " wins!" << std::endl;
    }
    void Interpreter::take_turn() {
        std::cout << "Turn options:" << std::endl;
        std::vector<std::shared_ptr<ast::Statement>> statements = 
            ast::get_statements(this->ast.get(), ast::TURN);
        int choice;
        for (int i = 0; i < statements.size(); i++) {
            std::shared_ptr<ast::FunctionCallExpression> f = 
                std::dynamic_pointer_cast<ast::FunctionCallExpression>(statements[i]);
            const builtins::func_descriptor *desc = builtins::map_func(f->name.get_value());
            if (desc)
                std::cout << i << ": " << desc->name << std::endl;
        }
        std::cin >> choice;
        std::shared_ptr<ast::FunctionCallExpression> f = 
            std::dynamic_pointer_cast<ast::FunctionCallExpression>(statements[choice]);
        const builtins::func_descriptor *desc = builtins::map_func(f->name.get_value());
        if (desc)
            desc->func(this->state, f->args);
    }
    void Interpreter::print_board() {
        std::cout << "  ";
        for (int i = 0; i < this->state.board[0].size(); i++)
            std::cout << i << " ";
        std::cout << std::endl;
        for (int i = 0; i < this->state.board.size(); i++) {
            std::cout << i << " ";
            for (int j = 0; j < this->state.board[i].size(); j++) {
                if (this->state.board[i][j])
                    std::cout << this->state.board[i][j]->owner << " ";
                else
                    std::cout << "E ";
            }
            std::cout << std::endl;
        }
    }
    int Interpreter::get_winner() {
        std::vector<std::shared_ptr<ast::Statement>> statements = 
            ast::get_statements(this->ast.get(), ast::WIN);
        for (int i = 0; i < statements.size(); i++) {
            std::shared_ptr<ast::FunctionCallExpression> f = 
                std::dynamic_pointer_cast<ast::FunctionCallExpression>(statements[i]);
            const builtins::func_descriptor *desc = builtins::map_func(f->name.get_value());
            if (desc) {
                std::shared_ptr<ast::NumberNode> ret((ast::NumberNode *)desc->func(this->state, f->args));
                return ret->get_value();
            }
        }
        return 0;
    }
    bool Interpreter::check_end() {
        std::vector<std::shared_ptr<ast::Statement>> statements = 
            ast::get_statements(this->ast.get(), ast::END);
        for (int i = 0; i < statements.size(); i++) {
            std::shared_ptr<ast::FunctionCallExpression> f = 
                std::dynamic_pointer_cast<ast::FunctionCallExpression>(statements[i]);
            const builtins::func_descriptor *desc = builtins::map_func(f->name.get_value());
            if (desc) {
                std::shared_ptr<ast::NumberNode> ret((ast::NumberNode *)desc->func(this->state, f->args));
                if (ret->get_value()) {
                    std::cout << desc->name << std::endl;
                    return true;
                }
            }
        }
        return false;
    }
    void Interpreter::make_board(std::shared_ptr<ast::BoardStatement> b) {
        std::vector<std::vector<std::shared_ptr<builtins::GamePiece>>> board = 
            std::vector<std::vector<std::shared_ptr<builtins::GamePiece>>>(b->x.get_value());
        for (int i = 0; i < b->x.get_value(); i++) {
            board[i] = std::vector<std::shared_ptr<builtins::GamePiece>>(b->y.get_value());
            for (int j = 0; j < b->y.get_value(); j++) {
                board[i][j] = NULL;
            }
        }
        this->state.board = board;
    }
    void Interpreter::make_pieces(std::vector<std::shared_ptr<ast::PieceStatement>> ps) {
        std::vector<std::vector<std::shared_ptr<builtins::PieceObj>>> pieces =
            std::vector<std::vector<std::shared_ptr<builtins::PieceObj>>>(ps.size());
        for (int i = 0; i < ps.size(); i ++)  {
            pieces[i] = std::vector<std::shared_ptr<builtins::PieceObj>>(this->players);
            for (int j = 0; j < this->players; j++) {
                pieces[i][j] = std::shared_ptr<builtins::PieceObj>(new builtins::PieceObj(
                    ps[i]->num.get_value(),
                    ps[i]->name.get_value(),
                    std::dynamic_pointer_cast<ast::StringNode>(ps[i]->display[j])->get_value()
                ));
            }
        }
        this->state.pieces = pieces;
    }
}
