/*
 * Timer.h
 *
 *  Created on: 17.05.2015
 *      Author: lukasTest
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h> // Integer Typen
#include <stdlib.h> // Speicherverwaltung
#include <stdio.h> // Ein- Ausgabe
#include <time.h>
#include <iostream>
#include <unistd.h>
#include <sys/neutrino.h>
#include "TimerManagement.h"


class Timer {

private:
	timer_t timerid;
	struct itimerspec result;
	struct itimerspec val;
	struct timespec stopval;
	struct sigevent timerEvent;
	bool stop;

public:
	void createTimer();
	int createTimerPulse();
	void createSignalTimer(int s, int ns, int errorcode);
	void waitForTimeOut(int, int, bool scaleTime);
	void waitForTimeOut(int, int);
	void waitForTimeOut();
	void deleteTimer();
	void setTimer(int,int);
	void setTimer(int,int, bool scaleTime);
	void setTimer(int s, int ns, bool scaleTime, bool shouldUpdate);
	void getTime(struct timespec *);
	void stopTimer();
	void continueTimer();
	bool isStopped();
	Timer();
	virtual ~Timer();

	bool scaleTime;
	bool shouldContinue;
	double currentScale;
};

#endif /* TIMER_H_ */
