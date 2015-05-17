/*

 *  CalibrateThread.cpp

 *

 *  Created on: 17.04.2015

 *  Author: Lukas Wendt

 *

 *	

 */



#include "CalibrateThread.h"
#include "HAL.h"


CalibrateThread::CalibrateThread(void) {

	cout << "ctor Calibrate" << endl;

}

CalibrateThread::~CalibrateThread() {

	// TODO Auto-generated destructor stub

	cout << "dtor Calibrate" << endl;
}

void CalibrateThread::execute(void*){

	cout << "Calibration started" << endl;
	HAL *hal = HAL::getInstance();
	while(hal->is_puck_running_in()==0){}
	hal->band_right_normal();
	while(hal->is_puck_in_height_determination()==0){}
	//TIME
	while(hal->is_puck_in_gate()==0){}
	//TIME



}





void CalibrateThread::shutdown(){
    cout << "Communication Test shutdown" << endl;

}

