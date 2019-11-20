#include "builtins.hpp" 

namespace builtins {
    PieceObj::PieceObj() {}
    PieceObj::PieceObj(int num, std::string name, std::string display) {
        this->num = num;
        this->name = name;
        this->display = display;
    }
    GamePiece::GamePiece() {}
    GamePiece::GamePiece(int owner, std::shared_ptr<PieceObj> desc) {
        this->owner = owner;
        this->desc = desc;
    }
    func_descriptor::func_descriptor() {
        this->func = NULL;
    }
    func_descriptor::func_descriptor(std::string name,
                                     void *(*f)(GameState &,
                                              std::vector<std::shared_ptr<ast::Expression>>),
                                     std::vector<ast::Types> args,
                                     ast::Types ret) {
        this->name = name;
        this->func = f;
        this->args = args;
        this->ret = ret;
    }

    const func_descriptor * map_func(std::string n) {
        for (int i = 0; i < func_map.size(); i++) {
            if (func_map[i].name == n) {
                std::cout << "FOUND FUNC" << std::endl;
                const func_descriptor *t = &(func_map[i]);
                return t;
            }
        } 
        return NULL;
    }
    void * in_a_row(GameState &,
                    std::vector<std::shared_ptr<ast::Expression>> args) {
        // std::shared_ptr<ast::NumberNode> num = std::dynamic_pointer_cast<ast::NumberNode>(args[0]);
        // std::shared_ptr<ast::StringNode> direction = std::dynamic_pointer_cast<ast::StringNode>(args[1]);
        std::cout <<"FUNCTION CALL SUCESS" << std::endl;
        return NULL;
    }
}
