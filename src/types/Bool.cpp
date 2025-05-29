#include "Bool.hpp"

Bool::Bool(const bool b) : value(b) {
    type_id = T_BOOL;
}

std::string Bool::to_string() const {
    return (value == true ? "true" : "false");
}
