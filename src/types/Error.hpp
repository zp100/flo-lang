#pragma once
#include <string>
#include "Value.hpp"

class Error : public Value {
    public:

    Error(const std::string);
    std::string to_string() const;
    Error* copy() const;

    private:

    const std::string error_message;
};
