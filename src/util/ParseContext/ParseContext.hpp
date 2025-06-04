#pragma once
#include <string>
#include <vector>
#include "../../types/Value/Value.hpp"

class ParseContext {
    public:

    using ValueList = std::vector<Value::Ptr>;

    enum ParseState {
        DEFAULT,
        COMMENT,
        WORD,

        NUMBER_SIGNED,
        NUMBER,
        NUMBER_DECIMALS,
        NUMBER_SCIENTIFIC_START,
        NUMBER_SCIENTIFIC_SIGNED,
        NUMBER_SCIENTIFIC,

        EXIT,
    };

    ParseState state;
    ValueList value_list;
    std::string token;
    char next;

    ParseContext() : state(DEFAULT) {}
};
