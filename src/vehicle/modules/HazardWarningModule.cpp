/**
 * HazardWarningModule.cpp
 *	
 *  Created on: Oct 15, 2014
 *      Author: trevor
 */

#include "HazardWarningModule.h"

HazardWarningModule::HazardWarningModule() {
	// TODO Auto-generated constructor stub

}

HazardWarningModule::~HazardWarningModule() {
	// TODO Auto-generated destructor stub
}

void HazardWarningModule::handle(Message &msg) {
	HazardMessage& hazard_msg = dynamic_cast<HazardMessage&>(msg);
	Hazard hazard = hazard_msg.get_hazard();
	if (!is_known_hazard(hazard)) {
		add_hazard(hazard);
	}
	//TODO: how respond to the actual hazard
}

void HazardWarningModule::add_hazard(Hazard &h) {
	_hazards.insert(h); //push_back(h);
}
void HazardWarningModule::remove_hazard(Hazard &h) {
	_hazards.erase(h);
}

bool HazardWarningModule::is_known_hazard(Hazard &h) {
	std::unordered_set<Hazard, HazardHash>::const_iterator found = _hazards.find(h);
	if (found != _hazards.end()) {
		return true;
	}
	return false;
}

void HazardWarningModule::update() {
	//Remove any old hazards that have passed
}
