/*
 * VehicleManager.cpp
 *
 *  Created on: Aug 25, 2014
 *      Author: trevor
 */

#include "VehicleManager.h"

//Define vector
std::vector<const Vehicle*> VehicleManager::vehicles;

VehicleManager::VehicleManager() {

}

VehicleManager::~VehicleManager() {
	// TODO Auto-generated destructor stub
}


void VehicleManager::register_vehicle(const Vehicle* v) {
	vehicles.push_back(v);
}


std::vector<Vehicle> VehicleManager::get_nearest(int n) {
	std::vector<Vehicle> nearest;
	return nearest;
}
