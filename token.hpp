#ifndef TOKEN_HPP
#define TOKEN_HPP

#include "pch.hpp"

class Token {
public: 
	enum class Type {
		UNKNOWN,
		NUMBER,
		OPERATOR,
		LEFT_PARENTHESIS,
		RIGHT_PARENTHESIS,
		FUNCTION,
		COMMA
	};

	Type type;
	int precedence;
	string elements; 
};

#endif