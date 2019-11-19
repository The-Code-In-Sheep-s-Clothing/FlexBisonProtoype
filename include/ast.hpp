#ifndef AST_HPP
#define AST_HPP
#include <iostream>
#include <string>
#include <memory>
#include <vector>

namespace ast {
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
    class Expression : public Node {};
    class Statement : public Node {};

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

    // Statements
    class Block : public Statement {
        protected:
            std::vector<std::shared_ptr<Statement>> statements;
        public:
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
            virtual void print(std::ostream &, PrintContext &) override;
    };
    class PlayersStatement : public Statement {
        NumberNode num;
        public:
            PlayersStatement();
            PlayersStatement(NumberNode);
            virtual void print(std::ostream &) override;
            virtual void print(std::ostream &, PrintContext &) override;
    };
    class BoardStatement : public Statement {
        StringNode name;
        NumberNode x;
        NumberNode y;
        public:
            BoardStatement();
            BoardStatement(StringNode, NumberNode, NumberNode);
            virtual void print(std::ostream &) override;
            virtual void print(std::ostream &, PrintContext &) override;
    };
    // Piece Block
    class PieceBlock : public Block {
        StringNode name;
        NumberNode num;
        public:
            PieceBlock();
            PieceBlock(std::shared_ptr<Statement>);
            void set_name(StringNode);
            void set_num(NumberNode);
            // virtual void print(std::ostream &) override;
            virtual void print(std::ostream &, PrintContext &) override;
    };
    class PlayerPieceStatement : public Statement {
        NumberNode num;
        StringNode display;
        public:
            PlayerPieceStatement(NumberNode, StringNode);
            virtual void print(std::ostream &) override;
            virtual void print(std::ostream &, PrintContext &) override;
    };
    // Turn Block
    class TurnBlock : public Block {
        public:
            TurnBlock();
    };
    class ActionStatement : public Statement {
        public:
            ActionStatement();
    };
    // Win Block
    class WinBlock : public Block {
        StringNode name;
        public:
            WinBlock();
    };
    class WinConditionStatement : public Statement {
        StringNode name;
        public:
            WinConditionStatement();
    };
}
#endif
