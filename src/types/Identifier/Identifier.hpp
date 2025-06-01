#pragma once
#include "../Value/Value.hpp"

class Identifier : public Value {
    public:

    Identifier(const std::string);
    static Ptr from_string(const std::string);
    std::string to_string() const override;

    private:

    const std::string id_name;
};
