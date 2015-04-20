/*
 * Hal_Test_Thread.h
 *
 *  Created on: 20.04.2015
 *      Author: Lukas Wendt
 */

#ifndef HAL_TEST_THREAD_H_
#define HAL_TEST_THREAD_H_

#include <stdint.h>
#include <pthread.h>
#include "lib/HAWThread.h"

using namespace thread;

class Hal_Test_Thread: public HAWThread {
public:
	Hal_Test_Thread();
	virtual ~Hal_Test_Thread();

private:
	Hal_Test_Thread(const Hal_Test_Thread& b);      ///< Copy-Konstruktor. Privat, deshalb kann dieses Objekt nicht als "Call-by-value" uebergeben werden.
	Hal_Test_Thread& operator=(Hal_Test_Thread& b);
	virtual void execute(void*); ///< Geerbt aus HAWThread. Muss implementiert werden.
	virtual void shutdown();
};

#endif /* HAL_TEST_THREAD_H_ */
