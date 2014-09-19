/*
 * SensorData.h
 *
 *  Created on: Aug 23, 2014
 *      Author: trevor
 */

#ifndef SENSORDATA_H_
#define SENSORDATA_H_

#include <string>

#include "data_types/Acceleration.h"
#include "data_types/BrakePressure.h"
#include "data_types/Heading.h"
#include "data_types/Position.h"
#include "data_types/Speed.h"
#include "data_types/TurnRate.h"

struct VehicleSensorData {

	std::string VEHICLE_UUID;
	bool WARN;

	const Position* POSITION;
	const Speed* SPEED;
	const Heading* HEADING;
	const Acceleration* ACCELERATION;
	const TurnRate* VEHICLE_TURN_RATE;
	const TurnRate* STEERING_WHEEL_TURN_RATE;
	const BrakePressure* BRAKE_PRESSURE;

	/*
	 * Free memory
	 */
//	~VehicleSensorData() {
//		delete POSITION;
//		delete SPEED;
//		delete HEADING;
//		delete ACCELERATION;
//		delete VEHICLE_TURN_RATE;
//		delete STEERING_WHEEL_TURN_RATE;
//		delete BRAKE_PRESSURE;
//	}

};



#endif /* SENSORDATA_H_ */
