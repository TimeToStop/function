#pragma once
#include "functionnode.h"

class SwitchSignNode : public FunctionNode
{
public:
    SwitchSignNode();
	virtual ~SwitchSignNode();

    virtual double calculate() const override;
};

