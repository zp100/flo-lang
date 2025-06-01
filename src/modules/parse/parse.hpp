#pragma once
#include <fstream>
#include "../../types/Bool/Bool.hpp"
#include "../../types/Identifier/Identifier.hpp"
#include "../../types/Null/Null.hpp"
#include "../../types/Num/Num.hpp"
#include "../../types/Value/Value.hpp"
#include "../../util/ParseContext/ParseContext.hpp"
#include "../lib/lib.hpp"

namespace Parse {
    std::vector<Value::Ptr> parse(std::ifstream& source_file);
    void p_default(ParseContext& cx);
    void p_comment(ParseContext& cx);
    void p_number_signed(ParseContext& cx);
    void p_number(ParseContext& cx);
    void p_number_decimals(ParseContext& cx);
    void p_number_scientific_start(ParseContext& cx);
    void p_number_scientific_signed(ParseContext& cx);
    void p_number_scientific(ParseContext& cx);
    void p_word(ParseContext& cx);
    void p_call_start(ParseContext& cx);
    void p_function_name(ParseContext& cx);
    Value::ValueId call_function(ParseContext& cx);
}
