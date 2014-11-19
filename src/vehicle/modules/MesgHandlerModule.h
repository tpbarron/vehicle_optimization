/**
 * MesgHandlerModule.h
 *	
 *  Created on: Nov 16, 2014
 *      Author: trevor
 */

#ifndef MESGHANDLERMODULE_H_
#define MESGHANDLERMODULE_H_

class ModuleMediator;
#include "ModuleMediator.h"

/**
 * This module sends out messages to nearby vehicles.
 */
class MesgHandlerModule {
public:

	virtual ~MesgHandlerModule();
	MesgHandlerModule();

	void set_mediator(ModuleMediator *mediator);

private:

	ModuleMediator *_mediator;
};

#endif /* MESGHANDLERMODULE_H_ */
