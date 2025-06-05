#pragma once

#include <iostream>
#include <stack>
#include <algorithm>
#include <sstream>

class RPN{
private:
    std::stack<int> numbers;
    int result;
    std::string input;

public:
    RPN();
    RPN(const RPN &other);
    RPN& operator=(const RPN &other);
    ~RPN();
    void readInput(std::string input);
    bool valideInput(std::string input);
    void calculate();
    void printResult();
};
