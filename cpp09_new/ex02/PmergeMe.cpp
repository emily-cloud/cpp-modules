
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
        while (it != input.end() && std::isspace(*it)) {
            ++it;
        }
        if (it == input.end())
            break;
        if (!std::isdigit(*it)) {
            std::cerr << "Error: invalid input" << std::endl;
            return false;
        }
        int num = 0;
        while (it != input.end() && std::isdigit(*it)) {
            if (*it == '0' && num == 0) {
                std::cerr << "Error: invalid input (leading zero or 0)" << std::endl;
                return false;
            }
            num = num * 10 + (*it - '0');
            ++it;
        }
        numbers.push_back(num);
    }
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
            node current;
            current.value = number;
            current.big = nullptr;
            current.small = nullptr;
            vectorData.push_back(current);
    }
}

std::vector<node> PmergeMe::fordJohnsonSortVector(std::vector<node> &vectorData) {
    if(vectorData.size() < 2){
        return vectorData;
    }

    std::vector<node> winners;
    compareVectorPair(vectorData, winners);// Compare pairs of nodes and store winners
    std::vector<node> sortedWinners = fordJohnsonSortVector(winners);// Sort the bigs using Ford-Johnson algorithm
    std::vector<node> smalls;
    readVectorSmalls(vectorData, winners, smalls);// Extract smalls from winners

    std::vector<int> insertOrder;
    insertOrder = generateJacobsthalOrderVector(smalls.size());// Generate Jacobsthal order for smalls

    for (size_t i = 0; i < insertOrder.size(); ++i) {
        size_t idx = insertOrder[i];
        if (idx < smalls.size())
            binaryInsertVector(sortedWinners, smalls[idx].value);
    }
    return sortedWinners;
}

void PmergeMe::compareVectorPair(std::vector<node> &data, std::vector<node> &winners) {
    for(size_t i = 0; i + 1 < data.size(); i += 2){
        node current;
        if(data[i].value > data[i + 1].value){
            current.value = data[i].value;
            current.big = &data[i];
            current.small = &data[i + 1];
        } else {
            current.value = data[i + 1].value;
            current.big = &data[i + 1];
            current.small = &data[i];
        }
        winners.push_back(current);
    }
}

void PmergeMe::readVectorSmalls(std::vector<node> &data, const std::vector<node> &winners,std::vector<node> &smalls) {
    for (size_t i = 0; i < winners.size(); ++i) {
        if (winners[i].small != nullptr) {
            node smallNode;
            smallNode.value = winners[i].small->value;
            smallNode.big = nullptr; // Link to the big node
            smallNode.small = nullptr; // No small for the small node
            smalls.push_back(smallNode);
        }
    }

    if(data.size() % 2 != 0){
        node lastSmall;
        lastSmall.value = data.back().value;
        lastSmall.big = nullptr; // No big for the last unmatched
        lastSmall.small = nullptr; // No small for the last unmatched
        smalls.push_back(lastSmall);
    }
}

void PmergeMe::binaryInsertVector(std::vector<node> &vec, int value) {
    size_t left = 0;
    size_t right = vec.size();
    while (left < right) {
        size_t mid = (left + right) / 2;
        if (vec[mid].value < value)
            left = mid + 1;
        else
            right = mid;
    }
    node current;
    current.value = value;
    current.big = nullptr; // No big for the new node
    current.small = nullptr; // No small for the new node
    vec.insert(vec.begin() + left, current);
}

std::vector<int> PmergeMe::generateJacobsthalOrderVector(size_t n) {
    std::vector<int> order;
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
    return order;
}

void PmergeMe::readSortVector(){
    clock_t start = clock();
    readInputToVector();
    sortedVector = fordJohnsonSortVector(vectorData);
    clock_t end = clock();
    vectorDuration  = static_cast<double>(end - start) / CLOCKS_PER_SEC;
}


