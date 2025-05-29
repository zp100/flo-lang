#pragma once
#include "Value.hpp"

class Null : public Value {
    public:

    Null();
    std::string to_string() const;
};

