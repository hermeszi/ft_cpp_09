#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
//#include "PmergeMe.hpp"

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    os << "[";
    for (size_t i = 0; i < v.size(); ++i)
    {
        os << v[i] << (i != v.size() - 1 ? ", " : "");
    }
    return os << "]";
}

static bool isPositiveInt(const std::string &s)
{
    if (s.empty()) return false;

    for (std::string::size_type i = 0; i < s.length(); ++i)
    {
        if (!std::isdigit(s[i])) return false;
    }

    std::stringstream iss(s);
    long value;
    iss >> value;

    if (iss.fail() || !iss.eof())
        return false;
    if (value <= 0 || value > std::numeric_limits<int>::max())
        return false;

    return true;
}

static bool parseArgs(int argc, char **argv, std::vector<int> &input)
{
    for (int i = 1; i < argc; ++i)
    {
        std::string token(argv[i]);

        if (!isPositiveInt(token))
            return false;

        std::stringstream iss(token);
        int value;
        iss >> value;
        input.push_back(value);
    }
    return true;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Error\n" << "Example:\t";
        std::cerr << "./PmergeMe 3 5 9 7 4" << std::endl;
        return 1;
    }

    std::vector<int> input;
    if (!parseArgs(argc, argv, input))
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    try
    {
        std::cout << input << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
