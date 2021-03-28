#pragma once

#include "../node/functionnode.h"

class Function
{
public:
	Function();
	~Function();

	double x() const;
	double calculate(double x);

	void setRoot(const std::shared_ptr<FunctionNode>& node);

private:
	double _x;
	std::shared_ptr<FunctionNode> _root;
};

