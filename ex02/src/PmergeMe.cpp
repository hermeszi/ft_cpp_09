#include <iostream>
#include <sstream>
#include <cstdlib>
#include <exception>
#include <string>
#include <ctime>
#include <iomanip>
#include "PmergeMe.hpp"
#define MILLION 1000000

const std::vector<int>& PmergeMe::getSortV() const { return sortV; }
const std::deque<int>& PmergeMe::getSortD() const { return sortD; }
PmergeMe::PmergeMe(PmergeMe const &src){ this->operator=(src); }
PmergeMe & PmergeMe::operator=(PmergeMe const &rhs)
{
    if (this != &rhs)
    {
        this->sortV = rhs.sortV;
        this->sortD = rhs.sortD;
        this->input = rhs.input;
    }
    return *this;
}

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
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::deque<T>& d)
{
    os << "[";
    for (size_t i = 0; i < d.size(); ++i)
    {                                           
        os << d[i] << (i != d.size() - 1 ? ", " : "");
    }
    return os << "]";
}

int PmergeMe::run ()
{
    try
    {
        size_t size = input.size();
        if (size == 0)
        {
            std::cerr << "Error: No input provided" << std::endl;
            return 1;
        }

        std::cout << "Before :" << input << std::endl;
        
        clock_t startV = clock();
        this->sortVector();
        clock_t endV = clock();
        std::cout << "After (vector): " << sortV << std::endl;

        clock_t startD = clock();
        this->sortDeque(); 
        clock_t endD = clock();
        std::cout << "After (deque) : " << sortD << std::endl;

        double timeV = (static_cast<double>(endV - startV) / CLOCKS_PER_SEC) * MILLION;
        double timeD = (static_cast<double>(endD - startD) / CLOCKS_PER_SEC) * MILLION;

        std::cout  << "Time to process a range of " << size << " elements with std::vector : " 
                   << std::fixed << timeV << " us" << std::endl;
        std::cout  << "Time to process a range of " << size << " elements with std::deque  : " 
                   << std::fixed << timeD << " us" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
     }

    return 0;
}

PmergeMe::pair PmergeMe::mkPair(int a, int b)
{
    PmergeMe::pair newPair;

    if (a > b)
    {
        newPair.alpha = a;
        newPair.beta = b;
    }
    else
    {
        newPair.alpha = b;
        newPair.beta = a;
    }
    return newPair;
}

static std::vector<size_t> generateJacobsthal(size_t n)
{
    std::vector<size_t> chain;
    if (n == 0)
    {
        chain.push_back(0);
        chain.push_back(1);
    }
    else
    {
        chain = generateJacobsthal(n - 1);
        //J(n) = J(n-1) + 2 * J(n-2)
        chain.push_back(chain[chain.size() - 1] + (2 * chain[chain.size() - 2]));
    }
    return chain;
}

std::vector<int> PmergeMe::insertOrder(size_t n)
{
    std::vector<size_t> jacobsthal = generateJacobsthal(n);
    std::cout << "Jacobsthal sequence: " << jacobsthal << std::endl;
    std::vector<int> order;
    order.push_back(0); // start with 0, which is the first element of the pend list

    for (size_t i = 2; i < jacobsthal.size(); ++i)
    {
        size_t temp = jacobsthal[i];
        order.push_back(temp);
        if (jacobsthal[i] > n)
            break;
        if (temp > 0 && temp > jacobsthal[i - 1])
            order.push_back(jacobsthal[i] - 1);
    }
    return order;
}

template <typename Container>
Container PmergeMe::FJSort(std::vector<PmergeMe::pair> &receivedPairs)
{
    Container mainChain;

    // 1. base case: one pair
    if (receivedPairs.size() == 1)
    {   
        mainChain.push_back(receivedPairs.at(0).beta);
        mainChain.push_back(receivedPairs.at(0).alpha);
        return mainChain;
    }

    // 2. check if odd number of pairs -> save last pair as remaining to insert later
    PmergeMe::pair laggard;
    bool hasLaggard = false;
    if (receivedPairs.size() % 2 != 0)
    {   hasLaggard = true;
        laggard = receivedPairs.back();
        receivedPairs.pop_back();
    }

    // 3. form new pairs from alphas of current pairs
    std::vector<PmergeMe::pair> newPairs;
    for (size_t i = 0; i < receivedPairs.size(); i+=2)
    {        
        newPairs.push_back(mkPair(receivedPairs.at(i).alpha, receivedPairs.at(i + 1).alpha));
    }

    // 4. recurse: FJSort(new pairs)
    mainChain = FJSort <Container>(newPairs);

    // 5. insert remaining pend elements into mainChain using binary search
    while (!receivedPairs.empty())
    {   
        std::cout << "testing insertion order:" << this->insertOrder(receivedPairs.size()) << std::endl;
        PmergeMe::pair currentPair = receivedPairs.front();
        receivedPairs.erase(receivedPairs.begin());
        typename Container::iterator upperBound = std::lower_bound(mainChain.begin(), mainChain.end(), currentPair.alpha);
        typename Container::iterator pos = std::lower_bound(mainChain.begin(), upperBound, currentPair.beta);
        mainChain.insert(pos, currentPair.beta);
    }

    // 6. if remaining exists (from the starting pairing), insert it into mainChain using binary search
    if (hasLaggard)
    {   
        typename Container::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), laggard.alpha);
        mainChain.insert(pos, laggard.alpha);
        typename Container::iterator upperBound = std::lower_bound(mainChain.begin(), mainChain.end(), laggard.alpha);
        pos = std::lower_bound(mainChain.begin(), upperBound, laggard.beta);
        mainChain.insert(pos, laggard.beta);
    }

    return mainChain;
}

