#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <exception>
#include <cctype>
#include "BitcoinExchange.hpp"

template <typename T>
static T strToType(std::string str)
{
    T value;
    std::stringstream ss(str);
    if (ss >> value)
        return value;
    throw std::runtime_error("bad input => " + str);
}
static int dateOk(std::string str)
{
    size_t len = str.size();
    if (len != 10)
        return 0;
    for (size_t i = 0; i < len; ++i)
    {
        if (i == 4 || i == 7)
        {
            if (str[i] != '-')
                return 0;
        }
        else
        {
            if (!std::isdigit(str[i]))
                return 0;
        }
    }
    try
    {
        int year = strToType<int>(str.substr(0,4));
        int month = strToType<int>(str.substr(5,2));
        int day = strToType<int>(str.substr(8,2));
        bool leapyear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (month < 1 || month > 12)
            return 0;
        int maxDay = 31;
        if (month == 4 || month == 6 || month == 9 || month == 11)
            maxDay = 30;
        else if (month == 2)
            maxDay = leapyear ? 29 : 28;
        if (day < 1 || day > maxDay)
            return 0;
        return 1;
    
    }
    catch (std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 0;
    }
}

BitcoinExchange::BitcoinExchange(){}

BitcoinExchange::BitcoinExchange(std::string const &src)
{
    this->loadCSV(src);
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &src)
{
    this->operator=(src);
}

BitcoinExchange & BitcoinExchange::operator=(BitcoinExchange const &rhs)
{
    if (&rhs != this)
    {
        this->db_ = rhs.db_;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange(){}

void    BitcoinExchange::loadCSV(std::string const &filename)
{
    std::ifstream fin(filename.c_str());
    if (!fin)
    {
        throw std::runtime_error("Error: could not open csv file.");
    }
    std::string line;
    std::getline(fin, line);
    while (std::getline(fin, line))
    {

        std::stringstream ss(line);
        std::string key;
        std::string value;
        getline(ss, key, ',');
        if (dateOk(key))
        {
            getline(ss, value);
            db_[key] = strToType<float>(value);
        }
        else
        {
            std::cerr << "Error: line skipped => " << key << std::endl;
        }
    }
    fin.close();
}

float   BitcoinExchange::getValue(std::string const &date) const
{
    std::map<std::string, float>::const_iterator it;
    it = this->db_.upper_bound(date);
    if (it != db_.begin())
        --it;
    return it->second;
}

void    BitcoinExchange::processInput(std::string const &filename)
{
    std::ifstream fin(filename.c_str());
    if (!fin)
    {
        throw std::runtime_error("Error: could not open file.");
    }
    std::string line;
    std::getline(fin, line);
    while (std::getline(fin, line))
    {
        try
        {
            std::stringstream ss(line);
            std::string key;
            std::string valueStr;
            getline(ss, key, '|');
            size_t non_space = key.find_last_not_of(" ");
            if (non_space == std::string::npos)
            {
                std::cout << "Error: bad input" << std::endl;
                continue;
            }
            key = key.substr(0, non_space + 1);
            if (dateOk(key))
            {
                getline(ss, valueStr);
                non_space = valueStr.find_first_not_of(" ");
                if (non_space == std::string::npos)
                {
                    std::cout << "Error: bad input" << std::endl;
                    continue;
                }
                valueStr = valueStr.substr(non_space);
                float valueFloat = strToType<float>(valueStr);
                if (valueFloat >= 0)
                {
                    if (valueFloat <= 1000)
                    {
                        std::cout << key << " => " << valueStr << " = " << this->getValue(key) * valueFloat << std::endl;
                    }
                    else
                    {
                        std::cout << "Error: too large a number." << std::endl;
                    }
                }
                else
                {
                    std::cout << "Error: not a positive number." << std::endl;
                }

            }
            else
            {
                std::cout << "Error: bad input => " << key << std::endl;
            }
        }
        catch (std::exception &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
            continue;
        }
    }
    fin.close();
}

std::map<std::string, float> const & BitcoinExchange::getDb() const
{
    return db_;
}
