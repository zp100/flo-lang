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
#include "../../util/ParseContext/ParseContext.hpp"

using FunctionType = std::function<Value::Ptr(ParseContext::ValueList)>;
using MapType = std::map<std::string, FunctionType>;

std::map<std::string, FunctionType> getFunctionMap();
template <typename T> T cast(Value::Ptr);

// TYPE UNARY
Value::Ptr lib_Bool(const ParseContext::ValueList&);
Value::Ptr lib_Num(const ParseContext::ValueList&);
Value::Ptr lib_Char(const ParseContext::ValueList&);
Value::Ptr lib_Byte(const ParseContext::ValueList&);
Value::Ptr lib_Symbol(const ParseContext::ValueList&);
Value::Ptr lib_List(const ParseContext::ValueList&);
Value::Ptr lib_Hash(const ParseContext::ValueList&);
Value::Ptr lib_Set(const ParseContext::ValueList&);

// MATH UNARY
Value::Ptr lib_neg(const ParseContext::ValueList&);
Value::Ptr lib_abs(const ParseContext::ValueList&);
Value::Ptr lib_round(const ParseContext::ValueList&);
Value::Ptr lib_floor(const ParseContext::ValueList&);
Value::Ptr lib_ceil(const ParseContext::ValueList&);

// MATH BINARY
Value::Ptr lib_add(const ParseContext::ValueList&);
Value::Ptr lib_sub(const ParseContext::ValueList&);
Value::Ptr lib_mul(const ParseContext::ValueList&);
Value::Ptr lib_div(const ParseContext::ValueList&);
Value::Ptr lib_mod(const ParseContext::ValueList&);
Value::Ptr lib_divmod(const ParseContext::ValueList&);
Value::Ptr lib_exp(const ParseContext::ValueList&);

// MATH GROUP (0+)
Value::Ptr lib_sum(const ParseContext::ValueList&);
Value::Ptr lib_prod(const ParseContext::ValueList&);

// MATH GROUP (1+)
Value::Ptr lib_min(const ParseContext::ValueList&);
Value::Ptr lib_max(const ParseContext::ValueList&);
Value::Ptr lib_avg(const ParseContext::ValueList&);

// LOGICAL UNARY
Value::Ptr lib_not(const ParseContext::ValueList&);

// LOGICAL BINARY
Value::Ptr lib_and(const ParseContext::ValueList&);
Value::Ptr lib_or(const ParseContext::ValueList&);
Value::Ptr lib_xor(const ParseContext::ValueList&);
Value::Ptr lib_else(const ParseContext::ValueList&);

// LOGICAL GROUP (2+)
Value::Ptr lib_alland(const ParseContext::ValueList&);
Value::Ptr lib_allor(const ParseContext::ValueList&);
Value::Ptr lib_allxor(const ParseContext::ValueList&);

// COMPARISON BINARY
Value::Ptr lib_lt(const ParseContext::ValueList&);
Value::Ptr lib_lteq(const ParseContext::ValueList&);
Value::Ptr lib_gt(const ParseContext::ValueList&);
Value::Ptr lib_gteq(const ParseContext::ValueList&);
Value::Ptr lib_eq(const ParseContext::ValueList&);
Value::Ptr lib_neq(const ParseContext::ValueList&);
Value::Ptr lib_in(const ParseContext::ValueList&);
// isinstance or instanceof?

// COMPARISON TERNARY
Value::Ptr lib_between(const ParseContext::ValueList&);

// GROUPS
Value::Ptr lib_size(const ParseContext::ValueList&);
Value::Ptr lib_at(const ParseContext::ValueList&);
Value::Ptr lib_with(const ParseContext::ValueList&);
Value::Ptr lib_add(const ParseContext::ValueList&);
Value::Ptr lib_remove(const ParseContext::ValueList&);
Value::Ptr lib_push(const ParseContext::ValueList&);
Value::Ptr lib_pop(const ParseContext::ValueList&);
Value::Ptr lib_shift(const ParseContext::ValueList&);
Value::Ptr lib_unshift(const ParseContext::ValueList&);
Value::Ptr lib_endswith(const ParseContext::ValueList&);
Value::Ptr lib_slice(const ParseContext::ValueList&);
Value::Ptr lib_replace(const ParseContext::ValueList&);
Value::Ptr lib_insert(const ParseContext::ValueList&);
Value::Ptr lib_reverse(const ParseContext::ValueList&);
Value::Ptr lib_first(const ParseContext::ValueList&);
Value::Ptr lib_last(const ParseContext::ValueList&);
Value::Ptr lib_split(const ParseContext::ValueList&);
Value::Ptr lib_join(const ParseContext::ValueList&);
Value::Ptr lib_keys(const ParseContext::ValueList&);
Value::Ptr lib_values(const ParseContext::ValueList&);
Value::Ptr lib_entries(const ParseContext::ValueList&);
Value::Ptr lib_fill(const ParseContext::ValueList&);
// etc...

// NESTED GROUPS
Value::Ptr lib_flat(const ParseContext::ValueList&);
Value::Ptr lib_flateach(const ParseContext::ValueList&);
Value::Ptr lib_zip(const ParseContext::ValueList&);

// ITERATORS
Value::Ptr lib_all(const ParseContext::ValueList&);
Value::Ptr lib_any(const ParseContext::ValueList&);
Value::Ptr lib_each(const ParseContext::ValueList&);
Value::Ptr lib_filter(const ParseContext::ValueList&);
Value::Ptr lib_find(const ParseContext::ValueList&);
Value::Ptr lib_findlast(const ParseContext::ValueList&);
Value::Ptr lib_index(const ParseContext::ValueList&);
Value::Ptr lib_indexlast(const ParseContext::ValueList&);
Value::Ptr lib_reduce(const ParseContext::ValueList&);
Value::Ptr lib_sort(const ParseContext::ValueList&);

// STRINGS
Value::Ptr lib_print(const ParseContext::ValueList&);
Value::Ptr lib_println(const ParseContext::ValueList&);
Value::Ptr lib_input(const ParseContext::ValueList&);
Value::Ptr lib_lower(const ParseContext::ValueList&);
Value::Ptr lib_upper(const ParseContext::ValueList&);
Value::Ptr lib_islower(const ParseContext::ValueList&);
Value::Ptr lib_isupper(const ParseContext::ValueList&);
Value::Ptr lib_trim(const ParseContext::ValueList&);
// formatting functions...

// MISC
Value::Ptr lib_call(const ParseContext::ValueList&);
Value::Ptr lib_spread(const ParseContext::ValueList&);
Value::Ptr lib_range(const ParseContext::ValueList&);
Value::Ptr lib_type(const ParseContext::ValueList&);
