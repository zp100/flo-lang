#pragma once
#include <cstdint>
#include <string>
#include <vector>

class BigInt {
    public:

    using Digit = uint8_t;

    enum Comp {
        GREATER = 1,
        LESS = -1,
        EQUAL = 0,
    };

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

    private:

    std::vector<Digit> digits;

    void set_properties();
    void set_carry_loop(int, const int);
};
