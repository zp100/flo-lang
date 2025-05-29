#pragma once
#include "Value.hpp"

class Bool : public Value {
    public:

    Bool(const bool);
    std::string to_string() const;
    
    private:
    
    const bool value;
};
