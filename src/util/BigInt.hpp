#pragma once
#include <cstdint>
#include <string>
#include <vector>

class BigInt {
    public:

    using Item = uint8_t;

    enum Comp {
        GREATER = 1,
        LESS = -1,
        EQUAL = 0,
    };

    struct Pair {
        const BigInt* const a;
        const BigInt* const b;
    };

    std::vector<Item> bytes;
    int len;
    double as_double;

    BigInt(const Item);
    BigInt(const std::vector<Item>);
    BigInt* copy() const;
    BigInt* set_add(const BigInt* const);
    BigInt* set_add(const Item);
    BigInt* set_sub_ordered(const BigInt* const);
    BigInt* set_sub_ordered(const Item);
    BigInt* set_mul(const BigInt* const);
    BigInt* set_mul(const Item);
    Pair set_div_mod_nonzero(const BigInt* const);
    Pair set_div_mod_nonzero(const Item);
    Comp comp(const BigInt* const) const;
    Comp comp(const Item) const;

    private:

    void set_properties();
    void set_carry_loop(int, const int);
};
