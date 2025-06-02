
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
        if(!isdigit(*it) && *it != ' '){
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

void PmergeMe::readInputToContainer(std::string type){
   if(type == "vector"){
        std::istringstream iss(input);
        std::string number;
        while(iss >> number){
            int num =  stoi(number);
            vectorData.push_back(num);
    } 
    }else if(type == "deque"){
        std::istringstream iss(input);
        std::string number;
        while(iss >> number){
            int num =  stoi(number);
            dequeData.push_back(num);
        }
    }
}

void PmergeMe::readSortVector(){
    clock_t start = clock();
    readInputToContainer("vector");
    sortVectorAlgorithm();
    
    // for(size_t i = 0; i < vectorData.size(); i++){
    //     sortedVector.push_back(vectorData[i]);
    //     }
    
    // std::sort(sortedVector.begin(), sortedVector.end());
    clock_t end = clock();

    vectorDuration  = static_cast<double>(end - start) / CLOCKS_PER_SEC;
}

void PmergeMe::sortVectorAlgorithm(){
    std::vector<int> bigVector;
    std::vector<int> smallVector;
    for(size_t i = 0; i < vectorData.size(); i+2){
        int num1 = vectorData[i];
        int num2 = vectorData[i + 1];
        if(num1 > num2){
            smallVector.push_back(num2);
            bigVector.push_back(num1);
        } else {
            smallVector.push_back(num1);
            bigVector.push_back(num2);
        }
    }
    if(vectorData.size() % 2 != 0){
        bigVector.push_back(vectorData[vectorData.size() - 1]);
    }
   
    // sort the small vector
    sortSmallVector(smallVector);
    // rearrange the big vector to follow the 


}

void PmergeMe::sortSmallVector(std::vector<int> &smallVector){
    // sort the small vector
    for(size_t i = 0; i < smallVector.size() - 1; i++){
        for(size_t j = i + 1; j < smallVector.size(); j++){
            if(smallVector[i] > smallVector[j]){
                std::swap(smallVector[i], smallVector[j]);
            }
        }
    }
}

void PmergeMe::readSortDeque(){
    clock_t start = clock();
    readInputToContainer("deque");
    sortDequeAlgorithm();
    // system sort
    // for(size_t i = 0; i < dequeData.size(); i++){
    //     sortedDeque.push_back(dequeData[i]);
    //     }
    
    // std::sort(sortedDeque.begin(), sortedDeque.end());
    clock_t end = clock();
    dequeDuration  = static_cast<double>(end - start) / CLOCKS_PER_SEC;
}

void PmergeMe::sortDequeAlgorithm(){

}

void PmergeMe::printOutput() const{
    if(vectorData.size() == 0){
        //std::cerr << "Error: no data to process" << std::endl;
        return;
    }
    std::cout << "Before: ";
    for(size_t i = 0; i < vectorData.size(); i++){
        std::cout << vectorData[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "After: ";
    for(size_t i = 0; i < sortedVector.size(); i++){
        std::cout << sortedVector[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Time to process a range of " << vectorData.size() << " elements with std::vector : " 
        << std::fixed << std::setprecision(5) << vectorDuration * 1000 << " ms" << std::endl;
    std::cout << "Time to process a range of " << dequeData.size() << " elements with std::deque : "
        << std::fixed << std::setprecision(5) << dequeDuration* 1000 << " ms" << std::endl;
}

void PmergeMe::clearData(){
    vectorData.clear();
    dequeData.clear();
    sortedVector.clear();
    sortedDeque.clear();
}
