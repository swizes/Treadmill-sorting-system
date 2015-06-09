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
        
    int isPuckToBeReserved = 0;
    //TODO: Set isLastPuckMetal,isThisPuckMetal,isRsrvPuckMetal
//do:
    
	printf("Reihenfolge()\n");
	//Sub-Automaton = Overkill -> If/Else
    // LastPuckMetal ? 
    if(isLastPuckMetal){
        if(isThisPuckMetal){
            if(isRsrvPuckMetal){
                //...
            }else{//isRsrvPuckMetal:NO
                isPuckToBeReserved = 1;
            }
        }else{//isThisPuckMetal:NO
            //...
        }
    }else{//isLastPuckMetal:NO
        if(isThisPuckMetal){
            //...
        }else{//isThisPuckMetal:NO
            if(isRsrvPuckMetal){
                isPuckToBeReserved = 1;
            }else{//isRsrvPuckMetal:NO
                //...
            }
        }
    }
    
    //TODO: mark Puck with isPuckToBeReserved
    
    //AN WELCHER STELLE WIRD DER RESERVIERTE PUCK GENOMMEN?
	
    // Move to State: Waiting_for_arriving_Puck
	new (this) Waiting_for_arriving_Puck(this->con_);
}

Reihenfolge::~Reihenfolge(){
	printf("~Reihenfolge()\n");
}


