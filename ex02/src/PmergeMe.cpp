#include <iostream>
#include <sstream>
#include <cstdlib>
#include <exception>
#include <string>
#include <ctime>
#include "PmergeMe.hpp"

PmergeMe::PmergeMe(PmergeMe const &src)
{
    this->operator=(src);
}
PmergeMe & PmergeMe::operator=(PmergeMe const &rhs)
{
    if (this != &rhs)
    {
        this->vec_ = rhs.vec_;
        this->deq_ = rhs.deq_;
    }
    return *this;
}

static PmergeMe::pair mkPair(int a, int b)
{
    PmergeMe::pair newPair;

    if (a > b)
    {
        newPair.alpha = a;
        newPair.beta.push_back(b);
    }
    else
    {
        newPair.alpha = b;
        newPair.beta.push_back(a);
    }
    return newPair;
}

void PmergeMe::sortVector()
{
    if (vec_.size() < 2) return ;

    bool    hasLaggard = false;
    int     laggard_ = 0;
    if (vec_.size() % 2 != 0)
    {
        hasLaggard = true;
        laggard = vec_.back();
        vec_.pop_back();
    }

    std::vector <PmergeMe::pair> chain;
    for (size_t i = 0; i < vec_.size(); i+=2)
    {
        chain.push_back(mkPair(vec_.at(i), vec_.at(i + 1)));
    }

    std::vector<int> mainChain;
    std::vector<int> pend;
    for (size_t i = 0; i < chain.size(); ++i)
    {
        mainChain.push_back(chain[i].alpha);
        pend.push_back(chain[i].beta[0]);
    }

}




