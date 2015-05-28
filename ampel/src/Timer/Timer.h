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
#include "TimerManagement.h"



class Timer {

private:
	timer_t timerid;
	struct itimerspec result;
	struct itimerspec val;
	struct timespec stop;
	struct sigevent timerEvent;


public:
	void createTimer();
	void deleteTimer();
	void setTimer(int,int);
	void getTime(struct timespec *);
	void stopTimer();
	void continueTimer();
	Timer();
	virtual ~Timer();
};

#endif /* TIMER_H_ */
