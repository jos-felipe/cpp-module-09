/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:45:22 by josfelip          #+#    #+#             */
/*   Updated: 2025/03/17 19:41:15 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe& src)
{
    *this = src;
}

PmergeMe::~PmergeMe()
{
}

PmergeMe& PmergeMe::operator=(const PmergeMe& rhs)
{
    if (this != &rhs)
    {
        _vecNumbers = rhs._vecNumbers;
        _deqNumbers = rhs._deqNumbers;
    }
    return (*this);
}

bool PmergeMe::parseInput(int argc, char **argv)
{
    if (argc < 2)
        return false;

    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];
        std::istringstream iss(arg);
        int num;
        char remaining;

        // Check if argument is a valid positive integer
        if (!(iss >> num) || num < 0 || iss >> remaining)
            return false;

        _vecNumbers.push_back(num);
        _deqNumbers.push_back(num);
    }
    return true;
}

// Ford-Johnson algorithm for vector
void PmergeMe::sortVector()
{
    // Step 1: Handle edge cases
    if (_vecNumbers.size() <= 1)
        return;

    // Step 2: Keep track of any odd element
    int oddElement = -1;
    bool hasOddElement = false;
    
    if (_vecNumbers.size() % 2 != 0)
    {
        hasOddElement = true;
        oddElement = _vecNumbers.back();
        _vecNumbers.pop_back();
    }

    // Step 3: Create pairs of elements
    std::vector<std::pair<int, int> > pairs;
    for (size_t i = 0; i < _vecNumbers.size(); i += 2)
    {
        // Sort each pair internally (smaller first, larger second)
        if (_vecNumbers[i] > _vecNumbers[i + 1])
            pairs.push_back(std::make_pair(_vecNumbers[i + 1], _vecNumbers[i]));
        else
            pairs.push_back(std::make_pair(_vecNumbers[i], _vecNumbers[i + 1]));
    }

    // Step 4: Sort pairs by their larger elements (second element)
    for (size_t i = 0; i < pairs.size(); i++)
    {
        for (size_t j = 0; j < pairs.size() - i - 1; j++)
        {
            if (pairs[j].second > pairs[j + 1].second)
            {
                std::pair<int, int> temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
            }
        }
    }

    // Step 5: Create main chain with larger elements
    std::vector<int> result;
    for (size_t i = 0; i < pairs.size(); i++)
    {
        result.push_back(pairs[i].second);
    }

    // Step 6: Insert smaller elements 
    // Start with the first pair's smaller element
    result.insert(result.begin(), pairs[0].first);
    
    // Insert remaining smaller elements using binary search
    for (size_t i = 1; i < pairs.size(); i++)
    {
        int value = pairs[i].first;
        int low = 0;
        int high = i;
        
        // Binary search to find insertion position
        while (low < high)
        {
            int mid = low + (high - low) / 2;
            if (result[mid] < value)
                low = mid + 1;
            else
                high = mid;
        }
        
        result.insert(result.begin() + low, value);
    }
    
    // Step 7: Handle the odd element if it exists
    if (hasOddElement)
    {
        int low = 0;
        int high = result.size();
        
        // Binary search to find insertion position for odd element
        while (low < high)
        {
            int mid = low + (high - low) / 2;
            if (result[mid] < oddElement)
                low = mid + 1;
            else
                high = mid;
        }
        
        result.insert(result.begin() + low, oddElement);
    }
    
    // Update the original vector
    _vecNumbers = result;
}

// Ford-Johnson algorithm for deque
void PmergeMe::sortDeque()
{
    // Step 1: Handle edge cases
    if (_deqNumbers.size() <= 1)
        return;

    // Step 2: Keep track of any odd element
    int oddElement = -1;
    bool hasOddElement = false;
    
    if (_deqNumbers.size() % 2 != 0)
    {
        hasOddElement = true;
        oddElement = _deqNumbers.back();
        _deqNumbers.pop_back();
    }

    // Step 3: Create pairs of elements
    std::deque<std::pair<int, int> > pairs;
    for (size_t i = 0; i < _deqNumbers.size(); i += 2)
    {
        // Sort each pair internally (smaller first, larger second)
        if (_deqNumbers[i] > _deqNumbers[i + 1])
            pairs.push_back(std::make_pair(_deqNumbers[i + 1], _deqNumbers[i]));
        else
            pairs.push_back(std::make_pair(_deqNumbers[i], _deqNumbers[i + 1]));
    }

    // Step 4: Sort pairs by their larger elements (second element)
    for (size_t i = 0; i < pairs.size(); i++)
    {
        for (size_t j = 0; j < pairs.size() - i - 1; j++)
        {
            if (pairs[j].second > pairs[j + 1].second)
            {
                std::pair<int, int> temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
            }
        }
    }

    // Step 5: Create main chain with larger elements
    std::deque<int> result;
    for (size_t i = 0; i < pairs.size(); i++)
    {
        result.push_back(pairs[i].second);
    }

    // Step 6: Insert smaller elements 
    // Start with the first pair's smaller element
    result.push_front(pairs[0].first);
    
    // Insert remaining smaller elements using binary search
    for (size_t i = 1; i < pairs.size(); i++)
    {
        int value = pairs[i].first;
        int low = 0;
        int high = i;
        
        // Binary search to find insertion position
        while (low < high)
        {
            int mid = low + (high - low) / 2;
            if (result[mid] < value)
                low = mid + 1;
            else
                high = mid;
        }
        
        result.insert(result.begin() + low, value);
    }
    
    // Step 7: Handle the odd element if it exists
    if (hasOddElement)
    {
        int low = 0;
        int high = result.size();
        
        // Binary search to find insertion position for odd element
        while (low < high)
        {
            int mid = low + (high - low) / 2;
            if (result[mid] < oddElement)
                low = mid + 1;
            else
                high = mid;
        }
        
        result.insert(result.begin() + low, oddElement);
    }
    
    // Update the original deque
    _deqNumbers = result;
}

void PmergeMe::sortAndMeasure()
{
    clock_t start, end;
    double vecTime, deqTime;

    // Display the unsorted sequence
    std::cout << "Before: ";
    for (size_t i = 0; i < _vecNumbers.size(); i++)
    {
        std::cout << _vecNumbers[i];
        if (i < _vecNumbers.size() - 1)
            std::cout << " ";
    }
    std::cout << std::endl;

    // Sort with vector and measure time
    start = clock();
    sortVector();
    end = clock();
    vecTime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;

    // Sort with deque and measure time
    start = clock();
    sortDeque();
    end = clock();
    deqTime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;

    // Display the sorted sequence
    std::cout << "After: ";
    for (size_t i = 0; i < _vecNumbers.size(); i++)
    {
        std::cout << _vecNumbers[i];
        if (i < _vecNumbers.size() - 1)
            std::cout << " ";
    }
    std::cout << std::endl;

    // Display timing information
    displayResults(vecTime, deqTime);
}

void PmergeMe::displayResults(double vecTime, double deqTime) const
{
    std::cout << "Time to process a range of " << _vecNumbers.size() 
              << " elements with std::vector : " << std::fixed 
              << std::setprecision(5) << vecTime << " us" << std::endl;
    
    std::cout << "Time to process a range of " << _deqNumbers.size() 
              << " elements with std::deque : " << std::fixed 
              << std::setprecision(5) << deqTime << " us" << std::endl;
}

const std::vector<int>& PmergeMe::getVecNumbers() const
{
    return _vecNumbers;
}

const std::deque<int>& PmergeMe::getDeqNumbers() const
{
    return _deqNumbers;
}