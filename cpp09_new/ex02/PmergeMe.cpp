
#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other){
    input = other.input;
    vectorData = other.vectorData;
    dequeData = other.dequeData;
    sortedVector = other.sortedVector;
    sortedDeque = other.sortedDeque;
    dequeDuration = other.dequeDuration;
    vectorDuration = other.vectorDuration;
}

PmergeMe& PmergeMe::operator=(const PmergeMe &other){
    if(this != &other){
        input = other.input;
        vectorData = other.vectorData;
        dequeData = other.dequeData;
        sortedVector = other.sortedVector;
        sortedDeque = other.sortedDeque;
        dequeDuration = other.dequeDuration;
        vectorDuration = other.vectorDuration;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}


bool PmergeMe::checkSpaces(const std::string& input) {
    if (input.empty()) {
        std::cerr << "Error: empty argument" << std::endl;
        return false;
    }

    bool onlySpaces = true;
    for (size_t i = 0; i < input.length(); ++i) {
        if (!std::isspace(input[i])) {
            onlySpaces = false;
            break;
        }
    }

    if (onlySpaces) {
        std::cerr << "Error: argument contains only spaces" << std::endl;
        return false;
    }

    return true;
}

void PmergeMe::readVarifyInput(int argc, char **argv){
    std::string rawInput;

    for(int i = 1; i < argc; i++){
        rawInput += argv[i];
        rawInput += " ";
    }

    if(!checkSpaces(rawInput))
        return;

    if(!valideInputSyntax(rawInput))
        return;
    input = rawInput;
}

bool PmergeMe::valideInputSyntax(std::string input){
    std::vector<int> numbers;
    std::string::iterator it = input.begin();

    while(it != input.end()){
        // Skip any leading spaces
        while (it != input.end() && std::isspace(*it)) {
            ++it;
        }
        // Handle end of string
        if (it == input.end())
            break;
        // Must be digit
        if (!std::isdigit(*it)) {
            std::cerr << "Error: invalid input" << std::endl;
            return false;
        }
        // Parse number
        int num = 0;
        while (it != input.end() && std::isdigit(*it)) {
            if (*it == '0' && num == 0) { // optional: disallow leading zero
                std::cerr << "Error: invalid input (leading zero or 0)" << std::endl;
                return false;
            }
            num = num * 10 + (*it - '0');
            ++it;
        }

        numbers.push_back(num);
    }
    // Check for duplicates
    for (size_t i = 0; i < numbers.size(); ++i) {
        for (size_t j = i + 1; j < numbers.size(); ++j) {
            if (numbers[i] == numbers[j]) {
                std::cerr << "Error: duplicate number found: " << numbers[i] << std::endl;
                return false;
            }
        }
    }
    return true;
}


void PmergeMe::readInputToVector(){
        std::istringstream iss(input);
        int number;
        while(iss >> number){
            vectorData.push_back(number);
    }
}


std::vector<node> PmergeMe::fordJohnsonSortVector(std::vector<node> &vectorData) {
    if(vectorData.size() < 2){
        return vectorData;
    }

    std::vector<node> winners, smalls;
    compareVectorPair(winners, smalls);//make pairs, put the bigs in one container and smalls in pair.first
    std::vector<node> sortedWinners = fordJohnsonSortVector(winners);// Sort the bigs using Ford-Johnson algorithm

    std::vector<int> insertOrder;
    generateJacobsthalOrderVector(smalls.size());// Generate Jacobsthal order for smalls
    // std::cout << "Insert order: ";
    // debugPrint(insertOrder);
    // Insert smalls into sortedBigs according to the Jacobsthal order
    for (size_t i = 0; i < insertOrder.size(); ++i) {
        size_t idx = insertOrder[i];
        if (idx < reorderedSmalls.size())
            binaryInsert(sortedBigs, reorderedSmalls[idx]);
    }
    return sortedBigs;
}

template<typename T, typename PairContainer>
void PmergeMe::comparePair(const T &container, T &bigs, PairContainer &pairs) {
   for(size_t i = 0; i + 1 < container.size(); i += 2){
        int num1 = container[i];
        int num2 = container[i + 1];
        if(num1 > num2){
            std::swap(num1, num2);
        }
        bigs.push_back(num2);
        pairs.push_back(std::make_pair(num1, num2));
    }

    if(container.size() % 2 != 0){
        pairs.push_back(std::make_pair(container.back(), -1)); // dummy -1 for unmatched
    }
}

template<typename T>
void PmergeMe::binaryInsert(T& container, int value) {
    size_t left = 0;
    size_t right = container.size();
    while (left < right) {
        size_t mid = (left + right) / 2;
        if (container[mid] < value)
            left = mid + 1;
        else
            right = mid;
    }
    container.insert(container.begin() + left, value);
}

template<typename T, typename PairContainer>
void PmergeMe::rearrangeSmalls(PairContainer &pairs, T &reorderedSmalls, T &sortedBigs) {
       for (typename T::const_iterator it = sortedBigs.begin(); it != sortedBigs.end(); ++it) {
        for (size_t j = 0; j < pairs.size(); ++j) {
            if (pairs[j].second == *it) {
                reorderedSmalls.push_back(pairs[j].first);
                break;
            }
        }
    }
}

template<typename T>
void PmergeMe::generateJacobsthalOrder(size_t n, T &order) {
    std::vector<size_t> jacob;

    jacob.push_back(1);
    jacob.push_back(3);

    // Build Jacobsthal numbers until we exceed n
    while (jacob.back() < n) {
        size_t next = jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2];
        jacob.push_back(next);
    }

    // Always insert 0 first
    if (n > 0)
        order.push_back(0);

    for (size_t i = 1; i < jacob.size(); ++i) {
        size_t high = jacob[i];
        size_t low = jacob[i - 1];

        // From high - 1 down to low
        for (size_t j = high - 1; j + 1 > low; --j) {
            if (j < n && j != 0) // skip 0, already pushed
                order.push_back(j);
        }
    }
}

void PmergeMe::readSortVector(){
    clock_t start = clock();
    readInputToVector();
    sortedVector = fordJohnsonSort();
    clock_t end = clock();
    vectorDuration  = static_cast<double>(end - start) / CLOCKS_PER_SEC;
}

void PmergeMe::readSortDeque(){
    clock_t start = clock();
    readInputToContainer(dequeData);
    sortedDeque = fordJohnsonSort(dequeData);
    clock_t end = clock();
    dequeDuration  = static_cast<double>(end - start) / CLOCKS_PER_SEC;
}

void PmergeMe::printOutput() const{
    if(vectorData.size() == 0){
        return;
    }
    std::cout << "Before: ";
    for(std::vector<int>::const_iterator it = vectorData.begin(); it != vectorData.end(); ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "After: ";
    for(std::vector<int>::const_iterator it = sortedVector.begin(); it != sortedVector.end(); ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Time to process a range of " << vectorData.size() << " elements with std::vector : " 
        << std::fixed << std::setprecision(5) << vectorDuration * 1000 << " ms" << std::endl;
    std::cout << "Time to process a range of " << dequeData.size() << " elements with std::deque : "
        << std::fixed << std::setprecision(5) << dequeDuration* 1000 << " ms" << std::endl;
}

void PmergeMe::clearData(){
    input.clear();
    vectorData.clear();
    dequeData.clear();
    sortedVector.clear();
    sortedDeque.clear();
}

// template<typename T>    
// void PmergeMe::debugPrint(const T &container) const 
// {
//     for(typename T::const_iterator it = container.begin(); it != container.end(); ++it){
//         std::cout << *it << " ";
//     }
//     std::cout << std::endl;
// }
