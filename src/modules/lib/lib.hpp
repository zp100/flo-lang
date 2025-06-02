#pragma once
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include "../../types/Bool/Bool.hpp"
#include "../../types/Error/Error.hpp"
#include "../../types/Null/Null.hpp"
#include "../../types/Num/Num.hpp"
#include "../../types/Value/Value.hpp"
#include "../../util/BigInt/BigInt.hpp"
#include "../../util/ParseContext/ParseContext.hpp"

namespace Lib {
    using FunctionType = std::function<Value::Ptr(ParseContext::ValueList)>;
    using MapType = std::map<std::string, FunctionType>;

    std::map<std::string, FunctionType> getFunctionMap();
    template <typename T> T cast(Value::Ptr);

    // TYPE UNARY
    Value::Ptr t_Bool(const ParseContext::ValueList&);
    Value::Ptr t_Num(const ParseContext::ValueList&);
    Value::Ptr t_Char(const ParseContext::ValueList&);
    Value::Ptr t_Byte(const ParseContext::ValueList&);
    Value::Ptr t_Symbol(const ParseContext::ValueList&);
    Value::Ptr t_List(const ParseContext::ValueList&);
    Value::Ptr t_Hash(const ParseContext::ValueList&);
    Value::Ptr t_Set(const ParseContext::ValueList&);

    // MATH UNARY
    Value::Ptr neg(const ParseContext::ValueList&);
    Value::Ptr abs(const ParseContext::ValueList&);
    Value::Ptr round(const ParseContext::ValueList&);
    Value::Ptr floor(const ParseContext::ValueList&);
    Value::Ptr ceil(const ParseContext::ValueList&);

    // MATH BINARY
    Value::Ptr add(const ParseContext::ValueList&);
    Value::Ptr sub(const ParseContext::ValueList&);
    Value::Ptr mul(const ParseContext::ValueList&);
    Value::Ptr div(const ParseContext::ValueList&);
    Value::Ptr mod(const ParseContext::ValueList&);
    Value::Ptr divmod(const ParseContext::ValueList&);
    Value::Ptr exp(const ParseContext::ValueList&);

    // MATH GROUP (0+)
    Value::Ptr sum(const ParseContext::ValueList&);
    Value::Ptr prod(const ParseContext::ValueList&);

    // MATH GROUP (1+)
    Value::Ptr min(const ParseContext::ValueList&);
    Value::Ptr max(const ParseContext::ValueList&);
    Value::Ptr avg(const ParseContext::ValueList&);

    // LOGICAL UNARY
    Value::Ptr l_not(const ParseContext::ValueList&);

    // LOGICAL BINARY
    Value::Ptr l_and(const ParseContext::ValueList&);
    Value::Ptr l_or(const ParseContext::ValueList&);
    Value::Ptr l_xor(const ParseContext::ValueList&);
    Value::Ptr l_else(const ParseContext::ValueList&);

    // LOGICAL GROUP (0+)
    Value::Ptr alland(const ParseContext::ValueList&);
    Value::Ptr allor(const ParseContext::ValueList&);

    // COMPARISON BINARY
    Value::Ptr lt(const ParseContext::ValueList&);
    Value::Ptr lteq(const ParseContext::ValueList&);
    Value::Ptr gt(const ParseContext::ValueList&);
    Value::Ptr gteq(const ParseContext::ValueList&);
    Value::Ptr eq(const ParseContext::ValueList&);
    Value::Ptr neq(const ParseContext::ValueList&);
    Value::Ptr in(const ParseContext::ValueList&);
    // isinstance or instanceof?

    // COMPARISON TERNARY
    Value::Ptr between(const ParseContext::ValueList&);

    // GROUPS
    Value::Ptr size(const ParseContext::ValueList&);
    Value::Ptr at(const ParseContext::ValueList&);
    Value::Ptr with(const ParseContext::ValueList&);
    Value::Ptr add(const ParseContext::ValueList&);
    Value::Ptr remove(const ParseContext::ValueList&);
    Value::Ptr push(const ParseContext::ValueList&);
    Value::Ptr pop(const ParseContext::ValueList&);
    Value::Ptr shift(const ParseContext::ValueList&);
    Value::Ptr unshift(const ParseContext::ValueList&);
    Value::Ptr endswith(const ParseContext::ValueList&);
    Value::Ptr slice(const ParseContext::ValueList&);
    Value::Ptr replace(const ParseContext::ValueList&);
    Value::Ptr insert(const ParseContext::ValueList&);
    Value::Ptr reverse(const ParseContext::ValueList&);
    Value::Ptr first(const ParseContext::ValueList&);
    Value::Ptr last(const ParseContext::ValueList&);
    Value::Ptr split(const ParseContext::ValueList&);
    Value::Ptr join(const ParseContext::ValueList&);
    Value::Ptr keys(const ParseContext::ValueList&);
    Value::Ptr values(const ParseContext::ValueList&);
    Value::Ptr entries(const ParseContext::ValueList&);
    Value::Ptr fill(const ParseContext::ValueList&);
    // etc...

    // NESTED GROUPS
    Value::Ptr flat(const ParseContext::ValueList&);
    Value::Ptr flateach(const ParseContext::ValueList&);
    Value::Ptr zip(const ParseContext::ValueList&);

    // ITERATORS
    Value::Ptr all(const ParseContext::ValueList&);
    Value::Ptr any(const ParseContext::ValueList&);
    Value::Ptr each(const ParseContext::ValueList&);
    Value::Ptr filter(const ParseContext::ValueList&);
    Value::Ptr find(const ParseContext::ValueList&);
    Value::Ptr findlast(const ParseContext::ValueList&);
    Value::Ptr index(const ParseContext::ValueList&);
    Value::Ptr indexlast(const ParseContext::ValueList&);
    Value::Ptr reduce(const ParseContext::ValueList&);
    Value::Ptr sort(const ParseContext::ValueList&);

    // STRINGS
    Value::Ptr print(const ParseContext::ValueList&);
    Value::Ptr println(const ParseContext::ValueList&);
    Value::Ptr input(const ParseContext::ValueList&);
    Value::Ptr lower(const ParseContext::ValueList&);
    Value::Ptr upper(const ParseContext::ValueList&);
    Value::Ptr islower(const ParseContext::ValueList&);
    Value::Ptr isupper(const ParseContext::ValueList&);
    Value::Ptr trim(const ParseContext::ValueList&);
    // formatting functions...

    // MISC
    Value::Ptr call(const ParseContext::ValueList&);
    Value::Ptr spread(const ParseContext::ValueList&);
    Value::Ptr range(const ParseContext::ValueList&);
    Value::Ptr type(const ParseContext::ValueList&);
}
