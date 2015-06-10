/*
 * PuckLifcycleFSM.cpp
 *
 *  Created on: 10.06.2015
 *      Author: abn908
 */

#include "ReadySend.h"


ReadySend::ReadySend() {
	// TODO Auto-generated constructor stub

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
	}

}

void ReadySend::shutdown(){

}
