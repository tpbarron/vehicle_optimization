/*
 * VehicleSensor.cpp
 *
 *  Created on: Aug 23, 2014
 *      Author: trevor
 */

#include "VehicleSensor.h"
#include "../sim/Scenario.h"

VehicleSensor::VehicleSensor() {
	_accel = nullptr;
	_brake_pressure = nullptr;
	_heading = nullptr;
	_pos = nullptr;
	_spd = nullptr;
	_vehicle_turn_rate = nullptr;
	_wheel_turn_rate = nullptr;
}

VehicleSensor::~VehicleSensor() {
	// TODO Auto-generated destructor stub
}


/*
 * Set sensor data
 * UUID, WARN set in vehicle class
 */
void VehicleSensor::export_data(struct VehicleSensorData *data) {
	data->ACCELERATION = _accel;
	data->BRAKE_PRESSURE = _brake_pressure;
	data->HEADING = _heading;
	data->POSITION = _pos;
	data->SPEED = _spd;
	data->VEHICLE_TURN_RATE = _vehicle_turn_rate;
	data->STEERING_WHEEL_TURN_RATE = _wheel_turn_rate;
}

void VehicleSensor::set_uuid(boost::uuids::uuid &vid) {
	vehicle_uuid = vid;
}


void VehicleSensor::set_acceleration(Acceleration* accel) {
	_accel = accel;
}

void VehicleSensor::set_brake_pressure(BrakePressure* brake_pressure) {
	_brake_pressure = brake_pressure;
}

void VehicleSensor::set_heading(Heading* heading) {
	_heading = heading;
}
void VehicleSensor::set_position(Position* pos) {
	_pos = pos;
}

void VehicleSensor::set_speed(Speed* spd) {
	_spd = spd;
}

void VehicleSensor::set_vehicle_turn_rate(TurnRate* vehicle_turn_rate) {
	_vehicle_turn_rate = vehicle_turn_rate;
}

void VehicleSensor::set_wheel_turn_rate(TurnRate* wheel_turn_rate) {
	_wheel_turn_rate = wheel_turn_rate;
}


const Acceleration* VehicleSensor::get_acceleration() const {
	return _accel;
}

const BrakePressure* VehicleSensor::get_brake_pressure() const {
	return _brake_pressure;
}

const Heading* VehicleSensor::get_heading() const {
	return _heading;
}

const Position* VehicleSensor::get_position() const {
	return _pos;
}

const Speed* VehicleSensor::get_speed() const {
	return _spd;
}

const TurnRate* VehicleSensor::get_vehicle_turn_rate() const {
	return _vehicle_turn_rate;
}

const TurnRate* VehicleSensor::get_wheel_turn_rate() const {
	return _wheel_turn_rate;
}
