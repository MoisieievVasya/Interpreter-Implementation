#include "pch.hpp"


int main() {
	string line;
	vector<string> stringLineV;
	deque<Token> tokens;
	queue<Token> outputQueue;
	double result;
	string functionName;

	unordered_map<std::string, CustomFunction> customFunctions;
	unordered_map<std::string, int> variables;

	while(true){

		std::getline(std::cin, line);
		stringLineV.push_back(line);

		functionName = extractFunctionName(line);

		if (line.find("def") != string::npos) {
			CustomFunction func = parseFunction(line);
			addFunction(customFunctions, func);
			stringLineV.pop_back();
			continue;
		}
		
		if (line.find("=") != string::npos) {
			line = parseAndStoreVariable(variables, line);
		}

		if (customFunctions.find(functionName) != customFunctions.end()) {
			line = evaluateFunctionBody(customFunctions[functionName], parseFunctionCall(line).arguments);
		}
		

		vector<string>::iterator it;
		for (it = stringLineV.begin(); it != stringLineV.end(); it++) {
			tokens = GetTokens(*it);
			outputQueue = ShuntingYard(tokens);
			result = CalculateResult(outputQueue);
			cout << "= " << result << endl;
		}
		stringLineV.clear();
	}
	return 0;
}