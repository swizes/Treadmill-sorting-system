/*
 * Give_New_Puck.cpp
 *
 *  Created on: 02.06.2015
 *      Author: swizes
 */

#include "PuckStates.h"
#include "ReadySend.h"

ReadySend rdySend;
static int rdyS = 0;

Give_New_Puck::Give_New_Puck(Context* con): State::State(con){
	printf("Give_New_Puck()\n");
	if(rdyS == 0){
		rdySend.start(NULL);
		rdyS = 1;
	}


    HAL *hal = HAL::getInstance();

    rdySend.setBusy(1);

    //Receive FiFo Entry (Puck ID) from Band1
    puckStruct puck;
    ser.recvPacket(&puck);

    Puck* p = new Puck();
    p->setPuckFromStruct(puck);
    this->con_ = new Context(p);
    this->con_->setState(this);

    rdySend.setBusy(0);

    int loop = 1;
	while(loop){
        if( hal->is_startButton_pushed()==0) {
            hal->band_left_normal();
            // Move to State: Working_Band2
            new (this) Working_Band2(this->con_);
            loop = 0;
        }
        if( hal->is_resetButton_pushed()==1){
            hal->band_stop();
            // Move to State: Working_Band2
            new (this) Ready(this->con_);
            loop=0;
        }
    }
}

Give_New_Puck::~Give_New_Puck(){
	printf("~Give_New_Puck()\n");
}



