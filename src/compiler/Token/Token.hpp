#pragma once
#include "memory"
#include "string"

class Token {
    public:

    using Ptr = std::shared_ptr<Token>;

    enum TokenId {
        SEPARATOR,
        IDENTIFIER,
        NUMBER,
        OPERATOR,
        ERROR,
        EMPTY,
    };

    TokenId id;
    std::string raw_text;

    Token(TokenId, std::string);
};
