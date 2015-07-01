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

TestClass *tclass;

Timer_Test_Thread::Timer_Test_Thread() {
	cout << "ctor Timer Test" << endl;
}

Timer_Test_Thread::~Timer_Test_Thread() {
	cout << "dtor Timer Test" << endl;
}

void Timer_Test_Thread::execute(void*){
	//test1();
	test2();
	//tclass = new TestClass();
	//tclass->waitForTimeoutFunc();
}

void Timer_Test_Thread::test1() {
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

	cout << "OfS: " << offset.tv_sec << ",  OfNs: " << offset.tv_nsec << endl;

	delay(500);
	timeM->continueTimer();
	timer.getTime(&result);

	cout << "Sec: " << result.tv_sec << ",  nSec: " << result.tv_nsec << ",  diffSec: " << result.tv_sec-offset.tv_sec
			<< ",  diffnSec: " << result.tv_nsec-offset.tv_nsec << endl;


	timer.deleteTimer();

	timeM->deleteTimer();
	Timer timer15;
	Timer timer10;
	timer15.setTimer(15,0);
	timer10.setTimer(10,0);


	delay(500);

	struct timespec time15;
	timer15.getTime(&time15);
	struct timespec time10;
	timer10.getTime(&time10);
	delay(500);

	cout << "S: " << time15.tv_sec << ",  NS: " << time15.tv_nsec << ",  S: " << time10.tv_sec << ",  NS: " << time10.tv_nsec << endl;
	//timer15.stopTimer();
	delay(500);
	timeM->stopTimer();

	delay(1000);
	timeM->continueTimer();
	delay(1000);

	timer10.getTime(&time10);
	timer15.getTime(&time15);

	cout << "S: " << time15.tv_sec << ",  NS: " << time15.tv_nsec << ",  S: " << time10.tv_sec << ",  NS: " << time10.tv_nsec << endl;



	cout << "Test erfolgreich Timer" << endl;

	cout << "Pulse Timer" << endl;
	timeM->deleteTimer();
	Timer pulseTimer;

	struct _pulse  pulse;
	int channel = pulseTimer.createTimerPulse();
	pulseTimer.setTimer(2,0);
	timeM->stopTimer();
	delay(1000);
	timeM->continueTimer();
	//Blockiert bis Pulse
	MsgReceivePulse(channel, &pulse, sizeof (pulse), NULL);
}

void Timer_Test_Thread::test2() {
	cout << "test timing" << endl;
	Timer timer0;

	struct timespec t0, t1;
	clock_gettime( CLOCK_REALTIME, &t0 );
	cout << "start at " << t0.tv_sec << ":" << t0.tv_nsec << endl;
	timer0.waitForTimeOut(2,0);
	clock_gettime( CLOCK_REALTIME, &t1 );
	cout << "end at " << t1.tv_sec << ":" << t1.tv_nsec << endl;
	cout << "diff: " << t1.tv_sec - t0.tv_sec << ":" << (t1.tv_nsec - t0.tv_nsec) / 1000000 << ":" << ((t1.tv_nsec - t0.tv_nsec) % 1000000) / 1000 << endl;

	cout << "expected 2 secs" << endl;

	cout << "timeScale test" << endl;
	Timer timer1;
	TimerManagement *timeM = TimerManagement::getInstance();
	timeM->setTimeScaleFactor(0.5);
	timeM->setScaleTime(SLOW);
	clock_gettime( CLOCK_REALTIME, &t0 );
	cout << "start at " << t0.tv_sec << ":" << t0.tv_nsec << endl;
	timer1.waitForTimeOut(2,0, true);
	clock_gettime( CLOCK_REALTIME, &t1 );
	cout << "end at " << t1.tv_sec << ":" << t1.tv_nsec << endl;
	cout << "diff: " << t1.tv_sec - t0.tv_sec << ":" << (t1.tv_nsec - t0.tv_nsec) / 1000000 << ":" << ((t1.tv_nsec - t0.tv_nsec) % 1000000) / 1000 << endl;

	cout << "expected 1 sec" << endl;

	cout << "multi timeScale test" << endl;
	Timer timer2;
	Timer timer3;
	timespec ts2, ts3;

	timer2.setTimer(2,0,true);
	timer3.setTimer(4,0,true);

	timeM->setTimeScaleFactor(2.0);

	cout << "set stopped" << endl;
	timeM->setScaleTime(STOPPED);

	cout << "wait 4 secs..";
	delay(4000);
	cout << " done" << endl;

	cout << "set slow" << endl;
	timeM->setScaleTime(SLOW);
	timer2.getTime(&ts2);
	timer3.getTime(&ts3);
	cout << "timer2:" << ts2.tv_sec << ":" << ts2.tv_nsec << endl;
	cout << "timer3:" << ts3.tv_sec << ":" << ts3.tv_nsec << endl;

	delay(2000);
	timer2.getTime(&ts2);
	timer3.getTime(&ts3);
	cout << "timer2:" << ts2.tv_sec << ":" << ts2.tv_nsec << endl;
	cout << "timer3:" << ts3.tv_sec << ":" << ts3.tv_nsec << endl;
	cout << "expected 2 and 4" << endl;

	cout << "set fast" << endl;
	timeM->setScaleTime(FAST);
	timer2.getTime(&ts2);
	timer3.getTime(&ts3);
	cout << "timer2:" << ts2.tv_sec << ":" << ts2.tv_nsec << endl;
	cout << "timer3:" << ts3.tv_sec << ":" << ts3.tv_nsec << endl;
	cout << "expected 1 and 2" << endl;
}

void Timer_Test_Thread::shutdown(){
    cout << "Timer Test shutdown" << endl;
}

void Timer_Test_Thread::getTestClass(TestClass *testclass) {
	testclass = this->tclass;
}

void TestClass::waitForTimeoutFunc() {
	Timer t;

	cout << "wait for timeout test func. Waiting.." << endl;
	t.waitForTimeOut(8,0);
	cout << "after wait for timeout" << endl;
}


void Timer_Test_Thread::killTestClass(TestClass *testclass)
{
	Timer t2;

	cout << "kill testclass in 2 secs..." << endl;
	t2.waitForTimeOut(2,0);
	delete(testclass);
	cout << "testclass deleted" << endl;
}
