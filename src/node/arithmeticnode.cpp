#include "arithmeticnode.h"

#include <stdexcept>
#include <math.h>

ArithmeticNode::ArithmeticNode(char operation):
    FunctionNode(),
	_operation(operation)
{
}

ArithmeticNode::~ArithmeticNode()
{
}

double ArithmeticNode::calculate() const
{
	if (_children.size() != 2) throw std::runtime_error("Arithmetic has to have 2 child");

    double left = (*std::next(_children.begin(), 0))->calculate();
    double right = (*std::next(_children.begin(), 1))->calculate();

	switch (_operation)
	{
	case '+': return left + right;
	case '-': return left - right;
	case '*': return left * right;
	case '/': return left / right;
	case '^': return pow(left, right);
	default:
		throw std::runtime_error("No operator available");
	}
}

void ArithmeticNode::setOperation(char operation)
{
	_operation = operation;
}

char ArithmeticNode::operation() const
{
	return _operation;
}
