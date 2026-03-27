#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <iostream>

class BitcoinExchange
{
    private:
        std::map<std::string, float> db_;

    public:
        BitcoinExchange();
        BitcoinExchange(BitcoinExchange const &src);
        BitcoinExchange &operator=(BitcoinExchange const &rhs);
        ~BitcoinExchange();

        void    loadCSV(std::string const &filename);
        float   getValue(std::string const &date);
        void    processInput(std::string const &filename);
};

#endif
