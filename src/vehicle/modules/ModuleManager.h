/**
 * ModuleManager.h
 *	
 *  Created on: Oct 20, 2014
 *      Author: trevor
 */

#ifndef MODULEMANAGER_H_
#define MODULEMANAGER_H_

#include "data_types/Distance.h"
#include "data_types/Heading.h"
#include "data_types/Position.h"
#include "map/Map.h"
#include "HazardWarningModule.h"
#include "RoutingModule.h"

/**
 *
 */
class ModuleManager {

public:
	ModuleManager();
	virtual ~ModuleManager();

	void generate_route();

	const Position& get_goal_position() const;
	void set_goal_position(const Position& goal_position);

	const Map& get_map() const;
	void set_map(const Map& map);

	const Position& get_start_position() const;
	void set_start_position(const Position& start_position);

	Speed get_current_speed();
	Position get_new_position(Distance& d);
	Heading get_current_heading();

	void update_modules();

private:

	Map _map;
	Position _start_position;
	Position _goal_position;

	HazardWarningModule _hazard_module;
	RoutingModule _routing_module;

};

#endif /* MODULEMANAGER_H_ */
