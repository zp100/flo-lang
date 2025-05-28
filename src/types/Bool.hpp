#pragma once
#include <string>
#include "Value.hpp"

class Bool : public Value {
    public:

    Bool(const bool);
    std::string to_string() const;
    Bool* copy() const;

    private:

    const bool value;
};
