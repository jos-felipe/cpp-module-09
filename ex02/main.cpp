/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:00:15 by josfelip          #+#    #+#             */
/*   Updated: 2025/03/13 13:59:15 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    // Check if there are command line arguments
    if (argc < 2)
    {
        std::cerr << "Error: No arguments provided." << std::endl;
        std::cerr << "Usage: " << argv[0] << " [positive integers]" 
                  << std::endl;
        return 1;
    }

    PmergeMe sorter;
    
    // Parse the input arguments
    if (!sorter.parseInput(argc, argv))
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    // Sort and measure time
    sorter.sortAndMeasure();

    return 0;
}