#include "Bool.hpp"

Bool::Bool(const bool b) : value(b) {
    type_id = T_BOOL;
}

Value::Ptr Bool::from_string(const std::string str) {
    if (str == "true") {
        return std::make_shared<const Bool>(true);
    } else if (str == "false") {
        return std::make_shared<const Bool>(false);
    } else {
        return std::shared_ptr<const Bool>(nullptr);
    }
}

std::string Bool::to_string() const {
    return (value == true ? "true" : "false");
}

Bool Bool::b_not() const {
    return Bool(!value);
}

Bool Bool::b_and(const Bool right) const {
    return Bool(value && right.value);
}

Bool Bool::b_or(const Bool right) const {
    return Bool(value || right.value);
}

Bool Bool::b_xor(const Bool right) const {
    return Bool(
        (value || right.value)
        && !(value && right.value)
    );
}
