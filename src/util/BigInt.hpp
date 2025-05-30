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

    static const int DIGIT_SIZE_FACTOR = UINT32_MAX + 1;
    int len;
    bool is_one;
    double as_double;

    BigInt(const Digit);
    Comp comp(const Digit) const;
    Comp comp(const BigInt&) const;
    BigInt& dup() const;
    BigInt& add(const Digit);
    BigInt& add(const BigInt&);
    BigInt& sub(const Digit);
    BigInt& sub(const BigInt&);
    BigInt& mul(const Digit);
    BigInt& mul(const BigInt&);
    BigInt& div(const Digit);
    BigInt& mod(const Digit);

    private:

    std::vector<Digit> digits;

    void set_properties();
    void set_carry_loop(Result, const int);
    void set_carry_loop_signed(ResultSigned, const int);
};
