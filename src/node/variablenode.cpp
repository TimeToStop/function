#include "variablenode.h"

VariableNode::VariableNode(Function* function):
    FunctionNode(),
    _function(function)
{
}

VariableNode::~VariableNode()
{
}

double VariableNode::calculate() const
{
    return _function->x();
}

// For one argument function - x
bool VariableNode::isVariable(const std::string& variable)
{
    return variable == "x";
}