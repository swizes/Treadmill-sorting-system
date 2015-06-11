/*
 * CommunnicationThread.h
 *
 *  Created on: 17.04.2015
 *      Author: lukasTest, Tobi
 */


#ifndef CALIBRATETHREAD_H_
#define CALIBRATETHREAD_H_

#define CHECKSUM 10

#include <stdint.h>
#include <pthread.h>
#include "lib/HAWThread.h"
#include "Serial.h"

#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class ConfigManager;

using namespace thread;

class CalibrateThread: public HAWThread {
public:
	virtual ~CalibrateThread();

	static CalibrateThread* getInstance();
	bool configLoaded;

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

	int getNoPuckHeight() const{
		return noPuckHeight;
	}

	bool isBand() const {
		return band;
	}

	int getBigPuck() const {
		return bigPuck;
	}

	int getHoleHeight() const {
		return holeHeight;
	}

	int getSmallPuck() const {
		return smallPuck;
	}

private:
	CalibrateThread();
	CalibrateThread(const CalibrateThread& b);      ///< Copy-Konstruktor. Privat, deshalb kann dieses Objekt nicht als "Call-by-value" uebergeben werden.
	CalibrateThread& operator=(CalibrateThread& b);
	virtual void execute(void*); ///< Geerbt aus HAWThread. Muss implementiert werden.
	virtual void shutdown();
	int timespecToMs(struct timespec *);
	void saveConfig();

	static CalibrateThread* instance_;
	ConfigManager* configManager;
	int L0toHeightFast;
	int HeighttoGateFast;
	int L0toL1Fast;
	int GatetoL1Fast;
	int L0toHeightSlow;
	int HeighttoGateSlow;
	int L0toL1Slow;
	int GatetoL1Slow;
	int noPuckHeight;
	bool band; // 0 ->Band1 1->Band2

	int bigPuck;
	int smallPuck;
	int holeHeight;
};

#endif /* COMMUNNICATIONTHREAD_H_ */
