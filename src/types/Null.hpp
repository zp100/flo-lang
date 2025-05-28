#pragma once
#include <string>
#include "Value.hpp"

class Null : public Value {
    public:

    Null();
    std::string to_string() const;
    Null* copy() const;
};

