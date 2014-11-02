/**
 *  Message.cpp
 *	
 *  Created on: Oct 31, 2014
 *      Author: trevor
 */

#include "Message.h"

Message::~Message() {
	// no-op, let subclasses handle destruction
}

message_types::MessageType Message::get_type() const {
	return type;
}

void Message::set_type(message_types::MessageType type) {
	this->type = type;
}
