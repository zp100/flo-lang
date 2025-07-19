#pragma once
#include <memory>

class Value {
    public:

    using Ptr = std::shared_ptr<Value>;

    enum DataType {
        D_NULL,
        D_BOOL,
        D_NUM,
    };

    const DataType type;
};
