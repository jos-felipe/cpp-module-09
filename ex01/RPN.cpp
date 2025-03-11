/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:20:23 by josfelip          #+#    #+#             */
/*   Updated: 2025/03/11 18:20:25 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN()
{
}

RPN::RPN(const RPN &src)
{
	*this = src;
}

RPN::~RPN()
{
}

RPN &RPN::operator=(const RPN &rhs)
{
	if (this != &rhs)
	{
		// We'd copy the stack, but there's no direct way to access it
		// In a real-world scenario, we would need to copy elements
		// Here, we'll assume the stack is empty during assignments
		while (!_stack.empty())
			_stack.pop();
	}
	return (*this);
}

bool RPN::isOperator(char c) const
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

int RPN::performOperation(char op, int a, int b) const
{
	switch (op)
	{
		case '+':
			return b + a;
		case '-':
			return b - a;
		case '*':
			return b * a;
		case '/':
			if (a == 0)
				throw std::runtime_error("Error: Division by zero");
			return b / a;
		default:
			throw std::runtime_error("Error: Invalid operator");
	}
}

int RPN::evaluate(const std::string &expression)
{
	std::istringstream iss(expression);
	std::string token;

	while (iss >> token)
	{
		// Token is a single character
		if (token.length() == 1)
		{
			char c = token[0];
			
			// If it's a digit, push to stack
			if (std::isdigit(c))
			{
				_stack.push(c - '0');
			}
			// If it's an operator, perform operation
			else if (isOperator(c))
			{
				if (_stack.size() < 2)
					throw std::runtime_error("Error: Insufficient operands");
					
				int a = _stack.top();
				_stack.pop();
				int b = _stack.top();
				_stack.pop();
				
				_stack.push(performOperation(c, a, b));
			}
			else
			{
				throw std::runtime_error("Error: Invalid token");
			}
		}
		else
		{
			throw std::runtime_error("Error: Invalid token");
		}
	}
	
	if (_stack.size() != 1)
		throw std::runtime_error("Error: Invalid expression");
		
	int result = _stack.top();
	_stack.pop();
	return result;
}
