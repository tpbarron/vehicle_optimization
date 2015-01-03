/**
 * HazardWarningModule.cpp
 *	
 *  Created on: Oct 15, 2014
 *      Author: trevor
 */

#include "HazardWarningModule.h"

#include "utils/Logger.h"

const Distance HazardWarningModule::HAZARD_DIST_THRESHOLD(10);
const Heading HazardWarningModule::HAZARD_HEADING_THRESHOLD(.5);

HazardWarningModule::HazardWarningModule() :
	_mediator(nullptr) {
}

HazardWarningModule::~HazardWarningModule() {
}

void HazardWarningModule::set_mediator(ModuleMediator *mediator) {
	_mediator = mediator;
}

void HazardWarningModule::handle(HazardMessage *mesg) {
	Logger::info("HazardWarningModule handling HazardMessage");
	Hazard hazard = mesg->get_hazard();
	if (!is_known_hazard(hazard)) {
		Logger::info("HazardWarningModule saving new Hazard");
		add_hazard(hazard);
	} else {
		Logger::info("HazardWarningModule Hazard already known");
	}
}

/**
 * Pass a copy to this function so the freeing of
 * memory does not make this hazard invalid
 */
void HazardWarningModule::add_hazard(Hazard h) {
	_hazards.insert(h); //push_back(h);
}
void HazardWarningModule::remove_hazard(Hazard &h) {
	_hazards.erase(h);
}

/**
 * Check to see whether there are any hazards within reasonable range in
 * vicinity of current heading.
 */
bool HazardWarningModule::is_known_relevant_hazards(Position &pos, Heading &hdng) {
	for (auto itr = _hazards.begin(); itr != _hazards.end(); ++itr)
	{
		//For each hazard,
		//Get the distance from current position to hazard position
		Position hazard_pos = itr->get_position();
		Distance euclidean_dist = MathUtils::get_distance(pos, hazard_pos);
		if (euclidean_dist > HAZARD_DIST_THRESHOLD)
			continue;

		//get heading from current position to hazard position
		//If the heading is within threshold save
		Heading hazard_hdng;
		hazard_hdng.set_from_pts(pos, hazard_pos);
		double delta = std::abs(hdng.get_heading() - hazard_hdng.get_heading());
		Heading delta_hdng(delta);
		if (delta_hdng < HAZARD_HEADING_THRESHOLD)
			return true;
	}
	return false;
}

/**
 * Determine if a hazard is known
 */
bool HazardWarningModule::is_known_hazard(Hazard &h) {
	std::unordered_set<Hazard, HazardHash>::const_iterator found = _hazards.find(h);
	return found != _hazards.end();
}

/**
 *
 */
Speed HazardWarningModule::get_safe_speed(Position &pos, Heading &hdng, Speed& default_spd) {
	for (auto itr = _hazards.begin(); itr != _hazards.end(); ++itr) {
		Hazard h = *itr;
		Speed max_safe = h.get_max_safe_speed();
		if (max_safe < default_spd) {
			default_spd = max_safe;
		}
	}
	return default_spd;
}

HazardMessage HazardWarningModule::create_message(Hazard &h) {
	HazardMessage mesg(h);
	return mesg;
}



void HazardWarningModule::update() {
	//Remove any old hazards that have passed
}
