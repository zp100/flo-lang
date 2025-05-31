#pragma once
#include <cstdint>
#include <string>
#include <vector>

class BigInt {
    public:

    using Digit = uint32_t;
    using Result = uint64_t;
    using ResultSigned = int64_t;

    enum Comp {
        GREATER = 1,
        LESS = -1,
        EQUAL = 0,
    };

    static const Result DIGIT_SIZE_FACTOR = Result(UINT32_MAX) + 1;
    int len;
    bool is_one;
    double as_double;

    BigInt(const Digit);
    Comp comp(const Digit) const;
    Comp comp(const BigInt&) const;
    BigInt& add(const Digit);
    BigInt& add(const BigInt&);
    BigInt& sub_ordered(const Digit);
    BigInt& sub_ordered(const BigInt&);
    BigInt& mul(const Digit);
    BigInt& mul(const BigInt&);
    BigInt& int_div_nonzero(const Digit);
    BigInt& int_div_nonzero(const BigInt&);

    private:

    std::vector<Digit> digits;

    void unshift(const Digit);
    void set_properties();
    void set_carry_loop(Result, const int);
    void set_carry_loop_signed(ResultSigned, const int);
};
