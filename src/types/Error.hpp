#pragma once
#include "Value.hpp"

class Error : public Value {
    public:

    Error(const std::string);
    std::string to_string() const;

    private:

    const std::string error_message;
};
