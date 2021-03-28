#include "exception.h"

Exception::Exception():
    _msg()
{
}

Exception::~Exception()
{
}

const char* Exception::what() const noexcept
{
    return _msg.c_str();
}
