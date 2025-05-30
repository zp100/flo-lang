#pragma once
#include "Value.hpp"

class Error : public Value {
    public:

    Error(const std::string);
    static Ptr from_string(const std::string);
    std::string to_string() const override;

    private:

    const std::string error_message;
};
