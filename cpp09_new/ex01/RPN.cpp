#include "RPN.hpp"

RPN::RPN() : result(0) {}

RPN::RPN(const RPN &other) : numbers(other.numbers), 
     result(other.result),input(other.input) {}

RPN& RPN::operator=(const RPN &other) {
    if(this != &other){
        numbers = other.numbers;
        result = other.result;
        input = other.input;
    }
    return *this;
}

RPN::~RPN() {}

void RPN::readInput(std::string rawinput) {
    if(rawinput.empty()){
        std::cerr << "Error: empty input" << std::endl;
        return;
    }
    if(!valideInput(rawinput)){
        return;
    }
    input = rawinput;
}

bool RPN::valideInput(std::string input){
    int numberCount = 0;
    int operatorCount = 0;
    for (std::string::iterator it = input.begin(); it != input.end(); ++it) {
        if (!isdigit(*it) && *it != ' ' && *it != '+' && *it != '-' && *it != '*' && *it != '/') {
            std::cerr << "Error: invalid input" << std::endl;
            return false;
        }
        if(isdigit(*it)){
            numberCount++;
        } else if(*it == '+' || *it == '-' || *it == '*' || *it == '/'){
            operatorCount++;
        }
    }
    if(numberCount < 2){
        std::cerr << "Error: invalid input" << std::endl;
        return false;
    }
    if( operatorCount != numberCount - 1){
        std::cerr << "Error: invalid input" << std::endl;
        return false;
    }
    return true;
}

void RPN::calculate() {
    std::istringstream iss(input);
    std::string element;
    while(iss >> element){
        if(element.size() == 1 && isdigit(element[0])){
            int num = atoi(element.c_str());
            numbers.push(num);
        }
        else if (element == "+" || element == "-" || element == "*" || element == "/") {
            char op = element[0];
            if (numbers.size() < 2) {
                std::cerr << "Error: insufficient operands" << std::endl;
                return;
            }
            int num2 = numbers.top();
            numbers.pop();
            int num1 = numbers.top();
            numbers.pop();

            switch(op){
                case '+':
                    result = num1 + num2;
                    break;
                case '-':
                    result = num1 - num2;
                    break;
                case '*':
                    result = num1 * num2;
                    break;
                case '/':
                    if(num2 == 0){
                        std::cerr << "Error: division by zero" << std::endl;
                        return;
                    }
                    result = num1 / num2;
                    break;
                default:
                    std::cerr << "Error: invalid operator" << std::endl;
                return;
            }
            numbers.push(result);
        } 
        else {
            std::cerr << "Error: unknown token '" << element << "'" << std::endl;
            return;
        }
    }
}

void RPN::printResult() {
    if(numbers.empty()){
        return;
    }
    else
        std::cout << "Result: " << result << std::endl;
}
