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
        NUMBER,
        EXIT,
    };

    ParseState state;
    ValueList value_list;
    std::string token;
    char next;

    ParseContext() : state(DEFAULT) {}
};
