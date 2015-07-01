/*
 * ESTOPTHREAD.cpp
 *
 *  Created on: 30.06.2015
 *      Author: abl441
 */

#include "E_Stop_Thread.h"
#include <exception>

#define E_STOP 7

int isrChannelPortC = 0;
int isrConnectionPortC = 0;
struct sigevent isrEventPortC;

E_Stop_Thread::E_Stop_Thread() {
	// TODO Auto-generated constructor stub


}

E_Stop_Thread::~E_Stop_Thread() {
	// TODO Auto-generated destructor stub
}

void E_Stop_Thread::execute(void*){

	HAL *hal = HAL::getInstance();
	BandController* bc = BandController::getInstance();

	int pushed = 0;
	while(1){
		if(hal->is_eStopButton_pushed() == 0 && pushed != 1){
			pushed = 1;
			hal->band_stop();
			//cout << "E_StopButton pushed" << endl;
			cout << "Bitte E_Stop rausziehen" << endl;
		}else if (hal->is_eStopButton_pushed() && pushed != 0){
			pushed = 0;
			while(hal->is_resetButton_pushed() == 0){}
			bc->refreshBand();
			//cout << "E_StopButton not pushed" << endl;
		}
	}
}





void E_Stop_Thread::shutdown(){
    cout << "E_Stop_Thread shutdown" << endl;
}
