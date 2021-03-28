#include "functionbuilder.h"

#include <iostream>

#include <stdexcept>

#include "functionparser.h"

#include "../exceptions/unexpectedtokenexception.h"

#include "../node/variablenode.h"
#include "../node/namenode.h"
#include "../node/arithmeticnode.h"
#include "../node/numbernode.h"
#include "../node/switchsignnode.h"

FunctionBuilder::FunctionBuilder():
	_current(TokenType::END_OF_INPUT),
	_prev(TokenType::END_OF_INPUT),
	_function(nullptr),
	_parser()
{
}

FunctionBuilder::~FunctionBuilder()
{
}

void FunctionBuilder::build(Function* function, const std::string& src)
{
	_function = function;
	_parser.load(src);

	std::shared_ptr<FunctionNode> root = parse();

	next();

	if (!_current.isEqual(TokenType::END_OF_INPUT)) throw UnexpectedTokenException("expected end of input", _parser);

	_function->setRoot(root);
}

void FunctionBuilder::next()
{
	_prev = _current;
	_current = _parser.next();
}

void FunctionBuilder::prev()
{
	_current = _parser.prev();
	_prev = _parser.prev();
	_parser.next();
}

std::shared_ptr<FunctionNode> FunctionBuilder::parse()
{
	next();
	return expression();
}

std::shared_ptr<FunctionNode> FunctionBuilder::expression()
{
	std::shared_ptr<FunctionNode> left = term();
	next();

	if (_current.isEqual(TokenType::OPERATOR, "+"))
	{
        std::shared_ptr<FunctionNode> node = std::make_shared<ArithmeticNode>('+');
		next();

		std::shared_ptr<FunctionNode> right = expression();

		node->appendChild(left);
		node->appendChild(right);

		return node;
	}
	else if (_current.isEqual(TokenType::OPERATOR, "-"))
	{
		std::shared_ptr<FunctionNode> node = std::make_shared<ArithmeticNode>('-');
		next();

		std::shared_ptr<FunctionNode> right = expression();

		std::shared_ptr<ArithmeticNode> arithmetic = std::dynamic_pointer_cast<ArithmeticNode>(right);

		if (arithmetic != nullptr)
		{
			char operation = arithmetic->operation();
			
			if (operation == '+')
			{
				arithmetic->setOperation('-');
			}
			else if (operation == '-')
			{
				arithmetic->setOperation('+');
			}
		}

		node->appendChild(left);
		node->appendChild(right);

		return node;
	}
	
	prev();
	return left;
}

std::shared_ptr<FunctionNode> FunctionBuilder::term()
{
	std::shared_ptr<FunctionNode> left = power();
	next();

	if (_current.isEqual(TokenType::OPERATOR, "*"))
	{
        std::shared_ptr<FunctionNode> node = std::make_shared<ArithmeticNode>(_current.data()[0]);
		next();

		std::shared_ptr<FunctionNode> right = term();

		node->appendChild(left);
		node->appendChild(right);

		return node;
	}
	else if (_current.isEqual(TokenType::OPERATOR, "/"))
	{
		std::shared_ptr<FunctionNode> node = std::make_shared<ArithmeticNode>(_current.data()[0]);
		next();

		std::shared_ptr<FunctionNode> right = term();

		std::shared_ptr<ArithmeticNode> arithmetic = std::dynamic_pointer_cast<ArithmeticNode>(right);

		if (arithmetic != nullptr)
		{
			char operation = arithmetic->operation();

			if (operation == '*')
			{
				arithmetic->setOperation('/');
			}
			else if (operation == '/')
			{
				arithmetic->setOperation('*');
			}
		}

		node->appendChild(left);
		node->appendChild(right);

		return node;
	}

	prev();
	return left;
}

std::shared_ptr<FunctionNode> FunctionBuilder::factor()
{
	switch (_current.type())
	{
	case TokenType::NAME: 
		return name();
	case TokenType::NUMBER:
        return std::make_shared<NumberNode>(_current.data());
	case TokenType::OPERATOR:
		if (_current.data() == "-")
		{
			prev();
			prev();

			if (_prev.data() == "-" && _current.data() == "-")
			{
				throw UnexpectedTokenException("double switch sign is not allowed, expected NUMBER, VARIABLE, FUNCTION CALL or BRACKET", _parser);
			}

			next();
			next();

            std::shared_ptr<FunctionNode> node = std::make_shared<SwitchSignNode>();
			next();
			node->appendChild(factor());
			return node;
		}

		if (_current.data() == "(")
		{
			next();
			std::shared_ptr<FunctionNode> node = expression();
			next();
			if (!_current.isEqual(TokenType::OPERATOR, ")")) throw UnexpectedTokenException("expected closing bracket", _parser);
			return node;
		}
	
	default:
		throw UnexpectedTokenException("expected: NAME, NUMBER, BRACKET, NEGATIVE SIGN", _parser);
	}
}

std::shared_ptr<FunctionNode> FunctionBuilder::power()
{
	std::shared_ptr<FunctionNode> left = factor();
	next();

	if (_current.isEqual(TokenType::OPERATOR, "^"))
	{
        std::shared_ptr<FunctionNode> node = std::make_shared<ArithmeticNode>('^');
		next();
		node->appendChild(left);
		node->appendChild(power());
		return node;
	}

	prev();
	return left;
}

// 
// Expr -> Term - Expr  | Term + Expr | Term
// Term -> Pow * Term | Pow / Term | Pow
// Pow -> Factor ^ Pow | Factor 
// Factor -> -Factor | Name | Number | (Expr) 
// Name -> name(Expr) | x

std::shared_ptr<FunctionNode> FunctionBuilder::name()
{
	if (_current.type() == TokenType::NAME)
	{
		if (NumberNode::isConstant(_current.data())) return std::make_shared<NumberNode>(_current.data());

        if (VariableNode::isVariable(_current.data())) return std::make_shared<VariableNode>(_function);

		if (!NameNode::isName(_current.data())) throw UnexpectedTokenException("unknown function to call", _parser);
 
		next();

		if (!_current.isEqual(TokenType::OPERATOR, "(")) throw UnexpectedTokenException("expected function call with BRACKET", _parser);

        std::shared_ptr<FunctionNode> node = std::make_shared<NameNode>(_prev.data());

		next();
		node->appendChild(expression());
		next();

		if (!_current.isEqual(TokenType::OPERATOR, ")")) throw UnexpectedTokenException("expected closing bracket ", _parser);

		return node;
	}

	throw std::runtime_error("Expected Name token");
}
