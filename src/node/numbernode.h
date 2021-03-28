#pragma once
#include "functionnode.h"

#include <map>
#include <string>

class NumberNode : public FunctionNode
{
public:
    NumberNode(const std::string& value);
	virtual ~NumberNode();

    virtual double calculate() const override;

	static bool isConstant(const std::string& constant);

private:
	double _value;

	static const std::map<std::string, const double> _constants;
};

