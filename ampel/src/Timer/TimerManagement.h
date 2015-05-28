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



class TimerManagement {

private:
	static TimerManagement* instance_;
	TimerManagement();
public:
	static TimerManagement* getInstance();
	void addTimer(class Timer);
	void deleteTimer(class Timer);
	void stopTimer();
	void deleteTimer();
	virtual ~TimerManagement();
};

#endif /* TIMERMANAGEMENT_H_ */
