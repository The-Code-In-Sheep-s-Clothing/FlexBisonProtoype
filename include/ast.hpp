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
            int get_value() const; 
    };
    class StringNode : public Expression {
        std::string value;
        public:
            std::string get_value() const; 
    };

    // Operations
    class BinaryOpNode : public Expression {
        std::unique_ptr<Expression> left; 
        std::unique_ptr<Expression> right; 
    };
    class AdditionNode : public BinaryOpNode {

    };
    class Block : public Expression {
        std::vector<Expression> block;
        std::string test;
        public:
            Block();
            Block(std::string);
            void print(std::ostream &o) override;
    };
}
#endif
