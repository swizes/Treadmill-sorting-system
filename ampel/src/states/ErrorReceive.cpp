/*
 * PuckLifcycleFSM.cpp
 *
 *  Created on: 10.06.2015
 *      Author: abn908
 */

#include "ErrorReceive.h"


ErrorReceive::ErrorReceive() {
	cout << "ctor ErrorReceive" << endl;
}

ErrorReceive::~ErrorReceive() {
	// TODO Auto-generated destructor stub
}



void ErrorReceive::execute(void* con){
	Serial ser;
	Packet p;
	int i = 1;
	while(i){
		ser.recvPacket(&p);
		if(p.num == -1){
			i = -1;
		}
	}
	cout << "EStop" << endl;


}

void ErrorReceive::shutdown(){

}
