/*
 * Hal_Test_Thread.cpp
 *
 *  Created on: 20.04.2015
 *      Author: abn908
 */

#include <unistd.h>
#include <time.h>
#include "Hal_Test_Thread.h"
#include "lib/Lock.h"
#include "lib/HWaccess.h"


Hal_Test_Thread::Hal_Test_Thread() {
	// TODO Auto-generated constructor stub

}

Hal_Test_Thread::~Hal_Test_Thread() {
	// TODO Auto-generated destructor stub
}

void Hal_Test_Thread::execute(void*){
    cout << "Hello";
}


void Hal_Test_Thread::shutdown(){
    cout << "Blink_Thread shutdown" << endl;
}

