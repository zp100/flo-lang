#pragma once
#include <vector>
#include "../AstNode/AstNode.hpp"
#include "../Scanner/Scanner.hpp"
#include "../Token/Token.hpp"

class Parser {
    public:

    Parser(Scanner);
    std::vector<AstNode::Ptr> generate_ast();

    private:

    Scanner scanner;
};
