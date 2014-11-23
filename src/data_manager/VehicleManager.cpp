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

//Define set
std::set<IVehicleDataListener*, IVehicleDataListener::IVehicleDataListenerComp> VehicleManager::_vehicles;


VehicleManager::VehicleManager() {
}

VehicleManager::~VehicleManager() {
}


/**
 * Simply add a Vehicle to the vector
 */
void VehicleManager::register_vehicle(Vehicle *v) {
	_vehicles.insert(v);
}


/**
 * Get all the Vehicles currently active in the simulation
 */
std::set<IVehicleDataListener*, IVehicleDataListener::IVehicleDataListenerComp> VehicleManager::get_vehicles() {
	return _vehicles;
}


std::set<IVehicleDataListener*, IVehicleDataListener::IVehicleDataListenerComp>
VehicleManager::get_nearest(const Position &p, unsigned int num_vehicles, double meters) {

	std::set<IVehicleDataListener*, IVehicleDataListener::IVehicleDataListenerComp> nearest;

	for (auto itr = _vehicles.begin();
			itr != _vehicles.end();
			++itr) {
		if (p.get_distance_to((*itr)->get_position()).get_distance() < meters) {
			nearest.insert(*itr);
		}
	}

	return nearest;
}

std::set<IVehicleDataListener*, IVehicleDataListener::IVehicleDataListenerComp>
VehicleManager::get_nearest(IVehicleDataListener &v, unsigned int num_vehicles, double meters) {

	Position p = v.get_position();
	std::set<IVehicleDataListener*, IVehicleDataListener::IVehicleDataListenerComp> nearest =
			get_nearest(p, num_vehicles, meters);

	nearest.erase(&v);
	return nearest;
}

