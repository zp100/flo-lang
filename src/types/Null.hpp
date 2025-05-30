#pragma once
#include "Value.hpp"

class Null : public Value {
    public:

    Null();
    static Ptr from_string(const std::string);
    std::string to_string() const override;
};

