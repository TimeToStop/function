#include "namenode.h"

#include <stdexcept>
#include <math.h>

const std::map<std::string, NameNode::NameFunction> NameNode::_functions =
{
	{ "sin", &sin },
	{ "cos", &cos },
	{ "tg", &tan },
	{ "tan", &tan },
 	{ "arctg", &atan },
	{ "arctan", &atan },
	{ "arcsin", &asin },
	{ "asin", &asin },
	{ "arccos", &acos },
	{ "acos", &acos }
};

NameNode::NameNode(const std::string& name):
    FunctionNode(),
	_function(nullptr)
{
	auto it = _functions.find(name);

	if (it == _functions.end())
	{
		throw std::runtime_error("No such function name");
	}

	_function = it->second;
}

NameNode::~NameNode()
{
}

double NameNode::calculate() const
{
	if (_children.size() != 1) throw std::runtime_error("Name should have one child");
	
    const double value = (*_children.begin())->calculate();

	return _function(value);
}

bool NameNode::isName(const std::string& name)
{
	return _functions.find(name) != _functions.end();
}
