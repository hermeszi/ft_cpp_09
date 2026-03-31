/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:53:29 by myuen             #+#    #+#             */
/*   Updated: 2026/03/31 19:01:19 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <exception>
#include "RPN.hpp"

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << " Format:\t";
        std::cerr << "./RPN \"inverted Polish mathematical expression\"\n";
        std::cerr << "Example:\t";
        std::cerr << "./RPN \"8 9 * 9 - 9 - 9 - 4 - 1 +\"\n";
        return 1;
    }

    try
    {
        RPN rpn; 
        std::stringstream ss(argv[1]);
        std::string token;
        while (ss >> token)
            rpn.processInput(token);
        std::cout << rpn.getResult() << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}

/*
The following pairs of arithmetic expressions are equivalent:
Normal (infix)    	            Reverse Polish (postfix) 
(4 + 8) / (1 + 3) 	            4  8  +  1  3  +  /
28 / (6 + 2 * 4) 	            28  6  2  4  *  +  /
(4 + 2 * 5) / (1 + 3 * 2) 	    4  2  5  *  +  1  3  2  *  +  /

Example evaluation

4  2  5  *  +  1  3  2  *  +  /

becomes…

4  10  +  1  3  2  *  +  /

then

4  10  +  1  3  2  *  +  /

becomes…

14  1  3  2  *  +  /

then

14  1  3  2  *  +  /

becomes…

14  1  6  +  /

then

14  1  6  +  /

becomes…

14  7  /

then

14  7  /

becomes

2
*/
