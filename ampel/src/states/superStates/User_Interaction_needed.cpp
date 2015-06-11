/*
 * User_Interaction_needed.cpp
 *
 *  Created on: 09.06.2015
 *      Author: Roland
 */

#include "PuckStates.h"

User_Interaction_needed::User_Interaction_needed(Context* con): State::State(con){
//entry:	
	int isUserneeded = 0;
    printf("User_Interaction_needed()\n");
//do:
    if(con->getPuck()->isHoleOnTop() == false){
    	isUserneeded = 1;
    }

    //TODO: Check  User_Interaction_needed ? 1 : 0
	
    if(isUserneeded){
        HAL *hal = HAL::getInstance();
        
        //printf("Waiting for User Interaction (Press START after)\n");
        //while(!(hal->is_startButton_pushed()));
        
        // Move to State: Waiting_for_arriving_Puck
        new (this) Waiting_for_arriving_Puck(this->con_);
    }else{
        // Move to State: Reihenfolge
        new (this) Reihenfolge(this->con_);
    }
	
	//new (this) Ready(this->con_);
}

User_Interaction_needed::~User_Interaction_needed(){
	printf("~User_Interaction_needed()\n");
}


