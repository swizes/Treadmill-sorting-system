/*
 *  Give_Band_2_Pucks.cpp
 *
 *  Created on: 08.06.2015
 *      Author: Roland
 */

#include "PuckStates.h"

Give_Band_2_Pucks::Give_Band_2_Pucks(Context* con): State::State(con){
//entry:	
//do:
	printf("Give_Band_2_Pucks()\n");

    HAL *hal = HAL::getInstance();

    BandController* bc = BandController::getInstance();

    this->con_->getPuck()->stopBand();
    bc->refreshBand();

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

	//Band 2 frei => Gelbe Leuchte an!


	Blink_ThreadYellow* yel = Blink_ThreadYellow::getInstance();

	//yel->setLED(100000,100000);
	hal->turn_yellowLight_on();
	while(hal->is_puck_running_out()==1){}
	hal->turn_yellowLight_off();
	//yel->setLED(1,100000);

	puckStruct puck = this->con_->getPuck()->getPuckStruct();

	ser->sendPacket(&puck);

	bc->delPuck(this->con_->getPuck());
	bc->refreshBand();
}

Give_Band_2_Pucks::~Give_Band_2_Pucks(){
	printf("~Give_Band_2_Pucks()\n");
}


