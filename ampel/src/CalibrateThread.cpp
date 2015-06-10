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

CalibrateThread* CalibrateThread::instance_ = NULL;
#include "Timer.h"
#define TIMERSTART 20

/**
 * c'tor for the Thread-safe singleton Calibration implementation
 * @param none
 * @return A Pointer to the Singleton Calibration Object
 */
CalibrateThread* CalibrateThread::getInstance() {
	static pthread_mutex_t mtx_ = PTHREAD_MUTEX_INITIALIZER;

	if (instance_ == NULL) {
		pthread_mutex_lock(&mtx_);
		if (instance_ == NULL) {
			instance_ = new CalibrateThread();
		}
		pthread_mutex_unlock(&mtx_);
	}
	return instance_;
}

CalibrateThread::CalibrateThread() {

	cout << "ctor Calibrate" << endl;
	bigPuck = 1600;
	smallPuck = 1299;

}

CalibrateThread::~CalibrateThread() {

	// TODO Auto-generated destructor stub

	cout << "dtor Calibrate" << endl;
}

void CalibrateThread::execute(void*) {

	cout << "Calibration started" << endl;
	HAL *hal = HAL::getInstance();

	Timer time;
	time.createTimer();

	//Get Height with no Puck in Measurement
	noPuckHeight = hal->get_height_measure();

	struct timespec offset;/*
	cout << "Put a Puck in L0" << endl;
	while (hal->is_puck_running_in() == 0) {
	}

	//LO to Height
	time.setTimer(10, 0);
	time.setTimer(TIMERSTART,0);
	hal->band_right_normal();
	while (hal->is_puck_in_height_determination() == 0) {
	}
	time.getTime(&offset);
	L0toHeightFast = 10000 - timespecToMs(&offset);

	printf("L0ToHeightFast : %d\n", L0toHeightFast);
	hal->open_gate();

	//Height to Gate
	time.setTimer(10, 0);
	while (hal->is_puck_in_gate() == 0) {
	}
	time.getTime(&offset);
	HeighttoGateFast = 10000 - timespecToMs(&offset);
	printf("HeighttoGateFast : %d\n", HeighttoGateFast);
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
	while (hal->is_slide_full() == 0) {
	}
	hal->band_stop();

	//L0 to L1

	cout << "Put a puck in L0" << endl;

	while (hal->is_puck_running_in() == 0) {
	}
	time.setTimer(10, 0);

	while(hal->is_puck_running_in()==0){}
	time.setTimer(TIMERSTART,0);

	hal->band_right_normal();
	hal->open_gate();

	while (hal->is_puck_running_out() == 0) {
	}
	time.getTime(&offset);

	L0toL1Fast = 10000 - timespecToMs(&offset);
	printf("L0toL1Fast : %d\n", L0toL1Fast);

	L0toL1Fast = TIMERSTART*1000-timespecToMs(&offset);
	printf("L0toL1Fast : %d\n",L0toL1Fast);

	hal->band_stop();
	hal->close_gate();

	cout << "Put puck in L0" << endl;
	while (hal->is_puck_running_in() == 0) {
	}


	//LO to Height
	time.setTimer(10, 0);
	hal->band_right_slowly();
	while (hal->is_puck_in_height_determination() == 0) {
	}
	time.getTime(&offset);
	L0toHeightSlow = 10000 - timespecToMs(&offset);

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




	printf("L0ToHeighSlow : %d\n", L0toHeightSlow);
	hal->open_gate();

	//Height to Gate
	time.setTimer(10, 0);
	while (hal->is_puck_in_gate() == 0) {
	}
	time.getTime(&offset);
	HeighttoGateSlow = 10000 - timespecToMs(&offset);
	printf("HeighttoGateSlow : %d\n", HeighttoGateSlow);
	hal->close_gate();
	while (hal->is_slide_full() == 0) {
	}
	hal->band_stop();

	//L0 to L1

	cout << "Put a puck in L0" << endl;
	while (hal->is_puck_running_in() == 0) {
	}
	time.setTimer(10, 0);
	hal->band_right_slowly();
	hal->open_gate();

	while (hal->is_puck_running_out() == 0) {
	}
	time.getTime(&offset);
	L0toL1Slow = 10000 - timespecToMs(&offset);
	printf("L0toL1Slow : %d\n", L0toL1Slow);
	hal->band_stop();
	hal->close_gate();

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
		hal->close_gate();*/

		cout << "Put a Small puck in L0" << endl;
		while(hal->is_puck_running_in()==0){}
		hal->band_right_normal();
		while(hal->is_puck_in_height_determination()==0){}
		smallPuck = hal->get_height_measure();
		printf("smallPuk : %d\n",smallPuck);
		hal->open_gate();
		while(hal->is_puck_in_gate()==0){}
		hal->close_gate();
		while(hal->is_slide_full()==0){}
		hal->band_stop();

		cout << "Put a Big puck in L0" << endl;
		while(hal->is_puck_running_in()==0){}
		hal->band_right_normal();
		while(hal->is_puck_in_height_determination()==0){}
		bigPuck = hal->get_height_measure();
		printf("bigPuk : %d\n",bigPuck);
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
		//time.setTimer(TIMERSTART,0);
		while(abs(hal->get_height_measure()-first)<5){

		}
		holeHeight = hal->get_height_measure();
		//time.getTime(&offset);
		int diff = offset.tv_nsec;
		cout << diff << endl;
		printf("bigPuk : %d\n",bigPuck);
		hal->open_gate();
		while(hal->is_puck_in_gate()==0){}
		hal->close_gate();
		while(hal->is_slide_full()==0){}
		hal->band_stop();


		//time.deleteTimer();
	//while(hal->is_puck_in_height_determination()==0){}
	//TIME

	//TIME

	cout << "Close execute" << endl;

}

void CalibrateThread::shutdown() {
	cout << "Calibrate Thread shutdown" << endl;

}

int CalibrateThread::timespecToMs(struct timespec *time) {
	int nsec = time->tv_nsec;
	int sec = time->tv_sec;
	return sec * 1000 + nsec / 1000 / 1000;
}
