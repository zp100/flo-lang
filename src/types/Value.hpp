#pragma once
#include <string>

class Value {
    public:

    enum ValueId {
        T_NULL,
        T_BOOL,
        T_NUM,
        T_CHAR,
        T_ERROR,
    };

    ValueId type_id;
    virtual std::string to_string() const = 0;
    virtual Value* copy() const = 0;
};
