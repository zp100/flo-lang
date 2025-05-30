#include "Error.hpp"

Error::Error(const std::string em) : error_message(em) {
    type_id = T_ERROR;
}

Value::Ptr Error::from_string(const std::string str) {
    return std::make_unique<const Error>(str);
}

std::string Error::to_string() const {
    return error_message;
}
