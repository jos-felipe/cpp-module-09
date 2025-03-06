/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:50:11 by josfelip          #+#    #+#             */
/*   Updated: 2025/03/06 19:12:23 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src)
{
	*this = src;
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &rhs)
{
	if (this != &rhs)
	{
		_database = rhs._database;
	}
	return (*this);
}

void BitcoinExchange::loadDatabase(const std::string &filename)
{
	size_t	delimiterPos;
		float rate;
		char remaining;

	std::ifstream file(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open database file." << std::endl;
		return ;
	}
	std::string line;
	std::getline(file, line); // Skip header line
	while (std::getline(file, line))
	{
		delimiterPos = line.find(",");
		if (delimiterPos == std::string::npos)
			continue ;
		std::string date = line.substr(0, delimiterPos);
		std::string rateStr = line.substr(delimiterPos + 1);
		std::istringstream iss(rateStr);
		if (!(iss >> rate))
		{
			std::cerr << "Warning: invalid rate in database: " << rateStr << std::endl;
			continue ;
		}
		if (iss >> remaining)
		{
			std::cerr << "Warning: unexpected characters in rate: " << rateStr << std::endl;
			continue ;
		}
		_database[date] = rate;
	}
	file.close();
}

bool BitcoinExchange::isValidDate(const std::string &date) const
{
	// Check format: YYYY-MM-DD
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return (false);

	// Check digits
	for (int i = 0; i < 10; i++)
	{
		if (i == 4 || i == 7)
			continue ;
		if (!std::isdigit(date[i]))
			return (false);
	}

	// Extract year, month, day
	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());

	// Validate ranges
	if (month < 1 || month > 12)
		return (false);

	int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	// Leap year check
	if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
		daysInMonth[2] = 29;

	if (day < 1 || day > daysInMonth[month])
		return (false);

	return (true);
}

bool BitcoinExchange::isValidValue(const std::string &value, float &val) const
{
	std::istringstream iss(value);

	if (!(iss >> val))
		return (false);

	char remaining;
	if (iss >> remaining)
		return (false);

	if (val < 0)
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return (false);
	}

	if (val > 1000)
	{
		std::cerr << "Error: too large a number." << std::endl;
		return (false);
	}

	return (true);
}

float BitcoinExchange::getExchangeRate(const std::string &date) const
{
	// If the database is empty, return 0
	if (_database.empty())
		return (0.0f);

	// Find closest date (lower_bound gives first element >= date)
	std::map<std::string,
		float>::const_iterator it = _database.lower_bound(date);

	// Exact match
	if (it != _database.end() && it->first == date)
		return (it->second);

	// Date is before earliest date in database
	if (it == _database.begin())
		return (0.0f);

	// No exact match, use previous date (closest lower date)
	--it;
	return (it->second);
}

void	BitcoinExchange::processInput(const std::string &filename)
{
	std::ifstream file(filename.c_str());
	
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}

	std::string line;
	std::getline(file, line); // Skip header line if present
	
	while (std::getline(file, line))
	{
		// Skip empty lines
		if (line.empty())
			continue;

		size_t delimiterPos = line.find(" | ");
		if (delimiterPos == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		std::string date = line.substr(0, delimiterPos);
		std::string valueStr = line.substr(delimiterPos + 3);
		float value;
		
		if (!isValidDate(date))
		{
			std::cerr << "Error: bad input => " << date << std::endl;
			continue;
		}

		if (!isValidValue(valueStr, value))
			continue;

		float rate = getExchangeRate(date);
		float result = value * rate;

		std::cout << date << " => " << value << " = " << result << std::endl;
	}

	file.close();
}
