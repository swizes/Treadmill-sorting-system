/*
 * Logger.cpp
 *
 *  Created on: 17.06.2015
 *      Author: abq793
 */

#include "Logger.h"

#include "FileHelper.h"

using namespace std;

static const string debug_log_filename = "debug.log";
std::ofstream debug_fs;

Logger::Logger() {
	string filepath = DEFAULT_LOG_PATH + debug_log_filename;
	debug_fs.open (filepath.c_str());

	// Write the first lines
	if (debug_fs.is_open()) {
		debug_fs << "SE2 WA LOG " << std::endl;
		debug_fs << "Log file created" << std::endl << std::endl;
	}

}

Logger::~Logger() {
	if (debug_fs.is_open()) {
		debug_fs.close();
	}
}

// Overload << operator using log type
Logger &operator << (Logger &logger, const LOGLEVEL level) {

	switch (level) {
		case DEBUG:
			logger.debug_fs << "[DEBUG]: ";
			break;

		default:
			logger.debug_fs << "[INFO]: ";
			break;
	}


	return logger;

}

Logger &operator << (Logger &logger, const char *text) {
	logger.debug_fs << text << std::endl;
	return logger;
}

//Logger::Logger (const FileLogger &) = delete;
//Logger::Logger &operator= (const FileLogger &) = delete;
