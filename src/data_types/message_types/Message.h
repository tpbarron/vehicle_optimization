/**
 * Message.h
 *	
 *  Created on: Oct 31, 2014
 *      Author: trevor
 */

#ifndef IMESSAGE_H_
#define IMESSAGE_H_

#include "MessageTypes.h"

/**
 * This is an abstract class for all message types
 * All messages must have these fields
 */
class Message {
public:

	virtual ~Message();

	message_types::MessageType get_type() const;
	void set_type(message_types::MessageType type);

private:

	message_types::MessageType type;

};

#endif /* MESSAGE_H_ */
