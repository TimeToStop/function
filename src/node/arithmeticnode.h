#pragma once
#include "functionnode.h"

#include <map>

class ArithmeticNode : public FunctionNode
{
public: 
    ArithmeticNode(char operation);
	virtual ~ArithmeticNode();

    virtual double calculate() const override;

	void setOperation(char operation);

	char operation() const;

private:
	char _operation;
};

