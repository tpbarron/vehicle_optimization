/**
 * MesgHandlerModule.cpp
 *	
 *  Created on: Nov 16, 2014
 *      Author: trevor
 */

#include <vehicle/modules/MesgHandlerModule.h>

MesgHandlerModule::MesgHandlerModule() :
	_mediator(nullptr) {
}

MesgHandlerModule::~MesgHandlerModule() {
}

void MesgHandlerModule::set_mediator(ModuleMediator *mediator) {
	_mediator = mediator;
}
