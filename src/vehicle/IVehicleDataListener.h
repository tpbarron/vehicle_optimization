/*
 * IVehicleDataListener.h
 *
 *  Created on: Aug 23, 2014
 *      Author: trevor
 */

#ifndef IVEHICLEDATALISTENER_H_
#define IVEHICLEDATALISTENER_H_

#include <iostream>

#include "sensor/VehicleSensorData.h"

class IVehicleDataListener {

public:
	virtual ~IVehicleDataListener();

	virtual void recv(struct VehicleSensorData &data) = 0;
};

#endif /* IVEHICLEDATALISTENER_H_ */
