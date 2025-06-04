#include "parse.hpp"

std::vector<Value::Ptr> Parse::parse(std::ifstream& source_file) {
    ParseContext cx = ParseContext();

    while (cx.state != ParseContext::EXIT) {
        cx.next = source_file.get();

        switch (cx.state) {
            case ParseContext::DEFAULT:
                p_default(cx);
            break;

            case ParseContext::COMMENT:
                p_comment(cx);
            break;

            case ParseContext::WORD:
                p_word(cx);
            break;

            case ParseContext::NUMBER:
                p_number(cx);
            break;

            default: ; // NOOP
        }
    }

    return cx.value_list;
}

void Parse::p_default(ParseContext& cx) {
    if (cx.next == '#') {
        // Start comment.
        cx.state = ParseContext::COMMENT;
    } else if (is_word_char(cx.next, true)) {
        // Start word.
        cx.token.push_back(cx.next);
        cx.state = ParseContext::WORD;
    } else if (is_number_char(cx.next, true)) {
        // Start number.
        cx.token.push_back(cx.next);
        cx.state = ParseContext::NUMBER;
    } else if (is_space_char(cx.next) || is_separator_char(cx.next)) {
        // Whitespace or separator.
        // NOOP
    } else {
        // End of file or error.
        cx.state = ParseContext::EXIT;
    }
}

void Parse::p_comment(ParseContext& cx) {
    if (cx.next == '\n') {
        // End comment.
        cx.state = ParseContext::DEFAULT;
    } else if (cx.next == EOF) {
        // End of file.
        cx.state = ParseContext::EXIT;
    } else {
        // Continue comment.
        // NOOP
    }
}

void Parse::p_word(ParseContext& cx) {
    if (is_word_char(cx.next, false)) {
        // Continue word.
        cx.token.push_back(cx.next);
    } else if (is_space_char(cx.next) || is_separator_char(cx.next)) {
        // End word.
        handle_word(cx);
    } else if (cx.next == EOF) {
        // End of file.
        handle_word(cx);
        cx.state = ParseContext::EXIT;
    } else {
        // Error.
        cx.state = ParseContext::EXIT;
    }
}

void Parse::p_number(ParseContext& cx) {
    if (is_number_char(cx.next, false)) {
        // Continue number.
        cx.token.push_back(cx.next);
    } else if (is_space_char(cx.next) || is_separator_char(cx.next)) {
        // End number.
        handle_number(cx);
    } else if (cx.next == EOF) {
        // End of file.
        handle_number(cx);
        cx.state = ParseContext::EXIT;
    } else {
        // Error.
        cx.state = ParseContext::EXIT;
    }
}

void Parse::handle_word(ParseContext& cx) {
    Value::Ptr value;
    if (cx.token == "true" || cx.token == "false") {
        value = Bool::from_string(cx.token);
    } else if (cx.token == "null") {
        value = Null::from_string(cx.token);
    } else {
        Lib::MapType function_map = Lib::getFunctionMap();

        if (function_map.count(cx.token) > 0) {
            Lib::FunctionType _callee_ = function_map[cx.token];
            value = _callee_(cx.value_list);
        } else {
            value = Error::from_string("Invalid function \"" + cx.token + "\" called");
        }

        cx.value_list.clear();
    }

    cx.value_list.push_back(value);
    cx.token.clear();
    cx.state = (value->type_id == Value::T_ERROR ? ParseContext::EXIT : ParseContext::DEFAULT);
}

void Parse::handle_number(ParseContext& cx) {
    Value::Ptr value = Num::from_string(cx.token);

    cx.value_list.push_back(value);
    cx.token.clear();
    cx.state = ParseContext::DEFAULT;
}

bool Parse::is_space_char(const char c) {
    return (
        c == ' ' || c == '\f' || c == '\r' || c == '\t' || c == '\v'
    );
}

bool Parse::is_separator_char(const char c) {
    return (
        c == ' ' || c == '\n'
    );
}

bool Parse::is_word_char(const char c, const bool is_first) {
    return (
        (c >= 'A' && c <= 'Z')
        || (c >= 'a' && c <= 'z')
        || (!is_first && c >= '0' && c <= '9')
        || c == '_'
        || c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^' || c == '~'
        || c == '<' || c == '>' || c == '=' || c == '!' || c == '@'
    );
}

bool Parse::is_number_char(const char c, const bool is_first) {
    return (
        (!is_first && c == '0')
        || (c >= '1' && c <= '9')
        || (!is_first && c == '_')
        || (!is_first && c == 'e')
        || (!is_first && c == 'E')
        || c == '+' || c == '-' || c == '.'
    );
}
