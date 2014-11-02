/**
 * VehicleManager.cpp
 *
 *  Created on: Aug 25, 2014
 *      Author: trevor
 *
 * Implementation for VehicleManager class. Maintains current Vehicle instances.
 *
 *
 */

#include "VehicleManager.h"

#include <algorithm>

//Define vector
std::vector<Vehicle*> VehicleManager::_vehicles;


VehicleManager::VehicleManager() {

}

VehicleManager::~VehicleManager() {
	for (unsigned int i = 0; i < _vehicles.size(); ++i) {
		delete _vehicles[i];
	}
}


/*
 * Simply add a Vehicle to the vector
 */
void VehicleManager::register_vehicle(Vehicle *v) {
	_vehicles.push_back(v);
}


std::vector<Vehicle*> VehicleManager::get_vehicles() {
	return _vehicles;
}


/*
 * Return the num vehicles closest Vehicles < meters meters away.
 * TODO: exclude own vehicle
 */
std::vector<VehicleManager::VehicleDistPair> VehicleManager::get_nearest(const Position &p,
		unsigned int num_vehicles, unsigned int meters) {

	std::vector<VehicleManager::VehicleDistPair> nearest;
	std::cout << "Position: " << p.get_x() << " " << p.get_y() << std::endl;

	//Check all vehicles
	for (std::vector<Vehicle*>::iterator it = _vehicles.begin(); it != _vehicles.end(); ++it) {
		std::cout << "Checking vehicle" << std::endl;
		VehicleManager::VehicleDistPair vdist;
		vdist.first = p.get_distance_to((*it)->get_module_manager().get_current_position());
		vdist.second = (*it);
		nearest.push_back(vdist);
	}

	//Sort vector;
	std::sort(nearest.begin(), nearest.end(), VehicleManager::closer);
	std::cout << "sorted" << std::endl;
	if (nearest.size() < num_vehicles) {
		return nearest;
	} else {
		return std::vector<VehicleManager::VehicleDistPair>(nearest.begin(), nearest.begin()+num_vehicles);
	}
}
