#pragma once
#include <memory>
#include <vector>
#include "../Value/Value.hpp"

class AstNode
{
    public:

    using Ptr = std::shared_ptr<AstNode>;

    enum NodeType {
        VALUE,
        FUNCTION_CALL,
    };

    AstNode(const Value::Ptr);
    AstNode(const std::vector<AstNode::Ptr>);

    private:

    const NodeType type;
    const Value::Ptr value;
    const std::vector<AstNode::Ptr> children;
};
