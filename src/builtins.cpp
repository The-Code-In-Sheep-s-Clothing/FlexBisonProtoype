#include "builtins.hpp" 

namespace builtins {
    func_descriptor::func_descriptor() {
        this->func = NULL;
    }
    func_descriptor::func_descriptor(std::string name,
                                     void *(*func)(std::vector<std::shared_ptr<ast::Expression>>),
                                     std::vector<ast::Types> args,
                                     ast::Types ret) {
        this->name = name;
        this->func = func;
        this->args = args;
        this->ret = ret;
    }
    void * in_a_row(std::vector<std::shared_ptr<ast::Expression>> args) {
        std::shared_ptr<ast::NumberNode> num = std::dynamic_pointer_cast<ast::NumberNode>(args[0]);
        std::shared_ptr<ast::StringNode> direction = std::dynamic_pointer_cast<ast::StringNode>(args[1]);
        return NULL;
    }
}
