#pragma once
#include <string>

enum class TokenType
{
	END_OF_INPUT,
	NUMBER,
	OPERATOR,
	NAME
};

class Token
{
public:
	Token();
	Token(TokenType type, const std::string& data = "", size_t pos = 0);
	Token(const Token& other);
	Token(Token&& other);
	~Token();

	Token& operator=(const Token& other);

	bool isEqual(TokenType type, const std::string& data = "") const;
	std::string toString() const;

	size_t pos() const;
	TokenType type() const;
	std::string data() const;

private:
	size_t _pos;
	TokenType _type;
	std::string _data;
};

