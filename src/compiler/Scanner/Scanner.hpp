#pragma once
#include <fstream>
#include <memory>
#include "../Token/Token.hpp"

class Scanner {
    public:

    using FilePtr = std::shared_ptr<std::ifstream>;

    Scanner(FilePtr);
    Token::Ptr get_next_token();

    private:

    FilePtr source_file;
    char next_char;
    bool is_empty;

    void prep_next_char();
    bool is_space_char(const char) const;
    bool is_separator_char(const char) const;
    bool is_identifier_char(const char, const bool) const;
    bool is_number_char(const char, const bool) const;
    bool is_operator_char(const char, const int) const;
    bool is_operator_continuation_char(const char) const;
};
