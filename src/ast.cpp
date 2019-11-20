#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "ast.hpp"
#include "builtins.hpp"

namespace ast {
    PrintContext::PrintContext() {
        this->indent_level = 0;
    }
    void PrintContext::indent() {
        this->indent_level++;
    }
    void PrintContext::dedent() {
        this->indent_level--;
    }
    void PrintContext::print_indent(std::ostream &o) {
        for (int i = 0; i < this->indent_level; i++)
            o << "  ";
    }

    void Node::print(std::ostream &o) {
        o << "Generic Node" << std::endl;
    }
    void Node::print(std::ostream &o, PrintContext &p) {
        p.print_indent(o);
        this->print(o);
    }

    // Statement
    Types Statement::get_type() {
        return this->type;
    }
    // std::shared_ptr<Expression> Statement::evaluate(interpreter::GameState) {
    //     std::cout << "ERROR: this should be inherited" << std::endl; 
    //     return NULL;
    // }
    // NumberNode
    NumberNode::NumberNode() {
        this->value = 0;
        this->type = NUMBER;
    }
    NumberNode::NumberNode(int n) {
        this->value = n;
        this->type = NUMBER;
    }
    int NumberNode::get_value() const {
        return this->value;
    }
    void NumberNode::print(std::ostream &o) {
        o << this->value;
    }
    // End number node

    // StringNode
    StringNode::StringNode() {
        this->value = "";
        this->type = STRING;
    }
    StringNode::StringNode(std::string s) {
        this->value = s;
        this->type = STRING;
    }
    std::string StringNode::get_value() const {
        return this->value;
    }
    void StringNode::print(std::ostream &o) {
        o << "\"" << this->value << "\"";
    }
    // End string node

    // function call
    FunctionCallExpression::FunctionCallExpression() {}
    FunctionCallExpression::FunctionCallExpression(StringNode name, std::vector<std::shared_ptr<Expression>> args) {
        this->name = name;
        this->args = args;
    }
    void FunctionCallExpression::print(std::ostream &o) {
        o << "func ";
        this->name.print(o);
        o << ", args = { ";
        for (int i = 0; i < this->args.size(); i++) {
            this->args[i]->print(o);
            o << ", ";
        }
        o << "}" << std::endl;
    }
    // End function call

    // Block statement
    Block::Block() {}
    Block::Block(std::shared_ptr<Statement> s) {
        this->statements.push_back(s);
        this->type = STATEMENT;
    }
    Block::Block(std::vector<std::shared_ptr<Statement>> s) {
        this->statements = s;
        this->type = STATEMENT;
    }
    void Block::add(std::shared_ptr<Statement> s) {
        this->statements.push_back(s);
    }
    void Block::print(std::ostream &o) {
        PrintContext p;
        this->print(o, p);
    }
    void Block::print(std::ostream &o, PrintContext &p) {
        p.print_indent(o);
        this->print_imp(o);
        p.indent();
        for (int i = 0; i < (int)this->statements.size(); i++) {
            this->statements[i]->print(o, p);
        }
        p.dedent();
    }
    void Block::print_imp(std::ostream &o) {
        o << "Block:" << std::endl;
    }
    // End block

    // GameStatement
    GameStatement::GameStatement() {
        this->name = StringNode();
    }
    GameStatement::GameStatement(StringNode s) {
        this->name = s;
    }
    void GameStatement::print(std::ostream &o) {
        o << "game: { name = ";
        this->name.print(o);
        o << " }" << std::endl;
    }
    // End game statement

    // PlayersStatement
    PlayersStatement::PlayersStatement() {
        this->num = NumberNode();
        this->type = PLAYERS;
    }
    PlayersStatement::PlayersStatement(NumberNode n) {
        this->num = n;
        this->type = PLAYERS;
    }
    void PlayersStatement::print(std::ostream &o) {
        o << "players: { number = ";
        this->num.print(o);
        o << " }" << std::endl;
    }
    // End players statement

