#include "Identifier.hpp"

Identifier::Identifier(const std::string in) : id_name(in) {
    type_id = T_IDENTIFIER;
}

Value::Ptr Identifier::from_string(const std::string str) {
    return std::make_shared<const Identifier>(str);
}

std::string Identifier::to_string() const {
    return id_name;
}
