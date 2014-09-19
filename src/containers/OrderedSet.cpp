/*
 * OrderedSet.cpp
 *
 *  Created on: Sep 18, 2014
 *      Author: trevor
 */

#include "OrderedSet.h"

OrderedSet::OrderedSet() {
	// TODO Auto-generated constructor stub

}

OrderedSet::~OrderedSet() {
	// TODO Auto-generated destructor stub
}


bool OrderedSet::add(VehicleManager::VehicleDistPair &e) {
	bool already_exists = ids.find(e.second->get_id_as_string()) != ids.end();
	if (already_exists) {
		return false;
	}

	ids.insert(e.second->get_id_as_string());
	add_to_list(e);
	return true;
}

void OrderedSet::add_to_list(VehicleManager::VehicleDistPair &e) {
	for (unsigned int i = 0; i < elements.size(); ++i) {
		if (e.first->get_distance() < elements[i].first->get_distance()) {
			elements.insert(elements.begin() + i, e);
			return;
		}
	}
	//If reach this part of the function, this is the longest dist seen. Add to back.
	elements.push_back(e);
}
