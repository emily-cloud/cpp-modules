
#include "BitcoinExchange.hpp"


BitcoinExchange::BitcoinExchange() {}


BitcoinExchange::BitcoinExchange(const BitcoinExchange &other): 
    data(other.data) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
    if (this != &other) {
        data = other.data;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::readData(){

    std::ifstream file("data.csv");
    if(!file.is_open()){
        std::cerr << "Error opening file" << std::endl;
        return;
    }

    std::string line;
    if(std::getline(file, line)) {
        if (line != "date,exchange_rate")
            std::cerr << "Error: missing header => " << line << std::endl;
    }
    while(std::getline(file,line)){
        size_t commaPos = line.find(",");
        std::string date = line.substr(0, commaPos);
        std::string valueStr = line.substr(commaPos + 1); // +1 to skip ", "

        date.erase(0, date.find_first_not_of(" \t"));
        date.erase(date.find_last_not_of(" \t") + 1);
        valueStr.erase(0, valueStr.find_first_not_of(" \t"));
        valueStr.erase(valueStr.find_last_not_of(" \t") + 1);

        float value = std::atof(valueStr.c_str());
        data[date] = value;
    }
    file.close();
}

void BitcoinExchange::debugPrintData() const{
    std::map<std::string, double>::const_iterator it;
    for (it = data.begin(); it != data.end(); ++it) {
        std::cout << it->first << ": "  << std::fixed << std::setprecision(2) << it->second << std::endl;
    }
}

bool BitcoinExchange::checkFilename(const std::string& filename) {
    if (filename.empty()) {
        std::cerr << "Error: empty filename" << std::endl;
        return false;
    }

    bool onlySpaces = true;
    for (size_t i = 0; i < filename.length(); ++i) {
        if (!std::isspace(filename[i])) {
            onlySpaces = false;
            break;
        }
    }

    if (onlySpaces) {
        std::cerr << "Error: filename contains only spaces" << std::endl;
        return false;
    }

    return true;
}

void BitcoinExchange::calculatePrintExchange(const std::string &filename){
    std::ifstream file(filename.c_str());
    if(!checkFilename(filename))
        return;
    if(!file.is_open()){
        std::cerr << "Error opening file" << std::endl;
        return;
    }
    std::string line;
    if(std::getline(file, line)) {
        if (line != "date | value")
            std::cerr << "Error: missing header => " << line << std::endl;
    }
    float result;
    while(std::getline(file,line)){
        size_t pipePos = line.find("|");
        if (pipePos == std::string::npos) {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        std::string date = line.substr(0, pipePos);
        std::string valueStr = line.substr(pipePos + 1); // +1 to skip " | "
        date.erase(0, date.find_first_not_of(" \t"));
        date.erase(date.find_last_not_of(" \t") + 1);
        valueStr.erase(0, valueStr.find_first_not_of(" \t"));
        valueStr.erase(valueStr.find_last_not_of(" \t") + 1);

        if(!validateInput(date, valueStr))
            continue;
        double value = std::atof(valueStr.c_str());
        if(data.find(date) != data.end()){
            result = data[date] * value;
            std::cout << date << " => " << value << " = " << result << std::endl;
        } else {
            std::map<std::string, double>::const_iterator it;
            it = data.lower_bound(date);
            if(it != data.begin()){
                --it;
                result = it->second * value;
                std::cout << date << " => " << value << " = " << result << std::endl;
            } else {
                std::cerr << "No data for date: " << date << std::endl;
            }
        }    
    }
    file.close();
}

bool BitcoinExchange::validateInput(std::string date, std::string valueStr){
    if(date.length() != 10){
        std::cerr << "Error: invalid date format =>" << date << std::endl;
        return false;
    }
    for (int i = 0; i < 10; i++) {
        if ((i == 4 || i == 7) && date[i] != '-') {
            std::cerr << "Error: invalid date format => " << date << std::endl;
            return false;
        }
        if (i != 4 && i != 7 && !isdigit(date[i])) {
            std::cerr << "Error: invalid date format => " << date << std::endl;
            return false;
        }
    }

    valueStr.find(".");
    if ( valueStr.find(".") == 0 || valueStr.find(".") == valueStr.length() - 1) {
        std::cerr << "Error: not a digit number" << std::endl;
        return false;
    }

    int decimalPointCount = std::count(valueStr.begin(), valueStr.end(), '.');
    if (decimalPointCount > 1) {
        std::cerr << "Error: not a digit number" << std::endl;
        return false;
    }

    for (std::string::const_iterator it = valueStr.begin(); it != valueStr.end(); ++it) {
        if (!isdigit(*it) && *it != '.') {  // Allow decimal points and negative signs
            std::cerr << "Error: not a digit number" << std::endl;
            return false;
        }
    }

    double value = std::atof(valueStr.c_str());
    if(value < 0){
        std::cerr << "Error: not a positive number" << std::endl;
        return false;
    }
    if(value > 1000){
        std::cerr << "Error: too large a number" << std::endl;
        return false;
    }
    return true;
}
