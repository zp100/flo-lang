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
    void p_word(ParseContext& cx);
    void p_number(ParseContext& cx);

    void handle_word(ParseContext& cx);
    void handle_number(ParseContext& cx);
    bool is_space_char(const char);
    bool is_separator_char(const char);
    bool is_word_char(const char, const bool);
    bool is_number_char(const char, const bool);
}
