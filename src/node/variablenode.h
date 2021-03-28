#pragma once

#include "functionnode.h"

#include "../function/function.h"

#include <string>

class VariableNode : public FunctionNode
{
public:
    VariableNode(Function* function);
    virtual ~VariableNode();

    virtual double calculate() const override;

    static bool isVariable(const std::string& variable);

private:
    Function* _function;
};

