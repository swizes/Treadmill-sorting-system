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
        
    int wasThereReservPuck = 0,
    	wasThereLastPuck   = 0;

    int switchWithReserved = 0;
    int isInReihenfolge = 0;

	printf("Reihenfolge()\n");
//	printf("-------------\n");

    //TODO: Set isLastPuckMetal,isThisPuckMetal,isRsrvPuckMetal
    BandController* bc = BandController::getInstance();
    bc->setRecenctPuck(con_->getPuck());
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
            if(isRsrvPuckMetal && (wasThereReservPuck!=1)){
                //...
            }else{//isRsrvPuckMetal:NO
            	switchWithReserved = 1;
            	isInReihenfolge = 1;
            }
        }else{//isThisPuckMetal:NO
        	isInReihenfolge = 1;
        }
    }else{//isLastPuckMetal:NO
        if(isThisPuckMetal){
        	isInReihenfolge = 1;
        }else{//isThisPuckMetal:NO
        	//if reserved=NULL -> new reserved
        	wasThereReservPuck++;
            if(isRsrvPuckMetal && (wasThereReservPuck!=1)){
            	switchWithReserved = 1;
            	isInReihenfolge = 1;
            }else{//isRsrvPuckMetal:NO
                //...
            }
        }
    }
    cout<<endl;

    //Output: RecentPuck, LastPuck, ReservedPuck BEFORE they got switched
//    puck = bc->getRecentPuck();
//    cout << "[RCND:" << puck->getSizeTyp()  << "  ID:" << puck->getId() << "  Hole:" << puck->isHoleOnTop()
//		 << " Metal:" << puck->isMetal() << "]"  << endl;
//    puck = bc->getLastPuck();
//	cout << "[LAST:" << puck->getSizeTyp()  << "  ID:" << puck->getId() << "  Hole:" << puck->isHoleOnTop()
//		 << " Metal:" << puck->isMetal() << "]"  << endl;
//	puck = bc->getReservedPuck();
//	cout << "[RSRV:" << puck->getSizeTyp()  << "  ID:" << puck->getId() << "  Hole:" << puck->isHoleOnTop()
//		 << " Metal:" << puck->isMetal() << "]"  << endl;

    if(isInReihenfolge){
    	printf("[Reihenfolge: OK]\n");
    }else{
    	printf("[Reihenfolge: FALSE]\n");
    	bc->getRecentPuck()->setSizeTyp(NOT_OK);
    }

    if(switchWithReserved){
    	bc->setLastPuck(bc->getReservedPuck());
    	bc->setReservedPuck(bc->getRecentPuck());
    	bc->setRecenctPuck(bc->getLastPuck());
    	printf("[ PUCK MIT RESERVEPUCK AUSTAUSCHEN ]\n");
    	//Set This ReservedPuck as LastPuck for nextPuck!
    }else{
    	//Set This Puck as LastPuck for nextPuck!
    	bc->setLastPuck(bc->getRecentPuck());
    }

    printf("-------------\n");
    
    //Output: RecentPuck, LastPuck, ReservedPuck AFTER they got switched
//    puck = bc->getRecentPuck();
//    cout << "[RCND:" << puck->getSizeTyp()  << "  ID:" << puck->getId() << "  Hole:" << puck->isHoleOnTop()
//		 << " Metal:" << puck->isMetal() << "]"  << endl;
//    puck = bc->getLastPuck();
//	cout << "[LAST:" << puck->getSizeTyp()  << "  ID:" << puck->getId() << "  Hole:" << puck->isHoleOnTop()
//		 << " Metal:" << puck->isMetal() << "]"  << endl;
//	puck = bc->getReservedPuck();
	cout << "[RSRV:" << tempPuck->getSizeTyp()  << "  ID:" << tempPuck->getId() << "  Hole:" << tempPuck->isHoleOnTop()
		 << " Metal:" << tempPuck->isMetal() << "]"  << endl;


	bc->refreshBand();


	// Move to State: Waiting_for_arriving_Puck
	new (this) Waiting_for_arriving_Puck(this->con_);
}

Reihenfolge::~Reihenfolge(){
	printf("~Reihenfolge()\n");
}


