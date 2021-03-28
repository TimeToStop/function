#include "switchsignnode.h"

#include <stdexcept>

SwitchSignNode::SwitchSignNode():
    FunctionNode()
{
}

SwitchSignNode::~SwitchSignNode()
{
}

double SwitchSignNode::calculate() const
{
    if (_children.size() != 1) throw std::runtime_error("switch sign has to have one child");
    
    const double value = (*_children.begin())->calculate();
    return -value;
}
