#include "AstNode.hpp"

AstNode::AstNode(const Value::Ptr v) : type(VALUE), value(v), children({}) {}

AstNode::AstNode(const std::vector<AstNode::Ptr> c) : type(FUNCTION_CALL), value(nullptr), children(c) {}
