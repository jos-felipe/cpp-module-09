/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:30:10 by josfelip          #+#    #+#             */
/*   Updated: 2025/03/12 02:49:35 by josfelip         ###   ########.fr       */
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

class PmergeMe
{
private:
    std::vector<int> _vecNumbers;
    std::deque<int> _deqNumbers;
    
    // Helper methods for vector implementation
    void mergeSortVector(std::vector<int>& arr);
    void mergeInsertVector(std::vector<int>& arr, int left, int right);
    void insertVector(std::vector<int>& arr, int value, int start, int end);
    
    // Helper methods for deque implementation
    void mergeSortDeque(std::deque<int>& arr);
    void mergeInsertDeque(std::deque<int>& arr, int left, int right);
    void insertDeque(std::deque<int>& arr, int value, int start, int end);

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