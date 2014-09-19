/*
 * VehicleManager.cpp
 *
 *  Created on: Aug 25, 2014
 *      Author: trevor
 */

#include "VehicleManager.h"

#include <algorithm>

//Define vector
//std::unordered_set<const Vehicle*> VehicleManager::vehicles;
std::vector<Vehicle*> VehicleManager::vehicles;


VehicleManager::VehicleManager() {

}

VehicleManager::~VehicleManager() {
	// TODO Auto-generated destructor stub
}


void VehicleManager::register_vehicle(Vehicle *v) {
	vehicles.push_back(v);
	//insert(v);
}

std::vector<Vehicle*> VehicleManager::get_vehicles() {
	return vehicles;
}


/*
 * TODO: this is not optimal. But a good start
 */
std::vector<VehicleManager::VehicleDistPair> VehicleManager::get_nearest(const Position *p, unsigned int k, unsigned int m) {
	std::vector<VehicleManager::VehicleDistPair> nearest;
	std::cout << "Position: " << p->get_x() << " " << p->get_y() << std::endl;
	for (std::vector<Vehicle*>::iterator it = vehicles.begin(); it != vehicles.end(); ++it) {
		std::cout << "Checking vehicle" << std::endl;
		VehicleManager::VehicleDistPair vdist;
		vdist.first = p->get_distance_to((*it)->get_sensor().get_position());
		vdist.second = (*it);
		nearest.push_back(vdist);
	}
	//Sort vector;
	std::sort(nearest.begin(), nearest.end(), VehicleManager::closer);
	std::cout << "sorted" << std::endl;
	if (nearest.size() < k) {
		return nearest;
	} else {
		return std::vector<VehicleManager::VehicleDistPair>(nearest.begin(), nearest.begin()+k);
	}
}
