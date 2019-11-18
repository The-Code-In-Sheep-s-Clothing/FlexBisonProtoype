#include <iostream>
#include <string>
#include <memory>
#include "ast.hpp"

namespace ast {
    void Node::print(std::ostream &o) {
        o << "trash node" << std::endl;
    }

    // Block
    Block::Block() {

    }
    Block::Block(std::string s) {
        this->test = s;
    }
    void Block::print(std::ostream &o) {
        o << this->test << std::endl;
    }
}
