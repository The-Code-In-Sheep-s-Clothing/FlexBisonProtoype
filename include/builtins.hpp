#ifndef BUILTINS_HPP
#define BUILTINS_HPP
#include <map>
#include <memory>
#include <vector>
#include "ast.hpp"
#include "interpreter.hpp"

namespace builtins {
    struct func_descriptor {
        std::string name;
        void *(*func)(interpreter::GameState &, 
                      std::vector<std::shared_ptr<ast::Expression>>);
        std::vector<ast::Types> args;
        ast::Types ret;
        func_descriptor();
        func_descriptor(std::string, 
                        void *(*)(interpreter::GameState &,
                                  std::vector<std::shared_ptr<ast::Expression>>),
                        std::vector<ast::Types>,
                        ast::Types);

    };

    const func_descriptor * map_func(std::string);

    void * in_a_row(interpreter::GameState &,
                    std::vector<std::shared_ptr<ast::Expression>>);

    const std::vector<func_descriptor> func_map = {
        func_descriptor("InARow", in_a_row, 
                        std::vector<ast::Types>({ast::NUMBER, ast::STRING, ast::STRING}), 
                        ast::NUMBER),
    };
}
#endif
