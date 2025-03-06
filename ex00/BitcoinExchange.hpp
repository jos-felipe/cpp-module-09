/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:45:58 by josfelip          #+#    #+#             */
/*   Updated: 2025/03/06 12:46:00 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <fstream>
# include <string>
# include <map>
# include <cstdlib>
# include <sstream>

class BitcoinExchange
{
private:
	std::map<std::string, float> _database;

	bool	isValidDate(const std::string &date) const;
	bool	isValidValue(const std::string &value, float &val) const;
	float	getExchangeRate(const std::string &date) const;

public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &src);
	~BitcoinExchange();
	BitcoinExchange &operator=(const BitcoinExchange &rhs);

	void	loadDatabase(const std::string &filename);
	void	processInput(const std::string &filename);
};

#endif