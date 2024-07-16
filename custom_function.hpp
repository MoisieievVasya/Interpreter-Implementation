#ifndef CUSTOM_FUNCTION_HPP
#define CUSTOM_FUNCTION_HPP

#include "pch.hpp"

struct CustomFunction {
	string name;
	vector<string> parameters;
	string body;
};

struct ParsedFunctionCall {
	std::string name;
	std::vector<std::string> arguments;
};

#endif