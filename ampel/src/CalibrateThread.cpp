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
#include "Timer.h"


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

	Timer time;
	time.createTimer();




	struct timespec offset;
	cout << "Put a puck in L0" << endl;
	while(hal->is_puck_running_in()==0){}

	//LO to Height
	time.setTimer(10,0);
	hal->band_right_normal();
	while(hal->is_puck_in_height_determination()==0)
	time.getTime(&offset);
	L0toHeightFast = timespecToMs(&offset);
	cout << "L0ToHeight: " + L0toHeightFast << endl;
	hal->open_gate();

	//Height to Gate
	time.setTimer(10,0);
	while(hal->is_puck_in_gate()==0)
	time.getTime(&offset);
	HeighttoGateFast = timespecToMs(&offset);
	hal->close_gate();
	while(hal->is_slide_full()==0)
	cout << "stop"<< endl;
	hal->band_stop();






	time.deleteTimer();

	cout << "Put a puck in L0" << endl;
	while(hal->is_puck_running_in()==0){}
	time.setTimer(10,0);
	hal->band_right_normal();
	hal->open_gate();

	while(hal->is_puck_running_out()==0){}
	time.getTime(&offset);
	L0toL1Fast = timespecToMs(&offset);
	hal->band_stop();
	hal->close_gate();


	//while(hal->is_puck_in_height_determination()==0){}
	//TIME

	//TIME

	cout << "Close execute" << endl;

}





void CalibrateThread::shutdown(){
    cout << "Communication Test shutdown" << endl;

}

int CalibrateThread::timespecToMs(struct timespec *time){
	int nsec = time->tv_nsec;
	int sec = time->tv_sec;
	return sec * 1000 + nsec/1000/1000;
}

