#include "Scanner.hpp"

Scanner::Scanner(FilePtr sf) : source_file(sf), is_empty(false) {
    prep_next_char();
}

Token::Ptr Scanner::get_next_token() {
    while (is_space_char(next_char)) {
        prep_next_char();
    }

    if (is_empty) {
        return std::make_shared<Token>(Token::EMPTY, "");
    }

    std::string raw_text { next_char };
    Token::TokenId id;

    if (is_separator_char(next_char)) {
        prep_next_char();

        id = Token::SEPARATOR;
    } else if (is_identifier_char(next_char, true)) {
        prep_next_char();
        while (is_identifier_char(next_char, false)) {
            raw_text += next_char;
            prep_next_char();
        }
        
        id = Token::IDENTIFIER;
    } else if (is_number_char(next_char, true)) {
        prep_next_char();
        while (is_number_char(next_char, false)) {
            raw_text += next_char;
            prep_next_char();
        }

        id = Token::NUMBER;
    } else if (is_operator_char(next_char, 0)) {
        if (is_operator_continuation_char(next_char)) {
            prep_next_char();
            if (is_operator_char(next_char, 1)) {
                raw_text += next_char;
                prep_next_char();
            }
        } else {
            prep_next_char();
        }

        id = Token::OPERATOR;
    } else {
        prep_next_char();

        id = Token::ERROR;
    }

    return std::make_shared<Token>(id, raw_text);
}

void Scanner::prep_next_char() {
    next_char = source_file->get();
    if (next_char == EOF) {
        is_empty = true;
    }
}

bool Scanner::is_space_char(const char c) const {
    return (
        c == ' ' || c == '\f' || c == '\r' || c == '\t' || c == '\v'
    );
}

bool Scanner::is_separator_char(const char c) const {
    return (
        c == ';' || c == '\n'
    );
}

bool Scanner::is_identifier_char(const char c, const bool is_first) const {
    return (
        (c >= 'A' && c <= 'Z')
        || (c >= 'a' && c <= 'z')
        || c == '_' || c == '$'
        || (!is_first && c >= '0' && c <= '9')
    );
}

bool Scanner::is_number_char(const char c, const bool is_first) const {
    return (
        (c >= '0' && c <= '9')
        || c == '+' || c == '-' || c == '.'
        || (!is_first && c == '_')
        || (!is_first && c == 'e')
        || (!is_first && c == 'E')
    );
}

bool Scanner::is_operator_char(const char c, const int i) const {
    switch (i) {
        case 0: return (
            c == '+' || c == '-' || c == '*' || c == '/' || c == '%'
            || c == ':' || c == ','
            || is_operator_continuation_char(c)
        );
        
        case 1: return (
            c == '='
        );
    }

    return false;
}

bool Scanner::is_operator_continuation_char(const char c) const {
    return (
        c == '=' || c == '!' || c == '<' || c == '>'
    );
}