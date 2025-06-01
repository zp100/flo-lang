#pragma once
#include <fstream>
#include "../../types/Num/Num.hpp"
#include "../../types/Value/Value.hpp"
#include "../../util/ParseContext/ParseContext.hpp"
#include "../lib/lib.hpp"

std::vector<Value::Ptr> parse(std::ifstream& source_file);
void parse_default(ParseContext& cx);
void parse_comment(ParseContext& cx);
void parse_number_signed(ParseContext& cx);
void parse_number(ParseContext& cx);
void parse_number_decimals(ParseContext& cx);
void parse_number_scientific_start(ParseContext& cx);
void parse_number_scientific_signed(ParseContext& cx);
void parse_number_scientific(ParseContext& cx);
void parse_word(ParseContext& cx);
void parse_call_start(ParseContext& cx);
void parse_function_name(ParseContext& cx);
Value::ValueId call_function(ParseContext& cx);
