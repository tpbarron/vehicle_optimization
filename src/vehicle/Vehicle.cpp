/*
 * Vehicle.cpp
 *
 *  Created on: Aug 23, 2014
 *      Author: trevor
 */

#include "Vehicle.h"

Vehicle::Vehicle(std::string name, boost::asio::io_service *io, boost::asio::strand *strand) : count_(0) {

	id = Utils::gen_uuid();
	sensor.set_uuid(id);

	data = new VehicleSensorData();
	data->VEHICLE_UUID = get_id_as_string();

	readable_name = name;

	_io = io;
	_strand = strand;
	timer = new boost::asio::deadline_timer(*_io, boost::posix_time::seconds(1));
	t = nullptr;
}

/*
 * Free memory.
 * TODO: Why does freeing the data struct give an error?
 * Maybe the timer cannot be deallocated before the io service?
 */
Vehicle::~Vehicle() {
//	delete timer;
//	delete data;
	delete t;
}



void Vehicle::start() {
	(*timer).async_wait((*_strand).wrap(boost::bind(&Vehicle::update, this)));

	t = new boost::thread(boost::bind(
			static_cast<size_t (boost::asio::io_service::*)()> (&boost::asio::io_service::run),
			boost::ref(*_io)));
}


/*
 * Joins thread
 */
void Vehicle::stop() {
	t->join();
}

/*
 *
 * -------------------
 * - Communication   -
 * -------------------
 *
 */


void Vehicle::update() {
	if (count_ < 3) {
		populate_data_struct();
		broadcast_data();
		compute();
		std::cout << get_id_as_string() << ": " << count_ << "\n";
		++count_;

		(*timer).expires_at((*timer).expires_at() + boost::posix_time::milliseconds(250));
		(*timer).async_wait((*_strand).wrap(boost::bind(&Vehicle::update, this)));

		std::cout << std::endl;
	}
}

/*
 * Fill data struct will current values
 */
void Vehicle::populate_data_struct() {
	data->WARN = should_warn();
	sensor.export_data(data);
}

/*
 * Send out data struct to listeners
 */
void Vehicle::broadcast_data() {
	for (std::vector<const IVehicleDataListener*>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
		std::cout << "Sending data from " << get_id_as_string() << std::endl;
		(**it).recv(*data);
	}
}


/*
 * TODO: is it possible to get rid of one of the pointers here? I don't think it is. This has to be a reference
 * since can't instantiate the interface directly. Then need double pointer above in the iterator
 * for a ptr to ref.
 */
void Vehicle::add_listener(IVehicleDataListener const &l) {
	std::cout << "Adding listener to vehicle " << get_id_as_string() << std::endl;
	listeners.push_back(&l);
}


/*
 * Compute as necessary using received data
 */
void Vehicle::recv(struct VehicleSensorData &data) const {
	std::cout << get_id_as_string() << ": received data" << std::endl;
}



/*
 *
 * -------------------
 * - Setters	     -
 * -------------------
 *
 */


/*
 *
 */
void Vehicle::set_stopping_dist(Distance &dist) {

}


/*
 *
 * -------------------
 * - Getters	     -
 * -------------------
 *
 */

const boost::uuids::uuid Vehicle::get_id() const {
	return id;
}

const std::string Vehicle::get_id_as_string() const {
	return boost::uuids::to_string(id);
}

const std::string Vehicle::get_readable_name() const {
	return readable_name;
}

//TODO: should this calculate stopping dist?
//Should probably be cached
Distance* Vehicle::get_stopping_dist() {
	return &stopping_dist;
}

VehicleSensor& Vehicle::get_sensor() {
	return sensor;
}

/*
 *
 * -------------------
 * - Calculations
 * -------------------
 *
 */

void Vehicle::compute() {
	std::cout << get_id_as_string() << " Computing" << std::endl;
}

bool Vehicle::should_warn() {
	return false;
}

void Vehicle::calc_stopping_dist() {

}






