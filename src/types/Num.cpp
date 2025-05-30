#include "Num.hpp"

Num::Num(const int s, const BigInt& n, const BigInt& d) : is_int(d.is_one), sign(s), numerator(n), denominator(d) {
    type_id = T_NUM;
}

Num::Ptr Num::make() {
    return std::make_unique<const Num>(0, BigInt(0), BigInt(1));
}

Num::Ptr Num::make(const int s, const BigInt::Digit n, const BigInt::Digit d) {
    return std::make_unique<const Num>(s, BigInt(n), BigInt(d));
}

Num::Ptr Num::make(const int s, const BigInt& n, const BigInt& d) {
    return std::make_unique<const Num>(s, n, d);
}

// TODO: For now, this function assumes that the given string represents a valid number.
Num::Ptr Num::from_string(const std::string str) {
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
            int digit = str[i] - '0';
            new_n.mul(10).add(digit);
            if (in_decimals) {
                new_d.mul(10);
            }
        }
    }

    return make(new_s, new_n, new_d);
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

Num::Ptr Num::add(const Ptr rhs) const {
    // If either number is zero, return the other number.
    // ex: (+8) + (0) == (+8), or (0) + (-8) == (-8)
    if (rhs->sign == 0) {
        return make(sign, numerator, denominator);
    } else if (sign == 0) {
        return make(rhs->sign, rhs->numerator, rhs->denominator);
    }

    auto x = new BigInt(3);

    BigInt this_n_scaled = numerator.dup().mul(rhs->denominator);
    BigInt other_n_scaled = denominator.dup().mul(rhs->numerator);
    const BigInt::Comp comp_sign = this_n_scaled.comp(other_n_scaled);
    if (comp_sign == BigInt::EQUAL) {
        if (sign == rhs->sign) {
            // Equal magnitues and same signs: Double.
            // ex: (+6) + (+6) == (+12), or (-6) + (-6) == (-12)
            return make(
                sign,
                numerator.dup().mul(2),
                denominator
            );
        } else {
            // Equal magnitudes but opposite signs: Zero.
            // ex: (+6) + (-6) == (0), or (-6) + (+6) == (0)
            return make();
        }
    }

    BigInt d_scaled = denominator.dup().mul(rhs->denominator);
    if (sign == 1 && rhs->sign == -1 && comp_sign == BigInt::GREATER) {
        // Subtract.
        // ex: (+7) + (-5) == (+2)
        return make(
            1,
            this_n_scaled.sub(other_n_scaled),
            d_scaled
        );
    } else if (sign == 1 && rhs->sign == -1 && comp_sign == BigInt::LESS) {
        // Subtract reversed, then negate the result.
        // ex: (+5) + (-7) == (-2)
        return make(
            -1,
            other_n_scaled.sub(this_n_scaled),
            d_scaled
        );
    } else if (sign == -1 && rhs->sign == 1 && comp_sign == BigInt::GREATER) {
        // Subtract, then negate the result.
        // ex: (-7) + (+5) == (-2)
        return make(
            -1,
            this_n_scaled.sub(other_n_scaled),
            d_scaled
        );
    } else if (sign == -1 && rhs->sign == 1 && comp_sign == BigInt::LESS) {
        // Subtract reversed.
        // ex: (-5) + (+7) == (+2)
        return make(
            1,
            other_n_scaled.sub(this_n_scaled),
            d_scaled
        );
    } else {
        // Add.
        // ex: (+7) + (+5) == (+12), or (-7) + (-5) == (-12)
        // ex: (+5) + (+7) == (+12), or (-5) + (-7) == (-12)
        return make(
            sign,
            this_n_scaled.add(other_n_scaled),
            d_scaled
        );
    }
}

Num::Ptr Num::sub(const Ptr rhs) const {
    // If the subtrahend is zero, return this.
    // ex: (+8) - (0) == (+8), or (-8) - (0) == (-8)
    if (rhs->sign == 0) {
        return make(sign, numerator, denominator);
    }

    BigInt& this_n_scaled = numerator.dup().mul(rhs->denominator);
    BigInt& other_n_scaled = denominator.dup().mul(rhs->numerator);
    const BigInt::Comp comp_sign = this_n_scaled.comp(other_n_scaled);
    if (comp_sign == BigInt::EQUAL) {
        if (sign == rhs->sign) {
            // Equal magnitues and same signs: Zero.
            // ex: (+6) - (+6) == (0), or (-6) - (-6) == (0)
            return make();
        } else {
            // Equal magnitudes but opposite signs: Double.
            // ex: (+6) - (-6) == (+12), or (-6) - (+6) == (-12)
            return make(
                sign,
                numerator.dup().mul(2),
                denominator
            );
        }
    }

    BigInt d_scaled = denominator.dup().mul(rhs->denominator);
    if (sign == 1 && rhs->sign == 1 && comp_sign == BigInt::GREATER) {
        // Subtract.
        // ex: (+7) - (+5) == (+2)
        return make(
            1,
            this_n_scaled.sub(other_n_scaled),
            d_scaled
        );
    } else if (sign == 1 && rhs->sign == 1 && comp_sign == BigInt::LESS) {
        // Subtract reversed, then negate the result.
        // ex: (+5) - (+7) == (-2)
        return make(
            -1,
            other_n_scaled.sub(this_n_scaled),
            d_scaled
        );
    } else if (sign == -1 && rhs->sign == -1 && comp_sign == BigInt::GREATER) {
        // Subtract, then negate the result.
        // ex: (-7) - (-5) == (-2)
        return make(
            -1,
            this_n_scaled.sub(other_n_scaled),
            d_scaled
        );
    } else if (sign == -1 && rhs->sign == -1 && comp_sign == BigInt::LESS) {
        // Subtract reversed.
        // ex: (-5) - (-7) == (+2)
        return make(
            1,
            other_n_scaled.sub(this_n_scaled),
            d_scaled
        );
    } else {
        // Add.
        // ex: (+7) - (-5) == (+12), or (-7) - (+5) == (-12)
        // ex: (+5) - (-7) == (+12), or (-5) - (+7) == (-12)
        return make(
            sign,
            this_n_scaled.add(other_n_scaled),
            d_scaled
        );
    }
}

Num::Ptr Num::mul(const Ptr rhs) const {
    // If either number is zero, return zero.
    if (sign == 0 || rhs->sign == 0) {
        return make();
    }

    // Multiply.
    return make(
        sign * rhs->sign,
        numerator.dup().mul(rhs->numerator),
        denominator.dup().mul(rhs->denominator)
    );
}

Num::Ptr Num::div_nonzero(const Ptr rhs) const {
    // If the dividend is zero, return zero.
    if (sign == 0) {
        return make();
    }

    // Multiply reciprocals.
    return make(
        sign * rhs->sign,
        numerator.dup().mul(rhs->denominator),
        denominator.dup().mul(rhs->numerator)
    );
}
