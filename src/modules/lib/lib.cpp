#include "lib.hpp"

Lib::MapType Lib::getFunctionMap() {
    return {
        { "+", Lib::f_add },
        { "-", Lib::f_sub },
        { "*", Lib::f_mul },
        { "^", Lib::f_exp },
        { "<", Lib::f_lt },
        { "<=", Lib::f_lteq },
        { ">", Lib::f_gt },
        { ">=", Lib::f_gteq },
        { "==", Lib::f_eq },
        { "!=", Lib::f_neq },
        { "/", Lib::f_div },
        { "%", Lib::f_mod },
        { "neg", Lib::f_neg },
        { "abs", Lib::f_abs },
        { "not", Lib::f_not },
        { "and", Lib::f_and },
        { "or", Lib::f_or },
        { "xor", Lib::f_xor },
        { "nand", Lib::f_nand },
        { "nor", Lib::f_nor },
        { "print", Lib::f_print },
        { "println", Lib::f_println },
    };
}

template <typename T> T Lib::cast(Value::Ptr value) {
    return *dynamic_cast<const T* const>(value.get());
}

Value::Ptr Lib::f_add(const ParseContext::ValueList& value_list) {
    if (value_list.size() != 2) {
        return Error::from_string("Invalid argument count for function \"+\"");
    } else if (value_list[0]->type_id != Value::T_NUM || value_list[1]->type_id != Value::T_NUM) {
        return Error::from_string("Invalid argument type(s) for function \"+\"");
    }

    const Num num1 = Lib::cast<Num>(value_list[0]);
    const Num num2 = Lib::cast<Num>(value_list[1]);

    const Num result = num1.add(num2);
    return std::make_shared<const Num>(result);
}

Value::Ptr Lib::f_sub(const ParseContext::ValueList& value_list) {
    if (value_list.size() != 2) {
        return Error::from_string("Invalid argument count for function \"-\"");
    } else if (value_list[0]->type_id != Value::T_NUM || value_list[1]->type_id != Value::T_NUM) {
        return Error::from_string("Invalid argument type(s) for function \"-\"");
    }

    const Num num1 = Lib::cast<Num>(value_list[0]);
    const Num num2 = Lib::cast<Num>(value_list[1]);

    const Num result = num1.sub(num2);
    return std::make_shared<const Num>(result);
}

Value::Ptr Lib::f_mul(const ParseContext::ValueList& value_list) {
    if (value_list.size() != 2) {
        return Error::from_string("Invalid argument count for function \"*\"");
    } else if (value_list[0]->type_id != Value::T_NUM || value_list[1]->type_id != Value::T_NUM) {
        return Error::from_string("Invalid argument type(s) for function \"*\"");
    }

    const Num num1 = Lib::cast<Num>(value_list[0]);
    const Num num2 = Lib::cast<Num>(value_list[1]);

    const Num result = num1.mul(num2);
    return std::make_shared<const Num>(result);
}

Value::Ptr Lib::f_exp(const ParseContext::ValueList& value_list) {
    if (value_list.size() != 2) {
        return Error::from_string("Invalid argument count for function \"^\"");
    } else if (value_list[0]->type_id != Value::T_NUM || value_list[1]->type_id != Value::T_NUM) {
        return Error::from_string("Invalid argument type(s) for function \"^\"");
    }

    const Num num1 = Lib::cast<Num>(value_list[0]);
    const Num num2 = Lib::cast<Num>(value_list[1]);

    if (num2.sign == 0) {
        return Error::from_string("Division by zero");
    }

    const Num result = num1; // TODO
    return std::make_shared<const Num>(result);
}

Value::Ptr Lib::f_lt(const ParseContext::ValueList& value_list) {
    if (value_list.size() != 2) {
        return Error::from_string("Invalid argument count for function \"<\"");
    } else if (value_list[0]->type_id != Value::T_NUM || value_list[1]->type_id != Value::T_NUM) {
        return Error::from_string("Invalid argument type(s) for function \"<\"");
    }

    const Num num1 = Lib::cast<Num>(value_list[0]);
    const Num num2 = Lib::cast<Num>(value_list[1]);

    const Bool result (num1.comp(num2) == BigInt::LESS);
    return std::make_shared<const Bool>(result);
}

Value::Ptr Lib::f_lteq(const ParseContext::ValueList& value_list) {
    if (value_list.size() != 2) {
        return Error::from_string("Invalid argument count for function \"<=\"");
    } else if (value_list[0]->type_id != Value::T_NUM || value_list[1]->type_id != Value::T_NUM) {
        return Error::from_string("Invalid argument type(s) for function \"<=\"");
    }

    const Num num1 = Lib::cast<Num>(value_list[0]);
    const Num num2 = Lib::cast<Num>(value_list[1]);

    const Bool result (num1.comp(num2) != BigInt::GREATER);
    return std::make_shared<const Bool>(result);
}

