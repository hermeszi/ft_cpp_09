#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <iostream>
class PmergeMe
{
public:
    PmergeMe() : vec_(), deq_(){}
    PmergeMe(const std::vector<int>& input) : vec_(input), deq_(input.begin(), input.end()) {}
    PmergeMe(PmergeMe const &src);
    PmergeMe &operator=(PmergeMe const &rhs);
    ~PmergeMe(){};

private:
    std::vector<int> vec_;
    std::deque<int>  deq_;
    struct pair
    {
        std::vector<int> beta;
        int alpha; 
    };
    
    void sortVector();
};
#endif
