#pragma once
#include <cctype>
#include <fstream>
#include <iostream>
#include <regex>
#include "types/Num.hpp"
#include "types/Value.hpp"
#include "util/ParseContext.hpp"
#include "lib.hpp"

void parse(std::ifstream& source_file);
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
