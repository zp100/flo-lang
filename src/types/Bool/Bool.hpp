#pragma once
#include "../Value/Value.hpp"

class Bool : public Value {
    public:

    Bool(const bool);
    static Ptr from_string(const std::string);
    std::string to_string() const override;
    Bool b_not() const;
    Bool b_and(const Bool) const;
    Bool b_or(const Bool) const;
    Bool b_xor(const Bool) const;

    private:

    const bool value;
};
