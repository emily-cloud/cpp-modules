
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

void PmergeMe::prepareReadInput(int argc, char **argv){
    std::string rawInput;
    for(int i = 1; i < argc; i++){
        rawInput += argv[i];
        rawInput += " ";
    }

    if(!valideInputSyntax(rawInput))
        return;
    input = rawInput;
}


bool PmergeMe::valideInputSyntax(std::string input){
    std::vector<int> numbers;
    if(input.empty()){
        std::cerr << "Error: empty input" << std::endl;
        return false;
    }

    std::cout << "debug input: " << input << std::endl;
    std::string::iterator it = input.begin();
    while(it != input.end()){
        if((!isdigit(*it) && *it != ' ') || *it == '\n' || *it == '\t' || *it == '0'){
            std::cerr << "Error: invalid input" << std::endl;
            return false;
        }
        int num = 0;
        while(it != input.end() && isdigit(*it)){
            num = num * 10 + (*it - '0');
            ++it;
        }
        if( *it == ' ' && num > 0){
            numbers.push_back(num);
            ++it;
        }
        else if(num == 0 && *it == ' '){
            ++it;
        }
    }

    for(size_t i = 0; i < numbers.size(); i++) {
        for(size_t j = i + 1; j < numbers.size(); j++) {
            if(numbers[i] == numbers[j]) {
                // std::cout << "debug " << numbers[i] << std::endl;
                // std::cout << "debug " << numbers[j] << std::endl;
                std::cerr << "Error: duplicate number found: " << numbers[i] << std::endl;
                return false;
            }
        }
    }

    // for(size_t i = 0; i < numbers.size(); i++){
    //     std::cout <<"debug " << numbers[i] << std::endl;
    // }
    numbers.clear();
    return true;
}

template<typename T>
void PmergeMe::readInputToContainer( T& container){
        std::istringstream iss(input);
        std::string number;
        while(iss >> number){
            int num =  stoi(number);
            container.push_back(num);
    } 
}

void PmergeMe::readSortVector(){
    clock_t start = clock();
    readInputToContainer(vectorData); 
    sortedVector = fordJohnsonSort(vectorData);
    clock_t end = clock();

    vectorDuration  = static_cast<double>(end - start) / CLOCKS_PER_SEC;
}

template<typename T>
T PmergeMe::fordJohnsonSort(T &container) {
    if(container.size() < 2){
        return container; // No need to sort if the container has less than 2 elements
    }
    T bigs, smalls;
    for(size_t i = 0; i + 1 < container.size(); i += 2){
        int num1 = container[i];
        int num2 = container[i + 1];
        if(num1 > num2){
            std::swap(num1, num2);
        }
        smalls.push_back(num1);
        bigs.push_back(num2);
    }

    if(container.size() % 2 != 0){
        smalls.push_back(container[container.size() - 1]);
    }

    std::cout << "Bigger elements: ";
    debugPrint(bigs);
    std::cout << "Smaller elements: ";
    debugPrint(smalls);

    T insertOrder;
    T sortedBigs = fordJohnsonSort(bigs);
    generateJacobsthalOrder(smalls.size(), insertOrder);
    //reorder the smalls to make sure has the same order as the bigs
    //rearrangeSmalls(smalls, bigs);

    std::cout << "Insert order: ";
    debugPrint(insertOrder);

    for (size_t i = 0; i < insertOrder.size(); ++i) {
        size_t idx = insertOrder[i];
        if (idx < smalls.size())
            binaryInsert(sortedBigs, smalls[idx]);
    }
    std::cout << "Sorted bigs after insertion: ";
    debugPrint(sortedBigs);
    return sortedBigs;
}

template<typename T>
void PmergeMe::binaryInsert(T& vec, int value) {
    size_t left = 0;
    size_t right = vec.size();
    while (left < right) {
        size_t mid = (left + right) / 2;
        if (vec[mid] < value)
            left = mid + 1;
        else
            right = mid;
    }
    vec.insert(vec.begin() + left, value);
}

// template<typename T>
// void PmergeMe::rearrangeSmalls(T &smalls, T &bigs) {
//     // Ensure smalls are in the same order as bigs
//     T orderedSmalls;
//     for(int 
//     smalls = orderedSmalls; // Update smalls with the ordered version
// }

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

    for (size_t i = jacob.size() - 1; i > 0; --i) {
        size_t hi = jacob[i];
        size_t lo = jacob[i - 1];

        // From hi - 1 down to lo (inclusive)
        for (size_t j = hi; j-- > lo;) {
            if (j < n && j != 0) // valid and not 0 (already added)
                order.push_back(j);
        }
    }
}


void PmergeMe::readSortDeque(){
    clock_t start = clock();
    readInputToContainer(dequeData);
    sortedDeque = fordJohnsonSort(dequeData);

    // system sort
    // for(size_t i = 0; i < dequeData.size(); i++){
    //     sortedDeque.push_back(dequeData[i]);
    //     }
    
    // std::sort(sortedDeque.begin(), sortedDeque.end());
    clock_t end = clock();
    dequeDuration  = static_cast<double>(end - start) / CLOCKS_PER_SEC;
}

void PmergeMe::printOutput() const{
    if(vectorData.size() == 0){
        //std::cerr << "Error: no data to process" << std::endl;
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

template<typename T>    
void PmergeMe::debugPrint(const T &container) const 
{
    for(typename T::const_iterator it = container.begin(); it != container.end(); ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}
