#include <map>
#include <memory>
#include <vector>
#include "ast.hpp"

extern std::shared_ptr<ast::BoardStatement> board;
extern std::shared_ptr<ast::PlayersStatement> players;

namespace builtins {
    struct func_descriptor {
        std::string name;
        void *(*func)(std::vector<std::shared_ptr<ast::Expression>>);
        std::vector<ast::Types> args;
        ast::Types ret;
        func_descriptor();
        func_descriptor(std::string, 
                        void *(*)(std::vector<std::shared_ptr<ast::Expression>>),
                        std::vector<ast::Types>,
                        ast::Types);

    };

    void * in_a_row(std::vector<std::shared_ptr<ast::Expression>>);

    const std::vector<func_descriptor> func_map = {
        func_descriptor("InARow", in_a_row, std::vector<ast::Types>(ast::NUMBER), ast::NUMBER),
    };
}
