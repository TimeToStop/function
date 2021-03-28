#include "unexpectedsymbolexception.h"

UnexpectedSymbolException::UnexpectedSymbolException(char sybmol, FunctionParser& parser):
    Exception()
{
    _msg = "Unexpected symbol \"" + std::string(1, sybmol) + "\"\n";
    _msg += "f(x) = " + parser.input() + "\n";
    _msg += "       " + std::string(parser.current().pos(), ' ') + "^~~~~\n";
}

UnexpectedSymbolException::~UnexpectedSymbolException()
{
}