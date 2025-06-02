#pragma once
#include "../Value/Value.hpp"

class Error : public Value {
    public:

    const std::string error_message;

    Error(const std::string);
    static Ptr from_string(const std::string);
    std::string to_string() const override;
};
