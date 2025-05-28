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

    const static int SIMPLIFY_MIN_SIZE = 3;
    const int sign;
    const bool is_int;

    static Num* from_string(const std::string);
    static Num* sum(const std::vector<Num*>* const);
    static Num* prod(const std::vector<Num*>* const);
    Num();
    Num(const int, const BigInt::Item, const BigInt::Item);
    Num(const int, const BigInt* const, const BigInt* const);
    std::string to_string() const;
    Num* copy() const;
    Num* add(const Num* const) const;
    Num* sub(const Num* const) const;
    Num* mul(const Num* const) const;
    Num* div_nonzero(const Num* const) const;

    private:

    enum SubtractSide {
        A_SIDE,
        B_SIDE,
    };

    const BigInt* const numerator;
    const BigInt* const denominator;
};
