/**
 * HazardMessage.cpp
 *	
 *  Created on: Oct 31, 2014
 *      Author: trevor
 */


#include "HazardMessage.h"

#include "MessageTypes.h"


HazardMessage::HazardMessage() {
	set_type(message_types::TYPE_HAZARD_WARNING);
}

HazardMessage::~HazardMessage() {
}


const Hazard& HazardMessage::get_hazard() const {
	return hazard;
}

void HazardMessage::set_hazard(const Hazard& hazard) {
	this->hazard = hazard;
}
