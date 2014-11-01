/**
 * VehicleManager.h
 *
 *  Created on: Aug 25, 2014
 *      Author: trevor
 *
 *  The VehicleManager maintains the current list of vehicles and provides
 *  utility methods for operations between them.
 */

#ifndef VEHICLEMANAGER_H_
#define VEHICLEMANAGER_H_

#include <unordered_set>
#include <utility>
#include <vector>

#include "vehicle/Vehicle.h"
#include "data_types/sensor_types/Position.h"

class Vehicle;

class VehicleManager {
public:

	VehicleManager();
	~VehicleManager();

	/**
	 * Adds a Vehicle to the list of known current Vehicle instances
	 *
	 * @see Vehicle
	 */
	static void register_vehicle(Vehicle *v);

	/**
	 * Returns a vector of all the Vehicle instances
	 *
	 * @see Vehicle
	 */
	static std::vector<Vehicle*> get_vehicles();

	/**
	 * A std::pair relating a Distance and a Vehicle used to provide
	 * information on the closest Vehicle instances
	 *
	 * @see Distance
	 * @see Vehicle
	 */
	typedef std::pair<Distance, Vehicle*> VehicleDistPair;

	/**
	 * A helper function to compare two VehicleDistPair s and
	 * determine which Vehicle is closer
	 */
	inline static bool closer(VehicleDistPair p1, VehicleDistPair p2) {
		return ((p1.first.get_distance()) < (p2.first.get_distance()));
	}

	/**
	 * Returns a vector of VehicleDistPair containing no more than
	 * num_vehicles Vehicle objects at a max distance of meters
	 *
	 * @param p - The position to search from
	 * @param num_vehicles - The max number of vehicles to return
	 * @param meters - The distance all returned vehicles must be
	 *
	 * @see Position
	 * @see VehicleDistPair
	 * @see Vehicle
	 *
	 */
	static std::vector<VehicleDistPair> get_nearest(const Position &p,
			unsigned int num_vehicles, unsigned int meters);


private:

	/**
	 * A list of Vehicle
	 */
	static std::vector<Vehicle*> _vehicles;

};


#endif /* VEHICLEMANAGER_H_ */
