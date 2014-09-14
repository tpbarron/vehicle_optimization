/*
 * VehicleSensor.h
 *
 *  Created on: Aug 23, 2014
 *      Author: trevor
 */

#ifndef VEHICLESENSOR_H_
#define VEHICLESENSOR_H_

#include "../data_types/Acceleration.h"
#include "../data_types/BrakePressure.h"
#include "../data_types/Heading.h"
#include "../data_types/Position.h"
#include "../data_types/Speed.h"
#include "../data_types/TurnRate.h"

#include "VehicleSensorData.h"

#include <boost/uuid/uuid.hpp>

/**
 * Emits data from vehicle
 *
 * I'll going to make some assumptions about what this
 * sensor knows for simplicity.
 *
 * Speed
 * Direction
 * Exact position
 * Road (in real application would likely need to be calculated from position)
 * Lane on road
 * Current acceleration
 * Current steering wheel movement
 * Degree of brake currently applied
 *
 */
class VehicleSensor {

public:
	VehicleSensor();
	virtual ~VehicleSensor();

	void export_data(struct VehicleSensorData *data);

	void set_uuid(boost::uuids::uuid &vid);
	void set_position(Position &pos);
	void set_speed(Speed &spd);

	const Heading& get_heading() const;
	const Position& get_position() const;
	const Speed& get_speed() const;

private:

	boost::uuids::uuid vehicle_uuid;
	/*
	 * Keep these alphabetized
	 */
	Acceleration accel;
	BrakePressure brkprsr;
	Heading hdng;
	Position pos;
	Speed spd;
	TurnRate vturn;
	TurnRate wturn;


};

#endif /* VEHICLESENSOR_H_ */
