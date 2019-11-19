#ifndef AST_HPP
#define AST_HPP
#include <iostream>
#include <string>
#include <memory>
#include <vector>

namespace ast {
    class Node {
        public:
            virtual void print(std::ostream &o);
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
    };
    class StringNode : public Expression {
        std::string value;
        public:
            StringNode();
            StringNode(std::string);
            std::string get_value() const; 
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
        std::vector<Statement*> statements;
        public:
            Block();
            Block(Statement*);
            Block(std::vector<Statement*>);
            void print(std::ostream &o) override;
            void add(Statement*);
    };
    class GameStatement : public Statement {
        StringNode name;
        public:
            GameStatement();
            GameStatement(StringNode);
    };
    class PlayersStatement : public Statement {
        NumberNode num;
        public:
            PlayersStatement();
            PlayersStatement(NumberNode);
    };
    class BoardStatement : public Statement {
        StringNode name;
        NumberNode x;
        NumberNode y;
        public:
            BoardStatement();
            BoardStatement(StringNode, NumberNode, NumberNode);
    };
    // Piece Block
    class PieceBlock : public Block {
        StringNode name;
        NumberNode num;
        public:
            PieceBlock();
    };
    class PlayerPieceStatement : public Statement {
        NumberNode num;
        StringNode display;
        public:
            PlayerPieceStatement(NumberNode, StringNode);
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
