/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:30:10 by josfelip          #+#    #+#             */
/*   Updated: 2025/03/17 19:42:00 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <vector>
# include <deque>
# include <ctime>
# include <cstdlib>
# include <string>
# include <sstream>
# include <algorithm>
# include <iomanip>
# include <utility>  // For std::pair

class PmergeMe
{
private:
    std::vector<int> _vecNumbers;
    std::deque<int> _deqNumbers;
    
    // Ford-Johnson algorithm for each container
    void sortVector();
    void sortDeque();

public:
    PmergeMe();
    PmergeMe(const PmergeMe& src);
    ~PmergeMe();
    PmergeMe& operator=(const PmergeMe& rhs);
    
    // Parse and validate input
    bool parseInput(int argc, char **argv);
    
    // Sort using both containers and measure time
    void sortAndMeasure();
    
    // Display results
    void displayResults(double vecTime, double deqTime) const;
    
    // Getter methods
    const std::vector<int>& getVecNumbers() const;
    const std::deque<int>& getDeqNumbers() const;
};

#endif