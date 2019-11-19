#ifndef AST_HPP
#define AST_HPP
#include <iostream>
#include <string>
#include <memory>
#include <vector>

namespace ast {
    enum Types { NUMBER, STRING, BOARD, PLAYERS, STATEMENT };
    class PrintContext {
        int indent_level;
        public:
            PrintContext();
            void indent();
            void dedent();
            void print_indent(std::ostream &o);
    };
    class Node {
        public:
            virtual void print(std::ostream &);
            virtual void print(std::ostream &, PrintContext &);
    };
    class Statement : public Node {
        protected:
            Types type;
        public:
            Types get_type();
    };
    class Expression : public Statement {};

    // Primitives
    class NumberNode : public Expression {
        int value;
        public:
            NumberNode();
            NumberNode(int);
            int get_value() const; 
            virtual void print(std::ostream &) override;
    };
    class StringNode : public Expression {
        std::string value;
        public:
            StringNode();
            StringNode(std::string);
            std::string get_value() const; 
            virtual void print(std::ostream &) override;
    };

    // Operations
    class BinaryOpNode : public Expression {
        std::unique_ptr<Expression> left; 
        std::unique_ptr<Expression> right; 
    };
    class AdditionNode : public BinaryOpNode {

    };

    // function call
    class FunctionCallExpression : public Expression {
        StringNode name;
        std::vector<std::shared_ptr<Expression>> args;
        public:
            FunctionCallExpression(); 
            FunctionCallExpression(StringNode, std::vector<std::shared_ptr<Expression>>); 
            virtual void print(std::ostream &) override;
    };
    // End function call

    // Statements
    class Block : public Statement {
        virtual void print_imp(std::ostream &);
        public:
            std::vector<std::shared_ptr<Statement>> statements;
            Block();
            Block(std::shared_ptr<Statement>);
            Block(std::vector<std::shared_ptr<Statement>>);
            void add(std::shared_ptr<Statement>);
            virtual void print(std::ostream &) override;
            virtual void print(std::ostream &, PrintContext &) override;
    };
    class GameStatement : public Statement {
        StringNode name;
        public:
            GameStatement();
            GameStatement(StringNode);
            virtual void print(std::ostream &) override;
    };
    class PlayersStatement : public Statement {
        NumberNode num;
        public:
            PlayersStatement();
            PlayersStatement(NumberNode);
            virtual void print(std::ostream &) override;
    };
    class BoardStatement : public Statement {
        StringNode name;
        NumberNode x;
        NumberNode y;
        public:
            BoardStatement();
            BoardStatement(StringNode, NumberNode, NumberNode);
            virtual void print(std::ostream &) override;
    };
    // Piece Block
    class PieceBlock : public Block {
        StringNode name;
        NumberNode num;
        virtual void print_imp(std::ostream &) override;
        public:
            PieceBlock();
            PieceBlock(std::shared_ptr<Statement>);
            void set_name(StringNode);
            void set_num(NumberNode);
    };
    class PlayerPieceStatement : public Statement {
        NumberNode num;
        StringNode display;
        public:
            PlayerPieceStatement();
            PlayerPieceStatement(NumberNode, StringNode);
            virtual void print(std::ostream &) override;
    };
    // Turn Block
    class TurnBlock : public Block {
        virtual void print_imp(std::ostream &) override;
        public:
            TurnBlock();
            TurnBlock(std::shared_ptr<Statement>);
    };
    class PlaceTurnStatement : public Statement {
        StringNode piece;
        StringNode rule;
        public:
            PlaceTurnStatement();
            PlaceTurnStatement(StringNode, StringNode);
            virtual void print(std::ostream &) override;
    };
    // Other turn statements, probably "move" "remove"

    // Win Block
    class WinBlock : public Block {
        public:
            WinBlock();
            WinBlock(std::shared_ptr<Statement>);
            virtual void print_imp(std::ostream &) override;
    };
    // End Block
    class EndBlock : public Block {
        public:
            EndBlock();
            EndBlock(std::shared_ptr<Statement>);
            virtual void print_imp(std::ostream &) override;
    };

    // ast related functions
    std::shared_ptr<BoardStatement> get_board(Block *);
    std::shared_ptr<PlayersStatement> get_players(Block *);
}
#endif
