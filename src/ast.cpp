#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "ast.hpp"

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
        o << "Generic Node" << std::endl;
    }

    // NumberNode
    NumberNode::NumberNode() {
        this->value = 0;
    }
    NumberNode::NumberNode(int n) {
        this->value = n;
    }
    int NumberNode::get_value() const {
        return this->value;
    }
    void NumberNode::print(std::ostream &o) {
        o << this->value;
    }

    // StringNode
    StringNode::StringNode() {
        this->value = "";
    }
    StringNode::StringNode(std::string s) {
        this->value = s;
    }
    std::string StringNode::get_value() const {
        return this->value;
    }
    void StringNode::print(std::ostream &o) {
        o << "\"" << this->value << "\"";
    }

    // Block statement
    Block::Block() {}
    Block::Block(std::shared_ptr<Statement> s) {
        this->statements.push_back(s);
    }
    Block::Block(std::vector<std::shared_ptr<Statement>> s) {
        this->statements = s;
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
        o << "Block:" << std::endl;
        p.indent();
        for (int i = 0; i < (int)this->statements.size(); i++) {
            this->statements[i]->print(o, p);
        }
        p.dedent();
    }

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
    void GameStatement::print(std::ostream &o, PrintContext &p) {
        p.print_indent(o);
        this->print(o);
    }

    // PlayersStatement
    PlayersStatement::PlayersStatement() {
        this->num = NumberNode();
    }
    PlayersStatement::PlayersStatement(NumberNode n) {
        this->num = n;
    }
    void PlayersStatement::print(std::ostream &o) {
        o << "players: { number = ";
        this->num.print(o);
        o << " }" << std::endl;
    }
    void PlayersStatement::print(std::ostream &o, PrintContext &p) {
        p.print_indent(o);
        this->print(o);
    }

    // Board statement
    BoardStatement::BoardStatement() {
        this->name = StringNode();
        this->x = NumberNode();
        this->y = NumberNode();
    }
    BoardStatement::BoardStatement(StringNode s, NumberNode x, NumberNode y) {
        this->name = s;
        this->x = x;
        this->y = y;
    }
    void BoardStatement::print(std::ostream &o) {
        o << "board: ";
        o << " { name = "; this->name.print(o);
        o << ", x = "; this->x.print(o);
        o << ", y = "; this->y.print(o);
        o << " }" << std::endl;
    }
    void BoardStatement::print(std::ostream &o, PrintContext &p) {
        p.print_indent(o);
        this->print(o);
    }
    
    // Piece block
    PieceBlock::PieceBlock() {
        this->name = StringNode();
        this->num = NumberNode();
    }
    PieceBlock::PieceBlock(std::shared_ptr<Statement> s) {
        this->statements.push_back(s);
    }
    void PieceBlock::set_name(StringNode s) {
        this->name = s;
    }
    void PieceBlock::set_num(NumberNode n) {
        this->num = n;
    }
    void PieceBlock::print(std::ostream &o, PrintContext &p) {
        p.print_indent(o);
        o << "Piece Block: ";
        o << " { name = "; this->name.print(o);
        o << ", num = "; this->num.print(o);
        o << " }" << std::endl;
        p.indent();
        for (int i = 0; i < (int)this->statements.size(); i++) {
            this->statements[i]->print(o, p);
        }
        p.dedent();
    }

    // PlayerPieceStatement
    PlayerPieceStatement::PlayerPieceStatement(NumberNode n, StringNode s) {
        this->num = n;
        this->display = s;
    }
    void PlayerPieceStatement::print(std::ostream &o) {
        o << "piece: ";
        o << " { player_num = "; this->num.print(o);
        o << ", display = "; this->display.print(o);
        o << " }" << std::endl;
    }
    void PlayerPieceStatement::print(std::ostream &o, PrintContext &p) {
        p.print_indent(o);
        this->print(o);
    }

}
