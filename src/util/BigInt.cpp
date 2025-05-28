#include "BigInt.hpp"

BigInt::BigInt(const BigInt::Item b) : bytes(std::vector<BigInt::Item>(1, b)) {
    this->len = bytes.size();
    this->set_properties();
}

BigInt::BigInt(const std::vector<BigInt::Item> b) : bytes(b) {
    this->len = bytes.size();
    this->set_properties();
}

BigInt* BigInt::copy() const {
    return new BigInt(this->bytes);
}

BigInt* BigInt::set_add(const BigInt* const other) {
    int max_len = (this->len > other->len ? this->len : other->len);
    for (int i = max_len - 1; i >= 0; i--) {
        int result = (i < this->len ? this->bytes[i] : 0) + (i < other->len ? other->bytes[i] : 0);
        set_carry_loop(result, i);
    };

    this->set_properties();
    return this;
}

BigInt* BigInt::set_add(const BigInt::Item b) {
    return this->set_add(new BigInt(b));
}

// WARNING: This object must have a larger value than "other" object!
BigInt* BigInt::set_sub_ordered(const BigInt* const other) {
    for (int i = this->len - 1; i >= 0; i--) {
        int result = this->bytes[i] - (i < other->len ? other->bytes[i] : 0);
        set_carry_loop(result, i);
    };

    this->set_properties();
    return this;
}

BigInt* BigInt::set_sub_ordered(const BigInt::Item b) {
    return this->set_sub_ordered(new BigInt(b));
}

BigInt* BigInt::set_mul(const BigInt* const other) {
    for (int i = this->len - 1; i >= 0; i--) {
        for (int j = other->len - 1; j >= 0; j--) {
            int result = this->bytes[i] * other->bytes[j];
            set_carry_loop(result, i + j);
        };
    };

    this->set_properties();
    return this;
}

BigInt* BigInt::set_mul(const BigInt::Item b) {
    return this->set_mul(new BigInt(b));
}

// TODO: Currently only works if "other" has len 1.
// WARNING: "other" object cannot be zero!
BigInt::Pair BigInt::set_div_mod_nonzero(const BigInt* const other) {
    int rem = 0;
    for (int i = this->len - 1; i >= 0; i--) {
        this->bytes[i] = (rem * 256 + this->bytes[i]) / other->bytes[0];
        rem = this->bytes[i] % other->bytes[0];
    };

    this->set_properties();
    return Pair { this, new BigInt(rem) };
}

BigInt::Pair BigInt::set_div_mod_nonzero(const BigInt::Item b) {
    return this->set_div_mod_nonzero(new BigInt(b));
}

BigInt::Comp BigInt::comp(const BigInt* const other) const {
    if (this->len > other->len) {
        return GREATER;
    } else if (this->len < other->len) {
        return LESS;
    }

    for (int i = this->len - 1; i >= 0; i--) {
        int result = this->bytes[i] - other->bytes[i];
        if (result > 0) {
            return GREATER;
        } else if (result < 0) {
            return LESS;
        }
    };

    return EQUAL;
}

BigInt::Comp BigInt::comp(const BigInt::Item value) const {
    if (this->len > 1 || this->bytes[0] > value) {
        return GREATER;
    } else if (this->bytes[0] < value) {
        return LESS;
    }

    return EQUAL;
}

void BigInt::set_properties() {
    this->len = this->bytes.size();

    double d = 0.0;
    for (int i = this->len - 1; i >= 0; i--) {
        d = d * 256.0 + this->bytes[i];
    }
    this->as_double = d;
}

void BigInt::set_carry_loop(int carry, const int start_digit) {
    // If carry is nonzero, distribute its value into the start "digit" and any carryovers.
    for (int digit = start_digit; carry != 0; digit++) {
        // Ensure that there's an item for the current index.
        if (digit >= bytes.size()) {
            this->bytes.resize(digit + 1, 0);
        }

        // Get the new value for this item.
        int value = this->bytes[digit] + carry;
        int value_trunc = (value + 256) % 256;

        // Set this item to the new value (truncated to one byte).
        this->bytes[digit] = value_trunc;

        // Update the carryover.
        carry = (value / 256 + (value < 0 && value_trunc > 0 ? -1 : 0));
    };
}
