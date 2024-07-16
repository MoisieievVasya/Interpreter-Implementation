#ifndef SHUNTINGYARD_HPP
#define SHUNTINGYARD_HPP

#include "pch.hpp"

queue<Token> ShuntingYard(deque<Token> tokens);
double CalculateResult(queue<Token> outputQueue);

#endif