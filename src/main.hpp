#pragma once
#include <cctype>
#include <fstream>
#include <iostream>
#include <regex>
#include "types/Num.hpp"
#include "types/Value.hpp"
#include "util/ParseContext.hpp"
#include "lib.hpp"

void parse(std::ifstream* const source_file);
void parse_default(ParseContext* const cx);
void parse_comment(ParseContext* const cx);
void parse_number_signed(ParseContext* const cx);
void parse_number(ParseContext* const cx);
void parse_number_decimals(ParseContext* const cx);
void parse_number_scientific_start(ParseContext* const cx);
void parse_number_scientific_signed(ParseContext* const cx);
void parse_number_scientific(ParseContext* const cx);
void parse_word(ParseContext* const cx);
void parse_call_start(ParseContext* const cx);
void parse_function_name(ParseContext* const cx);
Value::ValueId call_function(ParseContext* const cx);
