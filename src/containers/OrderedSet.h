/*
 * OrderedSet.h
 *
 *  Created on: Sep 18, 2014
 *      Author: trevor
 */

#ifndef ORDEREDSET_H_
#define ORDEREDSET_H_

#include "data_manager/VehicleManager.h"
#include <vector>
#include <set>
#include <string>

class VehicleManager;
/*
 * This stores a list of VehicleDistPair in ascending order of distance
 * but ensures every element is unique
 */
class OrderedSet {
public:
	OrderedSet();
	virtual ~OrderedSet();

	/*
	 * Returns true if added
	 */
	bool add(VehicleManager::VehicleDistPair &e);


private:

	std::vector<VehicleManager::VehicleDistPair> elements;
	std::set<std::string> ids;

	void add_to_list(VehicleManager::VehicleDistPair &e);
};

#endif /* ORDEREDSET_H_ */
