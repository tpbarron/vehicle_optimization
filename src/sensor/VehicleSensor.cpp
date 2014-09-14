/*
 * VehicleSensor.cpp
 *
 *  Created on: Aug 23, 2014
 *      Author: trevor
 */

#include "VehicleSensor.h"
#include "../sim/Scenario.h"

VehicleSensor::VehicleSensor() {
	// TODO Auto-generated constructor stub

}

VehicleSensor::~VehicleSensor() {
	// TODO Auto-generated destructor stub
}


/*
 * Set sensor data
 * UUID, WARN set in vehicle class
 */
void VehicleSensor::export_data(struct VehicleSensorData *data) {
	//FIXME: need scenario to be singleton
	//sim.update_sensor_data(vehicle_uuid);
	data->ACCELERATION = &accel;
	data->BRAKE_PRESSURE = &brkprsr;
	data->HEADING = &hdng;
	data->POSITION = &pos;
	data->SPEED = &spd;
	data->VEHICLE_TURN_RATE = &vturn;
	data->STEERING_WHEEL_TURN_RATE = &wturn;
}

void VehicleSensor::set_uuid(boost::uuids::uuid &vid) {
	vehicle_uuid = vid;
}

void VehicleSensor::set_position(Position &pos) {

}

void VehicleSensor::set_speed(Speed &spd) {

}


const Position& VehicleSensor::get_position() const {
	return pos;
}

const Speed& VehicleSensor::get_speed() const {
	return spd;
}


const Heading& VehicleSensor::get_heading() const {
	return hdng;
}
