/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:53:29 by myuen             #+#    #+#             */
/*   Updated: 2026/03/30 17:29:58 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
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

    std::string input(argv[1]);

    return 0;
}
