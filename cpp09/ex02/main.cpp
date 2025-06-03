#include "PmergeMe.hpp"
//random input generation command:
// jot -r 4000 1 100000 | sort -n | uniq | head -n 3000 | tr '\n' ' ' | xargs ./PmergeMe

int main(int argc, char** argv){

    if(argc < 2){
        std::cerr << "Usage: " << argv[0] << " <numbers>" << std::endl;
        return 1;
    }

    PmergeMe pmergeme;
    pmergeme.prepareReadInput(argc, argv);
    pmergeme.readSortVector();
    pmergeme.readSortDeque();
    pmergeme.printOutput();
    pmergeme.clearData();
    return 0;
}
