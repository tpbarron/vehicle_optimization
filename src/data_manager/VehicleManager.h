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

#include <set>

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
	static std::set<IVehicleDataListener*, IVehicleDataListener::IVehicleDataListenerComp> get_vehicles();

	/**
	 * Returns a vector of IVehicleDataListener containing no more than
	 * `num_vehicles` objects at a max distance of `meters`
	 *
	 * TODO: (NOTE) The number of vehicles to return is currently ignored
	 *
	 * @param p - The position to search from
	 * @param num_vehicles - The max number of vehicles to return
	 * @param meters - The distance all returned vehicles must be
	 *
	 * @see Position
	 * @see IVehicleDataListener
	 * @see Vehicle
	 */
	static std::set<IVehicleDataListener*, IVehicleDataListener::IVehicleDataListenerComp>
		get_nearest(const Position &p, unsigned int num_vehicles, double meters);


	/**
	 * Operates the same as position based search (and calls that one) but
	 * finds position from vehicle and excludes self from search
	 */
	static std::set<IVehicleDataListener*, IVehicleDataListener::IVehicleDataListenerComp>
		get_nearest(IVehicleDataListener &v, unsigned int num_vehicles, double meters);




private:

	/**
	 * A list of Vehicle
	 */
	static std::set<IVehicleDataListener*, IVehicleDataListener::IVehicleDataListenerComp> _vehicles;

};


#endif /* VEHICLEMANAGER_H_ */
