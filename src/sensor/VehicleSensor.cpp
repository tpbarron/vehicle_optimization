/*
 * VehicleSensor.cpp
 *
 *  Created on: Aug 23, 2014
 *      Author: trevor
 */

#include "VehicleSensor.h"

#include "sim/Scenario.h"

VehicleSensor::VehicleSensor() : _accel(0), _brake_pressure(0), _heading(0),
	_pos(0, 0), _spd(0), _vehicle_turn_rate(0), _wheel_turn_rate(0) {
}

VehicleSensor::~VehicleSensor() {
	// TODO Auto-generated destructor stub
}


/*
 * Set sensor data
 * UUID, WARN set in vehicle class
 */
void VehicleSensor::export_data(struct VehicleSensorData *data) {
	data->ACCELERATION = &_accel;
	data->BRAKE_PRESSURE = &_brake_pressure;
	data->HEADING = &_heading;
	data->POSITION = &_pos;
	data->SPEED = &_spd;
	data->VEHICLE_TURN_RATE = &_vehicle_turn_rate;
	data->STEERING_WHEEL_TURN_RATE = &_wheel_turn_rate;
}

void VehicleSensor::set_acceleration(double accel) {
	_accel.set_acceleration(accel);
}

void VehicleSensor::set_brake_pressure(double brake_pressure) {
	_brake_pressure.set_pressure(brake_pressure);
}

void VehicleSensor::set_heading(const Heading &h) {
	_heading.set_heading(h);
}
void VehicleSensor::set_position(const Position &p) {
	_pos.set_position(p);
}

void VehicleSensor::set_speed(const Speed &spd) {
	_spd.set_speed(spd);
}

void VehicleSensor::set_vehicle_turn_rate(double vehicle_turn_rate) {
	_vehicle_turn_rate.set_turn_rate(vehicle_turn_rate);
}

void VehicleSensor::set_wheel_turn_rate(double wheel_turn_rate) {
	_wheel_turn_rate.set_turn_rate(wheel_turn_rate);
}


const Acceleration& VehicleSensor::get_acceleration() const {
	return _accel;
}

const BrakePressure& VehicleSensor::get_brake_pressure() const {
	return _brake_pressure;
}

const Heading& VehicleSensor::get_heading() const {
	return _heading;
}

const Position& VehicleSensor::get_position() const {
	return _pos;
}

const Speed& VehicleSensor::get_speed() const {
	return _spd;
}

const TurnRate& VehicleSensor::get_vehicle_turn_rate() const {
	return _vehicle_turn_rate;
}

const TurnRate& VehicleSensor::get_wheel_turn_rate() const {
	return _wheel_turn_rate;
}

std::string VehicleSensor::to_string() {
	std::string s = "Position: " + _pos.to_string() + "\n" +
//					"Acceleration: " + boost::lexical_cast<std::string>(_accel.get_acceleration()) + "\n" +
//					"Brake Pressure: " + boost::lexical_cast<std::string>(_brake_pressure.get_pressure()) + "\n" +
					"Heading: " + boost::lexical_cast<std::string>(_heading.get_heading()) + "\n";
//					"Position: " + _pos.to_string() + "\n" +
//					"Speed: " + boost::lexical_cast<std::string>(_spd.get_speed()) + "\n" +
//					"Vehicle Turn Rate: " + boost::lexical_cast<std::string>(_vehicle_turn_rate.get_turn_rate()) + "\n" +
//					"Wheel Turn Rate: " + boost::lexical_cast<std::string>(_wheel_turn_rate.get_turn_rate()) + "\n";
	return s;
}
