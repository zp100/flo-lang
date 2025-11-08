#include "Parser.hpp"

Parser::Parser(Scanner s) : scanner(s) {}

std::vector<AstNode::Ptr> Parser::generate_ast() {
    std::vector<AstNode::Ptr> abstract_syntax_tree {};
    std::vector<AstNode::Ptr> values {};

    while (true) {
        const Token::Ptr token = scanner.get_next_token();
        if (token->id == Token::SEPARATOR) {
            if (!values.empty) {
                ab
            }
        } else if (token->id == Token::WORD) {

        } else if (token->id == Token::NUMBER) {

        } else if (token->id == Token::OPERATOR) {

        } else if (token->id == Token::ERROR) {

        } else if (token->id == Token::EMPTY) {
            break;
        }
    }

    return abstract_syntax_tree;
}
