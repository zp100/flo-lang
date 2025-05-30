#pragma once
#include <cstdint>
#include <iomanip>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include "Value.hpp"
#include "../util/BigInt.hpp"

class Num : public Value {
    public:

    using Ptr = std::unique_ptr<const Num>;

    const static int SIMPLIFY_MIN_SIZE = 3;
    const bool is_int;
    const int sign;

    Num();
    Num(const int, const BigInt::Digit, const BigInt::Digit);
    Num(const int, const BigInt&, const BigInt&);
    static Num from_string(const std::string);
    std::string to_string() const;
    Num add(const Num) const;
    Num sub(const Num) const;
    Num mul(const Num) const;
    Num div_nonzero(const Num) const;

    private:

    const BigInt numerator;
    const BigInt denominator;
};
