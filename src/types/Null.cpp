#include "Null.hpp"

Null::Null() {
    type_id = T_NULL;
}

Value::Ptr Null::from_string(const std::string str) {
    if (str == "null") {
        return std::make_unique<const Null>();
    } else {
        return std::unique_ptr<const Null>(nullptr);
    }
}

std::string Null::to_string() const {
    return "null";
}
