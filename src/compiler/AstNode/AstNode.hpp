#pragma once
#include <vector>
#include "../Value/Value.hpp"

class AstNode
{
    public:

    enum NodeType {
        VALUE,
        FUNCTION_CALL,
    };

    AstNode(const Value::Ptr);
    AstNode(const std::vector<AstNode>);

    private:

    const NodeType type;
    const Value::Ptr value;
    const std::vector<AstNode> children;
};
