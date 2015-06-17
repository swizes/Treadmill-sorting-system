/*
 * Logger.h
 *
 *  Created on: 17.06.2015
 *      Author: abq793
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <fstream>

enum LOGLEVEL { INFO, DEBUG, WARN, ERROR };

class Logger {
public:
	Logger();
	virtual ~Logger();

	std::ofstream debug_fs;

	friend Logger &operator << (Logger &logger, const char *text);
	friend Logger &operator << (Logger &logger, const LOGLEVEL level);

};






#endif /* LOGGER_H_ */
