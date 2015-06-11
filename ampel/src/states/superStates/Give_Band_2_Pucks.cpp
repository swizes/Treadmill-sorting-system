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
	//TODO: Send ready PUCK ID to Band2
    HAL *hal = HAL::getInstance();
    //while(!(hal->is_startButton_pushed()));

    BandController* bc = BandController::getInstance();

    while(hal->is_puck_running_out() == 1);

    con->getPuck()->runBandFast();

    bc->delPuck(con->getPuck());

    /*
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
	*/

	bc->refreshBand();

	
    // Move to State: Working_Band1
	//new (this) Working_Band1(this->con_);
}

Give_Band_2_Pucks::~Give_Band_2_Pucks(){
	printf("~Give_Band_2_Pucks()\n");
}