void PmergeMe::sortVector()
{
    if (input.size() < 2)
    {
        sortV = input;
        return ;
    }

    bool        hasLaggard = false;
    int         laggard = 0;
    
    if (input.size() % 2 != 0)
    {
        hasLaggard = true;
        laggard = input.back();
        input.pop_back();
    }
    
    std::vector <PmergeMe::pair> vChain;
    for (size_t i = 0; i < input.size(); i+=2)
    {
        vChain.push_back(mkPair(input.at(i), input.at(i + 1)));
    }

    sortV = FJSort<std::vector<int> >(vChain);
    if (hasLaggard and !sortV.empty())
    {
        // insert laggard into sortV using binary search
        std::vector<int>::iterator pos = std::lower_bound(sortV.begin(), sortV.end(), laggard);
        sortV.insert(pos, laggard);
    }   
}

void PmergeMe::sortDeque()
{
    if (input.size() < 2)
    {
        sortD.assign(input.begin(), input.end());
        return ;
    }

    bool        hasLaggard = false;
    int         laggard = 0;
    
    if (input.size() % 2 != 0)
    {
        hasLaggard = true;
        laggard = input.back();
        input.pop_back();
    }
    
    std::vector <PmergeMe::pair> vChain;
    for (size_t i = 0; i < input.size(); i+=2)
    {
        vChain.push_back(mkPair(input.at(i), input.at(i + 1)));
    }

    sortD = FJSort<std::deque<int> >(vChain);
    if (hasLaggard and !sortD.empty())
    {
        // insert laggard into sortD using binary search
        std::deque<int>::iterator pos = std::lower_bound(sortD.begin(), sortD.end(), laggard);
        sortD.insert(pos, laggard);
    }   
}

/*=================================================================================================*/
// Previous implementation of FJSort, before template refactor. Kept for reference, but not used in final code.

// std::vector<int> PmergeMe::FJSort(std::vector<PmergeMe::pair> &receivedPairs)
// {
//     std::vector<int> mainChain;

//     // 1. base case: one pair → return [small, large]
//     if (receivedPairs.size() == 1)
//     {   
//         mainChain.push_back(receivedPairs.at(0).beta);
//         mainChain.push_back(receivedPairs.at(0).alpha);
//         return mainChain;
//     }

//     // 2. check if odd number of pairs → save last pair as remaining straggler (goes to pend later)
//     PmergeMe::pair laggard;
//     bool hasLaggard = false;
//     if (receivedPairs.size() % 2 != 0)
//     {
//         hasLaggard = true;
//         laggard = receivedPairs.back();
//         receivedPairs.pop_back();
//     }

//     // 3. form new pairs from alphas of current pairs
//     //    pair[0].large with pair[1].large, pair[2].large with pair[3].large, etc.

//     std::vector<PmergeMe::pair> newPairs;
//     for (size_t i = 0; i < receivedPairs.size(); i+=2)
//     {
//         newPairs.push_back(mkPair(receivedPairs.at(i).alpha, receivedPairs.at(i + 1).alpha));
//     }
    
//     // 4. recurse: FJSort(new pairs) → returns sorted mainChain
//     mainChain = FJSort(newPairs);

//     // use receivedPairs vector as pend list, since it has both beta and alpha values
//     // insert pend[0] at front of mainChain (free, no comparison needed)? deleted, saving is too small to implement

    
//     // 5. insert remaining pend elements into mainChain using binary search
//     //    upper bound for each search = position of its partnerValue in mainChain
//     //    no Jacobthal sequence yet, just insert in order of pend list

//     // Given: mainChain = [5, 7, 9], insert beta=3, partnerAlpha=9
//     //     Step i: find partner position
//     //         upperBound = lower_bound(mainChain.begin(), mainChain.end(), 9)
//     //         → points to 9

//     //     Step ii: binary search only up to upperBound
//     //         pos = lower_bound(mainChain.begin(), upperBound, 3)
//     //         → points to 5 (first element >= 3)

//     //     Step iii: insert
//     //         mainChain.insert(pos, 3)
//     //         → [3, 5, 7, 9]
//     while (!receivedPairs.empty()) // this is ok to start at the back, will put in Jacobthal order later
//     {
//         PmergeMe::pair currentPair = receivedPairs.front();
//         receivedPairs.erase(receivedPairs.begin());

//         std::vector<int>::iterator upperBound = std::lower_bound(mainChain.begin(), mainChain.end(), currentPair.alpha);//doesn't this cost a lot? but i'm ok with the spirit of it
//         std::vector<int>::iterator pos = std::lower_bound(mainChain.begin(), upperBound, currentPair.beta);
//         mainChain.insert(pos, currentPair.beta);
//     }

//     // 6. if straggler exists, insert it into mainChain using binary search
//     if (hasLaggard)
//     {
//         std::vector<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), laggard.alpha);
//         mainChain.insert(pos, laggard.alpha);
        
//         std::vector<int>::iterator upperBound = std::lower_bound(mainChain.begin(), mainChain.end(), laggard.alpha);
//         pos = std::lower_bound(mainChain.begin(), upperBound, laggard.beta);
//         mainChain.insert(pos, laggard.beta);
//     }

//     // 7. return mainChain
//     return mainChain;
// }