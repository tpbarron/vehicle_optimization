/*
 * Logger.cpp
 *
 *  Created on: Jan 1, 2015
 *      Author: trevor
 */

#include <utils/Logger.h>

#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>

namespace Logger {


void init() {
	boost::log::add_file_log("logs/vehicle.log");
	boost::log::add_console_log();
    boost::log::add_common_attributes();
}

void debug(std::string text) {
	BOOST_LOG_TRIVIAL(debug) << text;
}

void error(std::string text) {
	BOOST_LOG_TRIVIAL(error) << text;
}

void fatal(std::string text) {
	BOOST_LOG_TRIVIAL(fatal) << text;
}

void info(std::string text) {
	BOOST_LOG_TRIVIAL(info) << text;
}

void trace(std::string text) {
	BOOST_LOG_TRIVIAL(trace) << text;
}

void warning(std::string text) {
	BOOST_LOG_TRIVIAL(warning) << text;
}


}
