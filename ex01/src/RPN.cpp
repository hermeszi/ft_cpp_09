#include <iostream>
#include <sstream>
#include <cstdlib>
#include <exception>
#include <string>
#include "RPN.hpp"

// static bool isOperator(const std::string& input)
// {
//     std::string ops[] = {"+", "-", "/", "*"};

//     for (size_t i = 0; i < sizeof(ops) / sizeof(ops[0]); ++i)
//     {
//         if (input == ops[i])
//             return true;
//     }
//     return false;
// }

bool isOperator(char c)
{
    std::string ops = "+-*/";
    return (ops.find(c) != std::string::npos);
}

RPN::RPN(): error(false){}

RPN::RPN(RPN const &src)
{
    this->operator=(src);
}
RPN & RPN::operator=(RPN const &rhs)
{
    if (this != &rhs)
    {
        this->numStack = rhs.numStack;
        this->error = rhs.error;
    }
    return *this;
}

RPN::~RPN(){}

void RPN::processInput(std::string input)
{
    if (this->error)
        return;

    int num;
    if (input.size() == 1 && std::isdigit(input.at(0)))
    {
        std::stringstream(input) >> num;
        this->numStack.push(num);
    }
    else if(isOperator(input.at(0)))
    {
        this->performOp(input);
    }
    else
    {
        //std::cerr << "Error: Invalid Input\n";
        this->error = true;
    }
}

void RPN::performOp(std::string input)
{
    int lVal;
    int rVal;
    int result;

    if (this->error)
        return ;

    if (numStack.size() < 2)
    {
        //std::cerr << "Error: Invalid Expression\n";
        this->error = true;
        return ;
    }

    rVal = numStack.top();
    numStack.pop();

    lVal = numStack.top();
    numStack.pop();

    switch (input.at(0))
    {
        case '+':
        {
            result = lVal + rVal;
            break;
        }
        case '-':
        {
            result = lVal - rVal;
            break;
        }
        case '*':
        {
            result = lVal * rVal;
            break;
        }
        case '/':
        {
            result = lVal / rVal;
            break;
        }
        default:
        {
            //std::cerr << "Error: Invalid Operator\n";
            this->error = true;
            return ;
        }
    }
    numStack.push(result);
}

int RPN::getResult() const
{
    if (this->error)
        throw std::runtime_error("Error");
    if (numStack.size() != 1)
        throw std::runtime_error("Error: mutated expression");
    return numStack.top();
}
