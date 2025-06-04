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
    template<typename T> void readInputToContainer(T &container);
    bool valideInputSyntax(std::string input);
    bool checkSpaces(const std::string& input);
    void readSortVector();
    void readSortDeque();
    template<typename T> T fordJohnsonSort(T &container);
    template<typename T, typename PairContainer> void comparePair(const T &container, T &bigs, PairContainer &pairs);
    template<typename T> void generateJacobsthalOrder(size_t n, T &order);
    template<typename T, typename PairConatainer> void rearrangeSmalls(PairConatainer &pairs,T &smalls, T &bigs);
    template<typename T> void binaryInsert(T &vec, int value);
    void printOutput() const;
    void clearData();
    //template<typename T> void debugPrint(const T &container) const;
};


template<typename T>
struct PairContainer;

template<>
struct PairContainer<std::vector<int> > {
    typedef std::vector<std::pair<int, int> > type;
};

template<>
struct PairContainer<std::deque<int> > {
    typedef std::deque<std::pair<int, int> > type;
};
