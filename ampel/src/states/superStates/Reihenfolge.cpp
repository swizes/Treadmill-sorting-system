/*
 *  Reihenfolge.cpp
 *
 *  Created on: 08.06.2015
 *      Author: Roland
 */

#include "PuckStates.h"

Reihenfolge::Reihenfolge(Context* con): State::State(con){
//entry:	
	Puck *puck;

    int isLastPuckMetal = 0,
        isThisPuckMetal = 0,
        isRsrvPuckMetal = 0;
        
    int wasThereReservPuck = 0,
    	wasThereLastPuck   = 0;

    int switchWithReserved = 0;

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
//    	cout << "[LastPuck: Metal]";
        if(isThisPuckMetal){
//        	cout << " + [ThisPuck: Metal]";
        	//if reserved=NULL -> new reserved
        	wasThereReservPuck++;
            if(isRsrvPuckMetal && (wasThereReservPuck!=1)){
//            	cout << " + [ReservedPuck: Metal]";
                //...
//            	cout << " -> [ThisPuck == ReservedPuck]";
            }else{//isRsrvPuckMetal:NO
//            	cout << " + [ReservedPuck: NOT Metal]";
            	switchWithReserved = 1;
            }
            cout << " -> [Reihenfolge: NOT OK]" << endl;
        }else{//isThisPuckMetal:NO
//        	cout << " + [ThisPuck: NOT Metal]";
            //...
        	cout << " -> [Reinhenfolge:OK]";
        }
    }else{//isLastPuckMetal:NO
//    	cout << "[LastPuck: NOT Metal]";
        if(isThisPuckMetal){
//        	cout << " + [ThisPuck: Metal]";
            //...
        	cout << " -> [Reinhenfolge:OK]";
        }else{//isThisPuckMetal:NO
//        	cout << " + [ThisPuck: NOT Metal]";
        	//if reserved=NULL -> new reserved
        	wasThereReservPuck++;
            if(isRsrvPuckMetal && (wasThereReservPuck!=1)){
//            	cout << " + [ReservedPuck: Metal]";
            	switchWithReserved = 1;
            }else{//isRsrvPuckMetal:NO
//            	cout << " + [ReservedPuck: NOT Metal]";
                //...
//            	cout << " -> [ThisPuck == ReservedPuck]";
            }
            cout << " -> [Reihenfolge: NOT OK]" << endl;
        }
    }
    cout<<endl;

    puck = bc->getRecentPuck();
    cout << "[RCND:" << puck->getSizeTyp()  << "  ID:" << puck->getId() << "  Hole:" << puck->isHoleOnTop()
		 << " Metal:" << puck->isMetal() << "]"  << endl;
    puck = bc->getLastPuck();
	cout << "[LAST:" << puck->getSizeTyp()  << "  ID:" << puck->getId() << "  Hole:" << puck->isHoleOnTop()
		 << " Metal:" << puck->isMetal() << "]"  << endl;
	puck = bc->getReservedPuck();
	cout << "[RSRV:" << puck->getSizeTyp()  << "  ID:" << puck->getId() << "  Hole:" << puck->isHoleOnTop()
		 << " Metal:" << puck->isMetal() << "]"  << endl;


    if(switchWithReserved){
    	bc->setLastPuck(bc->getReservedPuck());
    	bc->setReservedPuck(bc->getRecentPuck());
    	bc->setRecenctPuck(bc->getLastPuck());

    	//Aktuellen Context ueberschreiben
    	this->con_ = new Context(bc->getRecentPuck());
    	this->con_->setState(this);

    	printf("[ PUCK MIT RESERVEPUCK AUSTAUSCHEN ]\n");
    	//Set This ReservedPuck as LastPuck for nextPuck!
    }else{
    	//Set This Puck as LastPuck for nextPuck!
    	bc->setLastPuck(bc->getRecentPuck());
    }
    printf("-------------\n");
    
    puck = bc->getRecentPuck();
    cout << "[RCND:" << puck->getSizeTyp()  << "  ID:" << puck->getId() << "  Hole:" << puck->isHoleOnTop()
		 << " Metal:" << puck->isMetal() << "]"  << endl;
    puck = bc->getLastPuck();
	cout << "[LAST:" << puck->getSizeTyp()  << "  ID:" << puck->getId() << "  Hole:" << puck->isHoleOnTop()
		 << " Metal:" << puck->isMetal() << "]"  << endl;
	puck = bc->getReservedPuck();
	cout << "[RSRV:" << puck->getSizeTyp()  << "  ID:" << puck->getId() << "  Hole:" << puck->isHoleOnTop()
		 << " Metal:" << puck->isMetal() << "]"  << endl;


	bc->refreshBand();

    // Move to State: Waiting_for_arriving_Puck
	new (this) Waiting_for_arriving_Puck(this->con_);
}

Reihenfolge::~Reihenfolge(){
	printf("~Reihenfolge()\n");
}


