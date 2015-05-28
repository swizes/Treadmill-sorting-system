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
#include "Timer.h"

class TimerManagement {

private:
	std::vector<int> data;
	static TimerManagement* instance_;
	TimerManagement();
public:
	static TimerManagement* getInstance();
	virtual ~TimerManagement();
};

#endif /* TIMERMANAGEMENT_H_ */
