#include "Char.hpp"

Char::Char(const char c) : value(c) {
    type_id = T_CHAR;
}

Value::Ptr Char::from_string(const std::string str) {
    if (str.size() == 1) {
        return std::make_shared<const Char>(str[0]);
    } else {
        return std::shared_ptr<const Char>(nullptr);
    }
}

std::string Char::to_string() const {
    return std::string(1, value);
}
