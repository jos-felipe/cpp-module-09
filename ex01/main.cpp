/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:20:35 by josfelip          #+#    #+#             */
/*   Updated: 2025/03/11 14:29:13 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "Error: Usage: ./RPN \"expression\"" << std::endl;
		return 1;
	}

	RPN calculator;
	try
	{
		int result = calculator.evaluate(argv[1]);
		std::cout << result << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}