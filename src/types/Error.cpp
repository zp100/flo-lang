#include "Error.hpp"

Error::Error(const std::string em) : error_message(em) {
    type_id = T_ERROR;
}

std::string Error::to_string() const {
    return error_message;
}
