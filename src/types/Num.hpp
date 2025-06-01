#pragma once
#include <cstdint>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include "Value.hpp"
#include "../util/BigInt.hpp"

class Num : public Value {
    public:

    const bool is_int;
    const short sign;

    Num(const short, const BigInt&, const BigInt&);
    static Ptr from_string(const std::string);
    std::string to_string() const override;
    Num add(const Num) const;
    Num sub(const Num) const;
    Num mul(const Num) const;
    Num div_nonzero(const Num) const;
    Num mod_nonzero(const Num) const;

    private:

    const BigInt numerator;
    const BigInt denominator;

    Num(); // zero
};
