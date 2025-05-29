#include "Char.hpp"

Char::Char(const char c) : value(c) {
    type_id = T_CHAR;
}

std::string Char::to_string() const {
    return std::string(1, value);
}
