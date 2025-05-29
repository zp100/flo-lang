#include "BigInt.hpp"

BigInt::BigInt(const Digit d) : digits(std::vector<Digit>(1, d)) {
    set_properties();
}

BigInt::Comp BigInt::comp(const BigInt::Digit d) const {
    if (len > 1 || digits[0] > d) {
        return GREATER;
    } else if (digits[0] < d) {
        return LESS;
    }

    return EQUAL;
}

BigInt::Comp BigInt::comp(const BigInt& rhs) const {
    if (len > rhs.len) {
        return GREATER;
    } else if (len < rhs.len) {
        return LESS;
    }

    for (int i = len - 1; i >= 0; i--) {
        int result = digits[i] - rhs.digits[i];
        if (result > 0) {
            return GREATER;
        } else if (result < 0) {
            return LESS;
        }
    };

    return EQUAL;
}

BigInt& BigInt::dup() const {
    BigInt res (*this);
    return res;
}

BigInt& BigInt::add(const Digit d) {
    return add(BigInt(d));
}

BigInt& BigInt::add(const BigInt& rhs) {
    int max_len = (len > rhs.len ? len : rhs.len);
    for (int i = max_len - 1; i >= 0; i--) {
        int result = (i < len ? digits[i] : 0) + (i < rhs.len ? rhs.digits[i] : 0);
        set_carry_loop(result, i);
    };

    set_properties();
    return *this;
}

BigInt& BigInt::sub(const Digit d) {
    return sub(BigInt(d));
}

BigInt& BigInt::sub(const BigInt& rhs) {
    for (int i = len - 1; i >= 0; i--) {
        int result = digits[i] - (i < rhs.len ? rhs.digits[i] : 0);
        set_carry_loop(result, i);
    };

    set_properties();
    return *this;
}

BigInt& BigInt::mul(const Digit d) {
    return mul(BigInt(d));
}

BigInt& BigInt::mul(const BigInt& rhs) {
    for (int i = len - 1; i >= 0; i--) {
        for (int j = rhs.len - 1; j >= 0; j--) {
            int result = digits[i] * rhs.digits[j];
            set_carry_loop(result, i + j);
        };
    };

    set_properties();
    return *this;
}

void BigInt::set_properties() {
    len = digits.size();
    is_one = comp(1) == EQUAL;

    double d = 0.0;
    for (int i = len - 1; i >= 0; i--) {
        d = d * 256.0 + digits[i];
    }
    as_double = d;
}

void BigInt::set_carry_loop(int carry, const int start_digit) {
    // If carry is nonzero, distribute its value into the start "digit" and any carryovers.
    for (int d = start_digit; carry != 0; d++) {
        // Ensure that there's an item for the current index.
        if (d >= digits.size()) {
            digits.resize(d + 1, 0);
        }

        // Get the new value for this item.
        int value = digits[d] + carry;
        int value_trunc = (value + 256) % 256;

        // Set this item to the new value (truncated to one byte).
        digits[d] = value_trunc;

        // Update the carryover.
        carry = (value / 256 + (value < 0 && value_trunc > 0 ? -1 : 0));
    };
}
