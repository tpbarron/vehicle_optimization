/*
 * Vehicle.cpp
 *
 *  Created on: Aug 23, 2014
 *      Author: trevor
 */

#include "Vehicle.h"

/**
 * Create a Vehicle object given the readable name and reference to global
 * boost::asio::io_service and boost::asio::strand vars
 *
 * @param name the readable name
 */
Vehicle::Vehicle(std::string name, boost::asio::io_service *io, boost::asio::strand *strand) :
		_count(0),
		_last_update_time(boost::posix_time::microsec_clock::local_time()),
		_self_update_timer(_self_update_io, boost::posix_time::milliseconds(100)) {

	_id = Utils::gen_uuid();

	_map = nullptr;
	_readable_name = name;

	_data = new VehicleSensorData();
	_data->VEHICLE_UUID = get_id_as_string();

	_io = io;
	_strand = strand;
	_timer = new boost::asio::deadline_timer(*_io, boost::posix_time::milliseconds(500));
	_t = nullptr;

	_self_update_thread = nullptr;
}

/**
 * Free the Vehicle memory
 */
Vehicle::~Vehicle() {
	delete _timer;
	delete _data;
	delete _t;

	delete _self_update_thread;
}

/**
 * Initialize memory and populate necessary data such as data struct
 */
void Vehicle::init() {
	//just set initial position
	_sensor.set_acceleration(0);
	_sensor.set_brake_pressure(0);
	_sensor.set_heading(0);
	_sensor.set_position(_start_position.get_x(), _start_position.get_y());
	_sensor.set_speed(0);
	_sensor.set_vehicle_turn_rate(0);
	_sensor.set_wheel_turn_rate(0);
}

/**
 * Start the Vehicle internal simulation
 */
void Vehicle::start() {
	init();

	std::pair<Intersection, Map::vertex_t> start = _map->get_intersection_closest_to(_start_position);
	std::pair<Intersection, Map::vertex_t> goal = _map->get_intersection_closest_to(_goal_position);

	Intersection start_int = start.first;
	Intersection goal_int = goal.first;

	_route.generate_route(start_int, goal_int);
	_route.print_route();

	// Start timer to update own position along route..
	_self_update_timer.async_wait(boost::bind(&Vehicle::update_self, this));
	_self_update_thread = new boost::thread(boost::bind(
			static_cast<size_t (boost::asio::io_service::*)()> (&boost::asio::io_service::run),
			boost::ref(_self_update_io)));

	// Start timer to send out updates
	(*_timer).async_wait((*_strand).wrap(boost::bind(&Vehicle::update, this)));
	_t = new boost::thread(boost::bind(
			static_cast<size_t (boost::asio::io_service::*)()> (&boost::asio::io_service::run),
			boost::ref(*_io)));
}


/**
 * Joins the Vehicle's update threads
 */
void Vehicle::stop() {
	_t->join();
	_self_update_thread->join();
}

/*
 *
 * -------------------
 * - Communication   -
 * -------------------
 *
 */

/**
 * Called regularly to send out data to other nearby vehicles..
 */
void Vehicle::update() {
	if (_count < 5) {
		std::vector<VehicleManager::VehicleDistPair> nearby_vehicles =
				VehicleManager::get_nearest(_sensor.get_position(), 10, 10);
		for (unsigned int i = 0; i < nearby_vehicles.size(); ++i) {
			_listeners.insert(nearby_vehicles[i].second);
		}

		broadcast_data();
		compute();
		std::cout << get_id_as_string() << ": " << _count << "\n";
		++_count;

		_timer->expires_at(_timer->expires_at() + boost::posix_time::milliseconds(250));
		_timer->async_wait(_strand->wrap(boost::bind(&Vehicle::update, this)));

		std::cout << std::endl;
	}
}

/**
 * Fill data struct will current values
 */
void Vehicle::populate_data_struct() {
	Scenario::update_vehicle_sensor(get_id_as_string(), _sensor);
	_data->WARN = should_warn();
	_sensor.export_data(_data);
}

/**
 * Send out data struct to listeners
 */
