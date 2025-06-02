#pragma once
#include "../Value/Value.hpp"

class Char : public Value {
    public:

    const char value;

    Char(const char);
    static Ptr from_string(const std::string);
    std::string to_string() const override;
};
