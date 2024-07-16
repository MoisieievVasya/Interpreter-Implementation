#include "pch.hpp"

deque<Token> GetTokens(string expression) {
    deque<Token> tokenStack;
    string tokenStr;
    Token token;
    bool expectOperand = true; 

    for (size_t i = 0; i < expression.length(); ++i) {
        char c = expression[i];

        
        if (isdigit(c) || (c == '.' && !tokenStr.empty() && isdigit(tokenStr.back()))) {
            tokenStr += c;
            if (i + 1 >= expression.length() || (!isdigit(expression[i + 1]) && expression[i + 1] != '.')) {
                token.elements = tokenStr;
                token.type = Token::Type::NUMBER;
                token.precedence = -1;
                tokenStack.push_back(token);
                tokenStr.clear();
                expectOperand = false; 
            }
            continue;
        }

        
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '(' || c == ')' || c == ',') {
            if (c == '*' || c == '/' || c == '%') {
                token.precedence = 2;
            }
            else if (c == '+' || c == '-') {
                token.precedence = 1;
            }
            else {
                token.precedence = -1;
            }

            if (c == '-' && expectOperand) { 
                tokenStr += c; 
            }
            else { 
                token.elements = string(1, c);
                token.type = (c == '(') ? Token::Type::LEFT_PARENTHESIS :
                    (c == ')') ? Token::Type::RIGHT_PARENTHESIS :
                    (c == ',') ? Token::Type::COMMA : Token::Type::OPERATOR;
                tokenStack.push_back(token);
                if (c == '(' || c == ',') {
                    expectOperand = true; 
                }
                else {
                    expectOperand = false;
                }
            }
            continue;
        }

        
        if (isalpha(c)) {
            tokenStr += c;
            if (i + 1 >= expression.length() || !isalpha(expression[i + 1])) {
                if (tokenStr == "max" || tokenStr == "min" || tokenStr == "pow" || tokenStr == "abs") {
                    token.type = Token::Type::FUNCTION;
                    token.precedence = 3;
                }
                else {
                    token.type = Token::Type::UNKNOWN;
                    token.precedence = -1;
                }
                token.elements = tokenStr;
                tokenStack.push_back(token);
                tokenStr.clear();
                expectOperand = false; 
            }
        }
    }

    if (!tokenStr.empty()) {
        token.elements = tokenStr;
        token.type = Token::Type::NUMBER;
        token.precedence = -1;
        tokenStack.push_back(token);
    }

    return tokenStack;
}
