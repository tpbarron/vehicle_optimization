/*
 * IVehicleDataListener.h
 *
 *  Created on: Aug 23, 2014
 *      Author: trevor
 */

#ifndef IVEHICLEDATALISTENER_H_
#define IVEHICLEDATALISTENER_H_

#include <string>

#include "data_types/message_types/Message.h"
#include "sensor/VehicleSensorData.h"

class IVehicleDataListener {

public:

	virtual ~IVehicleDataListener();

	virtual void recv(Message &data) = 0;
	virtual void add_listener(IVehicleDataListener &l) = 0;
	virtual const Position get_position() const = 0;
	virtual const std::string to_string() const = 0;
	virtual const std::string get_id() const = 0;

	/**
	 * Just compares vehicles by uuids. This is not a significant ordering
	 * but a comparison is needed for the set.
	 */
	struct IVehicleDataListenerComp {
		bool operator()(IVehicleDataListener *v1, IVehicleDataListener *v2) const {
			return v1->get_id() < v2->get_id();
		}
	};
};

#endif /* IVEHICLEDATALISTENER_H_ */
