#pragma once
#include "exception.h"

#include "../function/functionparser.h"

class UnexpectedSymbolException : public Exception
{
public:
	UnexpectedSymbolException(char sybmol, FunctionParser& parser);
	virtual ~UnexpectedSymbolException();
};

