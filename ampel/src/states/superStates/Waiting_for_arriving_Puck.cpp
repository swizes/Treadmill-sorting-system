/*
 * Waiting_for_arriving_Puck.cpp
 *
 *  Created on: 02.06.2015
 *      Author: swizes
 */
 
#include "PuckStates.h"

Waiting_for_arriving_Puck::Waiting_for_arriving_Puck(Context* con): State::State(con){
//entry:	
//do:
//	printf("Waiting_for_arriving_Puck()\n");
//    printf("Push START\n");
//    HAL *hal = HAL::getInstance();
    //while(!(hal->is_startButton_pushed()));
	
    // Move to State: Give_Band_2_Pucks
	new (this) Give_Band_2_Pucks(this->con_);
}

Waiting_for_arriving_Puck::~Waiting_for_arriving_Puck(){
	printf("~Waiting_for_arriving_Puck()\n");
}