    // Board statement
    BoardStatement::BoardStatement() {
        this->name = StringNode();
        this->x = NumberNode();
        this->y = NumberNode();
        this->type = BOARD;
    }
    BoardStatement::BoardStatement(StringNode s, NumberNode x, NumberNode y) {
        this->name = s;
        this->x = x;
        this->y = y;
        this->type = BOARD;
    }
    void BoardStatement::print(std::ostream &o) {
        o << "board: ";
        o << " { name = "; this->name.print(o);
        o << ", x = "; this->x.print(o);
        o << ", y = "; this->y.print(o);
        o << " }" << std::endl;
    }
    // End board statement
    
    // Piece block
    PieceStatement::PieceStatement() {
        this->type = PIECE;
    }
    PieceStatement::PieceStatement(StringNode name, 
                                   NumberNode num, 
                                   std::vector<std::shared_ptr<Expression>> display) {
        this->name = name;
        this->num = num;
        this->display = display;
        this->type = PIECE;
    }
    void PieceStatement::print(std::ostream &o) {
        o << "Piece: ";
        o << " { name = "; this->name.print(o);
        o << ", num = "; this->num.print(o);
        o << ", args = { ";
        for (int i = 0; i < this->display.size(); i++) {
            this->display[i]->print(o);
            o << ", ";
        }
        o << " }";
        o << " }" << std::endl;
    }

    // End piece statement

    // Turn block
    TurnBlock::TurnBlock() {
        this->type = TURN;
    }
    TurnBlock::TurnBlock(std::shared_ptr<Statement> s) {
        this->statements.push_back(s);
        this->type = TURN;
    }
    TurnBlock::TurnBlock(std::vector<std::shared_ptr<Statement>> stmts) {
        this->statements = stmts;
        this->type = TURN;
    }
    void TurnBlock::print_imp(std::ostream &o) {
        o << "Turn: " << std::endl;
    }
    // End turn block

    // Win block
    WinBlock::WinBlock() {
        this->type = WIN;
    }
    WinBlock::WinBlock(std::shared_ptr<Statement> s) {
        this->statements.push_back(s);
        this->type = WIN;
    }
    WinBlock::WinBlock(std::vector<std::shared_ptr<Statement>> stmts) {
        this->statements = stmts;
        this->type = WIN;
    }
    void WinBlock::print_imp(std::ostream &o) {
        o << "Win: " << std::endl;
    }
    // End Win Block


    // End block
    EndBlock::EndBlock() {
        this->type = END;
    }
    EndBlock::EndBlock(std::shared_ptr<Statement> s) {
        this->statements.push_back(s);
        this->type = END;
    }
    EndBlock::EndBlock(std::vector<std::shared_ptr<Statement>> stmts) {
        this->statements = stmts;
        this->type = END;
    }
    void EndBlock::print_imp(std::ostream &o) {
        o << "End: " << std::endl;
    }
    // End End Block

    // ast related functions
    std::shared_ptr<BoardStatement> get_board(Block * ast) {
        for (int i = 0; i < ast->statements.size(); i++) {
            if (ast->statements[i]->get_type() == BOARD) {
                return std::dynamic_pointer_cast<BoardStatement>(ast->statements[i]);
            }
        }
        return NULL;
    }
    std::shared_ptr<PlayersStatement> get_players(Block * ast) {
        for (int i = 0; i < ast->statements.size(); i++) {
            if (ast->statements[i]->get_type() == PLAYERS) {
                return std::dynamic_pointer_cast<PlayersStatement>(ast->statements[i]);
            }
        }
        return NULL;
    }
    std::vector<std::shared_ptr<PieceStatement>> get_pieces(Block * ast) {
        std::vector<std::shared_ptr<PieceStatement>> v;
        for (int i = 0; i < ast->statements.size(); i++) {
            if (ast->statements[i]->get_type() == PIECE) {
                v.push_back(std::dynamic_pointer_cast<PieceStatement>(ast->statements[i]));
            }
        }
        return v;
    }
    std::vector<std::shared_ptr<Statement>> get_statements(Block * ast, Types type) {
        for (int i = 0; i < ast->statements.size(); i++) {
            if (ast->statements[i]->get_type() == type) {
                return std::dynamic_pointer_cast<Block>(ast->statements[i])->statements;
            }
        }
        return std::vector<std::shared_ptr<Statement>>();
    }
}
