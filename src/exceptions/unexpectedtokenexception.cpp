#include "unexpectedtokenexception.h"

UnexpectedTokenException::UnexpectedTokenException(const std::string& msg, FunctionParser& parser):
	Exception()
{	
	_msg = "Unexpected token - " + msg + ", but found " + parser.current().toString() + "\n";
	_msg += "f(x) = " + parser.input() + "\n";
	_msg += "       " + std::string(parser.current().pos(), ' ');
	_msg += "^~~~~~";
}

UnexpectedTokenException::~UnexpectedTokenException()
{
}
