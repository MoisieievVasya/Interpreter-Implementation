#include "pch.hpp"

string trim(const std::string& str) {
    auto start = str.find_first_not_of(" \t");
    auto end = str.find_last_not_of(" \t");
    return start == std::string::npos ? "" : str.substr(start, end - start + 1);
}

string parseAndStoreVariable(std::unordered_map<std::string, int>& variables, const std::string& input) {
    auto eqPos = input.find('=');
    if (eqPos != std::string::npos) {
        std::string variable = trim(input.substr(0, eqPos));
        std::string expression = trim(input.substr(eqPos + 1));

        
        variables[variable] = 0;

        return expression; 
    }
    else {
        std::cerr << "Invalid expression format." << std::endl;
        return ""; 
    }
}