cmake_minimum_required(VERSION 3.10)

project(function)

add_executable(
	function 
	
	main.cpp
	
	src/exceptions/exception.cpp
	src/exceptions/unexpectedsymbolexception.cpp
	src/exceptions/unexpectedtokenexception.cpp

	src/function/function.cpp
	src/function/functionbuilder.cpp
	src/function/functionparser.cpp
	src/function/token.cpp

	src/node/arithmeticnode.cpp
	src/node/functionnode.cpp
	src/node/namenode.cpp
	src/node/numbernode.cpp	
	src/node/switchsignnode.cpp	
	src/node/variablenode.cpp

	src/exceptions/exception.h
	src/exceptions/unexpectedsymbolexception.h
	src/exceptions/unexpectedtokenexception.h

	src/function/function.h
	src/function/functionbuilder.h
	src/function/functionparser.h
	src/function/token.h

	src/node/arithmeticnode.h
	src/node/functionnode.h
	src/node/namenode.h
	src/node/numbernode.h	
	src/node/switchsignnode.h	
	src/node/variablenode.h
)