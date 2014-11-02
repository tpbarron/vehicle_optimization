/**
 * HazardMessage.h
 *	
 *  Created on: Oct 31, 2014
 *      Author: trevor
 */

#ifndef HAZARDMESSAGE_H_
#define HAZARDMESSAGE_H_


#include "data_types/message_types/Message.h"
#include "data_types/module_types/Hazard.h"

/**
 *
 */
class HazardMessage : public Message {

public:

	HazardMessage();
	virtual ~HazardMessage();

	const Hazard& get_hazard() const;
	void set_hazard(const Hazard& hazard);

private:

	/**
	 * This is the Hazard we are sending out a notification for
	 */
	Hazard hazard;

};

#endif /* HAZARDMESSAGE_H_ */
