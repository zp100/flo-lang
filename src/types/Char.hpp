#pragma once
#include <string>
#include "Value.hpp"

class Char : public Value {
    public:

    Char(const char v);
    std::string to_string() const;
    Char* copy() const;

    private:

    const char value;
};
