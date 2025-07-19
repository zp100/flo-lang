#pragma once
#include <vector>
#include "../AstNode/AstNode.hpp"
#include "../Scanner/Scanner.hpp"

class Parser {
    public:

    Parser(const Scanner);
    std::vector<AstNode> generate_ast() const;

    private:

    const Scanner scanner;
};
