/*
 * Hal_Test_Thread.cpp
 *
 *  Created on: 20.04.2015
 *      Author: abn908
 */

#include <unistd.h>
#include <time.h>
#include "Timer_Test_Thread.h"
#include "../lib/Lock.h"
#include "../lib/HWaccess.h"
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

	TimerManagement *timeM = TimerManagement::getInstance();
	Timer timer2;
	timer2.createTimer();
	Timer timer;



	timer.createTimer();
	timer.setTimer(9,0);

	struct timespec result;
	delay(500);
	timer.getTime(&result);
	struct timespec offset;
	offset.tv_nsec = result.tv_nsec;
	offset.tv_sec  = result.tv_sec;
	timeM->stopTimer();
	printf("OfS: %ld, OfNs: %ld\n",offset.tv_sec,offset.tv_nsec);

	delay(500);
	timeM->continueTimer();
	timer.getTime(&result);

	printf("Sec: %ld, nSec: %ld, diffSec: %ld, diffnSec: %ld\n",result.tv_sec,result.tv_nsec,result.tv_sec-offset.tv_sec,result.tv_nsec-offset.tv_nsec);

	timer.deleteTimer();

	timeM->deleteTimer();
	Timer timer15;
	Timer timer10;
	timer15.setTimer(15,0);
	timer10.setTimer(10,0);


	delay(500);

	struct timespec time15;
	timer15.getTime(&result);
	struct timespec time10;
	timer10.getTime(&time10);
	delay(500);

	printf("S: %ld, NS: %ld, S: %ld, NS: %ld\n",result.tv_sec,result.tv_sec,time10.tv_sec,time10.tv_nsec);

	delay(500);
	timeM->stopTimer();
	delay(100);
	timeM->continueTimer();




    cout << "Test erfolgreich" << endl;

}


void Timer_Test_Thread::shutdown(){
    cout << "Timer Test shutdown" << endl;
}




