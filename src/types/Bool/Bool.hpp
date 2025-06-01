#pragma once
#include "../Value/Value.hpp"

class Bool : public Value {
    public:

    Bool(const bool);
    static Ptr from_string(const std::string);
    std::string to_string() const override;
    Bool l_not() const;
    Bool l_and(const Bool) const;
    Bool l_or(const Bool) const;
    Bool l_xor(const Bool) const;

    private:

    const bool value;
};
