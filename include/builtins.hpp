#ifndef BUILTINS_HPP
#define BUILTINS_HPP
#include <map>
#include <memory>
#include <vector>
#include "ast.hpp"

namespace builtins {
    class PieceObj {
        public:
            int num;
            std::string name;
            std::string display;
            PieceObj();
            PieceObj(int, std::string, std::string);
    };
    class GamePiece {
        public:
            int owner;
            std::shared_ptr<PieceObj> desc;
            GamePiece();
            GamePiece(int, std::shared_ptr<PieceObj>);
    };
    class GameState {
        public:
            int current_player;
            std::vector<std::vector<std::shared_ptr<GamePiece>>> board;
            std::vector<std::vector<std::shared_ptr<PieceObj>>> pieces;
    };
    struct func_descriptor {
        std::string name;
        void *(*func)(GameState &, 
                      std::vector<std::shared_ptr<ast::Expression>>);
        std::vector<ast::Types> args;
        ast::Types ret;
        func_descriptor();
        func_descriptor(std::string, 
                        void *(*)(GameState &,
                                  std::vector<std::shared_ptr<ast::Expression>>),
                        std::vector<ast::Types>,
                        ast::Types);

    };

    const func_descriptor * map_func(std::string);

    void * in_a_row(GameState &,
                    std::vector<std::shared_ptr<ast::Expression>>);

    void * place(GameState &,
                 std::vector<std::shared_ptr<ast::Expression>>);

    void * is_full(GameState &,
                    std::vector<std::shared_ptr<ast::Expression>>);

    const std::vector<func_descriptor> func_map = {
        func_descriptor("InARow", in_a_row, 
                        std::vector<ast::Types>({ast::NUMBER, ast::STRING, ast::STRING}), 
                        ast::NUMBER),
        func_descriptor("Place", place, 
                        std::vector<ast::Types>({ast::STRING, ast::STRING}), 
                        ast::NUMBER),
        func_descriptor("IsFull", is_full, 
                        std::vector<ast::Types>({}), 
                        ast::NUMBER),
    };
}
#endif
