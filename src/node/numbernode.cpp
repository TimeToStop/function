#include "numbernode.h"

#define _USE_MATH_DEFINES 
#include <math.h>
#include <stdexcept>

const std::map<std::string, const double> NumberNode::_constants =
{
    { "e", M_E },
    { "E", M_E },
    { "pi", M_PI }
};

NumberNode::NumberNode(const std::string& value):
    FunctionNode(),
    _value(0)
{
    auto it = _constants.find(value);

    if (it != _constants.end())
    {
        _value = it->second;
    }
    else
    {
        size_t index = 0;
        _value = std::stod(value, &index);

        if (index != value.size()) throw std::runtime_error("Cannot parse full string to double");
    }
}

NumberNode::~NumberNode()
{
}

double NumberNode::calculate() const
{
    return _value;
}

bool NumberNode::isConstant(const std::string& constant)
{
    return _constants.find(constant) != _constants.end();
}