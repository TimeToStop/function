#include "token.h"

Token::Token():
    _type(TokenType::END_OF_INPUT),
    _data(""),
    _pos(0)
{
}

Token::Token(TokenType type, const std::string& data, size_t pos):
    _type(type),
    _data(data),
    _pos(pos)
{
}

Token::Token(const Token& other):
    _type(other._type),
    _data(other._data),
    _pos(other._pos)
{
}

Token::Token(Token&& other):
    _type(other._type),
    _data(std::move(other._data)),
    _pos(other._pos)
{
}

Token::~Token()
{
}

Token& Token::operator=(const Token& other)
{
    _type = other._type;
    _data = other._data;
    _pos = other._pos;
    return *this;
}

bool Token::isEqual(TokenType type, const std::string& data) const
{
    return (_type == type) && (_data == data);
}

std::string Token::toString() const
{
    std::string s;

    switch (_type)
    {
        case TokenType::END_OF_INPUT:
            s = "END_OF_INPUT";
            break;
        case TokenType::NAME:
            s = "NAME";
            break;
        case TokenType::NUMBER:
            s = "NUMBER";
            break;
        case TokenType::OPERATOR:
            s = "OPERATOR";
            break;
    }
    s += "(\"";
    s += _data;
    s += "\")";
    return s;
}

size_t Token::pos() const
{
    return _pos;
}

TokenType Token::type() const
{
    return _type;
}

std::string Token::data() const
{
    return _data;
}
