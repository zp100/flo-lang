#include "lib.hpp"

MapType getFunctionMap() {
    return {
        { "add", lib_add },
        { "sub", lib_sub },
        { "mul", lib_mul },
        { "div", lib_div },
        { "print", lib_print },
        { "println", lib_println },
    };
}

template <typename T> T cast(Value::Ptr value) {
    return *dynamic_cast<const T* const>(value.get());
}

Value::Ptr lib_add(ParseContext& cx) {
    if (cx.value_list.size() != 2) {
        return Error::from_string("Invalid argument count for function \"add\"");
    } else if (cx.value_list[0]->type_id != Value::T_NUM || cx.value_list[1]->type_id != Value::T_NUM) {
        return Error::from_string("Invalid argument type(s) for function \"add\"");
    }

    const Num num1 = cast<Num>(cx.value_list[0]);
    const Num num2 = cast<Num>(cx.value_list[1]);

    return std::make_shared<const Num>(num1.add(num2));
}

Value::Ptr lib_sub(ParseContext& cx) {
    if (cx.value_list.size() != 2) {
        return Error::from_string("Invalid argument count for function \"sub\"");
    } else if (cx.value_list[0]->type_id != Value::T_NUM || cx.value_list[1]->type_id != Value::T_NUM) {
        return Error::from_string("Invalid argument type(s) for function \"sub\"");
    }

    const Num num1 = cast<Num>(cx.value_list[0]);
    const Num num2 = cast<Num>(cx.value_list[1]);

    return std::make_shared<const Num>(num1.sub(num2));
}

Value::Ptr lib_mul(ParseContext& cx) {
    if (cx.value_list.size() != 2) {
        return Error::from_string("Invalid argument count for function \"mul\"");
    } else if (cx.value_list[0]->type_id != Value::T_NUM || cx.value_list[1]->type_id != Value::T_NUM) {
        return Error::from_string("Invalid argument type(s) for function \"mul\"");
    }

    const Num num1 = cast<Num>(cx.value_list[0]);
    const Num num2 = cast<Num>(cx.value_list[1]);

    return std::make_shared<const Num>(num1.mul(num2));
}

Value::Ptr lib_div(ParseContext& cx) {
    if (cx.value_list.size() != 2) {
        return Error::from_string("Invalid argument count for function \"div\"");
    } else if (cx.value_list[0]->type_id != Value::T_NUM || cx.value_list[1]->type_id != Value::T_NUM) {
        return Error::from_string("Invalid argument type(s) for function \"div\"");
    }

    const Num num1 = cast<Num>(cx.value_list[0]);
    const Num num2 = cast<Num>(cx.value_list[1]);

    if (num2.sign == 0) {
        return Error::from_string("Division by zero");
    }

    return std::make_shared<const Num>(num1.div_nonzero(num2));
}

Value::Ptr lib_print(ParseContext& cx) {
    for (int i = 0; i < cx.value_list.size(); i++) {
        std::cout << cx.value_list[i]->to_string() << " ";
    };

    return std::make_shared<const Null>();
}

Value::Ptr lib_println(ParseContext& cx) {
    Value::Ptr value = lib_print(cx);
    if (value->type_id == Value::T_ERROR) {
        return value;
    }

    std::cout << std::endl;
    return value;
}
