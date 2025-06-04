#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>

struct node {
    int value;
    node *small;
};


class PmergeMe{
private:
    std::string input;
    std::vector<node> vectorData;
    std::deque<node> dequeData;
    std::vector<node> sortedVector;
    std::deque<node> sortedDeque;
    double vectorDuration;
    double dequeDuration;


public:
    PmergeMe();
    PmergeMe(const PmergeMe &other);
    PmergeMe& operator=(const PmergeMe &other);
    ~PmergeMe();

    void readVarifyInput(int argc, char **argv);
    bool checkSpaces(const std::string& input);
    bool valideInputSyntax(std::string input);
    void readInputToVector();
    void readInputToDeque();
    std::vector<node> fordJohnsonSortVector(std::vector<node> &winners);
    std::deque<node> fordJohnsonSortDeque(std::deque<node> &deque);
    void compareVectorPair(std::vector<node> &data,std::vector<node> &winners);
    void compareDequePair(std::deque<node> &data, std::deque<node> &winners);
    void readVectorSmalls(std::vector<node> &data,const std::vector<node> &winners, std::vector<node> &smalls);
    void readDequeSmalls(std::deque<node> &data, const std::deque<node> &winners, std::deque<node> &smalls);
    std::vector<int> generateJacobsthalOrderVector(size_t n);
    std::deque<int> generateJacobsthalOrderDeque(size_t n);
    void binaryInsertVector(std::vector<node> &vec, int value);
    void binaryInsertDeque(std::deque<node> &deq, int value);
    void readSortVector();
    void readSortDeque();
    void printOutput() const;
    void clearData();
    template<typename T> void debugPrint(const T &container) const;
};



