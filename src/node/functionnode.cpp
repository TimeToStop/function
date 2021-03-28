#include "functionnode.h"

FunctionNode::FunctionNode():
    _children()
{
}

FunctionNode::~FunctionNode()
{
}

void FunctionNode::appendChild(const ChildNode& node)
{
    _children.push_back(node);
}

ChildNode FunctionNode::child(size_t index) const
{
    auto it = _children.begin();
    std::advance(it, index);
    return *it;
}
