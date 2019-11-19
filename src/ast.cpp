#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "ast.hpp"

namespace ast {
    void Node::print(std::ostream &o) {
        o << "trash node" << std::endl;
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

    // Block
    Block::Block() {

    }
    Block::Block(Statement *s) {
        this->statements.push_back(s);
    }
    Block::Block(std::vector<Statement*> s) {
        this->statements = s;
    }
    void Block::print(std::ostream &o) {
        for (int i = 0; i < (int)this->statements.size(); i++) {
            o << "Something" << std::endl;
        }
    }
    void Block::add(Statement *s) {
        this->statements.push_back(s);
    }

    // PlayerPieceStatement
    PlayerPieceStatement::PlayerPieceStatement(NumberNode n, StringNode s) {
        this->num = n;
        this->display = s;
    }
}
