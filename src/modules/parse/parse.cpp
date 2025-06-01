#include "parse.hpp"

std::vector<Value::Ptr> parse(std::ifstream& source_file) {
    ParseContext cx = ParseContext();

    while (cx.state != ParseContext::EXIT) {
        cx.next = source_file.get();

        switch (cx.state) {
            case ParseContext::DEFAULT:
                parse_default(cx);
            break;

            case ParseContext::COMMENT:
                parse_comment(cx);
            break;

            case ParseContext::NUMBER_SIGNED:
                parse_number_signed(cx);
            break;

            case ParseContext::NUMBER:
                parse_number(cx);
            break;

            case ParseContext::NUMBER_DECIMALS:
                parse_number_decimals(cx);
            break;

            case ParseContext::NUMBER_SCIENTIFIC_START:
                parse_number_scientific_start(cx);
            break;

            case ParseContext::NUMBER_SCIENTIFIC_SIGNED:
                parse_number_scientific_signed(cx);
            break;

            case ParseContext::NUMBER_SCIENTIFIC:
                parse_number_scientific(cx);
            break;

            case ParseContext::CALL_START:
                parse_call_start(cx);
            break;

            case ParseContext::FUNCTION_NAME:
                parse_function_name(cx);
            break;

            default: ; // NOOP
        }
    }

    return cx.value_list;
}

void parse_default(ParseContext& cx) {
    if (cx.next == '#') {
        // Start comment.
        cx.state = ParseContext::COMMENT;
    } else if (cx.next == '-') {
        // Start number.
        cx.token.push_back(cx.next);
        cx.state = ParseContext::NUMBER_SIGNED;
    } else if (cx.next >= '0' && cx.next <= '9') {
        // Start number.
        cx.token.push_back(cx.next);
        cx.state = ParseContext::NUMBER;
    } else if (cx.next == '.') {
        // Start number.
        cx.token.push_back(cx.next);
        cx.state = ParseContext::NUMBER_DECIMALS;
    } else if ((cx.next >= 'A' && cx.next <= 'Z') || cx.next == '_' || (cx.next >= 'a' && cx.next <= 'z')) {
        // Start word.
        cx.token.push_back(cx.next);
        cx.state = ParseContext::WORD;
    } else if (cx.next == ':') {
        // Call function.
        cx.state = ParseContext::CALL_START;
    } else if (cx.next == '\t' || cx.next == '\n' || cx.next == '\v' || cx.next == '\f' || cx.next == '\r' || cx.next == ' ' || cx.next == ';') {
        // Whitespace.
        // NOOP
    } else {
        // Error or end of file.
        cx.state = ParseContext::EXIT;
    }
}

