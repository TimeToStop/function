#pragma once
#include "functionnode.h"

#include <string>
#include <map>

class NameNode : public FunctionNode
{
	using NameFunction = double (*)(double);

public:
    NameNode(const std::string&);
	virtual ~NameNode();

    virtual double calculate() const override;

	static bool isName(const std::string& name);

private:
	NameFunction _function;

	static const std::map<std::string, NameFunction> _functions;
};

