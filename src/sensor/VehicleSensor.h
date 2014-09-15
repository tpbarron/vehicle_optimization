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

	void set_acceleration(Acceleration* accel);
	void set_brake_pressure(BrakePressure* brake_pressure);
	void set_heading(Heading* heading);
	void set_position(Position* pos);
	void set_speed(Speed* spd);
	void set_vehicle_turn_rate(TurnRate* vehicle_turn_rate);
	void set_wheel_turn_rate(TurnRate* wheel_turn_rate);

	const Acceleration* get_acceleration() const;
	const BrakePressure* get_brake_pressure() const;
	const Heading* get_heading() const;
	const Position* get_position() const;
	const Speed* get_speed() const;
	const TurnRate* get_vehicle_turn_rate() const;
	const TurnRate* get_wheel_turn_rate() const;

private:

	//TODO: this probably isn't needed... if referencing from Vehicle.
	boost::uuids::uuid vehicle_uuid;

	/*
	 * Keep these alphabetized
	 */
	Acceleration* _accel;
	BrakePressure* _brake_pressure;
	Heading* _heading;
	Position* _pos;
	Speed* _spd;
	TurnRate* _vehicle_turn_rate;
	TurnRate* _wheel_turn_rate;


};

#endif /* VEHICLESENSOR_H_ */
