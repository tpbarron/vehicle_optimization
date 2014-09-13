/*
 * Utils.h
 *
 *  Created on: Sep 3, 2014
 *      Author: trevor
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <string>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

class Utils {

public:

	Utils();
	~Utils();

	const static std::string DATA_DIR;

	static boost::uuids::random_generator gen_uuid;

};

#endif /* UTILS_H_ */

