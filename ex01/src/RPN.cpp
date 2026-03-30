
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <exception>
#include <string>
#include "RPN.hpp"

static bool isOperator(const std::string& input)
{
    std::string ops[] = {"+", "-", "/", "*"};

    for (size_t i = 0; i < sizeof(ops) / sizeof(ops[0]); ++i)
    {
        if (input == ops[i])
            return true;
    }
    return false;
}

RPN::RPN(){}

RPN::RPN(RPN const &src)
{
    this->operator=(src);
}
RPN & RPN::operator=(RPN const &rhs)
{
    if (this != &rhs)
    {
        this->numStack = rhs.numStack;
    }
    return *this;
}

RPN::~RPN(){}

void RPN::processInput(std::string input)
{
    int num;

    if (std::stringstream(input) >> num)
    {
        this->numStack.push(num);
    }
    else if(isOperator(input))
    {
        this->performOp(input);
    }
    else
    {
        std::cerr << "Error: Invalid Input\n";
    }
}

void RPN::performOp(std::string input)
{
    (void)input;
}
