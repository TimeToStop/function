#include "functionparser.h"

#include "../exceptions/unexpectedsymbolexception.h"

#include <list>
#include <stdexcept>

FunctionParser::FunctionParser():
    _stashed(),
    _prevs(),
    _it(),
    _input()
{
}

FunctionParser::~FunctionParser()
{
}

void FunctionParser::load(const std::string& input)
{
    _input = input;
    _it = _input.begin();

    _prevs = std::stack<Token>();
    _stashed = std::stack<Token>();
}

Token FunctionParser::next()
{
    Token token;
    
    if (_stashed.empty())
    {
        token = parseNext();
        _prevs.push(token);
    }
    else
    {
        token = _stashed.top();
        _stashed.pop();
        _prevs.push(token);
    }

    _last_token = token;
    return token;
}

Token FunctionParser::prev()
{
    if (_prevs.empty())
    {
        Token token(TokenType::END_OF_INPUT);
        _last_token = token;
        return token;
    }
    else
    {
        Token token = _prevs.top();
        _prevs.pop();
        _stashed.push(token);
        _last_token = token;
        return token;
    }
}

Token FunctionParser::current() const
{
    return _last_token;
}

std::string FunctionParser::input() const
{
    return _input;
}

Token FunctionParser::parseNext()
{
    while (_it != _input.end() && isspace(*_it) != 0)
    {
        _it++;
    }

    const size_t start_index = std::distance(_input.cbegin(), _it);

    if (_it == _input.end()) return Token(TokenType::END_OF_INPUT, "", start_index);

    const char c = *_it;

    switch (c)
    {
    case '(':
    case ')':
    case '+':
    case '-':
    case '*':
    case '/':
    case '^':
        _it++;
        return Token(TokenType::OPERATOR, std::string(1, c), start_index);
    default:
        break;
    }

    if (isdigit(c))
    {
        bool has_dot = false;
        std::list<char> number;

        while (_it != _input.end() && (isdigit(*_it) || *_it == '.'))
        {
            if (*_it == '.')
            {
                if (has_dot)
                {
                    throw UnexpectedSymbolException('.', *this);
                }
                else
                {
                    has_dot = true;
                }
            }

            number.push_back(*_it);
            _it++;
        }

        return Token(TokenType::NUMBER, std::string(number.begin(), number.end()), start_index);
    }
    else if (isalpha(c))
    {
        std::list<char> name;

        while (_it != _input.end() && isalpha(*_it))
        {
            name.push_back(*_it);
            _it++;
        }

        return Token(TokenType::NAME, std::string(name.begin(), name.end()), start_index);
    }

    throw UnexpectedSymbolException(*_it, *this);
}