void Vehicle::broadcast_data() {
	for (std::unordered_set<IVehicleDataListener*, vehicle_hash>::iterator it = _listeners.begin(); it != _listeners.end(); ++it) {
		std::cout << "Sending data from " << get_id_as_string() << std::endl;
		(*it)->recv(*_data);
	}
}


/**
 * Add a new object that will listen to updates from this Vehicle
 *
 * @param l the object to add to the listeners list
 */
void Vehicle::add_listener(IVehicleDataListener &l) {
	std::cout << "Adding listener to vehicle " << get_id_as_string() << std::endl;
	_listeners.insert(&l);
}


/**
 * Entry point for data coming in from other Vehicle.
 * Compute as necessary using received data
 *
 * @param data the data struct sent out by a nearby Vehicle
 */
void Vehicle::recv(struct VehicleSensorData &data) {
	std::cout << get_id_as_string() << ": received data" << std::endl;
	//TODO: start thread for computation...
	compute();
}



/*
 *
 * -------------------
 * - Update self     -
 * -------------------
 *
 */

/**
 * Called regularly to move this Vehicle along route
 */
void Vehicle::update_self() {
	std::cout << "Updating self: " << get_id_as_string() << std::endl;
	_self_update_timer.expires_at(_self_update_timer.expires_at() + boost::posix_time::milliseconds(100));
	_self_update_timer.async_wait(boost::bind(&Vehicle::update_self, this));

	//Get time diff, calc new position from current
	boost::posix_time::ptime cur_time = boost::posix_time::microsec_clock::local_time();
	boost::posix_time::time_duration diff = cur_time - _last_update_time;
	long diff_millis = diff.total_milliseconds();
	calculate_progress(diff_millis);

	_last_update_time = cur_time;

	std::cout << _sensor.to_string() << std::endl;
//	populate_data_struct();
}

/**
 * Given elapsed time since last update calculates progress
 *
 * @param millis the time in milliseconds since the last update
 */
void Vehicle::calculate_progress(long millis) {
	// Get the allowed speed at the current position
	Speed speed = _route.get_current_speed_limit();
	_sensor.set_speed(speed.get_speed());

	// Get the distance in meters that would be covered in the allotted time
	Distance dist = speed.get_distance_for_time(millis);
	// Get a new position from the route after moving dist towards destination
	// TODO: there could have been a road change here and thus a speed change
	// Perhaps the update is frequent enough that it isn't important to
	// refresh immediately.
	Position pos = _route.get_new_position(dist);
	_sensor.set_position(pos.get_x(), pos.get_y());

	// Get the heading from the route using the last two positions
	Heading hdng = _route.get_current_heading();
	_sensor.set_heading(hdng.get_heading());

	// TODO: for now assume the following are constant
	_sensor.set_acceleration(0);
	_sensor.set_brake_pressure(0);
	_sensor.set_vehicle_turn_rate(0);
	_sensor.set_wheel_turn_rate(0);
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

void Vehicle::set_start_position(double x, double y) {
	_start_position.set_position(x, y);
}

void Vehicle::set_goal_position(double x, double y) {
	_goal_position.set_position(x, y);
}

/*
 * TODO: do both the vehicle and the route need a map reference?
 */
void Vehicle::set_map(Map *m) {
	_map = m;
	_route.set_map(m);
}

/*
 *
 * -------------------
 * - Getters	     -
 * -------------------
 *
 */

const boost::uuids::uuid Vehicle::get_id() const {
	return _id;
}

const std::string Vehicle::get_id_as_string() const {
	return boost::uuids::to_string(_id);
}

const std::string Vehicle::get_readable_name() const {
	return _readable_name;
}

//TODO: should this calculate stopping dist?
//Should probably be cached
Distance* Vehicle::get_stopping_dist() {
	return &_stopping_dist;
}

VehicleSensor& Vehicle::get_sensor() {
	return _sensor;
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




/**
 *
 * Return a unique name for this Vehicle as
 *
 * Readable name: UUID
 */
std::string Vehicle::to_string() {
	return _readable_name + ": " + get_id_as_string();
}
