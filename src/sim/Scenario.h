/*
 * Scenario.h
 *
 *  Created on: Sep 8, 2014
 *      Author: trevor
 */

#ifndef SCENARIO_H_
#define SCENARIO_H_

#include <string>
#include <fstream>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "data_manager/VehicleManager.h"
#include "data_types/module_types/Hazard.h"
#include "map/Intersection.h"
#include "map/Lane.h"
#include "map/Map.h"
#include "map/Road.h"
#include "sensor/VehicleSensor.h"
#include "utils/Utils.h"
#include "vehicle/modules/routing/Route.h"
#include "vehicle/Vehicle.h"

namespace Scenario {

/*
 * Scenario json keys
 */
const std::string SCENARIO_NAME = "_name";
const std::string SCENARIO_DESC = "_desc";

const std::string SCENARIO_VEHICLES = "vehicles";
const std::string SCENARIO_VEHICLES_NAME = "name";
const std::string SCENARIO_VEHICLES_DATA = "data";

/*
 * Map keys
 */
const std::string SCENARIO_MAP = "map";
const std::string SCENARIO_MAP_WIDTH = "width";
const std::string SCENARIO_MAP_HEIGHT = "height";
const std::string SCENARIO_MAP_INTERSECTIONS = "intersections";
const std::string SCENARIO_MAP_ROADS = "roads";

/*
 * Vehicle keys
 */
const std::string VEHICLE_TYPE = "type";
const std::string VEHICLE_START = "start";
const std::string VEHICLE_GOAL = "goal";
const std::string VEHICLE_POSITION_X = "x";
const std::string VEHICLE_POSITION_Y = "y";


/*
 * Intersection keys
 */
const std::string INTERSECTION_DATA = "intersections";
const std::string INTERSECTION_ID = "id";
const std::string INTERSECTION_POSITION_X = "pos_x";
const std::string INTERSECTION_POSITION_Y = "pos_y";
const std::string INTERSECTION_WIDTH = "width";
const std::string INTERSECTION_HEIGHT = "height";

/*
 * Road keys
 */
const std::string ROAD_DATA = "roads";
const std::string ROAD_START_INT_ID = "start_intersection";
const std::string ROAD_END_INT_ID = "end_intersection";
const std::string ROAD_SPEED_LIMIT = "speed_limit";
const std::string ROAD_DISTANCE = "distance";
const std::string ROAD_LANES = "lanes";
const std::string ROAD_FORWARD_LANES = "forward";
const std::string ROAD_BACKWARD_LANES = "backward";
const std::string ROAD_HAZARDS = "hazards";

/*
 * Lane keys
 */
const std::string LANE_WAYPOINTS = "waypoints";
const std::string LANE_POINT_X = "ptx";
const std::string LANE_POINT_Y = "pty";

/*
 * Hazard keys
 */
const std::string HAZARD_POSITION_X = "pos_x";
const std::string HAZARD_POSITION_Y = "pos_y";
const std::string HAZARD_MAX_SAFE_SPEED = "max_safe_speed";

void init();
void cleanup();

void load_scenario(std::string file);
void load_scenario_map(std::string scenario, boost::property_tree::ptree &map_tree);
void load_scenario_roads(std::string scenario, std::string file);
Lane load_road_lane(std::string scenario, std::string file);
Hazard load_road_hazard(std::string scenario, std::string file);
void load_scenario_intersections(std::string scenario, std::string file);
void load_vehicle(std::string vehicle_name, std::string vehicle_file);
void populate_map();
Intersection& get_intersection_from_id(int id);

void start();
void stop();

void test_get_closest_vehicles();
void test_print_map();
//void test_routing();

extern boost::posix_time::ptime _start_time;
extern Map _map;
extern std::vector<Intersection> _intersections;
extern std::vector<Road> _roads;

};

#endif /* SCENARIO_H_ */
