/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:20:11 by josfelip          #+#    #+#             */
/*   Updated: 2025/03/11 13:47:51 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <stack>
# include <string>
# include <sstream>
# include <cctype>
# include <stdexcept>

class RPN
{
private:
	std::stack<int> _stack;
	
	bool isOperator(char c) const;
	int performOperation(char op, int a, int b) const;

public:
	RPN();
	RPN(const RPN &src);
	~RPN();
	RPN &operator=(const RPN &rhs);

	int evaluate(const std::string &expression);
};

#endif
