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
#include "./Timer/Timer.h"


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
	while(hal->is_puck_in_height_determination()==0){}
	time.getTime(&offset);
	L0toHeightFast = 10000-timespecToMs(&offset);
	printf("L0ToHeightFast : %d\n",L0toHeightFast);
	hal->open_gate();

	//Height to Gate
	time.setTimer(10,0);
	while(hal->is_puck_in_gate()==0){}
	time.getTime(&offset);
	HeighttoGateFast = 10000-timespecToMs(&offset);
	printf("HeighttoGateFast : %d\n",HeighttoGateFast);
	hal->close_gate();
	while(hal->is_slide_full()==0){}
	hal->band_stop();



	//L0 to L1


	cout << "Put a puck in L0" << endl;
	while(hal->is_puck_running_in()==0){}
	time.setTimer(10,0);
	hal->band_right_normal();
	hal->open_gate();

	while(hal->is_puck_running_out()==0){}
	time.getTime(&offset);
	L0toL1Fast = 10000-timespecToMs(&offset);
	printf("L0toL1Fast : %d\n",L0toL1Fast);
	hal->band_stop();
	hal->close_gate();


		cout << "Put a puck in L0" << endl;
		while(hal->is_puck_running_in()==0){}

		//LO to Height
		time.setTimer(10,0);
		hal->band_right_slowly();
		while(hal->is_puck_in_height_determination()==0){}
		time.getTime(&offset);
		L0toHeightSlow = 10000-timespecToMs(&offset);
		printf("L0ToHeighSlow : %d\n",L0toHeightSlow);
		hal->open_gate();

		//Height to Gate
		time.setTimer(10,0);
		while(hal->is_puck_in_gate()==0){}
		time.getTime(&offset);
		HeighttoGateSlow = 10000-timespecToMs(&offset);
		printf("HeighttoGateSlow : %d\n",HeighttoGateSlow);
		hal->close_gate();
		while(hal->is_slide_full()==0){}
		hal->band_stop();



		//L0 to L1


		cout << "Put a puck in L0" << endl;
		while(hal->is_puck_running_in()==0){}
		time.setTimer(10,0);
		hal->band_right_slowly();
		hal->open_gate();

		while(hal->is_puck_running_out()==0){}
		time.getTime(&offset);
		L0toL1Slow = 10000-timespecToMs(&offset);
		printf("L0toL1Slow : %d\n",L0toL1Slow);
		hal->band_stop();
		hal->close_gate();


	time.deleteTimer();
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