Value::Ptr Lib::f_gt(const ParseContext::ValueList& value_list) {
    if (value_list.size() != 2) {
        return Error::from_string("Invalid argument count for function \">\"");
    } else if (value_list[0]->type_id != Value::T_NUM || value_list[1]->type_id != Value::T_NUM) {
        return Error::from_string("Invalid argument type(s) for function \">\"");
    }

    const Num num1 = Lib::cast<Num>(value_list[0]);
    const Num num2 = Lib::cast<Num>(value_list[1]);

    const Bool result (num1.comp(num2) == BigInt::GREATER);
    return std::make_shared<const Bool>(result);
}

Value::Ptr Lib::f_gteq(const ParseContext::ValueList& value_list) {
    if (value_list.size() != 2) {
        return Error::from_string("Invalid argument count for function \">=\"");
    } else if (value_list[0]->type_id != Value::T_NUM || value_list[1]->type_id != Value::T_NUM) {
        return Error::from_string("Invalid argument type(s) for function \">=\"");
    }

    const Num num1 = Lib::cast<Num>(value_list[0]);
    const Num num2 = Lib::cast<Num>(value_list[1]);

    const Bool result (num1.comp(num2) != BigInt::LESS);
    return std::make_shared<const Bool>(result);
}

Value::Ptr Lib::f_eq(const ParseContext::ValueList& value_list) {
    if (value_list.size() != 2) {
        return Error::from_string("Invalid argument count for function \"==\"");
    } else if (value_list[0]->type_id != Value::T_NUM || value_list[1]->type_id != Value::T_NUM) {
        return Error::from_string("Invalid argument type(s) for function \"==\"");
    }

    const Num num1 = Lib::cast<Num>(value_list[0]);
    const Num num2 = Lib::cast<Num>(value_list[1]);

    const Bool result (num1.comp(num2) == BigInt::EQUAL);
    return std::make_shared<const Bool>(result);
}

Value::Ptr Lib::f_neq(const ParseContext::ValueList& value_list) {
    if (value_list.size() != 2) {
        return Error::from_string("Invalid argument count for function \"!=\"");
    } else if (value_list[0]->type_id != Value::T_NUM || value_list[1]->type_id != Value::T_NUM) {
        return Error::from_string("Invalid argument type(s) for function \"!=\"");
    }

    const Num num1 = Lib::cast<Num>(value_list[0]);
    const Num num2 = Lib::cast<Num>(value_list[1]);

    const Bool result (num1.comp(num2) != BigInt::EQUAL);
    return std::make_shared<const Bool>(result);
}

Value::Ptr Lib::f_div(const ParseContext::ValueList& value_list) {
    if (value_list.size() != 2) {
        return Error::from_string("Invalid argument count for function \"/\"");
    } else if (value_list[0]->type_id != Value::T_NUM || value_list[1]->type_id != Value::T_NUM) {
        return Error::from_string("Invalid argument type(s) for function \"/\"");
    }

    const Num num1 = Lib::cast<Num>(value_list[0]);
    const Num num2 = Lib::cast<Num>(value_list[1]);

    if (num2.sign == 0) {
        return Error::from_string("Division by zero");
    }

    const Num result = num1.div_nonzero(num2);
    return std::make_shared<const Num>(result);
}

Value::Ptr Lib::f_mod(const ParseContext::ValueList& value_list) {
    if (value_list.size() != 2) {
        return Error::from_string("Invalid argument count for function \"%\"");
    } else if (value_list[0]->type_id != Value::T_NUM || value_list[1]->type_id != Value::T_NUM) {
        return Error::from_string("Invalid argument type(s) for function \"%\"");
    }

    const Num num1 = Lib::cast<Num>(value_list[0]);
    const Num num2 = Lib::cast<Num>(value_list[1]);

    if (num2.sign == 0) {
        return Error::from_string("Division by zero");
    }

    const Num result = num1.mod_nonzero(num2);
    return std::make_shared<const Num>(result);
}

Value::Ptr Lib::f_neg(const ParseContext::ValueList& value_list) {
    if (value_list.size() != 1) {
        return Error::from_string("Invalid argument count for function \"neg\"");
    } else if (value_list[0]->type_id != Value::T_NUM) {
        return Error::from_string("Invalid argument type(s) for function \"neg\"");
    }

    const Num num1 = Lib::cast<Num>(value_list[0]);

    const Num result (num1.sign * -1, num1.numerator, num1.denominator);
    return std::make_shared<const Num>(result);
}

