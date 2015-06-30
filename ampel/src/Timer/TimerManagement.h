/*
 * TimerManagement.h
 *
 *  Created on: 28.05.2015
 *      Author: abn908
 */

#ifndef TIMERMANAGEMENT_H_
#define TIMERMANAGEMENT_H_

#include <iostream>
#include <vector>
#include "./Timer.h"

using namespace std;
class Timer; // forward declaration


class TimerManagement {

private:
	static TimerManagement* instance_;
	TimerManagement();
	double timeScaleFactor;
	bool timeScaleSet;
public:
	static TimerManagement* getInstance();
	void addTimer(Timer*);
	void deleteTimer(Timer*);
	void stopTimer();
	void deleteTimer();
	void continueTimer();
	void setTimeScaleFactor(double timeScaleFactor);
	void setScaleTime(bool scaleTime);
	virtual ~TimerManagement();
	void updateTimer(Timer *timer);
};

#endif /* TIMERMANAGEMENT_H_ */
