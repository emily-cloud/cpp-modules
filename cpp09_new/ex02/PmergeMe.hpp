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

class PmergeMe{
private:
    std::string input;
    std::vector<int> vectorData;
    std::deque<int> dequeData;
    std::vector<int> sortedVector;
    std::deque<int> sortedDeque;
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
    void readInputToDeque(std::deque<node> dequeData);
    std::vector<node> fordJohnsonSortVector(std::vector<node> &winners);
    std::deque<node> fordJohnsonSort(std::deque<node> &deq);
    void compareVectorPair(std::vector<node> &winners, std::vector<node> &smalls);
    void compareDequePair(std::deque<node> &winners);
    std::vector<int> generateJacobsthalOrderVector(size_t n);
    std::deque<int> generateJacobsthalOrderDeque(size_t n);
    void binaryInsertVector(std::vector<node> &vec, int value);
    void binaryInsertDeque(std::deque<node> &deq, int value);
    void readSortVector();
    void readSortDeque();
    void printOutput() const;
    void clearData();
    //template<typename T> void debugPrint(const T &container) const;
};

struct node {
    int value_winner;
    node *big;
    node *small;
};


