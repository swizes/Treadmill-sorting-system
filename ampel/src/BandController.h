/*
 * BandController.h
 *
 *  Created on: 10.06.2015
 *      Author: abn908
 */

#ifndef BANDCONTROLLER_H_
#define BANDCONTROLLER_H_

#include "Puck.h"
#include "HAL.h"
#include <pthread.h>

#define STOPPED 0
#define SLOW 1
#define FAST 2

#define MAX_PUCKS 5

class BandController {
public:

	static BandController* getInstance();

	void  addPuck(Puck* puck);
	void  delPuck(Puck* puck);
	void  setReservedPuck(Puck* puck);
	Puck* getReservedPuck(void);
	Puck* getRecentPuck(void);
	Puck* getLastPuck(void);
	void  setRecenctPuck(Puck* puck);
	void  setLastPuck(Puck* puck);

	void refreshBand();
	int getBandStatus();

private:
	BandController(const BandController& other);
    BandController& operator=(const BandController& other);
	BandController();
	virtual ~BandController();

	Puck* pucklist[MAX_PUCKS];
	int puckCounter;
	static BandController*  instance;
	HAL* hal;
	bool stopped;
	bool runSlowly;
	Puck reservedPuck;
	Puck lastPuck;
};

#endif /* BANDCONTROLLER_H_ */
