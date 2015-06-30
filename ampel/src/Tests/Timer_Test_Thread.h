/*
 * Hal_Test_Thread.h
 *
 *  Created on: 20.04.2015
 *      Author: Lukas Wendt
 *
 *      Todo Test Timer and TimerManagement
 */

#ifndef TIMER_TEST_THREAD_H_
#define TIMER_TEST_THREAD_H_

#include "../lib/HAWThread.h"

using namespace thread;

class Timer_Test_Thread: public HAWThread {
public:
	Timer_Test_Thread();
	virtual ~Timer_Test_Thread();

private:
	Timer_Test_Thread(const Timer_Test_Thread& b);      ///< Copy-Konstruktor. Privat, deshalb kann dieses Objekt nicht als "Call-by-value" uebergeben werden.
	Timer_Test_Thread& operator=(Timer_Test_Thread& b);
	virtual void execute(void*); ///< Geerbt aus HAWThread. Muss implementiert werden.
	virtual void shutdown();

};

#endif /* TIMER_TEST_THREAD_H_ */
