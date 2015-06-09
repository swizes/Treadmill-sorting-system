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
    while(!(hal->is_startButton_pushed()));
	
    // Move to State: Working_Band1
	new (this) Working_Band1(this->con_);
}

Give_Band_2_Pucks::~Give_Band_2_Pucks(){
	printf("~Give_Band_2_Pucks()\n");
}


