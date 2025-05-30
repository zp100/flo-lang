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
