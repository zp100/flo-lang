#include "Num.hpp"

// TODO: For now, this function assumes that the given string represents a valid number.
Num* Num::from_string(const std::string str) {
    int new_s = 1;
    BigInt* const new_n = new BigInt(0);
    BigInt* const new_d = new BigInt(1);
    bool in_decimals = false;

    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '-') {
            new_s = -1;
        } else if (str[i] == '.') {
            in_decimals = true;
        } else if (str[i] >= '0' && str[i] <= '9') {
            int digit = str[i] - '0';
            new_n->set_mul(BigInt::Item(10))->set_add(digit);
            if (in_decimals) {
                new_d->set_mul(10);
            }
        }
    }

    return new Num(
        new_s,
        new_n,
        new_d
    );
}

Num::Num() : sign(0), is_int(true), numerator(new BigInt(0)), denominator(new BigInt(1)) {
    this->type_id = T_NUM;
}

Num::Num(const int s, const BigInt::Item n, const BigInt::Item d) : sign(s), is_int(d == 1), numerator(new BigInt(n)), denominator(new BigInt(d)) {
    this->type_id = T_NUM;
}

Num::Num(const int s, const BigInt* const big_n, const BigInt* const big_d) : sign(s), is_int(big_d->comp(1) == BigInt::EQUAL), numerator(big_n), denominator(big_d) {
    this->type_id = T_NUM;
}

// DEBUG
std::string Num::to_string() const {
    if (this->sign == 0) {
        return "0";
    }

    double value = this->sign * this->numerator->as_double / this->denominator->as_double;
    std::stringstream stream;
    if (this->denominator->comp(2) == BigInt::LESS) {
        stream << std::fixed << std::setprecision(0);
    }
    stream << value;
    return stream.str();
}

Num* Num::copy() const {
    return new Num(
        this->sign,
        this->numerator,
        this->denominator
    );
}

Num* Num::add(const Num* const other) const {
    // If either number is zero, return the other number.
    // ex: (+8) + (0) == (+8), or (0) + (-8) == (-8)
    if (other->sign == 0) {
        return this->copy();
    } else if (this->sign == 0) {
        return other->copy();
    }

    BigInt* const this_n_scaled = this->numerator->copy()->set_mul(other->denominator);
    BigInt* const other_n_scaled = this->denominator->copy()->set_mul(other->numerator);
    const BigInt::Comp comp_sign = this_n_scaled->comp(other_n_scaled);
    if (comp_sign == BigInt::EQUAL) {
        if (this->sign == other->sign) {
            // Equal magnitues and same signs: Double.
            // ex: (+6) + (+6) == (+12), or (-6) + (-6) == (-12)
            return new Num(
                this->sign,
                this->numerator->copy()->set_mul(2),
                this->denominator
            );
        } else {
            // Equal magnitudes but opposite signs: Zero.
            // ex: (+6) + (-6) == (0), or (-6) + (+6) == (0)
            return new Num();
        }
    }

    BigInt* const d_scaled = this->denominator->copy()->set_mul(other->denominator);
    if (this->sign == 1 && other->sign == -1 && comp_sign == BigInt::GREATER) {
        // Subtract.
        // ex: (+7) + (-5) == (+2)
        return new Num(
            1,
            this_n_scaled->set_sub_ordered(other_n_scaled),
            d_scaled
        );
    } else if (this->sign == 1 && other->sign == -1 && comp_sign == BigInt::LESS) {
        // Subtract reversed, then negate the result.
        // ex: (+5) + (-7) == (-2)
        return new Num(
            -1,
            other_n_scaled->set_sub_ordered(this_n_scaled),
            d_scaled
        );
    } else if (this->sign == -1 && other->sign == 1 && comp_sign == BigInt::GREATER) {
        // Subtract, then negate the result.
        // ex: (-7) + (+5) == (-2)
        return new Num(
            -1,
            this_n_scaled->set_sub_ordered(other_n_scaled),
            d_scaled
        );
    } else if (this->sign == -1 && other->sign == 1 && comp_sign == BigInt::LESS) {
        // Subtract reversed.
        // ex: (-5) + (+7) == (+2)
        return new Num(
            1,
            other_n_scaled->set_sub_ordered(this_n_scaled),
            d_scaled
        );
    } else {
        // Add.
        // ex: (+7) + (+5) == (+12), or (-7) + (-5) == (-12)
        // ex: (+5) + (+7) == (+12), or (-5) + (-7) == (-12)
        return new Num(
            this->sign,
            this_n_scaled->set_add(other_n_scaled),
            d_scaled
        );
    }
}

