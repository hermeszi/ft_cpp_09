#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <iostream>

public:
    PmergeMe();
    PmergeMe(char **argv);
    PmergeMe(PmergeMe const &src);
    PmergeMe &operator=(PmergeMe const &rhs);
    ~PmergeMe();
    
    void run();

private:
    std::vector<int> vec_;
    std::deque<int>  deq_;

    void parseInput(char **argv);

    // void fjVector(std::vector<int>& v);
    // void fjDeque(std::deque<int>& d);

    // int lowerBoundVector(const std::vector<int>& v, int end, int value);
    // int lowerBoundDeque(const std::deque<int>& d, int end, int value);

    // bool isValidPositiveInt(const std::string& s);
    // void printBefore() const;
    // void printAfter(const std::vector<int>& sorted) const;

#endif
