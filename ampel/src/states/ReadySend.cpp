/*
 * PuckLifcycleFSM.cpp
 *
 *  Created on: 10.06.2015
 *      Author: abn908
 */

#include "ReadySend.h"


ReadySend::ReadySend() {
	cout << "ReadySend" << endl;
	busy = 1;
}

ReadySend::~ReadySend() {
	// TODO Auto-generated destructor stub
}



void ReadySend::execute(void* con){
	Serial ser;
	Packet p;
	while(1){
		p.num = this->busy;
		ser.sendPacket(&p);
		Timer time;
		time.waitForTimeOut(0,100000000);
		//cout << "Ready" << endl;
	}

}

void ReadySend::shutdown(){

}
