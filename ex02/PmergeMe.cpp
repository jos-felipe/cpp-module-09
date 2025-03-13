/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:45:22 by josfelip          #+#    #+#             */
/*   Updated: 2025/03/13 14:03:36 by josfelip         ###   ########.fr       */
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

        // Check if argument is a valid positive integer
        char remaining;
        if (!(iss >> num) || num < 0 || iss >> remaining)
            return false;

        _vecNumbers.push_back(num);
        _deqNumbers.push_back(num);
    }
    return true;
}

// Ford-Johnson algorithm for vector
void PmergeMe::mergeSortVector(std::vector<int>& arr)
{
    if (arr.size() <= 1)
        return;

    mergeInsertVector(arr, 0, arr.size() - 1);
}

void PmergeMe::mergeInsertVector(std::vector<int>& arr, int left, int right)
{
    // Base case: single element
    if (left >= right)
        return;

    // For small arrays, use insertion sort
    if (right - left <= 16)
    {
        for (int i = left + 1; i <= right; i++)
        {
            int key = arr[i];
            int j = i - 1;
            while (j >= left && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
        return;
    }

    // Recursive case: divide and conquer
    int mid = left + (right - left) / 2;
    mergeInsertVector(arr, left, mid);
    mergeInsertVector(arr, mid + 1, right);

    // Merge the sorted halves
    std::vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= mid)
        temp[k++] = arr[i++];

    while (j <= right)
        temp[k++] = arr[j++];

    for (i = 0; i < k; i++)
        arr[left + i] = temp[i];
}

void PmergeMe::insertVector(std::vector<int>& arr, int value, int start, 
                           int end)
{
    int mid;

    while (start <= end)
    {
        mid = start + (end - start) / 2;
        if (arr[mid] == value)
            return;
        if (arr[mid] < value)
            start = mid + 1;
        else
            end = mid - 1;
    }

    // Insert the value at the correct position
    arr.insert(arr.begin() + start, value);
}

// Ford-Johnson algorithm for deque
void PmergeMe::mergeSortDeque(std::deque<int>& arr)
{
    if (arr.size() <= 1)
        return;

    mergeInsertDeque(arr, 0, arr.size() - 1);
}

void PmergeMe::mergeInsertDeque(std::deque<int>& arr, int left, int right)
{
    // Base case: single element
    if (left >= right)
        return;

    // For small arrays, use insertion sort
    if (right - left <= 16)
    {
        for (int i = left + 1; i <= right; i++)
        {
            int key = arr[i];
            int j = i - 1;
            while (j >= left && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
        return;
    }

    // Recursive case: divide and conquer
    int mid = left + (right - left) / 2;
    mergeInsertDeque(arr, left, mid);
    mergeInsertDeque(arr, mid + 1, right);

    // Merge the sorted halves
    std::deque<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= mid)
        temp[k++] = arr[i++];

    while (j <= right)
        temp[k++] = arr[j++];

    for (i = 0; i < k; i++)
        arr[left + i] = temp[i];
}

void PmergeMe::insertDeque(std::deque<int>& arr, int value, int start, 
                          int end)
{
    int mid;

    while (start <= end)
    {
        mid = start + (end - start) / 2;
        if (arr[mid] == value)
            return;
        if (arr[mid] < value)
            start = mid + 1;
        else
            end = mid - 1;
    }

    // Insert the value at the correct position
    arr.insert(arr.begin() + start, value);
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
    mergeSortVector(_vecNumbers);
    end = clock();
    vecTime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;

    // Sort with deque and measure time
    start = clock();
    mergeSortDeque(_deqNumbers);
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