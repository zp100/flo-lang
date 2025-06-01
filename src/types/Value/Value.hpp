#pragma once
#include <memory>
#include <string>

class Value {
    public:

    using Ptr = std::shared_ptr<const Value>;

    enum ValueId {
        T_BOOL,
        T_CHAR,
        T_ERROR,
        T_IDENTIFIER,
        T_NULL,
        T_NUM,
    };

    ValueId type_id;

    virtual std::string to_string() const = 0; // DEBUG
};
