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
    void * in_a_row(GameState &gs, 
                    std::vector<std::shared_ptr<ast::Expression>> args) {
        int length = (std::dynamic_pointer_cast<ast::NumberNode>(args[0]))->get_value();
        std::string piecetype = (std::dynamic_pointer_cast<ast::StringNode>(args[1]))->get_value();
        std::string direction = (std::dynamic_pointer_cast<ast::StringNode>(args[2]))->get_value();


        if(direction == "Vertical" || direction == "AllDirections"){
            for(int x = 0; x < gs.board.size(); x++){
                for(int y = 0; y < gs.board[x].size() - length; y++){
                    if(gs.board[x][y]->desc->name == piecetype){
                        int count = 1;
                        int player = gs.board[x][y]->owner;
    
                        for(int l = 1; l < length; l++){
                            if(gs.board[x][y+l]->desc->name == piecetype &&
                                    gs.board[x][y+l]->owner == player){
                                count++;
                            }
                        }

                        if(count == length){
                            return new ast::NumberNode(player);
                        }
                    }
                }
            }
        }

        if(direction == "Horizontal" || direction == "AllDirections"){
            for(int x = 0; x < gs.board.size() - length; x++){
                for(int y = 0; y < gs.board[x].size(); y++){
                    if(gs.board[x][y]->desc->name == piecetype){
                        int count = 1;
                        int player = gs.board[x][y]->owner;
    
                        for(int l = 1; l < length; l++){
                            if(gs.board[x+l][y]->desc->name == piecetype &&
                                    gs.board[x+l][y]->owner == player){
                                count++;
                            }
                        }

                        if(count == length){
                            return new ast::NumberNode(player);
                        }
                    }
                }
            }
        }
        if(direction == "Diagonal" || direction == "AllDirections"){
            for(int x = 0; x < gs.board.size() - length; x++){
                for(int y = 0; y < gs.board[x].size() - length; y++){
                    if(gs.board[x][y]->desc->name == piecetype){
                        int count = 1;
                        int player = gs.board[x][y]->owner;
    
                        for(int l = 1; l < length; l++){
                            if(gs.board[x+l][y+l]->desc->name == piecetype &&
                                    gs.board[x+l][y+l]->owner == player){
                                count++;
                            }
                        }

                        if(count == length){
                            return new ast::NumberNode(player);
                        }
                    }
                }
            }
        }
        if(direction == "Diagonal" || direction == "AllDirections"){
            for(int x = 0; x < gs.board.size()-length; x++){
                for(int y = 2; y < gs.board[x].size(); y++){
                    if(gs.board[x][y]->desc->name == piecetype){
                        int count = 1;
                        int player = gs.board[x][y]->owner;
    
                        for(int l = 1; l < length; l++){
                            if(gs.board[x+l][y-l]->desc->name == piecetype &&
                                    gs.board[x+l][y-l]->owner == player){
                                count++;
                            }
                        }

                        if(count == length){
                            return new ast::NumberNode(player);
                        }
                    }
                }
            }
        }

        std::cout <<"FUNCTION CALL SUCESS" << std::endl;
        return NULL;
    }
}
