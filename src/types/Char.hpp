#pragma once
#include "Value.hpp"

class Char : public Value {
    public:

    Char(const char c);
    std::string to_string() const;

    private:

    const char value;
};