Value::Ptr Lib::f_abs(const ParseContext::ValueList& value_list) {
    if (value_list.size() != 1) {
        return Error::from_string("Invalid argument count for function \"abs\"");
    } else if (value_list[0]->type_id != Value::T_NUM) {
        return Error::from_string("Invalid argument type(s) for function \"abs\"");
    }

    const Num num1 = Lib::cast<Num>(value_list[0]);

    const Num result ((num1.sign ? 1 : 0), num1.numerator, num1.denominator);
    return std::make_shared<const Num>(result);
}

Value::Ptr Lib::f_not(const ParseContext::ValueList& value_list) {
    if (value_list.size() != 1) {
        return Error::from_string("Invalid argument count for function \"not\"");
    } else if (value_list[0]->type_id != Value::T_BOOL) {
        return Error::from_string("Invalid argument type(s) for function \"not\"");
    }

    const Bool bool1 = Lib::cast<Bool>(value_list[0]);

    const Bool result (!bool1.value);
    return std::make_shared<const Bool>(result);
}

Value::Ptr Lib::f_and(const ParseContext::ValueList& value_list) {
    if (value_list.size() != 2) {
        return Error::from_string("Invalid argument count for function \"and\"");
    } else if (value_list[0]->type_id != Value::T_BOOL || value_list[1]->type_id != Value::T_BOOL) {
        return Error::from_string("Invalid argument type(s) for function \"and\"");
    }

    const Bool bool1 = Lib::cast<Bool>(value_list[0]);
    const Bool bool2 = Lib::cast<Bool>(value_list[1]);

    const Bool result (bool1.value && bool2.value);
    return std::make_shared<const Bool>(bool1.value && bool2.value);
}

Value::Ptr Lib::f_or(const ParseContext::ValueList& value_list) {
    if (value_list.size() != 2) {
        return Error::from_string("Invalid argument count for function \"or\"");
    } else if (value_list[0]->type_id != Value::T_BOOL || value_list[1]->type_id != Value::T_BOOL) {
        return Error::from_string("Invalid argument type(s) for function \"or\"");
    }

    const Bool bool1 = Lib::cast<Bool>(value_list[0]);
    const Bool bool2 = Lib::cast<Bool>(value_list[1]);

    const Bool result (bool1.value || bool2.value);
    return std::make_shared<const Bool>(result);
}

Value::Ptr Lib::f_xor(const ParseContext::ValueList& value_list) {
    if (value_list.size() != 2) {
        return Error::from_string("Invalid argument count for function \"xor\"");
    } else if (value_list[0]->type_id != Value::T_BOOL || value_list[1]->type_id != Value::T_BOOL) {
        return Error::from_string("Invalid argument type(s) for function \"xor\"");
    }

    const Bool bool1 = Lib::cast<Bool>(value_list[0]);
    const Bool bool2 = Lib::cast<Bool>(value_list[1]);

    const Bool result ((bool1.value || bool2.value) && !(bool1.value && bool2.value));
    return std::make_shared<const Bool>(result);
}

Value::Ptr Lib::f_nand(const ParseContext::ValueList& value_list) {
    if (value_list.size() != 2) {
        return Error::from_string("Invalid argument count for function \"nand\"");
    } else if (value_list[0]->type_id != Value::T_BOOL || value_list[1]->type_id != Value::T_BOOL) {
        return Error::from_string("Invalid argument type(s) for function \"nand\"");
    }

    const Bool bool1 = Lib::cast<Bool>(value_list[0]);
    const Bool bool2 = Lib::cast<Bool>(value_list[1]);

    const Bool result (!(bool1.value && bool2.value));
    return std::make_shared<const Bool>(result);
}

Value::Ptr Lib::f_nor(const ParseContext::ValueList& value_list) {
    if (value_list.size() != 2) {
        return Error::from_string("Invalid argument count for function \"nor\"");
    } else if (value_list[0]->type_id != Value::T_BOOL || value_list[1]->type_id != Value::T_BOOL) {
        return Error::from_string("Invalid argument type(s) for function \"nor\"");
    }

    const Bool bool1 = Lib::cast<Bool>(value_list[0]);
    const Bool bool2 = Lib::cast<Bool>(value_list[1]);

    const Bool result (!(bool1.value || bool2.value));
    return std::make_shared<const Bool>(result);
}

Value::Ptr Lib::f_print(const ParseContext::ValueList& value_list) {
    for (std::size_t i = 0; i < value_list.size(); i++) {
        std::cout << value_list[i]->to_string() << " ";
    };

    return std::make_shared<const Null>();
}

Value::Ptr Lib::f_println(const ParseContext::ValueList& value_list) {
    Value::Ptr value = Lib::f_print(value_list);
    if (value->type_id == Value::T_ERROR) {
        return value;
    }

    std::cout << std::endl;
    return value;
}
