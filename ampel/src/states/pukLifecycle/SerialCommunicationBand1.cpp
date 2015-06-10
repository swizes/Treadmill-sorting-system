/*
 * serialCommunicationBand1.cpp
 *
 *  Created on: 10.06.2015
 *      Author: abn908
 */




#include "PuckStates.h"
#include "Serial.h"

SerialCommunicationBand1::SerialCommunicationBand1(Context* con): State::State(con){
	printf("SerialCommunicationBand1\n");

	Dispatcher* dsp = Dispatcher::getInstance();

	Serial* ser = new Serial();
	int res = 1;
	Packet p;

	//Wenn Band2 sagt ist frei, sendet es eine 1
	while(res){
		ser->recvPacket(&p);
		if(p.num == 1){
			res = 0;
		}
	}


	puckStruct puck = con->getPuck()->getPuckStruct();
	ser->sendPacket(&puck);




}

SerialCommunicationBand1::~SerialCommunicationBand1(){
	printf("~SerialCommunicationBand1()\n");
	printf("Lifecycle Puck: %d Band1 reached\n", con_->getPuck()->getId());
}

