/*
 * VehicleManager.h
 *
 *  Created on: Aug 25, 2014
 *      Author: trevor
 */

#ifndef VEHICLEMANAGER_H_
#define VEHICLEMANAGER_H_

#include <vector>

#include "../vehicle/Vehicle.h"

class Vehicle;

class VehicleManager {
public:

	VehicleManager();
	~VehicleManager();

	static std::vector<const Vehicle*> vehicles;

	static void register_vehicle(const Vehicle *v);
	static std::vector<Vehicle> get_nearest(int n);

private:

};


#endif /* VEHICLEMANAGER_H_ */
