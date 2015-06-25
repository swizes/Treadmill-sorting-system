/*
 * DoorKeeper.h
 *
 *  Created on: 23.06.2015
 *      Author: abl425
 */

#ifndef DOORKEEPER_H_
#define DOORKEEPER_H_


#include "../../HAL.h"
#include "Puck.h"
#include <pthread.h>

class DoorKeeper {
public:
	static DoorKeeper* getInstance();
	void startTimer(void* con);

	bool getRight() const{
		return right_;
	}

private:
    static DoorKeeper* instance_;
    bool greenLightOn;
    static bool right_;
    bool allowPuck;

private:
	DoorKeeper(const DoorKeeper& other);
	DoorKeeper& operator=(const DoorKeeper& other);
    DoorKeeper();
	virtual ~DoorKeeper();
	virtual void shutdown();
};

#endif /* DOORKEEPER_H_ */
