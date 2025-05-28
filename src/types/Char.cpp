#include "Char.hpp"

Char::Char(const char v) : value(v) {
    this->type_id = T_CHAR;
}

std::string Char::to_string() const {
    return std::string(1, this->value);
}

Char* Char::copy() const {
    return new Char(this->value);
}
