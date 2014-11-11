/**
 * HazardWarningModule.h
 *	
 *  Created on: Oct 15, 2014
 *      Author: trevor
 */

#ifndef HAZARDWARNINGMODULE_H_
#define HAZARDWARNINGMODULE_H_

#include <unordered_set>

#include <boost/functional/hash.hpp>

#include "data_types/message_types/Message.h"
#include "data_types/message_types/HazardMessage.h"
#include "data_types/module_types/Hazard.h"
#include "data_types/sensor_types/Position.h"


class ModuleMediator;

/**
 *
 */
class HazardWarningModule {

public:

	HazardWarningModule();
	virtual ~HazardWarningModule();

	void set_mediator(ModuleMediator *mediator);

	void handle(Message &msg);

	void add_hazard(Hazard &h);
	void remove_hazard(Hazard &h);

	bool is_known_hazard(Hazard &h);

	void update();

private:

	ModuleMediator *_mediator;

	struct HazardHash {
	    size_t operator()(const Hazard &h) const
	    {
	    	std::size_t seed = 0;

	    	Position p = h.get_position();

	    	boost::hash_combine(seed, boost::hash_value(p.get_x()));
	    	boost::hash_combine(seed, boost::hash_value(p.get_y()));

	    	return seed;
	    }
	};

	std::unordered_set<Hazard, HazardHash> _hazards;
//	std::vector<Hazard> _hazards;

};

#endif /* HAZARDWARNINGMODULE_H_ */
