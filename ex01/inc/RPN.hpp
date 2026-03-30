#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <iostream>

class RPN
{
    private:
        std::stack<int> numStack;
        bool error;

    public:
        RPN();
        RPN(RPN const &src);
        RPN &operator=(RPN const &rhs);
        ~RPN();

        void processInput(std::string input);
        void performOp(std::string input);

        int getResult() const;
};

#endif
