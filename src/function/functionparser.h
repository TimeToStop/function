#pragma once
#include "token.h"

#include <stack>

class FunctionParser
{
public:
	FunctionParser();
	~FunctionParser();

	void load(const std::string& input);

	Token current() const;
	Token next();
	Token prev();

	std::string input() const;

private:
	Token parseNext();

private:
	Token _last_token;

	std::stack<Token> _stashed;
	std::stack<Token> _prevs;
	
	std::string::const_iterator _it;
	std::string _input;
};