void parse_comment(ParseContext& cx) {
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

void parse_number_signed(ParseContext& cx) {
    if (cx.next >= '0' && cx.next <= '9') {
        // Continue number.
        cx.token.push_back(cx.next);
        cx.state = ParseContext::NUMBER;
    } else if (cx.next == '.') {
        // Switch to decimal places.
        cx.token.push_back(cx.next);
        cx.state = ParseContext::NUMBER_DECIMALS;
    } else {
        // Error.
        cx.state = ParseContext::EXIT;
    }
}

void parse_number(ParseContext& cx) {
    if ((cx.next >= '0' && cx.next <= '9') || cx.next == '_') {
        // Continue number.
        cx.token.push_back(cx.next);
    } else if (cx.next == '.') {
        // Switch to decimal places.
        cx.token.push_back(cx.next);
        cx.state = ParseContext::NUMBER_DECIMALS;
    } else if (cx.next == 'E' || cx.next == 'e') {
        // Switch to scientific notation exponent.
        cx.token.push_back(cx.next);
        cx.state = ParseContext::NUMBER_SCIENTIFIC_START;
    } else if (cx.next == '\t' || cx.next == '\n' || cx.next == '\v' || cx.next == '\f' || cx.next == '\r' || cx.next == ' ' || cx.next == ';' || cx.next == EOF) {
        // End number.
        Value::Ptr value = Num::from_string(cx.token);
        cx.value_list.push_back(value);
        cx.token.clear();
        cx.state = ParseContext::DEFAULT;
    } else {
        // Error.
        cx.state = ParseContext::EXIT;
    }
}

void parse_number_decimals(ParseContext& cx) {
    if (cx.next >= '0' && cx.next <= '9') {
        // Continue number.
        cx.token.push_back(cx.next);
    } else if (cx.next == 'E' || cx.next == 'e') {
        // Switch to scientific notation exponent.
        cx.token.push_back(cx.next);
        cx.state = ParseContext::NUMBER_SCIENTIFIC_START;
    } else if (cx.next == '\t' || cx.next == '\n' || cx.next == '\v' || cx.next == '\f' || cx.next == '\r' || cx.next == ' ' || cx.next == ';' || cx.next == EOF) {
        // End number.
        Value::Ptr value = Num::from_string(cx.token);
        cx.value_list.push_back(value);
        cx.token.clear();
        cx.state = ParseContext::DEFAULT;
    } else {
        // Error.
        cx.state = ParseContext::EXIT;
    }
}

void parse_number_scientific_start(ParseContext& cx) {
    if (cx.next == '-') {
        // Continue number.
        cx.token.push_back(cx.next);
        cx.state = ParseContext::NUMBER_SCIENTIFIC_SIGNED;
    } else if (cx.next >= '0' && cx.next <= '9') {
        // Continue number.
        cx.token.push_back(cx.next);
        cx.state = ParseContext::NUMBER_SCIENTIFIC;
    } else {
        // Error.
        cx.state = ParseContext::EXIT;
    }
}

void parse_number_scientific_signed(ParseContext& cx) {
    if (cx.next >= '0' && cx.next <= '9') {
        // Continue number.
        cx.token.push_back(cx.next);
        cx.state = ParseContext::NUMBER_SCIENTIFIC;
    } else {
        // Error.
        cx.state = ParseContext::EXIT;
    }
}

void parse_number_scientific(ParseContext& cx) {
    if (cx.next >= '0' && cx.next <= '9') {
        // Continue number.
        cx.token.push_back(cx.next);
    } else if (cx.next == '\t' || cx.next == '\n' || cx.next == '\v' || cx.next == '\f' || cx.next == '\r' || cx.next == ' ' || cx.next == ';' || cx.next == EOF) {
        // End number.
        Value::Ptr value = Num::from_string(cx.token);
        cx.value_list.push_back(value);
        cx.token.clear();
        cx.state = ParseContext::DEFAULT;
    } else {
        // Error.
        cx.state = ParseContext::EXIT;
    }
}

void parse_word(ParseContext& cx) {
    if ((cx.next >= '0' && cx.next <= '9') || (cx.next >= 'A' && cx.next <= 'Z') || cx.next == '_' || (cx.next >= 'a' && cx.next <= 'z')) {
        // Continue word.
        cx.token.push_back(cx.next);
    } else if (cx.next == '\t' || cx.next == '\n' || cx.next == '\v' || cx.next == '\f' || cx.next == '\r' || cx.next == ' ' || cx.next == ';' || cx.next == EOF) {
        // // End word.
        // Value value (Value::FUNCTION, cx.token);

        // if (cx.token == "true") {
        //     value.type = Value::KEYWORD;
        //     value.keyword = Value::K_TRUE;
        // } else if (cx.token == "false") {
        //     value.type = Value::KEYWORD;
        //     value.keyword = Value::K_FALSE;
        // } else if (cx.token == "null") {
        //     value.type = Value::KEYWORD;
        //     value.keyword = Value::K_NULL;
        // }

        // cx.value_list.push_back(value);
        cx.token.clear();
        cx.state = ParseContext::DEFAULT;
    } else {
        // Error.
        cx.state = ParseContext::EXIT;
    }
}

void parse_call_start(ParseContext& cx) {
    if ((cx.next >= 'A' && cx.next <= 'Z') || cx.next == '_' || (cx.next >= 'a' && cx.next <= 'z')) {
        // Start word.
        cx.token.push_back(cx.next);
        cx.state = ParseContext::FUNCTION_NAME;
    } else {
        // Error.
        cx.state = ParseContext::EXIT;
    }
}

void parse_function_name(ParseContext& cx) {
    if ((cx.next >= '0' && cx.next <= '9') || (cx.next >= 'A' && cx.next <= 'Z') || cx.next == '_' || (cx.next >= 'a' && cx.next <= 'z')) {
        // Continue function name.
        cx.token.push_back(cx.next);
    } else if (cx.next == '\t' || cx.next == '\n' || cx.next == '\v' || cx.next == '\f' || cx.next == '\r' || cx.next == ' ' || cx.next == ';' || cx.next == EOF) {
        // End function name.
        if (cx.token == "true" || cx.token == "false" || cx.token == "null") {
            // Error.
            cx.state = ParseContext::EXIT;
            return;
        }

        Value::ValueId return_type_id = call_function(cx);
        cx.state = (return_type_id == Value::T_ERROR ? ParseContext::EXIT : ParseContext::DEFAULT);
    } else if (cx.next == EOF) {
        // End of file.
        call_function(cx);
        cx.state = ParseContext::EXIT;
    } else {
        // Error.
        cx.state = ParseContext::EXIT;
    }
}

Value::ValueId call_function(ParseContext& cx) {
    MapType function_map = getFunctionMap();

    Value::Ptr value;
    if (function_map.count(cx.token) > 0) {
        FunctionType _callee_ = function_map[cx.token];
        value = _callee_(cx);
    } else {
        value = Error::from_string("Invalid function \"" + cx.token + "\" called");
    }

    cx.value_list.clear();
    cx.value_list.push_back(value);
    cx.token.clear();
    return value->type_id;
}
