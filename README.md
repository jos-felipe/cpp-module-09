# C++ Module 09 - STL (Standard Template Library)

This module explores the usage of various STL containers in C++98, implementing practical programs that demonstrate their applications in different scenarios.

## Overview

The Standard Template Library (STL) is a powerful set of C++ template classes that provide general-purpose classes and functions with templates that implement many popular and commonly used algorithms and data structures. This module focuses on:

- Understanding different STL containers and their specific use cases
- Implementing algorithms that leverage container properties
- Learning the strengths and weaknesses of each container type
- Measuring performance differences between containers

## Exercises

### Exercise 00: Bitcoin Exchange

A program that computes the value of a certain amount of bitcoin on a specific date using historical exchange rate data.

**Key Concepts:**
- Using `std::map` for efficient date-based lookups
- File parsing and data validation
- Error handling

**Usage:**
```
./btc input.txt
```

**Example Output:**
```
2011-01-03 => 3 = 0.9
2011-01-03 => 2 = 0.6
2011-01-03 => 1 = 0.3
2011-01-03 => 1.2 = 0.36
2011-01-09 => 1 = 0.32
Error: not a positive number.
Error: bad input => 2001-42-42
2012-01-11 => 1 = 7.1
Error: too large a number.
```

### Exercise 01: Reverse Polish Notation

A calculator that evaluates mathematical expressions written in Reverse Polish Notation (RPN).

**Key Concepts:**
- Using `std::stack` for expression evaluation
- Parsing and validating input
- Implementing a stack-based algorithm

**Usage:**
```
./RPN "expression"
```

**Example Output:**
```
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
42
```

### Exercise 02: PmergeMe

An implementation of the Ford-Johnson merge-insert sort algorithm using two different containers to compare their performance characteristics.

**Key Concepts:**
- Implementing merge-insert sort (Ford-Johnson algorithm)
- Using `std::vector` and `std::deque` containers
- Performance measurement and comparison
- Binary search for efficient insertion

**Usage:**
```
./PmergeMe [positive integers]
```

**Example Output:**
```
Before: 3 5 9 7 4
After: 3 4 5 7 9
Time to process a range of 5 elements with std::vector : 0.00031 us
Time to process a range of 5 elements with std::deque : 0.00014 us
```

## Module Rules

- All code must compile with c++ flags: `-Wall -Wextra -Werror -std=c++98`
- Each exercise requires the use of at least one different STL container
- Exercise 02 requires the use of two different containers
- Orthodox Canonical Form must be followed for class design
- Memory leaks should be avoided
- Each program must include a Makefile with the rules: `$(NAME)`, `all`, `clean`, `fclean`, and `re`

## Building and Running

Each exercise has its own Makefile. To build and run any exercise:

```bash
# Navigate to the exercise directory
cd ex00

# Compile
make

# Run
./btc input.txt  # For exercise 00
./RPN "1 2 + 3 *"  # For exercise 01
./PmergeMe 5 3 9 1 8  # For exercise 02
```

## Learning Resources

For a deeper understanding of STL containers:

- **Map**: Associative container that stores key-value pairs sorted by keys
- **Stack**: LIFO (Last-In-First-Out) data structure
- **Vector**: Dynamic array with the ability to resize itself
- **Deque**: Double-ended queue that allows fast insertion and deletion at both ends

## Author

- [José Felipe](https://github.com/jos-felipe)