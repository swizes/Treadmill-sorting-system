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
#include <string.h>
#include "Errors.h"


#define MAX_PUCKS 10

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
	int   getPuckCounter(void);
	void  refreshBand();

	int getSlideCounter(void);
	void incSlideCounter();

	int   getErrcode(void);
	void  setErrcode(int errCode);

private:
	BandController(const BandController& other);
    BandController& operator=(const BandController& other);
	BandController();
	virtual ~BandController();

	Puck* pucklist[MAX_PUCKS];
	int puckCounter;
	static BandController*  instance;
	bool stopped;
	bool runSlowly;
	Puck reservedPuck;
	Puck lastPuck;
	int errCode;
	int slideCounter;

};

#endif /* BANDCONTROLLER_H_ */
