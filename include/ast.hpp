#ifndef AST_HPP
#define AST_HPP
#include <iostream>
#include <string>
#include <memory>
#include <vector>

namespace ast {
    enum Types { NUMBER, STRING, BOARD, PLAYERS, STATEMENT, PIECE, TURN, WIN, END };
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
    class Expression;
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
        public:
            StringNode name;
            std::vector<std::shared_ptr<Expression>> args;
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
        public:
            NumberNode num;
            PlayersStatement();
            PlayersStatement(NumberNode);
            virtual void print(std::ostream &) override;
    };
    class BoardStatement : public Statement {
        StringNode name;
        public:
            NumberNode x;
            NumberNode y;
            BoardStatement();
            BoardStatement(StringNode, NumberNode, NumberNode);
            virtual void print(std::ostream &) override;
    };
    // Piece Statement
    class PieceStatement : public Statement {
        public:
            StringNode name;
            NumberNode num;
            std::vector<std::shared_ptr<Expression>> display;
            PieceStatement();
            PieceStatement(StringNode, NumberNode, std::vector<std::shared_ptr<Expression>>);
            void set_name(StringNode);
            void set_num(NumberNode);
            virtual void print(std::ostream &) override;
    };
    // Turn Block
    class TurnBlock : public Block {
        virtual void print_imp(std::ostream &) override;
        public:
            TurnBlock();
            TurnBlock(std::shared_ptr<Statement>);
            TurnBlock(std::vector<std::shared_ptr<Statement>>);
    };

    // Win Block
    class WinBlock : public Block {
        public:
            WinBlock();
            WinBlock(std::shared_ptr<Statement>);
            WinBlock(std::vector<std::shared_ptr<Statement>>);
            virtual void print_imp(std::ostream &) override;
    };
    // End Block
    class EndBlock : public Block {
        public:
            EndBlock();
            EndBlock(std::shared_ptr<Statement>);
            EndBlock(std::vector<std::shared_ptr<Statement>>);
            virtual void print_imp(std::ostream &) override;
    };

    // ast related functions
    std::shared_ptr<BoardStatement> get_board(Block *);
    std::shared_ptr<PlayersStatement> get_players(Block *);
    std::vector<std::shared_ptr<PieceStatement>> get_pieces(Block *);
    std::vector<std::shared_ptr<Statement>> get_statements(Block *, Types);
}
#endif
