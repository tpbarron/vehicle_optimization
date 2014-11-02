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
	virtual std::string to_string() = 0;
};

#endif /* IVEHICLEDATALISTENER_H_ */
