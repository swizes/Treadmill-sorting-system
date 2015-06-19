/*
 * BlinkTest.cpp
 *
 *  Created on: 19.06.2015
 *      Author: abn908
 */

#include "BlinkTest.h"
#include "../Threads/Blink_ThreadRed.h"

BlinkTest::BlinkTest() {
	Blink_ThreadRed red;
	red.setLED(20,100000);
	usleep(2000000);
	red.setLED(-1,100000);
	usleep(2000000);
	red.setLED(0,100000);
	usleep(2000000);
}

BlinkTest::~BlinkTest() {
	// TODO Auto-generated destructor stub
}

