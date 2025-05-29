#pragma once
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include "types/Error.hpp"
#include "types/Null.hpp"
#include "types/Num.hpp"
#include "types/Value.hpp"
#include "util/ParseContext.hpp"

using FunctionType = std::function<const Value&(ParseContext&)>;
using MapType = std::map<std::string, FunctionType>;

std::map<std::string, FunctionType> getFunctionMap();

// TYPE UNARY
const Value& lib_Bool(ParseContext&);
const Value& lib_Num(ParseContext&);
const Value& lib_Char(ParseContext&);
const Value& lib_Byte(ParseContext&);
const Value& lib_Symbol(ParseContext&);
const Value& lib_List(ParseContext&);
const Value& lib_Hash(ParseContext&);
const Value& lib_Set(ParseContext&);

// MATH UNARY
const Value& lib_neg(ParseContext&);
const Value& lib_abs(ParseContext&);
const Value& lib_round(ParseContext&);
const Value& lib_floor(ParseContext&);
const Value& lib_ceil(ParseContext&);

// MATH BINARY
const Value& lib_add(ParseContext&);
const Value& lib_sub(ParseContext&);
const Value& lib_mul(ParseContext&);
const Value& lib_div(ParseContext&);
const Value& lib_mod(ParseContext&);
const Value& lib_divmod(ParseContext&);
const Value& lib_exp(ParseContext&);

// MATH GROUP (0+)
const Value& lib_sum(ParseContext&);
const Value& lib_prod(ParseContext&);

// MATH GROUP (1+)
const Value& lib_min(ParseContext&);
const Value& lib_max(ParseContext&);
const Value& lib_avg(ParseContext&);

// LOGICAL UNARY
const Value& lib_not(ParseContext&);

// LOGICAL BINARY
const Value& lib_and(ParseContext&);
const Value& lib_or(ParseContext&);
const Value& lib_xor(ParseContext&);
const Value& lib_else(ParseContext&);

// LOGICAL GROUP (2+)
const Value& lib_alland(ParseContext&);
const Value& lib_allor(ParseContext&);
const Value& lib_allxor(ParseContext&);

// COMPARISON BINARY
const Value& lib_lt(ParseContext&);
const Value& lib_lteq(ParseContext&);
const Value& lib_gt(ParseContext&);
const Value& lib_gteq(ParseContext&);
const Value& lib_eq(ParseContext&);
const Value& lib_neq(ParseContext&);
const Value& lib_in(ParseContext&);
// isinstance or instanceof?

// COMPARISON TERNARY
const Value& lib_between(ParseContext&);

// GROUPS
const Value& lib_size(ParseContext&);
const Value& lib_at(ParseContext&);
const Value& lib_with(ParseContext&);
const Value& lib_add(ParseContext&);
const Value& lib_remove(ParseContext&);
const Value& lib_push(ParseContext&);
const Value& lib_pop(ParseContext&);
const Value& lib_shift(ParseContext&);
const Value& lib_unshift(ParseContext&);
const Value& lib_endswith(ParseContext&);
const Value& lib_slice(ParseContext&);
const Value& lib_replace(ParseContext&);
const Value& lib_insert(ParseContext&);
const Value& lib_reverse(ParseContext&);
const Value& lib_first(ParseContext&);
const Value& lib_last(ParseContext&);
const Value& lib_split(ParseContext&);
const Value& lib_join(ParseContext&);
const Value& lib_keys(ParseContext&);
const Value& lib_values(ParseContext&);
const Value& lib_entries(ParseContext&);
const Value& lib_fill(ParseContext&);
// etc...

// NESTED GROUPS
const Value& lib_flat(ParseContext&);
const Value& lib_flateach(ParseContext&);
const Value& lib_zip(ParseContext&);

// ITERATORS
const Value& lib_all(ParseContext&);
const Value& lib_any(ParseContext&);
const Value& lib_each(ParseContext&);
const Value& lib_filter(ParseContext&);
const Value& lib_find(ParseContext&);
const Value& lib_findlast(ParseContext&);
const Value& lib_index(ParseContext&);
const Value& lib_indexlast(ParseContext&);
const Value& lib_reduce(ParseContext&);
const Value& lib_sort(ParseContext&);

// STRINGS
const Value& lib_print(ParseContext&);
const Value& lib_println(ParseContext&);
const Value& lib_input(ParseContext&);
const Value& lib_lower(ParseContext&);
const Value& lib_upper(ParseContext&);
const Value& lib_islower(ParseContext&);
const Value& lib_isupper(ParseContext&);
const Value& lib_trim(ParseContext&);
// formatting functions...

// MISC
const Value& lib_call(ParseContext&);
const Value& lib_spread(ParseContext&);
const Value& lib_range(ParseContext&);
const Value& lib_type(ParseContext&);
