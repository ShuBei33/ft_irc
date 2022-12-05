/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 05:03:51 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/05 16:18:11 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Logger.hpp"
#include "colours.h"
#include <iostream>
#include <iomanip>

struct LogContext
{
	std::string name;
	std::string color;
	std::ostream& stream;
};

static std::string __now()
{
	char buffer[10];
	time_t timestamp;
	tm* timeinfo;
	size_t res;

	time(&timestamp);
	timeinfo = localtime(&timestamp);
	res = strftime(buffer, sizeof (buffer), "%H:%M:%S", timeinfo);
	return std::string(buffer, res);
}

Logger::Logger(LogLevel level)
{
	this->_level = level;
}

Logger::~Logger()
{}

void Logger::log(LogLevel level, std::string const& message)
{
	static LogContext __CONTEXTS[] = {
		{"DEBUG", GREEN, std::cout},
		{"INFO", WHITE, std::cout},
		{"NOTICE", CYAN, std::cout},
		{"WARNING", YELLOW, std::cerr},
		{"ERROR", H_RED, std::cerr},
		{"FATAL", RED, std::cerr},
	};

	// TODO find out why valgrind reports uninitialized memory for this->_level
	if (level < DEBUG)
		return;

	LogContext& ctx = __CONTEXTS[level];

	ctx.stream
		<< "[" << __now() << "] "
		<< ctx.color << std::left << std::setw(7) << ctx.name << END << " | "
		<< message << '\n';
	;
}