Num* Num::sub(const Num* const other) const {
    // If the subtrahend is zero, return this.
    // ex: (+8) - (0) == (+8), or (-8) - (0) == (-8)
    if (other->sign == 0) {
        return this->copy();
    }

    BigInt* const this_n_scaled = this->numerator->copy()->set_mul(other->denominator);
    BigInt* const other_n_scaled = this->denominator->copy()->set_mul(other->numerator);
    const BigInt::Comp comp_sign = this_n_scaled->comp(other_n_scaled);
    if (comp_sign == BigInt::EQUAL) {
        if (this->sign == other->sign) {
            // Equal magnitues and same signs: Zero.
            // ex: (+6) - (+6) == (0), or (-6) - (-6) == (0)
            return new Num();
        } else {
            // Equal magnitudes but opposite signs: Double.
            // ex: (+6) - (-6) == (+12), or (-6) - (+6) == (-12)
            return new Num(
                this->sign,
                this->numerator->copy()->set_mul(2),
                this->denominator
            );
        }
    }

    BigInt* const d_scaled = this->denominator->copy()->set_mul(other->denominator);
    if (this->sign == 1 && other->sign == 1 && comp_sign == BigInt::GREATER) {
        // Subtract.
        // ex: (+7) - (+5) == (+2)
        return new Num(
            1,
            this_n_scaled->set_sub_ordered(other_n_scaled),
            d_scaled
        );
    } else if (this->sign == 1 && other->sign == 1 && comp_sign == BigInt::LESS) {
        // Subtract reversed, then negate the result.
        // ex: (+5) - (+7) == (-2)
        return new Num(
            -1,
            other_n_scaled->set_sub_ordered(this_n_scaled),
            d_scaled
        );
    } else if (this->sign == -1 && other->sign == -1 && comp_sign == BigInt::GREATER) {
        // Subtract, then negate the result.
        // ex: (-7) - (-5) == (-2)
        return new Num(
            -1,
            this_n_scaled->set_sub_ordered(other_n_scaled),
            d_scaled
        );
    } else if (this->sign == -1 && other->sign == -1 && comp_sign == BigInt::LESS) {
        // Subtract reversed.
        // ex: (-5) - (-7) == (+2)
        return new Num(
            1,
            other_n_scaled->set_sub_ordered(this_n_scaled),
            d_scaled
        );
    } else {
        // Add.
        // ex: (+7) - (-5) == (+12), or (-7) - (+5) == (-12)
        // ex: (+5) - (-7) == (+12), or (-5) - (+7) == (-12)
        return new Num(
            this->sign,
            this_n_scaled->set_add(other_n_scaled),
            d_scaled
        );
    }
}

Num* Num::mul(const Num* const other) const {
    // If either number is zero, return zero.
    if (this->sign == 0 || other->sign == 0) {
        return new Num();
    }

    // Multiply.
    return new Num(
        this->sign * other->sign,
        this->numerator->copy()->set_mul(other->numerator),
        this->denominator->copy()->set_mul(other->denominator)
    );
}

Num* Num::div_nonzero(const Num* const other) const {
    // If the dividend is zero, return zero.
    if (this->sign == 0) {
        return new Num();
    }

    // Multiply reciprocals.
    return new Num(
        this->sign * other->sign,
        this->numerator->copy()->set_mul(other->denominator),
        this->denominator->copy()->set_mul(other->numerator)
    );
}
