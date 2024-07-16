#include "pch.hpp"

CustomFunction parseFunction(const string& input) {
	CustomFunction func;
	size_t defPos = input.find("def");
	size_t paramsStart = input.find("(", defPos);
	size_t paramsEnd = input.find(")", paramsStart);
	size_t bodyStart = input.find("{", paramsEnd);
	size_t bodyEnd = input.find("}", bodyStart);

	func.name = input.substr(defPos + 4, paramsStart - defPos - 4);

	string paramsStr = input.substr(paramsStart + 1, paramsEnd - paramsStart - 1);
	istringstream paramsStream(paramsStr);
	string param;

	while (getline(paramsStream, param, ',')) {
		func.parameters.push_back(param);
	}

	func.body = input.substr(bodyStart + 1, bodyEnd - bodyStart - 1);

	return func;
}


void addFunction(unordered_map<string, CustomFunction>& functionsMap, const CustomFunction& func) {
	functionsMap[func.name] = func;
}


ParsedFunctionCall parseFunctionCall(const string& call) {
	ParsedFunctionCall parsedCall;
	size_t nameEnd = call.find("(");
	size_t argsEnd = call.find(")");

	parsedCall.name = call.substr(0, nameEnd);

	std::string argsStr = call.substr(nameEnd + 1, argsEnd - nameEnd - 1);
	std::istringstream argsStream(argsStr);
	std::string arg;
	while (getline(argsStream, arg, ',')) {
		parsedCall.arguments.push_back(arg);
	}

	return parsedCall;
}

string evaluateFunctionBody(const CustomFunction& func, const vector<string>& arguments) {
	std::string evaluatedBody = func.body;
	for (size_t i = 0; i < func.parameters.size(); ++i) {
		size_t pos;
		while ((pos = evaluatedBody.find(func.parameters[i])) != std::string::npos) {
			evaluatedBody.replace(pos, func.parameters[i].length(), arguments[i]);
		}
	}
	return evaluatedBody;
}

string evaluateFunctionCall(unordered_map<string, CustomFunction>& functionMap, const string& call) {
	ParsedFunctionCall parsedCall = parseFunctionCall(call);
	if (functionMap.find(parsedCall.name) != functionMap.end()) {
		CustomFunction func = functionMap[parsedCall.name];
		string evaluatedBody = evaluateFunctionBody(func, parsedCall.arguments);

		return evaluatedBody;
	}
	else {
		std::cerr << "Function not found: " << parsedCall.name << std::endl;
	}
}

string extractFunctionName(const string& input) {
	size_t nameEnd = input.find("(");
	if (nameEnd != std::string::npos) {
		return input.substr(0, nameEnd);
	}
	return "";
}