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

    // OPERATORS
    Value::Ptr f_add(const ParseContext::ValueList&);
    Value::Ptr f_sub(const ParseContext::ValueList&);
    Value::Ptr f_mul(const ParseContext::ValueList&);
    Value::Ptr f_exp(const ParseContext::ValueList&);
    Value::Ptr f_lt(const ParseContext::ValueList&);
    Value::Ptr f_lteq(const ParseContext::ValueList&);
    Value::Ptr f_gt(const ParseContext::ValueList&);
    Value::Ptr f_gteq(const ParseContext::ValueList&);
    Value::Ptr f_eq(const ParseContext::ValueList&);
    Value::Ptr f_neq(const ParseContext::ValueList&);

    // OPERATORS (nullable)
    Value::Ptr f_div(const ParseContext::ValueList&);
    Value::Ptr f_mod(const ParseContext::ValueList&);

    // TYPE UNARY
    Value::Ptr f_Bool(const ParseContext::ValueList&);
    Value::Ptr f_Num(const ParseContext::ValueList&);
    Value::Ptr f_Char(const ParseContext::ValueList&);
    Value::Ptr f_Byte(const ParseContext::ValueList&);
    Value::Ptr f_Symbol(const ParseContext::ValueList&);
    Value::Ptr f_List(const ParseContext::ValueList&);
    Value::Ptr f_Hash(const ParseContext::ValueList&);
    Value::Ptr f_Set(const ParseContext::ValueList&);

    // MATH UNARY
    Value::Ptr f_neg(const ParseContext::ValueList&);
    Value::Ptr f_abs(const ParseContext::ValueList&);
    Value::Ptr f_floor(const ParseContext::ValueList&);
    Value::Ptr f_ceil(const ParseContext::ValueList&);
    Value::Ptr f_round(const ParseContext::ValueList&);

    // MATH BINARY (nullable)
    Value::Ptr f_divmod(const ParseContext::ValueList&);

    // MATH GROUP
    Value::Ptr f_sum(const ParseContext::ValueList&);
    Value::Ptr f_prod(const ParseContext::ValueList&);

    // MATH GROUP (nullable)
    Value::Ptr f_min(const ParseContext::ValueList&);
    Value::Ptr f_max(const ParseContext::ValueList&);
    Value::Ptr f_avg(const ParseContext::ValueList&);

    // COMPARISON BINARY
    Value::Ptr f_in(const ParseContext::ValueList&);
    // isinstance or instanceof?

    // COMPARISON TERNARY
    Value::Ptr f_between(const ParseContext::ValueList&);

    // COMPARISON GROUP
    Value::Ptr f_alleq(const ParseContext::ValueList&);
    Value::Ptr f_allneq(const ParseContext::ValueList&);

    // LOGICAL UNARY
    Value::Ptr f_not(const ParseContext::ValueList&);

    // LOGICAL BINARY
    Value::Ptr f_and(const ParseContext::ValueList&);
    Value::Ptr f_or(const ParseContext::ValueList&);
    Value::Ptr f_xor(const ParseContext::ValueList&);
    Value::Ptr f_nand(const ParseContext::ValueList&);
    Value::Ptr f_nor(const ParseContext::ValueList&);
    Value::Ptr f_else(const ParseContext::ValueList&);

    // LOGICAL GROUP
    Value::Ptr f_alland(const ParseContext::ValueList&);
    Value::Ptr f_allor(const ParseContext::ValueList&);
    Value::Ptr f_allnand(const ParseContext::ValueList&);
    Value::Ptr f_allnor(const ParseContext::ValueList&);

    // GROUPS
    Value::Ptr f_size(const ParseContext::ValueList&);
    Value::Ptr f_at(const ParseContext::ValueList&);
    Value::Ptr f_with(const ParseContext::ValueList&);
    Value::Ptr f_add(const ParseContext::ValueList&);
    Value::Ptr f_remove(const ParseContext::ValueList&);
    Value::Ptr f_push(const ParseContext::ValueList&);
    Value::Ptr f_pop(const ParseContext::ValueList&);
    Value::Ptr f_shift(const ParseContext::ValueList&);
    Value::Ptr f_unshift(const ParseContext::ValueList&);
    Value::Ptr f_endswith(const ParseContext::ValueList&);
    Value::Ptr f_slice(const ParseContext::ValueList&);
    Value::Ptr f_replace(const ParseContext::ValueList&);
    Value::Ptr f_insert(const ParseContext::ValueList&);
    Value::Ptr f_reverse(const ParseContext::ValueList&);
    Value::Ptr f_first(const ParseContext::ValueList&);
    Value::Ptr f_last(const ParseContext::ValueList&);
    Value::Ptr f_split(const ParseContext::ValueList&);
    Value::Ptr f_join(const ParseContext::ValueList&);
    Value::Ptr f_keys(const ParseContext::ValueList&);
    Value::Ptr f_values(const ParseContext::ValueList&);
    Value::Ptr f_entries(const ParseContext::ValueList&);
    Value::Ptr f_fill(const ParseContext::ValueList&);
    // etc...

    // NESTED GROUPS
    Value::Ptr f_flat(const ParseContext::ValueList&);
    Value::Ptr f_flateach(const ParseContext::ValueList&);
    Value::Ptr f_zip(const ParseContext::ValueList&);

    // ITERATORS
    Value::Ptr f_all(const ParseContext::ValueList&);
    Value::Ptr f_any(const ParseContext::ValueList&);
    Value::Ptr f_each(const ParseContext::ValueList&);
    Value::Ptr f_filter(const ParseContext::ValueList&);
    Value::Ptr f_find(const ParseContext::ValueList&);
    Value::Ptr f_findlast(const ParseContext::ValueList&);
    Value::Ptr f_index(const ParseContext::ValueList&);
    Value::Ptr f_indexlast(const ParseContext::ValueList&);
    Value::Ptr f_reduce(const ParseContext::ValueList&);
    Value::Ptr f_sort(const ParseContext::ValueList&);

    // STRINGS
    Value::Ptr f_print(const ParseContext::ValueList&);
    Value::Ptr f_println(const ParseContext::ValueList&);
    Value::Ptr f_input(const ParseContext::ValueList&);
    Value::Ptr f_lower(const ParseContext::ValueList&);
    Value::Ptr f_upper(const ParseContext::ValueList&);
    Value::Ptr f_islower(const ParseContext::ValueList&);
    Value::Ptr f_isupper(const ParseContext::ValueList&);
    Value::Ptr f_trim(const ParseContext::ValueList&);
    // formatting functions...

    // MISC
    Value::Ptr f_call(const ParseContext::ValueList&);
    Value::Ptr f_spread(const ParseContext::ValueList&);
    Value::Ptr f_range(const ParseContext::ValueList&);
    Value::Ptr f_type(const ParseContext::ValueList&);
}
