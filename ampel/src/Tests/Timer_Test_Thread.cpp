/*
 * Hal_Test_Thread.cpp
 *
 *  Created on: 20.04.2015
 *      Author: abn908
 */

#include <unistd.h>
#include <time.h>
#include "Timer_Test_Thread.h"
#include "lib/Lock.h"
#include "lib/HWaccess.h"
#include "Hal.h"
#include "../Timer/Timer.h"
#include <time.h>


Timer_Test_Thread::Timer_Test_Thread() {
	cout << "ctor Timer Test" << endl;
}

Timer_Test_Thread::~Timer_Test_Thread() {
	cout << "dtor Timer Test" << endl;
}

void Timer_Test_Thread::execute(void*){

	Timer timer;
	timer.createTimer();
	timer.setTimer(9,0);
	struct timespec result;
	delay(500);
	timer.stopTimer();
	timer.getTime(&result);

	struct timespec offset;
	offset.tv_nsec = result.tv_nsec;
	offset.tv_sec  = result.tv_sec;

	delay(5000);
	timer.continueTimer();
	timer.getTime(&result);

	printf("Sec: %ld, nSec: %ld, diffSec: %ld, diffnSec: %ld\n",result.tv_sec,result.tv_nsec,result.tv_sec-offset.tv_sec,result.tv_nsec-offset.tv_nsec);

	timer.deleteTimer();

    cout << "Test erfolgreich" << endl;

}


void Timer_Test_Thread::shutdown(){
    cout << "Timer Test shutdown" << endl;
}




