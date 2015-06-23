/*
 * Give_New_Puck.cpp
 *
 *  Created on: 02.06.2015
 *      Author: swizes
 */

#include "PuckStates.h"
#include "ReadySend.h"

Give_New_Puck::Give_New_Puck(Context* con): State::State(con){
//entry:	
//do:
	printf("Give_New_Puck()\n");
    HAL *hal = HAL::getInstance();
    //TODO: Receive FiFo Entry (Puck ID) from Band1
	
	
	ReadySend* rdySend = new ReadySend();
	rdySend.execute();
	
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
    // Move to State: Ready
	//new (this) Ready(this->con_);
}

Give_New_Puck::~Give_New_Puck(){
	printf("~Give_New_Puck()\n");
}



