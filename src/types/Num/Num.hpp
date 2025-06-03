#pragma once
#include <cstdint>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include "../Bool/Bool.hpp"
#include "../Value/Value.hpp"
#include "../../util/BigInt/BigInt.hpp"

class Num : public Value {
    public:

    const bool is_int;
    const short sign;
    const BigInt numerator;
    const BigInt denominator;

    Num(const short, const BigInt&, const BigInt&);
    static Ptr from_string(const std::string);
    std::string to_string() const override;
    Num add(const Num) const;
    Num sub(const Num) const;
    Num mul(const Num) const;
    Num div_nonzero(const Num) const;
    Num mod_nonzero(const Num) const;
    BigInt::Comp comp(const Num) const;

    private:

    Num(); // zero
    Num maybe_simplify() const;
};
