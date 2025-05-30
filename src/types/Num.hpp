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

    Num(const int, const BigInt&, const BigInt&);
    static Ptr make();
    static Ptr make(const int, const BigInt::Digit, const BigInt::Digit);
    static Ptr make(const int, const BigInt&, const BigInt&);
    static Ptr from_string(const std::string);
    std::string to_string() const;
    Ptr add(const Ptr) const;
    Ptr sub(const Ptr) const;
    Ptr mul(const Ptr) const;
    Ptr div_nonzero(const Ptr) const;

    private:

    const BigInt numerator;
    const BigInt denominator;
};
