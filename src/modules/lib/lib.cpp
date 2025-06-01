#include "lib.hpp"

Lib::MapType Lib::getFunctionMap() {
    return {
        { "add", Lib::add },
        { "sub", Lib::sub },
        { "mul", Lib::mul },
        { "div", Lib::div },
        { "mod", Lib::mod },
        { "not", Lib::l_not },
        { "and", Lib::l_and },
        { "or", Lib::l_or },
        { "xor", Lib::l_xor },
        { "print", Lib::print },
        { "println", Lib::println },
    };
}

template <typename T> T Lib::cast(Value::Ptr value) {
    return *dynamic_cast<const T* const>(value.get());
}

Value::Ptr Lib::add(const ParseContext::ValueList& value_list) {
    if (value_list.size() != 2) {
        return Error::from_string("Invalid argument count for function \"add\"");
    } else if (value_list[0]->type_id != Value::T_NUM || value_list[1]->type_id != Value::T_NUM) {
        return Error::from_string("Invalid argument type(s) for function \"add\"");
    }

    const Num num1 = Lib::cast<Num>(value_list[0]);
    const Num num2 = Lib::cast<Num>(value_list[1]);

    return std::make_shared<const Num>(num1.add(num2));
}

Value::Ptr Lib::sub(const ParseContext::ValueList& value_list) {
    if (value_list.size() != 2) {
        return Error::from_string("Invalid argument count for function \"sub\"");
    } else if (value_list[0]->type_id != Value::T_NUM || value_list[1]->type_id != Value::T_NUM) {
        return Error::from_string("Invalid argument type(s) for function \"sub\"");
    }

    const Num num1 = Lib::cast<Num>(value_list[0]);
    const Num num2 = Lib::cast<Num>(value_list[1]);

    return std::make_shared<const Num>(num1.sub(num2));
}

Value::Ptr Lib::mul(const ParseContext::ValueList& value_list) {
    if (value_list.size() != 2) {
        return Error::from_string("Invalid argument count for function \"mul\"");
    } else if (value_list[0]->type_id != Value::T_NUM || value_list[1]->type_id != Value::T_NUM) {
        return Error::from_string("Invalid argument type(s) for function \"mul\"");
    }

    const Num num1 = Lib::cast<Num>(value_list[0]);
    const Num num2 = Lib::cast<Num>(value_list[1]);

    return std::make_shared<const Num>(num1.mul(num2));
}

Value::Ptr Lib::div(const ParseContext::ValueList& value_list) {
    if (value_list.size() != 2) {
        return Error::from_string("Invalid argument count for function \"div\"");
    } else if (value_list[0]->type_id != Value::T_NUM || value_list[1]->type_id != Value::T_NUM) {
        return Error::from_string("Invalid argument type(s) for function \"div\"");
    }

    const Num num1 = Lib::cast<Num>(value_list[0]);
    const Num num2 = Lib::cast<Num>(value_list[1]);

    if (num2.sign == 0) {
        return Error::from_string("Division by zero");
    }

    return std::make_shared<const Num>(num1.div_nonzero(num2));
}

Value::Ptr Lib::mod(const ParseContext::ValueList& value_list) {
    if (value_list.size() != 2) {
        return Error::from_string("Invalid argument count for function \"mod\"");
    } else if (value_list[0]->type_id != Value::T_NUM || value_list[1]->type_id != Value::T_NUM) {
        return Error::from_string("Invalid argument type(s) for function \"mod\"");
    }

    const Num num1 = Lib::cast<Num>(value_list[0]);
    const Num num2 = Lib::cast<Num>(value_list[1]);

    if (num2.sign == 0) {
        return Error::from_string("Division by zero");
    }

    return std::make_shared<const Num>(num1.mod_nonzero(num2));
}

Value::Ptr Lib::l_not(const ParseContext::ValueList& value_list) {
    if (value_list.size() != 1) {
        return Error::from_string("Invalid argument count for function \"not\"");
    } else if (value_list[0]->type_id != Value::T_BOOL) {
        return Error::from_string("Invalid argument type(s) for function \"not\"");
    }

    const Bool bool1 = Lib::cast<Bool>(value_list[0]);

    return std::make_shared<const Bool>(bool1.l_not());
}

Value::Ptr Lib::l_and(const ParseContext::ValueList& value_list) {
    if (value_list.size() != 2) {
        return Error::from_string("Invalid argument count for function \"and\"");
    } else if (value_list[0]->type_id != Value::T_BOOL || value_list[1]->type_id != Value::T_BOOL) {
        return Error::from_string("Invalid argument type(s) for function \"and\"");
    }

    const Bool bool1 = Lib::cast<Bool>(value_list[0]);
    const Bool bool2 = Lib::cast<Bool>(value_list[1]);

    return std::make_shared<const Bool>(bool1.l_and(bool2));
}

Value::Ptr Lib::l_or(const ParseContext::ValueList& value_list) {
    if (value_list.size() != 2) {
        return Error::from_string("Invalid argument count for function \"or\"");
    } else if (value_list[0]->type_id != Value::T_BOOL || value_list[1]->type_id != Value::T_BOOL) {
        return Error::from_string("Invalid argument type(s) for function \"or\"");
    }

    const Bool bool1 = Lib::cast<Bool>(value_list[0]);
    const Bool bool2 = Lib::cast<Bool>(value_list[1]);

    return std::make_shared<const Bool>(bool1.l_or(bool2));
}

Value::Ptr Lib::l_xor(const ParseContext::ValueList& value_list) {
    if (value_list.size() != 2) {
        return Error::from_string("Invalid argument count for function \"xor\"");
    } else if (value_list[0]->type_id != Value::T_BOOL || value_list[1]->type_id != Value::T_BOOL) {
        return Error::from_string("Invalid argument type(s) for function \"xor\"");
    }

    const Bool bool1 = Lib::cast<Bool>(value_list[0]);
    const Bool bool2 = Lib::cast<Bool>(value_list[1]);

    return std::make_shared<const Bool>(bool1.l_xor(bool2));
}

Value::Ptr Lib::print(const ParseContext::ValueList& value_list) {
    for (std::size_t i = 0; i < value_list.size(); i++) {
        std::cout << value_list[i]->to_string() << " ";
    };

    return std::make_shared<const Null>();
}

Value::Ptr Lib::println(const ParseContext::ValueList& value_list) {
    Value::Ptr value = Lib::print(value_list);
    if (value->type_id == Value::T_ERROR) {
        return value;
    }

    std::cout << std::endl;
    return value;
}
