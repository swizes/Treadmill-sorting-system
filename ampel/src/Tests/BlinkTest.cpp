/*
 * BlinkTest.cpp
 *
 *  Created on: 19.06.2015
 *      Author: abn908
 */

#include "BlinkTest.h"
#include "../Threads/Blink_ThreadRed.h"
#include "../Threads/Blink_ThreadGreen.h"
#include "../Threads/Blink_ThreadYellow.h"

BlinkTest::BlinkTest() {
	Blink_ThreadRed* red = Blink_ThreadRed::getInstance();
	Blink_ThreadYellow* yel = Blink_ThreadYellow::getInstance();
	Blink_ThreadGreen* gre = Blink_ThreadGreen::getInstance();
	//red->setLED(40,100000);
	yel->setLED(40,100000);
	//gre->setLED(10,400000);

}

BlinkTest::~BlinkTest() {
	// TODO Auto-generated destructor stub
}

