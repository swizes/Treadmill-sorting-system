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
#define TIMERSTART 20


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
	time.setTimer(TIMERSTART,0);
	hal->band_right_normal();
	while(hal->is_puck_in_height_determination()==0){}
	time.getTime(&offset);
	L0toHeightFast = TIMERSTART*1000-timespecToMs(&offset);
	printf("L0ToHeightFast : %d\n",L0toHeightFast);
	hal->open_gate();

	//Height to Gate
	time.setTimer(TIMERSTART,0);
	while(hal->is_puck_in_gate()==0){}
	time.getTime(&offset);
	HeighttoGateFast = TIMERSTART*1000-timespecToMs(&offset);
	printf("HeighttoGateFast : %d\n",HeighttoGateFast);
	hal->close_gate();
	while(hal->is_slide_full()==0){}
	hal->band_stop();



	//L0 to L1


	cout << "Put a puck in L0" << endl;
	while(hal->is_puck_running_in()==0){}
	time.setTimer(TIMERSTART,0);
	hal->band_right_normal();
	hal->open_gate();

	while(hal->is_puck_running_out()==0){}
	time.getTime(&offset);
	L0toL1Fast = TIMERSTART*1000-timespecToMs(&offset);
	printf("L0toL1Fast : %d\n",L0toL1Fast);
	hal->band_stop();
	hal->close_gate();


		cout << "Put a puck in L0" << endl;
		while(hal->is_puck_running_in()==0){}

		//LO to Height
		time.setTimer(TIMERSTART,0);
		hal->band_right_slowly();
		while(hal->is_puck_in_height_determination()==0){}
		time.getTime(&offset);
		L0toHeightSlow = TIMERSTART*1000-timespecToMs(&offset);
		printf("L0ToHeighSlow : %d\n",L0toHeightSlow);
		hal->open_gate();

		//Height to Gate
		time.setTimer(TIMERSTART,0);
		while(hal->is_puck_in_gate()==0){}
		time.getTime(&offset);
		HeighttoGateSlow = TIMERSTART*1000-timespecToMs(&offset);
		printf("HeighttoGateSlow : %d\n",HeighttoGateSlow);
		hal->close_gate();
		while(hal->is_slide_full()==0){}
		hal->band_stop();



		//L0 to L1


		cout << "Put a puck in L0" << endl;
		while(hal->is_puck_running_in()==0){}
		time.setTimer(TIMERSTART,0);
		hal->band_right_slowly();
		hal->open_gate();

		while(hal->is_puck_running_out()==0){}
		time.getTime(&offset);
		L0toL1Slow = TIMERSTART*1000-timespecToMs(&offset);
		printf("L0toL1Slow : %d\n",L0toL1Slow);
		hal->band_stop();
		hal->close_gate();

		cout << "Put a Small puck in L0" << endl;
		while(hal->is_puck_running_in()==0){}
		hal->band_right_normal();
		while(hal->is_puck_in_height_determination()==0){}
		smallPuk = hal->get_height_measure();
		printf("smallPuk : %d\n",smallPuk);
		hal->open_gate();
		while(hal->is_puck_in_gate()==0){}
		hal->close_gate();
		while(hal->is_slide_full()==0){}
		hal->band_stop();

		cout << "Put a Big puck in L0" << endl;
		while(hal->is_puck_running_in()==0){}
		hal->band_right_normal();
		while(hal->is_puck_in_height_determination()==0){}
		bigPuk = hal->get_height_measure();
		printf("bigPuk : %d\n",bigPuk);
		hal->open_gate();
		while(hal->is_puck_in_gate()==0){}
		hal->close_gate();
		while(hal->is_slide_full()==0){}
		hal->band_stop();


		//Locherkennung todo delay not ok
		cout << "Put a Puck with Hole on Top" << endl;
		while(hal->is_puck_running_in()==0){}
		hal->band_right_normal();
		while(hal->is_puck_in_height_determination()==0){}
		hal->band_right_slowly();
		int first = hal->get_height_measure();
		time.setTimer(TIMERSTART,0);
		while(abs(hal->get_height_measure()-first)<5){

		}
		holeHeight = hal->get_height_measure();
		time.getTime(&offset);
		int diff = offset.tv_nsec;
		cout << diff << endl;
		printf("bigPuk : %d\n",bigPuk);
		hal->open_gate();
		while(hal->is_puck_in_gate()==0){}
		hal->close_gate();
		while(hal->is_slide_full()==0){}
		hal->band_stop();


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



