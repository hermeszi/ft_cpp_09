
#include <map>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <exception>
#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &src)
{

}

BitcoinExchange & BitcoinExchange::operator=(BitcoinExchange const &rhs)
{
    return *this;
}

BitcoinExchange::~BitcoinExchange(){}

void    BitcoinExchange::loadCSV(std::string const &filename)
{
    ifstream fin(filename.c_str());
    if (!fin)
    {
        throw std::runtime_error("open file for input failed!");
    }
    std::string line;
    std::getline(fin, line);
    while (std::getline(fin, line))
    {
        std::stringstream ss(line);
        std::string key;
        std::string value;
        getline(ss, key, ',');
        getline(ss, value);
        db_[key] = strToFloat(value);
    }
}

float   BitcoinExchange::getValue(std::string const &date)
{
    return 0;
}

void    processInput(std::string const &filename)
{

}

static float strToFloat(std::string str)
{
    float value;

    std::stringstream ss(str);

    if (ss >> value)
    {
        return value;
    } 
    else
    {
        throw std::runtime_error("Could not convert string to float.");
    }

    return 0;
}
