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
	HAL* hal = HAL::getInstance();


	Serial* ser = new Serial();
	int res = 1;
	Packet p;

	//Wenn Band2 sagt ist frei, sendet es eine 1
	while(res){
		ser->recvPacket(&p);
		printf("Received Packet. %d\n", p.num);
		if(p.num == 1){
			res = 0;
		}
	}


	puckStruct puck = con->getPuck()->getPuckStruct();
	ser->sendPacket(&puck);

	hal->band_right_normal();



}

SerialCommunicationBand1::~SerialCommunicationBand1(){
	printf("~SerialCommunicationBand1()\n");
	printf("Lifecycle Puck: %d Band1 reached\n", con_->getPuck()->getId());
}

