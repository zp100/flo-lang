#include "Null.hpp"

Null::Null() {
    type_id = T_NULL;
}

std::string Null::to_string() const {
    return "null";
}
