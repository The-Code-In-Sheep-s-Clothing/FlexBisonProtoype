#include "interpreter.hpp"

namespace interpreter {
    Interpreter::Interpreter() {}
    Interpreter::Interpreter(ast::Block *ast) {
        this->ast = std::shared_ptr<ast::Block>(ast);
    }
}
