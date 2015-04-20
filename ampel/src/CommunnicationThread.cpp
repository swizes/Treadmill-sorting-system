/*
 * CommunnicationThread.cpp
 *
 *  Created on: 17.04.2015
 *      Author: lukasTest
 */

#include "CommunnicationThread.h"

#define SENDER


Communnication_Thread::Communnication_Thread(Serial& ser) {
	cout << "ctor Communication Test" << endl;
}

Communnication_Thread::~Communnication_Thread() {
	// TODO Auto-generated destructor stub
	cout << "dtor Communication Test" << endl;
}

void Communnication_Thread::execute(void*){


}


void Communnication_Thread::shutdown(){
    cout << "Hal Test shutdown" << endl;
}
