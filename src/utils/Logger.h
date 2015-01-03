/*
 * Logger.h
 *
 *  Created on: Jan 1, 2015
 *      Author: trevor
 */

#ifndef SRC_UTILS_LOGGER_H_
#define SRC_UTILS_LOGGER_H_

#include <string>

namespace Logger {

void init();
void debug(std::string text);
void error(std::string text);
void fatal(std::string text);
void info(std::string text);
void trace(std::string text);
void warning(std::string text);

};

#endif /* SRC_UTILS_LOGGER_H_ */
