#include "pch.hpp"

string FixPercision(string x) {
	ostringstream stroud;
	string str;

	double number = stod(x);
	stroud <<setprecision(10)<<number;
	str = stroud.str();
	size_t end = str.find_last_not_of('.') +1;
	str.erase(end);
	return str;
}

queue<Token> ShuntingYard(deque<Token> tokenStack) {
    Token token;
    queue<Token> outputQueue;
    stack<Token> operatorStack;

    while (!tokenStack.empty()) {
        token = tokenStack.front();
        tokenStack.pop_front();
        if (token.type == Token::Type::NUMBER) {
            token.elements = FixPercision(token.elements);
            outputQueue.push(token);
        }
        else if (token.type == Token::Type::OPERATOR) {
            Token o1 = token;
            while (!operatorStack.empty()) {
                Token o2 = operatorStack.top();
                if (o2.type != Token::Type::LEFT_PARENTHESIS && (o1.precedence <= o2.precedence)) {
                    outputQueue.push(o2);
                    operatorStack.pop();
                }
                else break;
            }
            operatorStack.push(o1);
        }
        else if (token.type == Token::Type::FUNCTION) {
            operatorStack.push(token);
        }
        else if (token.type == Token::Type::LEFT_PARENTHESIS) {
            operatorStack.push(token);
        }
        else if (token.type == Token::Type::COMMA) {
            
            while (!operatorStack.empty() && operatorStack.top().type != Token::Type::LEFT_PARENTHESIS) {
                outputQueue.push(operatorStack.top());
                operatorStack.pop();
            }
            
        }
        else if (token.type == Token::Type::RIGHT_PARENTHESIS) {
            while (!operatorStack.empty() && operatorStack.top().type != Token::Type::LEFT_PARENTHESIS) {
                outputQueue.push(operatorStack.top());
                operatorStack.pop();
            }
            if (!operatorStack.empty() && operatorStack.top().type == Token::Type::LEFT_PARENTHESIS) {
                operatorStack.pop(); 
            }
            if (!operatorStack.empty() && operatorStack.top().type == Token::Type::FUNCTION) {
                outputQueue.push(operatorStack.top());
                operatorStack.pop(); 
            }
        }
        else break;
    }
    while (!operatorStack.empty()) {
        if (operatorStack.top().type != Token::Type::LEFT_PARENTHESIS) {
            outputQueue.push(operatorStack.top());
            operatorStack.pop();
        }
        else break;
    }
    return outputQueue;
}



double CalculateResult(queue<Token> outputQueue) {
    vector<double> operandsV;

    while (!outputQueue.empty()) {
        Token token = outputQueue.front();
        outputQueue.pop();
        if (token.type == Token::Type::NUMBER) {
            operandsV.push_back(stod(token.elements));
        }
        else if (token.type == Token::Type::OPERATOR) {
            double operandR = operandsV.back();
            operandsV.pop_back();
            double operandL = operandsV.back();
            operandsV.pop_back();
            if (token.elements == "*") {
                operandsV.push_back(operandL * operandR);
            }
            else if (token.elements == "/") {
                operandsV.push_back(operandL / operandR);
            }
            else if (token.elements == "%") {
                operandsV.push_back((double)((int)operandL % (int)operandR));
            }
            else if (token.elements == "+") {
                operandsV.push_back(operandL + operandR);
            }
            else if (token.elements == "-") {
                operandsV.push_back(operandL - operandR);
            }
        }
        else if (token.type == Token::Type::FUNCTION) {
            if (token.elements == "max") {
                double operandR = operandsV.back();
                operandsV.pop_back();
                double operandL = operandsV.back();
                operandsV.pop_back();
                operandsV.push_back(max(operandL, operandR));
            }
            else if (token.elements == "min") {
                double operandR = operandsV.back();
                operandsV.pop_back();
                double operandL = operandsV.back();
                operandsV.pop_back();
                operandsV.push_back(min(operandL, operandR));
            }
            else if (token.elements == "pow") {
                double operandR = operandsV.back();
                operandsV.pop_back();
                double operandL = operandsV.back();
                operandsV.pop_back();
                operandsV.push_back(pow(operandL, operandR));
            }
            else if (token.elements == "abs") {
                double operand = operandsV.back();
                operandsV.pop_back();
                operandsV.push_back(abs(operand));
            }
        }
    }
    return operandsV[0];
}
