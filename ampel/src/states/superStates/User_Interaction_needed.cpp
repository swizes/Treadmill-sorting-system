/*
 * User_Interaction_needed.cpp
 *
 *  Created on: 09.06.2015
 *      Author: Roland
 */

#include "PuckStates.h"

User_Interaction_needed::User_Interaction_needed(Context* con): State::State(con){
//entry:	
    printf("User_Interaction_needed()\n");
    Puck *puck = this->con_->getPuck();
	cout << "[PuckType:" << puck->getSizeTyp()  << "  ID:" << puck->getId() << "  Hole:" << puck->isHoleOnTop()
		 << " Metal:" << puck->isMetal() << "]"  << endl;

//do:
    if( !(con->getPuck()->isHoleOnTop()) ){

    	con->getPuck()->setUserInteractionNeeded(true) ;
    }else{
    	con->getPuck()->setUserInteractionNeeded(false) ;
    }



    //Check  User_Interaction_needed ? 1 : 0
	
    if(this->con_->getPuck()->isUserInteractionNeeded()){
        printf("UserInterAction needed: true\n");
        //printf("Waiting for User Interaction (Press START after)\n");
        //while(!(hal->is_startButton_pushed()));
        
        // Move to State: Waiting_for_arriving_Puck
        new (this) Waiting_for_arriving_Puck(this->con_);
    }else{
    	printf("UserInterAction needed: false\n");
        // Move to State: Reihenfolge
        new (this) Reihenfolge(this->con_);
    	//new (this) Waiting_for_arriving_Puck(this->con_);
    }
	
	//new (this) Ready(this->con_);
}

User_Interaction_needed::~User_Interaction_needed(){
	printf("~User_Interaction_needed()\n");
}


