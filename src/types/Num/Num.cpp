#include "Num.hpp"

Num::Num(const short s, const BigInt& n, const BigInt& d) : is_int(d.is_one), sign(s), numerator(n), denominator(d) {
    type_id = T_NUM;
}

// TODO: For now, this function assumes that the given string represents a valid number.
Value::Ptr Num::from_string(const std::string str) {
    short new_s = 1;
    BigInt new_n (0);
    BigInt new_d (1);
    bool in_decimals = false;

    for (std::size_t i = 0; i < str.length(); i++) {
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

Num Num::add(const Num right) const {
    // If either number is zero, return the other number.
    // ex: (+8) + (0) == (+8), or (0) + (-8) == (-8)
    if (right.sign == 0) {
        return *this;
    } else if (sign == 0) {
        return right;
    }

    BigInt left_n_scaled = BigInt(numerator).mul(right.denominator);
    BigInt right_n_scaled = BigInt(denominator).mul(right.numerator);
    const BigInt::Comp comp_sign = left_n_scaled.comp(right_n_scaled);
    if (comp_sign == BigInt::EQUAL) {
        if (sign == right.sign) {
            // Equal magnitues and same signs: Double.
            // ex: (+6) + (+6) == (+12), or (-6) + (-6) == (-12)
            return Num(
                sign,
                BigInt(numerator).mul(2),
                denominator
            ).maybe_simplify();
        } else {
            // Equal magnitudes but opposite signs: Zero.
            // ex: (+6) + (-6) == (0), or (-6) + (+6) == (0)
            return Num();
        }
    }

    BigInt d_scaled = BigInt(denominator).mul(right.denominator);
    if (sign == 1 && right.sign == -1 && comp_sign == BigInt::GREATER) {
        // Subtract.
        // ex: (+7) + (-5) == (+2)
        return Num(
            1,
            left_n_scaled.sub_ordered(right_n_scaled),
            d_scaled
        ).maybe_simplify();
    } else if (sign == 1 && right.sign == -1 && comp_sign == BigInt::LESS) {
        // Subtract reversed, then negate the result.
        // ex: (+5) + (-7) == (-2)
        return Num(
            -1,
            right_n_scaled.sub_ordered(left_n_scaled),
            d_scaled
        ).maybe_simplify();
    } else if (sign == -1 && right.sign == 1 && comp_sign == BigInt::GREATER) {
        // Subtract, then negate the result.
        // ex: (-7) + (+5) == (-2)
        return Num(
            -1,
            left_n_scaled.sub_ordered(right_n_scaled),
            d_scaled
        ).maybe_simplify();
    } else if (sign == -1 && right.sign == 1 && comp_sign == BigInt::LESS) {
        // Subtract reversed.
        // ex: (-5) + (+7) == (+2)
        return Num(
            1,
            right_n_scaled.sub_ordered(left_n_scaled),
            d_scaled
        ).maybe_simplify();
    } else {
        // Add.
        // ex: (+7) + (+5) == (+12), or (-7) + (-5) == (-12)
        // ex: (+5) + (+7) == (+12), or (-5) + (-7) == (-12)
        return Num(
            sign,
            left_n_scaled.add(right_n_scaled),
            d_scaled
        ).maybe_simplify();
    }
}

Num Num::sub(const Num right) const {
    // If the right number is zero, return the left number.
    // ex: (+8) - (0) == (+8), or (-8) - (0) == (-8)
    if (right.sign == 0) {
        return *this;
    }

    BigInt left_n_scaled = BigInt(numerator).mul(right.denominator);
    BigInt right_n_scaled = BigInt(denominator).mul(right.numerator);
    const BigInt::Comp comp_sign = left_n_scaled.comp(right_n_scaled);
    if (comp_sign == BigInt::EQUAL) {
        if (sign == right.sign) {
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
            ).maybe_simplify();
        }
    }

    BigInt d_scaled = BigInt(denominator).mul(right.denominator);
    if (sign == 1 && right.sign == 1 && comp_sign == BigInt::GREATER) {
        // Subtract.
        // ex: (+7) - (+5) == (+2)
        return Num(
            1,
            left_n_scaled.sub_ordered(right_n_scaled),
            d_scaled
        ).maybe_simplify();
    } else if (sign == 1 && right.sign == 1 && comp_sign == BigInt::LESS) {
        // Subtract reversed, then negate the result.
        // ex: (+5) - (+7) == (-2)
        return Num(
            -1,
            right_n_scaled.sub_ordered(left_n_scaled),
            d_scaled
        ).maybe_simplify();
    } else if (sign == -1 && right.sign == -1 && comp_sign == BigInt::GREATER) {
        // Subtract, then negate the result.
        // ex: (-7) - (-5) == (-2)
        return Num(
            -1,
            left_n_scaled.sub_ordered(right_n_scaled),
            d_scaled
        ).maybe_simplify();
    } else if (sign == -1 && right.sign == -1 && comp_sign == BigInt::LESS) {
        // Subtract reversed.
        // ex: (-5) - (-7) == (+2)
        return Num(
            1,
            right_n_scaled.sub_ordered(left_n_scaled),
            d_scaled
        ).maybe_simplify();
    } else {
        // Add.
        // ex: (+7) - (-5) == (+12), or (-7) - (+5) == (-12)
        // ex: (+5) - (-7) == (+12), or (-5) - (+7) == (-12)
        return Num(
            sign,
            left_n_scaled.add(right_n_scaled),
            d_scaled
        ).maybe_simplify();
    }
}

Num Num::mul(const Num right) const {
    // If either number is zero, return zero.
    if (sign == 0 || right.sign == 0) {
        return Num();
    }

    // Multiply.
    return Num(
        sign * right.sign,
        BigInt(numerator).mul(right.numerator),
        BigInt(denominator).mul(right.denominator)
    ).maybe_simplify();
}

Num Num::div_nonzero(const Num right) const {
    // If the dividend is zero, return zero.
    if (sign == 0) {
        return Num();
    }

    // Multiply reciprocals.
    return Num(
        sign * right.sign,
        BigInt(numerator).mul(right.denominator),
        BigInt(denominator).mul(right.numerator)
    ).maybe_simplify();
}

Num Num::mod_nonzero(const Num right) const {
    // If the dividend is zero, return zero.
    if (sign == 0) {
        return Num();
    }

    BigInt left_n_scaled = BigInt(numerator).mul(right.denominator);
    BigInt right_n_scaled = BigInt(denominator).mul(right.numerator);
    BigInt d_scaled = BigInt(denominator).mul(right.denominator);
    if (sign == right.sign) {
        // Get remainder.
        // ex: (+7) % (+5) == (+2), or (-7) % (-5) == (-2)
        return Num(
            right.sign,
            left_n_scaled.mod_nonzero(right_n_scaled),
            d_scaled
        ).maybe_simplify();
    } else {
        // Get remainder, then subtract it from the divisor.
        // ex: (-7) % (+5) == (+3), or (+7) % (-5) == (-3)
        return Num(
            right.sign,
            right_n_scaled.sub_ordered(left_n_scaled.mod_nonzero(right_n_scaled)),
            d_scaled
        ).maybe_simplify();
    }
}

BigInt::Comp Num::comp(const Num right) const {
    // Shortcuts based on signs.
    if (sign > right.sign) {
        return BigInt::GREATER;
    } else if (sign < right.sign) {
        return BigInt::LESS;
    }

    BigInt left_n_scaled = BigInt(numerator).mul(right.denominator);
    BigInt right_n_scaled = BigInt(denominator).mul(right.numerator);
    return left_n_scaled.comp(right_n_scaled);
}

Num::Num() : is_int(true), sign(0), numerator(0), denominator(1) {
    type_id = T_NUM;
}

Num Num::maybe_simplify() const {
    if (denominator.is_one) {
        return *this;
    }

    BigInt new_n (numerator);
    BigInt new_d (denominator);
    BigInt::simplify_recursive(new_n, new_d);
    return Num(sign, new_n, new_d);
}
