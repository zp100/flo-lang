#include "Num.hpp"

Num::Num() : is_int(true), sign(0), numerator(0), denominator(1) {
    type_id = T_NUM;
}

Num::Num(const int s, const BigInt& n, const BigInt& d) : is_int(d.is_one), sign(s), numerator(n), denominator(d) {
    type_id = T_NUM;
}

// TODO: For now, this function assumes that the given string represents a valid number.
Value::Ptr Num::from_string(const std::string str) {
    int new_s = 1;
    BigInt new_n (0);
    BigInt new_d (1);
    bool in_decimals = false;

    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '-') {
            new_s = -1;
        } else if (str[i] == '.') {
            in_decimals = true;
        } else if (str[i] >= '0' && str[i] <= '9') {
            BigInt::Digit digit = str[i] - '0';
            new_n.mul(10).add(digit);
            if (in_decimals) {
                new_d.mul(10);
            }
        }
    }

    return std::make_shared<const Num>(new_s, new_n, new_d);
}

std::string Num::to_string() const {
    if (sign == 0) {
        return "0";
    }

    double value = sign * numerator.as_double / denominator.as_double;
    std::stringstream stream;
    if (denominator.comp(2) == BigInt::LESS) {
        stream << std::fixed << std::setprecision(0);
    }
    stream << value;
    return stream.str();
}

Num Num::add(const Num rhs) const {
    // If either number is zero, return the other number.
    // ex: (+8) + (0) == (+8), or (0) + (-8) == (-8)
    if (rhs.sign == 0) {
        return *this;
    } else if (sign == 0) {
        return rhs;
    }

    BigInt this_n_scaled = BigInt(numerator).mul(rhs.denominator);
    BigInt other_n_scaled = BigInt(denominator).mul(rhs.numerator);
    const BigInt::Comp comp_sign = this_n_scaled.comp(other_n_scaled);
    if (comp_sign == BigInt::EQUAL) {
        if (sign == rhs.sign) {
            // Equal magnitues and same signs: Double.
            // ex: (+6) + (+6) == (+12), or (-6) + (-6) == (-12)
            return Num(
                sign,
                BigInt(numerator).mul(2),
                denominator
            );
        } else {
            // Equal magnitudes but opposite signs: Zero.
            // ex: (+6) + (-6) == (0), or (-6) + (+6) == (0)
            return Num();
        }
    }

    BigInt d_scaled = BigInt(denominator).mul(rhs.denominator);
    if (sign == 1 && rhs.sign == -1 && comp_sign == BigInt::GREATER) {
        // Subtract.
        // ex: (+7) + (-5) == (+2)
        return Num(
            1,
            this_n_scaled.sub_ordered(other_n_scaled),
            d_scaled
        );
    } else if (sign == 1 && rhs.sign == -1 && comp_sign == BigInt::LESS) {
        // Subtract reversed, then negate the result.
        // ex: (+5) + (-7) == (-2)
        return Num(
            -1,
            other_n_scaled.sub_ordered(this_n_scaled),
            d_scaled
        );
    } else if (sign == -1 && rhs.sign == 1 && comp_sign == BigInt::GREATER) {
        // Subtract, then negate the result.
        // ex: (-7) + (+5) == (-2)
        return Num(
            -1,
            this_n_scaled.sub_ordered(other_n_scaled),
            d_scaled
        );
    } else if (sign == -1 && rhs.sign == 1 && comp_sign == BigInt::LESS) {
        // Subtract reversed.
        // ex: (-5) + (+7) == (+2)
        return Num(
            1,
            other_n_scaled.sub_ordered(this_n_scaled),
            d_scaled
        );
    } else {
        // Add.
        // ex: (+7) + (+5) == (+12), or (-7) + (-5) == (-12)
        // ex: (+5) + (+7) == (+12), or (-5) + (-7) == (-12)
        return Num(
            sign,
            this_n_scaled.add(other_n_scaled),
            d_scaled
        );
    }
}

Num Num::sub(const Num rhs) const {
    // If the sub is zero, return this.
    // ex: (+8) - (0) == (+8), or (-8) - (0) == (-8)
    if (rhs.sign == 0) {
        return *this;
    }

    BigInt this_n_scaled = BigInt(numerator).mul(rhs.denominator);
    BigInt other_n_scaled = BigInt(denominator).mul(rhs.numerator);
    const BigInt::Comp comp_sign = this_n_scaled.comp(other_n_scaled);
    if (comp_sign == BigInt::EQUAL) {
        if (sign == rhs.sign) {
            // Equal magnitues and same signs: Zero.
            // ex: (+6) - (+6) == (0), or (-6) - (-6) == (0)
            return Num();
        } else {
            // Equal magnitudes but opposite signs: Double.
            // ex: (+6) - (-6) == (+12), or (-6) - (+6) == (-12)
            return Num(
                sign,
                BigInt(numerator).mul(2),
                denominator
            );
        }
    }

    BigInt d_scaled = BigInt(denominator).mul(rhs.denominator);
    if (sign == 1 && rhs.sign == 1 && comp_sign == BigInt::GREATER) {
        // Subtract.
        // ex: (+7) - (+5) == (+2)
        return Num(
            1,
            this_n_scaled.sub_ordered(other_n_scaled),
            d_scaled
        );
    } else if (sign == 1 && rhs.sign == 1 && comp_sign == BigInt::LESS) {
        // Subtract reversed, then negate the result.
        // ex: (+5) - (+7) == (-2)
        return Num(
            -1,
            other_n_scaled.sub_ordered(this_n_scaled),
            d_scaled
        );
    } else if (sign == -1 && rhs.sign == -1 && comp_sign == BigInt::GREATER) {
        // Subtract, then negate the result.
        // ex: (-7) - (-5) == (-2)
        return Num(
            -1,
            this_n_scaled.sub_ordered(other_n_scaled),
            d_scaled
        );
    } else if (sign == -1 && rhs.sign == -1 && comp_sign == BigInt::LESS) {
        // Subtract reversed.
        // ex: (-5) - (-7) == (+2)
        return Num(
            1,
            other_n_scaled.sub_ordered(this_n_scaled),
            d_scaled
        );
    } else {
        // Add.
        // ex: (+7) - (-5) == (+12), or (-7) - (+5) == (-12)
        // ex: (+5) - (-7) == (+12), or (-5) - (+7) == (-12)
        return Num(
            sign,
            this_n_scaled.add(other_n_scaled),
            d_scaled
        );
    }
}

Num Num::mul(const Num rhs) const {
    // If either number is zero, return zero.
    if (sign == 0 || rhs.sign == 0) {
        return Num();
    }

    // Multiply.
    return Num(
        sign * rhs.sign,
        BigInt(numerator).mul(rhs.numerator),
        BigInt(denominator).mul(rhs.denominator)
    );
}

Num Num::div_nonzero(const Num rhs) const {
    // If the dividend is zero, return zero.
    if (sign == 0) {
        return Num();
    }

    // Multiply reciprocals.
    return Num(
        sign * rhs.sign,
        BigInt(numerator).mul(rhs.denominator),
        BigInt(denominator).mul(rhs.numerator)
    );
}
