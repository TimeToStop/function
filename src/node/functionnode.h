#pragma once
#include <memory>
#include <list>

class FunctionNode;

using ChildNode = std::shared_ptr<FunctionNode>;
using ChildrenNodes = std::list<ChildNode>;

class FunctionNode
{
public:
    FunctionNode();
	virtual ~FunctionNode();

    virtual double calculate() const = 0;

    void appendChild(const ChildNode& node);

    ChildNode child(size_t index) const;

protected:
    ChildrenNodes _children;
};