void PmergeMe::readInputToDeque(){
        std::istringstream iss(input);
        int number;
        while(iss >> number){
            node current;
            current.value = number;
            current.big = nullptr; // No big for the new node
            current.small = nullptr; // No small for the new node
            dequeData.push_back(current);
    }
}

std::deque<node> PmergeMe::fordJohnsonSortDeque(std::deque<node> &dequeData){
    if(dequeData.size() < 2){
        return dequeData;
    }

    std::deque<node> winners;
    compareDequePair(dequeData, winners);
    std::deque<node> sortedWinners = fordJohnsonSortDeque(winners);// Sort the bigs using Ford-Johnson algorithm
    std::deque<node> smalls;
    readDequeSmalls(dequeData, winners, smalls);// Extract smalls from winners

    std::deque<int> insertOrder;
    insertOrder = generateJacobsthalOrderDeque(smalls.size());// Generate Jacobsthal order for smalls

    for (size_t i = 0; i < insertOrder.size(); ++i) {
        size_t idx = insertOrder[i];
        if (idx < smalls.size())
            binaryInsertDeque(sortedWinners, smalls[idx].value);
    }
    return sortedWinners;
}

void PmergeMe::compareDequePair(std::deque<node> &data, std::deque<node> &winners) {
    for(size_t i = 0; i + 1 < data.size(); i += 2){
        node current;
        if(data[i].value > data[i + 1].value){
            current.value = data[i].value;
            current.big = &data[i];
            current.small = &data[i + 1];
        } else {
            current.value = data[i + 1].value;
            current.big = &data[i + 1];
            current.small = &data[i];
        }
        winners.push_back(current);
    }
}

void PmergeMe::readDequeSmalls(std::deque<node> &data, const std::deque<node> &winners, std::deque<node> &smalls) {
    for (size_t i = 0; i < winners.size(); ++i) {
        if (winners[i].small != nullptr) {
            node smallNode;
            smallNode.value = winners[i].small->value;
            smallNode.big = nullptr; // Link to the big node
            smallNode.small = nullptr; // No small for the small node
            smalls.push_back(smallNode);
        }
    }

    if(data.size() % 2 != 0){
        node lastSmall;
        lastSmall.value = data.back().value;
        lastSmall.big = nullptr; // No big for the last unmatched
        lastSmall.small = nullptr; // No small for the last unmatched
        smalls.push_back(lastSmall);
    }
}

void PmergeMe::binaryInsertDeque(std::deque<node> &deq, int value) {
    size_t left = 0;
    size_t right = deq.size();
    while (left < right) {
        size_t mid = (left + right) / 2;
        if (deq[mid].value < value)
            left = mid + 1;
        else
            right = mid;
    }
    node current;
    current.value = value;
    current.big = nullptr; // No big for the new node
    current.small = nullptr; // No small for the new node
    deq.insert(deq.begin() + left, current);
}

std::deque<int> PmergeMe::generateJacobsthalOrderDeque(size_t n) {
    std::deque<int> order;
    std::deque<size_t> jacob;

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
    return order;
}


void PmergeMe::readSortDeque(){
    clock_t start = clock();
    readInputToDeque();
    sortedDeque = fordJohnsonSortDeque(dequeData);
    clock_t end = clock();
    dequeDuration  = static_cast<double>(end - start) / CLOCKS_PER_SEC;
}

void PmergeMe::printOutput() const{
    if(vectorData.size() == 0){
        return;
    }
    std::cout << "Before: ";
    for(std::vector<node>::const_iterator it = vectorData.begin(); it != vectorData.end(); ++it){
        std::cout << it->value << " ";
    }
    std::cout << std::endl;

    std::cout << "After: ";
    for(std::vector<node>::const_iterator it = sortedVector.begin(); it != sortedVector.end(); ++it){
        std::cout << it->value << " ";
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

template<typename T>    
void PmergeMe::debugPrint(const T &container) const 
{
    for(typename T::const_iterator it = container.begin(); it != container.end(); ++it){
        std::cout << it->value << " ";
    }
    std::cout << std::endl;
}
