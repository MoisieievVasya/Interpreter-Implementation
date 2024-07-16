#ifndef CUSTOM_FUNCTIONS_PARSER_HPP
#define CUSTOM_FUNCTIONS_PARSER_HPP

#include "pch.hpp"

CustomFunction parseFunction(const string& input);

void addFunction(std::unordered_map<std::string, CustomFunction>& functionsMap, const CustomFunction& func);

ParsedFunctionCall parseFunctionCall(const std::string& call);

string evaluateFunctionBody(const CustomFunction& func, const vector<string>& arguments);

string evaluateFunctionCall(std::unordered_map<std::string, CustomFunction>& functionMap, const std::string& call);

string extractFunctionName(const string& input);
#endif