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

Value* lib_add(ParseContext* const cx) {
    if (cx->value_list.size() != 2) {
        return new Error("Invalid argument count for function \"add\"");
    } else if (cx->value_list[0]->type_id != Value::T_NUM || cx->value_list[1]->type_id != Value::T_NUM) {
        return new Error("Invalid argument type(s) for function \"add\"");
    }

    Num* const num1 = static_cast<Num*>(cx->value_list[0]);
    Num* const num2 = static_cast<Num*>(cx->value_list[1]);

    return num1->add(num2);
}

Value* lib_sub(ParseContext* const cx) {
    if (cx->value_list.size() != 2) {
        return new Error("Invalid argument count for function \"sub\"");
    } else if (cx->value_list[0]->type_id != Value::T_NUM || cx->value_list[1]->type_id != Value::T_NUM) {
        return new Error("Invalid argument type(s) for function \"sub\"");
    }

    Num* const num1 = static_cast<Num*>(cx->value_list[0]);
    Num* const num2 = static_cast<Num*>(cx->value_list[1]);

    return num1->sub(num2);
}

Value* lib_mul(ParseContext* const cx) {
    if (cx->value_list.size() != 2) {
        return new Error("Invalid argument count for function \"mul\"");
    } else if (cx->value_list[0]->type_id != Value::T_NUM || cx->value_list[1]->type_id != Value::T_NUM) {
        return new Error("Invalid argument type(s) for function \"mul\"");
    }

    Num* const num1 = static_cast<Num*>(cx->value_list[0]);
    Num* const num2 = static_cast<Num*>(cx->value_list[1]);

    return num1->mul(num2);
}

Value* lib_div(ParseContext* const cx) {
    if (cx->value_list.size() != 2) {
        return new Error("Invalid argument count for function \"div\"");
    } else if (cx->value_list[0]->type_id != Value::T_NUM || cx->value_list[1]->type_id != Value::T_NUM) {
        return new Error("Invalid argument type(s) for function \"div\"");
    }

    Num* const num1 = static_cast<Num*>(cx->value_list[0]);
    Num* const num2 = static_cast<Num*>(cx->value_list[1]);

    if (num2->sign == 0) {
        return new Error("Division by zero");
    }

    return num1->div_nonzero(num2);
}

Value* lib_print(ParseContext* const cx) {
    for (int i = 0; i < cx->value_list.size(); i++) {
        std::cout << cx->value_list[i]->to_string() << " ";
    };

    return new Null();
}

Value* lib_println(ParseContext* const cx) {
    Value* value = lib_print(cx);
    if (value->type_id == Value::T_ERROR) {
        return value;
    }

    std::cout << std::endl;
    return value;
}
