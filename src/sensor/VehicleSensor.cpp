/*
 * VehicleSensor.cpp
 *
 *  Created on: Aug 23, 2014
 *      Author: trevor
 */

#include "VehicleSensor.h"

#include "sim/Scenario.h"

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

//TODO: update these to check whether null ptr, if so create obj
//otherwise set obj.
void VehicleSensor::set_acceleration(double accel) {
	if (_accel == nullptr) {
		_accel = new Acceleration(accel);
	} else {
		_accel->set_acceleration(accel);
	}
}

void VehicleSensor::set_brake_pressure(double brake_pressure) {
	if (_brake_pressure == nullptr) {
		_brake_pressure = new BrakePressure(brake_pressure);
	} else {
		_brake_pressure->set_pressure(brake_pressure);
	}
}

void VehicleSensor::set_heading(double heading) {
	if (_heading == nullptr) {
		_heading = new Heading(heading);
	} else {
		_heading->set_heading(heading);
	}
}
void VehicleSensor::set_position(double pos_x, double pos_y) {
	if (_pos == nullptr) {
		_pos = new Position(pos_x, pos_y);
	} else {
		_pos->set_position(pos_x, pos_y);
	}
}

void VehicleSensor::set_speed(double spd) {
	if (_spd == nullptr) {
		_spd = new Speed(spd);
	} else {
		_spd->set_speed(spd);
	}
}

void VehicleSensor::set_vehicle_turn_rate(double vehicle_turn_rate) {
	if (_vehicle_turn_rate == nullptr) {
		_vehicle_turn_rate = new TurnRate(vehicle_turn_rate);
	} else {
		_vehicle_turn_rate->set_turn_rate(vehicle_turn_rate);
	}
}

void VehicleSensor::set_wheel_turn_rate(double wheel_turn_rate) {
	if (_wheel_turn_rate == nullptr) {
		_wheel_turn_rate = new TurnRate(wheel_turn_rate);
	} else {
		_wheel_turn_rate->set_turn_rate(wheel_turn_rate);
	}
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
