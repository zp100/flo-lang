#pragma once
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include "../../types/Error/Error.hpp"
#include "../../types/Null/Null.hpp"
#include "../../types/Num/Num.hpp"
#include "../../types/Value/Value.hpp"
#include "../../util/ParseContext/ParseContext.hpp"

using FunctionType = std::function<Value::Ptr(ParseContext&)>;
using MapType = std::map<std::string, FunctionType>;

std::map<std::string, FunctionType> getFunctionMap();
template <typename T> T cast(const Value*);

// TYPE UNARY
Value::Ptr lib_Bool(ParseContext&);
Value::Ptr lib_Num(ParseContext&);
Value::Ptr lib_Char(ParseContext&);
Value::Ptr lib_Byte(ParseContext&);
Value::Ptr lib_Symbol(ParseContext&);
Value::Ptr lib_List(ParseContext&);
Value::Ptr lib_Hash(ParseContext&);
Value::Ptr lib_Set(ParseContext&);

// MATH UNARY
Value::Ptr lib_neg(ParseContext&);
Value::Ptr lib_abs(ParseContext&);
Value::Ptr lib_round(ParseContext&);
Value::Ptr lib_floor(ParseContext&);
Value::Ptr lib_ceil(ParseContext&);

// MATH BINARY
Value::Ptr lib_add(ParseContext&);
Value::Ptr lib_sub(ParseContext&);
Value::Ptr lib_mul(ParseContext&);
Value::Ptr lib_div(ParseContext&);
Value::Ptr lib_mod(ParseContext&);
Value::Ptr lib_divmod(ParseContext&);
Value::Ptr lib_exp(ParseContext&);

// MATH GROUP (0+)
Value::Ptr lib_sum(ParseContext&);
Value::Ptr lib_prod(ParseContext&);

// MATH GROUP (1+)
Value::Ptr lib_min(ParseContext&);
Value::Ptr lib_max(ParseContext&);
Value::Ptr lib_avg(ParseContext&);

// LOGICAL UNARY
Value::Ptr lib_not(ParseContext&);

// LOGICAL BINARY
Value::Ptr lib_and(ParseContext&);
Value::Ptr lib_or(ParseContext&);
Value::Ptr lib_xor(ParseContext&);
Value::Ptr lib_else(ParseContext&);

// LOGICAL GROUP (2+)
Value::Ptr lib_alland(ParseContext&);
Value::Ptr lib_allor(ParseContext&);
Value::Ptr lib_allxor(ParseContext&);

// COMPARISON BINARY
Value::Ptr lib_lt(ParseContext&);
Value::Ptr lib_lteq(ParseContext&);
Value::Ptr lib_gt(ParseContext&);
Value::Ptr lib_gteq(ParseContext&);
Value::Ptr lib_eq(ParseContext&);
Value::Ptr lib_neq(ParseContext&);
Value::Ptr lib_in(ParseContext&);
// isinstance or instanceof?

// COMPARISON TERNARY
Value::Ptr lib_between(ParseContext&);

// GROUPS
Value::Ptr lib_size(ParseContext&);
Value::Ptr lib_at(ParseContext&);
Value::Ptr lib_with(ParseContext&);
Value::Ptr lib_add(ParseContext&);
Value::Ptr lib_remove(ParseContext&);
Value::Ptr lib_push(ParseContext&);
Value::Ptr lib_pop(ParseContext&);
Value::Ptr lib_shift(ParseContext&);
Value::Ptr lib_unshift(ParseContext&);
Value::Ptr lib_endswith(ParseContext&);
Value::Ptr lib_slice(ParseContext&);
Value::Ptr lib_replace(ParseContext&);
Value::Ptr lib_insert(ParseContext&);
Value::Ptr lib_reverse(ParseContext&);
Value::Ptr lib_first(ParseContext&);
Value::Ptr lib_last(ParseContext&);
Value::Ptr lib_split(ParseContext&);
Value::Ptr lib_join(ParseContext&);
Value::Ptr lib_keys(ParseContext&);
Value::Ptr lib_values(ParseContext&);
Value::Ptr lib_entries(ParseContext&);
Value::Ptr lib_fill(ParseContext&);
// etc...

// NESTED GROUPS
Value::Ptr lib_flat(ParseContext&);
Value::Ptr lib_flateach(ParseContext&);
Value::Ptr lib_zip(ParseContext&);

// ITERATORS
Value::Ptr lib_all(ParseContext&);
Value::Ptr lib_any(ParseContext&);
Value::Ptr lib_each(ParseContext&);
Value::Ptr lib_filter(ParseContext&);
Value::Ptr lib_find(ParseContext&);
Value::Ptr lib_findlast(ParseContext&);
Value::Ptr lib_index(ParseContext&);
Value::Ptr lib_indexlast(ParseContext&);
Value::Ptr lib_reduce(ParseContext&);
Value::Ptr lib_sort(ParseContext&);

// STRINGS
Value::Ptr lib_print(ParseContext&);
Value::Ptr lib_println(ParseContext&);
Value::Ptr lib_input(ParseContext&);
Value::Ptr lib_lower(ParseContext&);
Value::Ptr lib_upper(ParseContext&);
Value::Ptr lib_islower(ParseContext&);
Value::Ptr lib_isupper(ParseContext&);
Value::Ptr lib_trim(ParseContext&);
// formatting functions...

// MISC
Value::Ptr lib_call(ParseContext&);
Value::Ptr lib_spread(ParseContext&);
Value::Ptr lib_range(ParseContext&);
Value::Ptr lib_type(ParseContext&);
