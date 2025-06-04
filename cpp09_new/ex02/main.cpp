#include "PmergeMe.hpp"
//random input generation command:
// jot -r 8000 1 10000 | awk '!seen[$0]++' | head -n 3000 | tr '\n' ' ' | tee >(wc -w) | xargs ./PmergeMe


//./PmergeMe $(shuf -i 1-5000 -n 3000)

int main(int argc, char** argv){
    if(argc < 2 || (argc == 2 && std::string(argv[1]).empty())){
        std::cerr << "Usage: " << argv[0] << " <numbers>" << std::endl;
        return 1;
    }

    PmergeMe pmergeme;
    pmergeme.readVarifyInput(argc, argv);
    pmergeme.readSortVector();
    pmergeme.readSortDeque();
    pmergeme.printOutput();
    pmergeme.clearData();
    return 0;
}
