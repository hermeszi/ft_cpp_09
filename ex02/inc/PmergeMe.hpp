#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <iostream>
class PmergeMe
{
public:
    PmergeMe() : input(), sortV(), sortD(){}
    PmergeMe(const std::vector<int>& input) : input(input), sortV(), sortD() {}
    PmergeMe(PmergeMe const &src);
    PmergeMe &operator=(PmergeMe const &rhs);
    ~PmergeMe(){};

    int run ();
    const std::vector<int>& getSortV() const;
    const std::deque<int>& getSortD() const;
private:
    std::vector<int> input;
    std::vector<int> sortV;
    std::deque<int>  sortD;
    struct pair
    {
        int alpha;
        int beta;
    };
    std::vector<int> FJSort(std::vector<PmergeMe::pair> &pairs);
    PmergeMe::pair mkPair(int a, int b);
    void sortVector();
};
#endif
