#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <chrono> 
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

    void prepareReadInput(int argc, char **argv);
    template<typename T> void readInputToContainer(T &container);
    bool valideInputSyntax(std::string input);
    void readSortVector();
    void readSortDeque();
    template<typename T> T fordJohnsonSort(T &container);
    template<typename T> void generateJacobsthalOrder(size_t n, T &order);
   // template<typename T> void rearrangeSmalls(T &smalls, T &bigs);
    template<typename T> void binaryInsert(T &vec, int value);
    template<typename T> void debugPrint(const T &container) const;
    void printOutput() const;
    void clearData();
};