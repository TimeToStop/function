#pragma once
#include <stdexcept>

#include <string>

class Exception : public std::exception
{
public:
	Exception();
	virtual ~Exception();

	virtual const char* what() const noexcept override;

protected:
	std::string _msg;
};

