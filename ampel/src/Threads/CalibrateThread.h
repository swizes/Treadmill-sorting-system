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
#include <math.h>
#include "lib/HAWThread.h"
#include "Serial.h"

#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>

class ConfigManager;

using namespace thread;

class CalibrateThread: public HAWThread {
public:
	virtual ~CalibrateThread();

	static CalibrateThread* getInstance();
	bool configLoaded;

	int timespecToMs(struct timespec *);
	void msToTimespec(int, struct timespec *);

	int getGatetoL1Slow() const {
		return GatetoL1Slow;
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

	double getScaleFastToSlow() const {
		return scaleFastToSlow;
	}

	double getScaleSlowToFast() const {
		return scaleSlowToFast;
	}

	bool isConfigLoaded() const {
		return configLoaded;
	}

	int getHeightToGateFast() const {
		return HeightToGateFast;
	}

	int getHeightToMetalFast() const {
		return HeightToMetalFast;
	}

	int getHoleHeightMetal() const {
		return holeHeightMetal;
	}

	int getInGateToSlideFast() const {
		return InGateToSlideFast;
	}

	int getMetalToIsInGateFast() const {
		return MetalToIsInGateFast;
	}

	int getOutGateToL1Fast() const {
		return OutGateToL1Fast;
	}


	int getHeightToGateFast2Sd() const {
		return HeightToGateFast2SD;
	}

	int getHeightToMetalFast2Sd() const {
		return HeightToMetalFast2SD;
	}

	int getInGateToSlideFast2Sd() const {
		return InGateToSlideFast2SD;
	}

	int getL0toHeightFast2Sd() const {
		return L0toHeightFast2SD;
	}

	int getL0toL1Fast2Sd() const {
		return L0toL1Fast2SD;
	}

	int getMetalToIsInGateFast2Sd() const {
		return MetalToIsInGateFast2SD;
	}

	int getOutGateToL1Fast2Sd() const {
		return OutGateToL1Fast2SD;
	}

private:
	CalibrateThread();
	CalibrateThread(const CalibrateThread& b);      ///< Copy-Konstruktor. Privat, deshalb kann dieses Objekt nicht als "Call-by-value" uebergeben werden.
	CalibrateThread& operator=(CalibrateThread& b);
	virtual void execute(void*); ///< Geerbt aus HAWThread. Muss implementiert werden.
	virtual void shutdown();
	void saveConfig();
	int getMeanValueHeight();
	void saveCalcMean();
	int mean(int *, int);
	int getMedianValueHeight();
	int calcStandardDeviation(int, int* ,int);


	static CalibrateThread* instance_;
	ConfigManager* configManager;
	int L0toHeightFast;
	int HeightToMetalFast;
	int MetalToIsInGateFast;
	int InGateToSlideFast;
	int OutGateToL1Fast;
	int HeightToGateFast;
	int L0toL1Fast;
	int L0toHeightSlow;
	int HeighttoGateSlow;
	int L0toL1Slow;
	int GatetoL1Slow;
	int noPuckHeight;
	bool band; // 0 ->Band1 1->Band2

	int bigPuck;
	int smallPuck;
	int holeHeight;
	int holeHeightMetal;

	double scaleSlowToFast;
	double scaleFastToSlow;

	int L0toHeightFastAr[3];
	int HeightToMetalFastAr[3];
	int MetalToIsInGateFastAr[3];
	int InGateToSlideFastAr[3];
	int OutGateToL1FastAr[3];
	int HeightToGateFastAr[3];
	int L0toL1FastAr[3];

	int L0toHeightFast2SD;
	int HeightToMetalFast2SD;
	int MetalToIsInGateFast2SD;
	int InGateToSlideFast2SD;
	int OutGateToL1Fast2SD;
	int HeightToGateFast2SD;
	int L0toL1Fast2SD;
};

#endif /* COMMUNNICATIONTHREAD_H_ */
