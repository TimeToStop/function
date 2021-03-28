#pragma once
#include "exception.h"

#include "../function/functionparser.h"

class UnexpectedTokenException : public Exception
{
public:
	UnexpectedTokenException(const std::string& msg, FunctionParser& parser);
	virtual ~UnexpectedTokenException();
};

