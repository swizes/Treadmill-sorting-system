/*
 * CommunnicationThread.h
 *
 *  Created on: 17.04.2015
 *      Author: lukasTest
 */


#ifndef CALIBRATETHREAD_H_
#define CALIBRATETHREAD_H_

#include <stdint.h>
#include <pthread.h>
#include "lib/HAWThread.h"
#include "Serial.h"

#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHECKSUM 10

using namespace thread;

class CalibrateThread: public HAWThread {
public:
	CalibrateThread(void);
	virtual ~CalibrateThread();

	int getGatetoL1Fast() const {
		return GatetoL1Fast;
	}

	int getGatetoL1Slow() const {
		return GatetoL1Slow;
	}

	int getHeighttoGateFast() const {
		return HeighttoGateFast;
	}

	int getHeighttoGateSlow() const {
		return HeighttoGateSlow;
	}

	int getL0toHeightFast() const {
		return L0toHeightFast;
	}

	int getL0toHeightSlow() const {
		return L0toHeightSlow;
	}

	int getL0toL1Fast() const {
		return L0toL1Fast;
	}

	int getL0toL1Slow() const {
		return L0toL1Slow;
	}

	int getBigPuk() const {
		return bigPuk;
	}

	int getHoleHeight() const {
		return holeHeight;
	}

	int getSmallPuk() const {
		return smallPuk;
	}

private:
	CalibrateThread(const CalibrateThread& b);      ///< Copy-Konstruktor. Privat, deshalb kann dieses Objekt nicht als "Call-by-value" uebergeben werden.
	CalibrateThread& operator=(CalibrateThread& b);
	virtual void execute(void*); ///< Geerbt aus HAWThread. Muss implementiert werden.
	virtual void shutdown();
	int timespecToMs(struct timespec *);

	int L0toHeightFast;
	int HeighttoGateFast;
	int L0toL1Fast;
	int GatetoL1Fast;
	int L0toHeightSlow;
	int HeighttoGateSlow;
	int L0toL1Slow;
	int GatetoL1Slow;
	int bigPuk;
	int smallPuk;
	int holeHeight;
};

#endif /* COMMUNNICATIONTHREAD_H_ */
