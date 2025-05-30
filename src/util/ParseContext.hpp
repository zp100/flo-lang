#pragma once
#include <string>
#include <vector>
#include "../types/Value.hpp"

class ParseContext {
    public:

    enum ParseState {
        DEFAULT,
        COMMENT,

        NUMBER_SIGNED,
        NUMBER,
        NUMBER_DECIMALS,
        NUMBER_SCIENTIFIC_START,
        NUMBER_SCIENTIFIC_SIGNED,
        NUMBER_SCIENTIFIC,

        WORD,
        CALL_START,
        FUNCTION_NAME,
        EXIT,
    };

    ParseState state;
    std::vector<Value::Ptr> value_list;
    std::string token;
    char next;

    ParseContext() : state(DEFAULT) {}
};
