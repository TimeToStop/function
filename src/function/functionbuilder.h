#pragma once
#include "function.h"
#include "functionparser.h"

#include <string>
#include <stack>

class FunctionBuilder
{
public:
	FunctionBuilder();
	~FunctionBuilder();

	void build(Function* function, const std::string& src);

private:
	void next();
	void prev();

	std::shared_ptr<FunctionNode> parse();

	std::shared_ptr<FunctionNode> expression();
	std::shared_ptr<FunctionNode> term();
	std::shared_ptr<FunctionNode> factor();
	std::shared_ptr<FunctionNode> power();

	std::shared_ptr<FunctionNode> name();

private:
	Token _current;
	Token _prev;
	Function* _function;
	FunctionParser _parser;
};
