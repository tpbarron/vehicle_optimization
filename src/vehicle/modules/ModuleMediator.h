/**
 * ModuleMediator.h
 *	
 *  Created on: Nov 10, 2014
 *      Author: trevor
 */

#ifndef MODULEMEDIATOR_H_
#define MODULEMEDIATOR_H_


class AutopilotModule;
class HazardWarningModule;
class RoutingModule;
class VehicleSensorModule;


/**
 *
 */
class ModuleMediator {

public:

	ModuleMediator();
	virtual ~ModuleMediator();

	void set_autopilot_module(AutopilotModule *autopilot);
	void set_hazard_warning_module(HazardWarningModule *hazard_module);
	void set_routing_module(RoutingModule *routing_module);
	void set_vehicle_sensor_module(VehicleSensorModule *vehicle_sensor_module);

private:

	AutopilotModule *_autopilot;
	HazardWarningModule *_hazard_module;
	RoutingModule *_routing_module;
	VehicleSensorModule *_vehicle_sensor_module;

};

#endif /* MODULEMEDIATOR_H_ */
