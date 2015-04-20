/*
 * CommunnicationThread.cpp
 *
 *  Created on: 17.04.2015
 *      Author: lukasTest
 */

#include "CommunnicationThread.h"

#define SENDER


Communnication_Thread::Communnication_Thread(void) {
	cout << "ctor Communication Test" << endl;
}

Communnication_Thread::~Communnication_Thread() {
	// TODO Auto-generated destructor stub
	cout << "dtor Communication Test" << endl;
}

void Communnication_Thread::execute(void*){

	Packet p;
	//allokieren und init
	memset(&p, 0 , sizeof(p));
	p.data = 0;

	#ifdef SENDER
		ser->sendPacket(&p);
	#endif

	while(p.data < 10){
		ser.recvPacket(&p);
		//printf("Pong: %d\n",p.data);

		p.data += 1;

		ser.sendPacket(&p);
		//printf("Ping: %d\n",p.data);
		usleep(1000000);
	}

}


void Communnication_Thread::shutdown(){
    cout << "Communication Test shutdown" << endl;
}
