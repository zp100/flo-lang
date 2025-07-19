#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include "compiler/AstNode/AstNode.hpp"
#include "compiler/Parser/Parser.hpp"
#include "compiler/Scanner/Scanner.hpp"
#include "compiler/Token/Token.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Error: Invalid argument count" << std::endl;
        return -1;
    }

    Scanner::FilePtr source_file = std::make_shared<std::ifstream>(argv[1], std::ios::in);
    if (!source_file->is_open()) {
        std::cerr << "Error: Failed to open file " << argv[1] << std::endl;
        return -1;
    }

    Scanner scanner (source_file);
    Parser parser (scanner);
    std::vector<AstNode> abstract_syntax_tree = parser.generate_ast();
    // TODO
}
