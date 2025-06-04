#include "RPN.hpp"

int main(int argc, char **argv){
    if(argc != 2 || (argc == 2 && std::string(argv[1]).empty())){
        std::cerr << "Usage: " << argv[0] << " <expression>" << std::endl;
        return 1;
    }

    RPN rpn;
    rpn.readInput(argv[1]);
    rpn.calculate();
    rpn.printResult();
    return 0;
}