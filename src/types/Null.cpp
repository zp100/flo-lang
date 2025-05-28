#include "Null.hpp"

Null::Null() {
    this->type_id = T_NULL;
}

std::string Null::to_string() const {
    return "null";
}

Null* Null::copy() const {
    return new Null();
}
