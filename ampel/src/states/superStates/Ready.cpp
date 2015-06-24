/*
 * Ready.cpp
 *
 *  Created on: 02.06.2015
 *      Author: swizes
 */

#include "PuckStates.h"
#include "PuckLifcycleFSM.h"

Ready::Ready(Context* con): State::State(con){
	CalibrateThread *cal = CalibrateThread::getInstance();
	//entry:
		//SET isBand2 ? 1 : 0;
	//do:
//   printf("Ready() as Band:%d\n",cal->isBand()+1);
	cout << "Ready" << endl;

	cout << "-----------------------------------" << endl;
    //Context* context = new Context();
    this->con_ = new Context();
    this->con_->setState(this);

    if(!cal->isBand()){ //Band 1
        Dispatcher* dsp = Dispatcher::getInstance();
        dsp->addListeners( this->con_, RUNNING_IN_TRUE);
    }
	HAL *hal = HAL::getInstance();
    bool run = 1;
    while(run){
		cout << "Double Click" << endl;
		while( hal->is_resetButton_pushed() == 0){}
		cout << "pressed 1" << endl;
		delay(100);
		while( hal->is_resetButton_pushed() == 1){}
		Timer *timer = new Timer();
		timer->setTimer(0,500000000);
		cout << "pressed 0" << endl;
		while( hal->is_resetButton_pushed() == 0 ){}
		struct timespec time;
		timer->getTime(&time);
		if(time.tv_nsec != 0){
			run = 0;
		}
    }
    cout << "pressed 1" << endl;
    delay(100);
    while( hal->is_resetButton_pushed() == 1){}
    cout << "pressed 0" << endl;




	
}

Ready::~Ready(){
	printf("~Ready()\n");
}

void Ready::Running_In_true(void){

	BandController* bc = BandController::getInstance();
	HAL *hal = HAL::getInstance();
	if(bc->getPuckCounter() == MAX_PUCKS){
			new (this) Error_Handling(this->con_);
	} else {
				Dispatcher* dsp = Dispatcher::getInstance();
				dsp->remListeners( this->con_, RUNNING_IN_TRUE);
			    // Move to State: Working_Band1
			//	new (this) Working_Band1(this->con_);
				PuckLifcycleFSM* pfsm = new PuckLifcycleFSM();
				pfsm->start(this->con_);
				//Switch To Ready
				new (this) Ready(NULL);

			}

		}

void Ready::calibration(){
	CalibrateThread *cal = CalibrateThread::getInstance();
	cal->start(NULL);
	cal->join();
}




