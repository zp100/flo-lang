#include "lib.hpp"

MapType getFunctionMap() {
    return {
        { "add", lib_add },
        { "sub", lib_sub },
        { "mul", lib_mul },
        { "div", lib_div },
        { "mod", lib_mod },
        { "not", lib_not },
        { "and", lib_and },
        { "or", lib_or },
        { "xor", lib_xor },
        { "print", lib_print },
        { "println", lib_println },
    };
}

template <typename T> T cast(Value::Ptr value) {
    return *dynamic_cast<const T* const>(value.get());
}

Value::Ptr lib_add(const ParseContext::ValueList& value_list) {
    if (value_list.size() != 2) {
        return Error::from_string("Invalid argument count for function \"add\"");
    } else if (value_list[0]->type_id != Value::T_NUM || value_list[1]->type_id != Value::T_NUM) {
        return Error::from_string("Invalid argument type(s) for function \"add\"");
    }

    const Num num1 = cast<Num>(value_list[0]);
    const Num num2 = cast<Num>(value_list[1]);

    return std::make_shared<const Num>(num1.add(num2));
}

Value::Ptr lib_sub(const ParseContext::ValueList& value_list) {
    if (value_list.size() != 2) {
        return Error::from_string("Invalid argument count for function \"sub\"");
    } else if (value_list[0]->type_id != Value::T_NUM || value_list[1]->type_id != Value::T_NUM) {
        return Error::from_string("Invalid argument type(s) for function \"sub\"");
    }

    const Num num1 = cast<Num>(value_list[0]);
    const Num num2 = cast<Num>(value_list[1]);

    return std::make_shared<const Num>(num1.sub(num2));
}

Value::Ptr lib_mul(const ParseContext::ValueList& value_list) {
    if (value_list.size() != 2) {
        return Error::from_string("Invalid argument count for function \"mul\"");
    } else if (value_list[0]->type_id != Value::T_NUM || value_list[1]->type_id != Value::T_NUM) {
        return Error::from_string("Invalid argument type(s) for function \"mul\"");
    }

    const Num num1 = cast<Num>(value_list[0]);
    const Num num2 = cast<Num>(value_list[1]);

    return std::make_shared<const Num>(num1.mul(num2));
}

Value::Ptr lib_div(const ParseContext::ValueList& value_list) {
    if (value_list.size() != 2) {
        return Error::from_string("Invalid argument count for function \"div\"");
    } else if (value_list[0]->type_id != Value::T_NUM || value_list[1]->type_id != Value::T_NUM) {
        return Error::from_string("Invalid argument type(s) for function \"div\"");
    }

    const Num num1 = cast<Num>(value_list[0]);
    const Num num2 = cast<Num>(value_list[1]);

    if (num2.sign == 0) {
        return Error::from_string("Division by zero");
    }

    return std::make_shared<const Num>(num1.div_nonzero(num2));
}

Value::Ptr lib_mod(const ParseContext::ValueList& value_list) {
    if (value_list.size() != 2) {
        return Error::from_string("Invalid argument count for function \"mod\"");
    } else if (value_list[0]->type_id != Value::T_NUM || value_list[1]->type_id != Value::T_NUM) {
        return Error::from_string("Invalid argument type(s) for function \"mod\"");
    }

    const Num num1 = cast<Num>(value_list[0]);
    const Num num2 = cast<Num>(value_list[1]);

    if (num2.sign == 0) {
        return Error::from_string("Division by zero");
    }

    return std::make_shared<const Num>(num1.mod_nonzero(num2));
}

Value::Ptr lib_not(const ParseContext::ValueList& value_list) {
    if (value_list.size() != 1) {
        return Error::from_string("Invalid argument count for function \"not\"");
    } else if (value_list[0]->type_id != Value::T_BOOL) {
        return Error::from_string("Invalid argument type(s) for function \"not\"");
    }

    const Bool bool1 = cast<Bool>(value_list[0]);

    return std::make_shared<const Bool>(bool1.b_not());
}

Value::Ptr lib_and(const ParseContext::ValueList& value_list) {
    if (value_list.size() != 2) {
        return Error::from_string("Invalid argument count for function \"and\"");
    } else if (value_list[0]->type_id != Value::T_BOOL || value_list[1]->type_id != Value::T_BOOL) {
        return Error::from_string("Invalid argument type(s) for function \"and\"");
    }

    const Bool bool1 = cast<Bool>(value_list[0]);
    const Bool bool2 = cast<Bool>(value_list[1]);

    return std::make_shared<const Bool>(bool1.b_and(bool2));
}

Value::Ptr lib_or(const ParseContext::ValueList& value_list) {
    if (value_list.size() != 2) {
        return Error::from_string("Invalid argument count for function \"or\"");
    } else if (value_list[0]->type_id != Value::T_BOOL || value_list[1]->type_id != Value::T_BOOL) {
        return Error::from_string("Invalid argument type(s) for function \"or\"");
    }

    const Bool bool1 = cast<Bool>(value_list[0]);
    const Bool bool2 = cast<Bool>(value_list[1]);

    return std::make_shared<const Bool>(bool1.b_or(bool2));
}

Value::Ptr lib_xor(const ParseContext::ValueList& value_list) {
    if (value_list.size() != 2) {
        return Error::from_string("Invalid argument count for function \"xor\"");
    } else if (value_list[0]->type_id != Value::T_BOOL || value_list[1]->type_id != Value::T_BOOL) {
        return Error::from_string("Invalid argument type(s) for function \"xor\"");
    }

    const Bool bool1 = cast<Bool>(value_list[0]);
    const Bool bool2 = cast<Bool>(value_list[1]);

    return std::make_shared<const Bool>(bool1.b_xor(bool2));
}

Value::Ptr lib_print(const ParseContext::ValueList& value_list) {
    for (std::size_t i = 0; i < value_list.size(); i++) {
        std::cout << value_list[i]->to_string() << " ";
    };

    return std::make_shared<const Null>();
}

Value::Ptr lib_println(const ParseContext::ValueList& value_list) {
    Value::Ptr value = lib_print(value_list);
    if (value->type_id == Value::T_ERROR) {
        return value;
    }

    std::cout << std::endl;
    return value;
}
