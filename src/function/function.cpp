#include "function.h"

Function::Function():
    _x(0),
    _root(nullptr)
{
}

Function::~Function()
{
}

double Function::x() const
{
    return _x;
}

double Function::calculate(double x)
{
    _x = x;
    return _root->calculate();
}

void Function::setRoot(const std::shared_ptr<FunctionNode>& node)
{
    _root = node;
}
