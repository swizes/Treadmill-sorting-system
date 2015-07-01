/*
 * PuckLifcycleFSM.cpp
 *
 *  Created on: 10.06.2015
 *      Author: abn908
 */

#include "ReadySend.h"


ReadySend* ReadySend::instance_ = NULL;

ReadySend::ReadySend() {
	cout << "ReadySend" << endl;
	busy = 1;
}

ReadySend::~ReadySend() {
	// TODO Auto-generated destructor stub
}

ReadySend* ReadySend::getInstance() {
	static pthread_mutex_t mtx_ = PTHREAD_MUTEX_INITIALIZER;

	if (instance_ == NULL) {
		pthread_mutex_lock(&mtx_);
		if (instance_ == NULL) {
			instance_ = new ReadySend();
		}
		pthread_mutex_unlock(&mtx_);
	}
	return instance_;
}



void ReadySend::execute(void* con){
	Serial ser;
	Packet p;
	while(1){
		p.num = this->busy;
		ser.sendPacket(&p);
		ser.recvPacket(&p);
		//Timer time;
		//time.waitForTimeOut(0,100000000);
		delay(100);
		//cout << "Ready" << endl;
	}

}

void ReadySend::shutdown(){

}
