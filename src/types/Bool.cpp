#include "Bool.hpp"

Bool::Bool(const bool v) : value(v) {
    this->type_id = T_BOOL;
}

std::string Bool::to_string() const {
    return (this->value == true ? "true" : "false");
}

Bool* Bool::copy() const {
    return new Bool(this->value);
}
