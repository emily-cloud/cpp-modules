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
    void readInputToContainer(std::string type);
    bool valideInputSyntax(std::string input);
    void readSortVector();
    void readSortDeque();
    void sortVectorAlgorithm();
    void sortSmallVector(std::vector<int> &smallVector);
    void sortDequeAlgorithm();
    void printOutput() const;
    void clearData();
};