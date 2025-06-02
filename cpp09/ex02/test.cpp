// #include <iostream>
// #include <vector>
// #include <cstdlib>
// #include <sstream>

// // Jacobsthal sequence generator
// std::vector<int> generateJacobsthalOrder(int n) {
//     std::vector<int> order;
//     std::vector<int> jacob;

//     // Generate Jacobsthal numbers up to n
//     jacob.push_back(0);
//     jacob.push_back(1);
//     while (jacob.back() < n) {
//         size_t next = jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2];
//         jacob.push_back(next);
//     }

//     // Fill in Jacobsthal insert order
//     for (size_t i = 2; i < jacob.size(); ++i) {
//         for (size_t j = jacob[i] - 1; j > jacob[i - 1] - 1 && j < n; --j)
//             order.push_back(j);
//     }
//     if (n > 0)
//         order.push_back(0); // Always insert the first element

//     return order;
// }

// // Binary insertion into sorted vector
// void binaryInsert(std::vector<int>& vec, int value) {
//     size_t left = 0;
//     size_t right = vec.size();
//     while (left < right) {
//         size_t mid = (left + right) / 2;
//         if (vec[mid] < value)
//             left = mid + 1;
//         else
//             right = mid;
//     }
//     vec.insert(vec.begin() + left, value);
// }


// void printVector(const std::vector<int>& vec) {
//     for (const int& val : vec)
//     {
//         std::cout << val << " ";
//     }
//     std::cout << std::endl;
// }

// // Ford-Johnson sorting algorithm
// std::vector<int> fordJohnsonSort(std::vector<int>& input) {
//     if (input.size() <= 1)
//         return input;

//     std::vector<int> bigs, smalls;

//     for (size_t i = 0; i + 1 < input.size(); i += 2) {
//         int a = input[i];
//         int b = input[i + 1];
//         if (a > b)
//             std::swap(a, b);
//         smalls.push_back(a);
//         bigs.push_back(b);
//     }

//     if (input.size() % 2 == 1)
//         smalls.push_back(input[input.size() - 1]);
//     std::cout << "Bigger elements: ";
//     printVector(bigs);
//     std::cout << "Smaller elements: ";
//     printVector(smalls);

//     std::vector<int> sortedBigs = fordJohnsonSort(bigs);
//     std::vector<int> insertOrder = generateJacobsthalOrder(smalls.size());
//     std::cout << "Insert order: ";
//     printVector(insertOrder);

//     for (size_t i = 0; i < insertOrder.size(); ++i) {
//         size_t idx = insertOrder[i];
//         if (idx < smalls.size())
//             binaryInsert(sortedBigs, smalls[idx]);
//     }
//     std::cout << "Sorted bigs after insertion: ";
//     printVector(sortedBigs);

//     return sortedBigs;
// }

// int main(int argc, char** argv) {
//     if (argc < 2) {
//         std::cerr << "Usage: " << argv[0] << " [list of integers]" << std::endl;
//         return 1;
//     }

//     std::vector<int> input;
//     for (int i = 1; i < argc; ++i)
//         input.push_back(std::atoi(argv[i]));

//     std::vector<int> sorted = fordJohnsonSort(input);

//     std::cout << "Sorted: ";
//     for (size_t i = 0; i < sorted.size(); ++i)
//         std::cout << sorted[i] << " ";
//     std::cout << std::endl;

//     return 0;
// }
#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream>

// Jacobsthal sequence generator
std::vector<int> generateJacobsthalOrder(int n) {
    std::vector<int> order;
    std::vector<int> jacob;

    // Generate Jacobsthal numbers up to n
    jacob.push_back(0);
    jacob.push_back(1);
    while (jacob.back() < n) {
        size_t next = jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2];
        jacob.push_back(next);
    }

    // Always insert index 0 first
    if (n > 0)
        order.push_back(0);

    // Fill in Jacobsthal insert order
    for (size_t i = 2; i < jacob.size(); ++i) {
        for (size_t j = jacob[i] - 1; j > jacob[i - 1] - 1 && j < n; --j) {
            if (j != 0) // avoid duplicating index 0
                order.push_back(j);
        }
    }

    return order;
}

void printVector(const std::vector<int>& vec) {
    for (const int& val : vec)
    {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

// Binary insertion into sorted vector
void binaryInsert(std::vector<int>& vec, int value) {
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

// Ford-Johnson sorting algorithm
std::vector<int> fordJohnsonSort(std::vector<int>& input) {
    if (input.size() <= 1)
        return input;

    std::vector<int> bigs, smalls;

    for (size_t i = 0; i + 1 < input.size(); i += 2) {
        int a = input[i];
        int b = input[i + 1];
        if (a > b)
            std::swap(a, b);
        smalls.push_back(a);
        bigs.push_back(b);
    }

    if (input.size() % 2 == 1)
        smalls.push_back(input[input.size() - 1]);

    std::cout << "Bigger elements: ";
    printVector(bigs);
    std::cout << "Smaller elements: ";
    printVector(smalls);

    std::vector<int> sortedBigs = fordJohnsonSort(bigs);
    std::vector<int> insertOrder = generateJacobsthalOrder(smalls.size());

    std::cout << "Insert order: ";
    printVector(insertOrder);

    for (size_t i = 0; i < insertOrder.size(); ++i) {
        size_t idx = insertOrder[i];
        if (idx < smalls.size())
            binaryInsert(sortedBigs, smalls[idx]);
    }
    std::cout << "Sorted bigs after insertion: ";
    printVector(sortedBigs);
    return sortedBigs;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " [list of integers]" << std::endl;
        return 1;
    }

    std::vector<int> input;
    for (int i = 1; i < argc; ++i)
        input.push_back(std::atoi(argv[i]));

    std::vector<int> sorted = fordJohnsonSort(input);

    std::cout << "Sorted: ";
    for (size_t i = 0; i < sorted.size(); ++i)
        std::cout << sorted[i] << " ";
    std::cout << std::endl;

    return 0;
}
