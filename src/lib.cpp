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

const Value& lib_add(ParseContext& cx) {
    Value* value_ptr;
    if (cx.value_list.size() != 2) {
        return *value_ptr = Error("Invalid argument count for function \"add\"");
    } else if (cx.value_list[0].type_id != Value::T_NUM || cx.value_list[1].type_id != Value::T_NUM) {
        return *value_ptr = Error("Invalid argument type(s) for function \"add\"");
    }

    Num num1 = static_cast<Num&>(cx.value_list[0]);
    Num num2 = static_cast<Num&>(cx.value_list[1]);
    return num1.add(num2);
}

const Value& lib_sub(ParseContext& cx) {
    if (cx.value_list.size() != 2) {
        return Error("Invalid argument count for function \"sub\"");
    } else if (cx.value_list[0].type_id != Value::T_NUM || cx.value_list[1].type_id != Value::T_NUM) {
        return Error("Invalid argument type(s) for function \"sub\"");
    }

    Num num1 = static_cast<Num&>(cx.value_list[0]);
    Num num2 = static_cast<Num&>(cx.value_list[1]);

    return num1.sub(num2);
}

const Value& lib_mul(ParseContext& cx) {
    if (cx.value_list.size() != 2) {
        return Error("Invalid argument count for function \"mul\"");
    } else if (cx.value_list[0].type_id != Value::T_NUM || cx.value_list[1].type_id != Value::T_NUM) {
        return Error("Invalid argument type(s) for function \"mul\"");
    }

    Num num1 = static_cast<Num&>(cx.value_list[0]);
    Num num2 = static_cast<Num&>(cx.value_list[1]);

    return num1.mul(num2);
}

const Value& lib_div(ParseContext& cx) {
    if (cx.value_list.size() != 2) {
        return Error("Invalid argument count for function \"div\"");
    } else if (cx.value_list[0].type_id != Value::T_NUM || cx.value_list[1].type_id != Value::T_NUM) {
        return Error("Invalid argument type(s) for function \"div\"");
    }

    Num num1 = static_cast<Num&>(cx.value_list[0]);
    Num num2 = static_cast<Num&>(cx.value_list[1]);

    if (num2.sign == 0) {
        return Error("Division by zero");
    }

    return num1.div_nonzero(num2);
}

const Value& lib_print(ParseContext& cx) {
    for (int i = 0; i < cx.value_list.size(); i++) {
        std::cout << cx.value_list[i].to_string() << " ";
    };

    return Null();
}

const Value& lib_println(ParseContext& cx) {
    const Value& value = lib_print(cx);
    if (value.type_id == Value::T_ERROR) {
        return value;
    }

    std::cout << std::endl;
    return value;
}
