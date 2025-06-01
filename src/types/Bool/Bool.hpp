#pragma once
#include "../Value/Value.hpp"

class Bool : public Value {
    public:

    Bool(const bool);
    static Ptr from_string(const std::string);
    std::string to_string() const override;

    private:

    const bool value;
};
