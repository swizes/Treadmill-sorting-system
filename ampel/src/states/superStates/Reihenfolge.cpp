/*
 *  Reihenfolge.cpp
 *
 *  Created on: 08.06.2015
 *      Author: Roland
 */

#include "PuckStates.h"

Reihenfolge::Reihenfolge(Context* con): State::State(con){
//entry:	
    int isLastPuckMetal = 0,
        isThisPuckMetal = 0,
        isRsrvPuckMetal = 0;
        
    int isPuckToBeReserved = 0,
    	wasThereReservPuck = 0,
    	wasThereLastPuck   = 0;

//	printf("Reihenfolge()\n");
//	printf("-------------\n");

    //TODO: Set isLastPuckMetal,isThisPuckMetal,isRsrvPuckMetal
    BandController* bc = BandController::getInstance();
    Puck* tempPuck;

    //This
    tempPuck = bc->getRecentPuck();
    if( tempPuck == NULL ) printf("SHOULD NEVER HAPPEN!!!\n");
    if( (tempPuck != NULL) && (tempPuck->isMetal())) isThisPuckMetal = 1;

    //Reserve
    tempPuck = bc->getReservedPuck();
    if( tempPuck == NULL ) printf("There is no ReservePuck\n");
    if(tempPuck != NULL) wasThereReservPuck = 1;
    if( (tempPuck != NULL) && (tempPuck->isMetal())) isRsrvPuckMetal = 1;

    //Last
    tempPuck = bc->getLastPuck();
    if( tempPuck == NULL ) printf("There is no LastPuck\n");
    if(tempPuck != NULL) wasThereLastPuck = 1;
    if( (tempPuck != NULL) && (tempPuck->isMetal())) isLastPuckMetal = 1;

    //If there was no LastPuck Then isLastPuckMetal has to be the opposite of isThisPuckMetal
    if( !wasThereLastPuck ) isThisPuckMetal == 1 ? isLastPuckMetal=0 : isLastPuckMetal=1;

//	printf("-------------\n");
//	printf("LastPuck Metal:%d\n",isLastPuckMetal);
//	printf("ThisPuck Metal:%d\n",isThisPuckMetal);
//	printf("RsrvPuck Metal:%d\n",isRsrvPuckMetal);

//do:

	//Sub-Automaton = Overkill -> If/Else
    // LastPuckMetal ? 
    if(isLastPuckMetal){
        if(isThisPuckMetal){
        	//if reserved=NULL -> new reserved
        	wasThereReservPuck++;
            if(isRsrvPuckMetal){
                //...
            }else{//isRsrvPuckMetal:NO
                if(wasThereReservPuck != 1)isPuckToBeReserved = 1;
            }
        }else{//isThisPuckMetal:NO
            //...
        }
    }else{//isLastPuckMetal:NO
        if(isThisPuckMetal){
            //...
        }else{//isThisPuckMetal:NO
        	//if reserved=NULL -> new reserved
        	wasThereReservPuck++;
            if(isRsrvPuckMetal && (wasThereReservPuck!=1)){
                isPuckToBeReserved = 1;
            }else{//isRsrvPuckMetal:NO
                //...
            }
        }
    }
    if(wasThereReservPuck == 2){
    	//This Puck is New Reserve
    	bc->setReservedPuck(bc->getRecentPuck());
    	printf("Dieser Puck ist nun ReservePuck\n");
    }
    if(isPuckToBeReserved && (wasThereReservPuck != 2)){
    	bc->switchWithReservedPuck(bc->getRecentPuck());
    	printf("Bitte den Puck mit dem ReservePuck austauschen\n");
    }
    printf("-------------\n");
    
    //TODO: mark Puck with isPuckToBeReserved
    
    //AN WELCHER STELLE WIRD DER RESERVIERTE PUCK GENOMMEN?
	
    // Move to State: Waiting_for_arriving_Puck
	new (this) Waiting_for_arriving_Puck(this->con_);
}

Reihenfolge::~Reihenfolge(){
	printf("~Reihenfolge()\n");
}


