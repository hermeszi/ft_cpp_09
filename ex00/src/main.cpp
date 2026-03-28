/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:53:29 by myuen             #+#    #+#             */
/*   Updated: 2026/03/28 16:27:36 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include "BitcoinExchange.hpp"

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Error: could not open file.\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open())
    {
        std::cerr << "Error: could not open file.\n";
        return 1;
    }
    file.close();
    try
    {
        BitcoinExchange btc("../data.csv");
        btc.processInput(argv[1]);        
        
        // std::map<std::string, float>::const_iterator it;
        // for (it = btc.getDb().begin(); it != btc.getDb().end(); ++it)
        // {
        //     std::cout << it->first << " | " << it->second << std::endl;
        // }

    }
    catch (std::exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}
