/*
 * VehicleManager.h
 *
 *  Created on: Aug 25, 2014
 *      Author: trevor
 */

#ifndef VEHICLEMANAGER_H_
#define VEHICLEMANAGER_H_

#include <unordered_set>
#include <utility>
#include <vector>

#include "vehicle/Vehicle.h"
#include "data_types/Position.h"

class Vehicle;

class VehicleManager {
public:

	VehicleManager();
	~VehicleManager();

	static void register_vehicle(Vehicle *v);
	static std::vector<Vehicle*> get_vehicles();

	typedef std::pair<const Distance*, Vehicle*> VehicleDistPair;

	inline static bool closer(VehicleDistPair p1, VehicleDistPair p2) {
		return ((p1.first->get_distance()) < (p2.first->get_distance()));
	}
	static std::vector<VehicleDistPair> get_nearest(const Position *p, unsigned int k, unsigned int m);


private:

	static std::vector<Vehicle*> vehicles;
//	static std::unordered_set<const Vehicle*> vehicles;

};


#endif /* VEHICLEMANAGER_H_ */
