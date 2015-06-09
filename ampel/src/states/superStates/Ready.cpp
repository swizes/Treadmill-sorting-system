/*
 * Ready.cpp
 *
 *  Created on: 02.06.2015
 *      Author: swizes
 */

#include "PuckStates.h"

Ready::Ready(Context* con): State::State(con){
int isBand2 = 0;
//entry:	
	//SET isBand2 ? 1 : 0;
//do:
    printf("Ready() as Band:%d\n",isBand2+1);
    if(!isBand2){
        Dispatcher* dsp = Dispatcher::getInstance();
        dsp->addListeners( this->con_, RUNNING_IN_TRUE);
    }
    
    HAL *hal = HAL::getInstance();
    while(1){
    //start gedrückt (nur band2)
        if( ( hal->is_startButton_pushed() && isBand2) {
            // Move to State: Give_New_Puck
            new (this) Give_New_Puck(this->con_);
        }
    //reset gedrückt -> kalibrierung band1&2
        if( hal->is_resetButton_pushed() ) {
            if(!isBand2) dsp->remListeners( this->con_, RUNNING_IN_TRUE);
            // Move to State: Calibration
            new (this) Calibration(this->con_);
        }
    }
	
}

Ready::~Ready(){
	printf("~Ready()\n");
}

void Ready::Running_In_true(void){
	dsp->remListeners( this->con_, RUNNING_IN_TRUE);
    // Move to State: Working_Band1
	new (this) Working_Band1(this->con_);
}



