#include <fstream>
#include <iostream>
#include <memory>
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

    // DEBUG
    while (true) {
        const Token::Ptr token = scanner.get_next_token();
        if (token->id != Token::EMPTY) {
            std::cout << "[" << token->id << "] " << (token->raw_text == "\n" ? "\\n" : token->raw_text) << std::endl;
        } else {
            break;
        }
    }
}
