#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP
#include <memory>
#include "ast.hpp"
namespace interpreter {
    class Interpreter {
        std::shared_ptr<ast::Block> ast;
        public:
            Interpreter();
            Interpreter(ast::Block *);

            void run();
    };
}
#endif
