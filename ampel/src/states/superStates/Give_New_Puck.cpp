/*
 * Give_New_Puck.cpp
 *
 *  Created on: 02.06.2015
 *      Author: swizes
 */

#include "PuckStates.h"


static int rdyS = 0;

Give_New_Puck::Give_New_Puck(Context* con): State::State(con){


	/*if(rdyS == 0){
		rdySend.start(NULL);
		rdyS = 1;
	}*/


	printf("Give_New_Puck()\n");
    HAL *hal = HAL::getInstance();

    //rdySend.setType(1);
    //rdySend.stop();
    //rdySend.start(NULL);

    //Receive FiFo Entry (Puck ID) from Band1
    SerialCommunicationThread *sct = SerialCommunicationThread::getInstance();
    Puck* puck = new Puck();
   // puckStruct puck;
    sct->receivePuck(puck);
    //ser.recvPacket(&puck);

    cout << "Puck ID: " << puck->getId();
    cout << "    Puck Metal: " << puck->isMetal();
    cout << "    Puck Hole: " << puck->isHoleOnTop() << endl;


   // Puck* p = new Puck();
   // p->setPuckFromStruct(puck);
    this->con_ = new Context(puck);
    this->con_->setState(this);

    //rdySend.setType(0);
    //rdySend.stop();
    //rdySend.start(NULL);

    int loop = 1;
	while(loop){
        if( hal->is_startButton_pushed()==0) {
            hal->band_left_normal();
            // Move to State: Working_Band2
            new (this) Working_Band2(this->con_);
            hal->turn_greenLight_off();
            loop = 0;
        }
        if( hal->is_resetButton_pushed()==1){
            hal->band_stop();
            // Move to State: Working_Band2
            new (this) Ready(this->con_);
            loop=0;
        }
    }
}

Give_New_Puck::~Give_New_Puck(){
	printf("~Give_New_Puck()\n");
}



