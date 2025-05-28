#include "Error.hpp"

Error::Error(const std::string em) : error_message(em) {
    this->type_id = T_ERROR;
}

std::string Error::to_string() const {
    return this->error_message;
}

Error* Error::copy() const {
    return new Error(this->error_message);
}
