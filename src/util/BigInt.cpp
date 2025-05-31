#include "BigInt.hpp"

BigInt::BigInt(const Digit d) {
    if (d > 0) {
        digits.push_back(d);
    }
    set_properties();
}

BigInt::Comp BigInt::comp(const BigInt::Digit d) const {
    switch (len) {
        case 0: return (d == 0 ? EQUAL : LESS);
        case 1: return (digits[0] > d ? GREATER : digits[0] < d ? LESS : EQUAL);
        default: return GREATER;
    }
}

BigInt::Comp BigInt::comp(const BigInt& rhs) const {
    if (len > rhs.len) {
        return GREATER;
    } else if (len < rhs.len) {
        return LESS;
    }

    for (int i = len - 1; i >= 0; i--) {
        ResultSigned result = ResultSigned(digits[i]) - ResultSigned(rhs.digits[i]);
        if (result > 0) {
            return GREATER;
        } else if (result < 0) {
            return LESS;
        }
    };

    return EQUAL;
}

BigInt& BigInt::add(const Digit d) {
    return add(BigInt(d));
}

BigInt& BigInt::add(const BigInt& rhs) {
    int max_len = (len > rhs.len ? len : rhs.len);
    for (int i = max_len - 1; i >= 0; i--) {
        Result result = (i < len ? Result(digits[i]) : 0)
            + (i < rhs.len ? Result(rhs.digits[i]) : 0);
        set_carry_loop(result, i);
    };

    set_properties();
    return *this;
}

BigInt& BigInt::sub_ordered(const Digit d) {
    return sub_ordered(BigInt(d));
}

BigInt& BigInt::sub_ordered(const BigInt& rhs) {
    for (int i = len - 1; i >= 0; i--) {
        ResultSigned result = ResultSigned(digits[i]) - (i < rhs.len ? ResultSigned(rhs.digits[i]) : 0);
        set_carry_loop_signed(result, i);
    };

    set_properties();
    return *this;
}

BigInt& BigInt::mul(const Digit d) {
    return mul(BigInt(d));
}

BigInt& BigInt::mul(const BigInt& rhs) {
    // Shortcut if either side is zero.
    if (len == 0 || rhs.len == 0) {
        digits.clear();
        set_properties();
        return *this;
    }

    for (int i = len - 1; i >= 0; i--) {
        for (int j = rhs.len - 1; j >= 0; j--) {
            Result result = Result(digits[i]) * Result(rhs.digits[j]);
            set_carry_loop(result, i + j);
        };
    };

    set_properties();
    return *this;
}

BigInt& BigInt::mod_nonzero(const Digit d) {
    return mod_nonzero(BigInt(d));
}

BigInt& BigInt::mod_nonzero(const BigInt& rhs) {
    std::vector<Digit> copy (digits);
    digits.clear();
    for (int i = len - 1; i >= 0; i--) {
        unshift(copy[i]);
        while (comp(rhs) != LESS) {
            sub_ordered(rhs);
        }
    }

    set_properties();
    return *this;
}

void BigInt::unshift(const Digit d) {
    digits.insert(digits.begin(), d);
    set_properties();
}

void BigInt::set_properties() {
    // Remove leading 0s.
    for (int i = digits.size() - 1; i >= 0 && digits[i] == 0; i--) {
        digits.pop_back();
    }

    len = digits.size();
    is_one = comp(1) == EQUAL;

    double d = 0.0;
    for (int i = len - 1; i >= 0; i--) {
        d = d * 256.0 + digits[i];
    }
    as_double = d;
}

void BigInt::set_carry_loop(Result carry, const int start_digit) {
    // Clear the start digit.
    if (start_digit < len) {
        digits[start_digit] = 0;
    }

    // If carry is nonzero, distribute its value into the start "digit" and any carryovers.
    for (int d = start_digit; carry > 0; d++) {
        // Ensure that there's a digit for the current index.
        if (d >= digits.size()) {
            digits.resize(d + 1, 0);
        }

        // Get the new value for this digit.
        Result value = digits[d] + carry;
        Digit value_trunc = value % DIGIT_SIZE_FACTOR;

        // Set this digit to the new value (truncated to one byte).
        digits[d] = value_trunc;

        // Update the carryover.
        carry = value / DIGIT_SIZE_FACTOR;
    };
}

void BigInt::set_carry_loop_signed(ResultSigned carry, const int start_digit) {
    // Clear the start digit.
    if (start_digit < len) {
        digits[start_digit] = 0;
    }

    // If carry is nonzero, distribute its value into the start "digit" and any carryovers.
    for (int d = start_digit; carry != 0; d++) {
        // Ensure that there's a digit for the current index.
        if (d >= digits.size()) {
            digits.resize(d + 1, 0);
        }

        // Get the new value for this digit.
        ResultSigned value = digits[d] + carry;
        Digit value_trunc = (value + DIGIT_SIZE_FACTOR) % DIGIT_SIZE_FACTOR;

        // Set this digit to the new value (truncated to one byte).
        digits[d] = value_trunc;

        // Update the carryover, using floor division instead of int division.
        carry = (value + DIGIT_SIZE_FACTOR) / DIGIT_SIZE_FACTOR - 1;
    };
}
