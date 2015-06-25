/*

 *  CalibrateThread.cpp

 *

 *  Created on: 17.04.2015

 *  Author: Lukas Wendt, Tobias Braack
 *

 *	

 */

#include "CalibrateThread.h"
#include "HAL.h"
#include "./Timer/Timer.h"
#include "ConfigManager.h"
#include <stdlib.h>


#define TIMERSTART 20
#define TIMERSTART_MS TIMERSTART * 1000

CalibrateThread* CalibrateThread::instance_ = NULL;
ConfigManager* configManager = NULL;
bool configLoaded = false;

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
	holeHeight = 490;
	holeHeightMetal = 450;

	// load defaults

	configManager = new ConfigManager();
	if(!configManager->readDefaultConfig()) {
		cout << "Error reading config" << endl;
		return;
	}

	if(!configManager->hasKey("configset"))
	{
		cout << "Config not set!" << endl;
		return;
	}


	std::string outVal;
	bool keyNotFound = false;

	configManager->getConfigValue("L0toHeightFast", &outVal) ? L0toHeightFast = atoi(outVal.c_str()) : keyNotFound = true;
	configManager->getConfigValue("HeighttoGateFast", &outVal) ? HeighttoGateFast = atoi(outVal.c_str()) : keyNotFound = true;
	configManager->getConfigValue("L0toL1Fast", &outVal) ? L0toL1Fast = atoi(outVal.c_str()) : keyNotFound = true;
	configManager->getConfigValue("GatetoL1Fast", &outVal) ? GatetoL1Fast = atoi(outVal.c_str()) : keyNotFound = true;
	configManager->getConfigValue("L0toHeightSlow", &outVal) ? L0toHeightSlow = atoi(outVal.c_str()) : keyNotFound = true;
	configManager->getConfigValue("HeighttoGateSlow", &outVal) ? HeighttoGateSlow = atoi(outVal.c_str()) : keyNotFound = true;
	configManager->getConfigValue("L0toL1Slow", &outVal) ? L0toL1Slow = atoi(outVal.c_str()) : keyNotFound = true;
	configManager->getConfigValue("GatetoL1Slow", &outVal) ? GatetoL1Slow = atoi(outVal.c_str()) : keyNotFound = true;
	configManager->getConfigValue("noPuckHeight", &outVal) ? noPuckHeight = atoi(outVal.c_str()) : keyNotFound = true;

	configManager->getConfigValue("band", &outVal) ? band = atoi(outVal.c_str()) : keyNotFound = true;

	configManager->getConfigValue("bigPuck", &outVal) ? bigPuck = atoi(outVal.c_str()) : keyNotFound = true;
	configManager->getConfigValue("smallPuck", &outVal) ? smallPuck = atoi(outVal.c_str()) : keyNotFound = true;
	configManager->getConfigValue("holeHeight", &outVal) ? holeHeight = atoi(outVal.c_str()) : keyNotFound = true;
	configManager->getConfigValue("holeHeightMetal", &outVal) ? holeHeight = atoi(outVal.c_str()) : keyNotFound = true;
	configManager->getConfigValue("scaleSlowToFast", &outVal) ? scaleSlowToFast = strtod(outVal.c_str(), NULL) : keyNotFound = true;
	configManager->getConfigValue("scaleFastToSlow", &outVal) ?	scaleFastToSlow = strtod(outVal.c_str(), NULL) : keyNotFound = true;
	
	if(keyNotFound) {
		cout << "Error! Key not found!" << endl;
	} else {
		configLoaded = true;
	}

}

CalibrateThread::~CalibrateThread() {
	cout << "dtor Calibrate" << endl;
}

void CalibrateThread::execute(void*) {

	if(configLoaded) {
		cout << "config loaded, skipping calibration" << endl;
		return;
	}


	cout << "Calibration started" << endl;
	HAL *hal = HAL::getInstance();

	Timer time;
	time.createTimer();

	//Get Height with no Puck in Measurement
	noPuckHeight = hal->get_height_measure();

	struct timespec offset;

	//LO to Height fast
	cout << "Put a Puck in L0" << endl;

	while (hal->is_puck_running_in() == 0) {
	}
	time.setTimer(TIMERSTART,0);
	hal->band_right_normal();
	while (hal->is_puck_in_height_determination() == 0) {
	}
	time.getTime(&offset);
	L0toHeightFast = TIMERSTART_MS - timespecToMs(&offset);

	//Height to Gate fast
	time.stopTimer();
	time.setTimer(TIMERSTART,0);
	while(hal->is_puck_in_gate()==0){}
	hal->open_gate();
	time.getTime(&offset);
	HeighttoGateFast = TIMERSTART_MS - timespecToMs(&offset);
	printf("HeighttoGateFast : %d\n",HeighttoGateFast);


	//Gate to L1 fast
	time.stopTimer();
	time.setTimer(TIMERSTART,0);
	while(hal->is_puck_running_out()==0){}
	time.getTime(&offset);
	GatetoL1Fast = TIMERSTART_MS - timespecToMs(&offset);
	printf("GatetoL1Fast : %d\n",GatetoL1Fast);
	hal->close_gate();
	hal->band_stop();


	//L0 to L1 fast
	cout << "Put a puck in L0" << endl;

	while (hal->is_puck_running_in() == 0) {
	}
	time.stopTimer();
	time.setTimer(TIMERSTART, 0);
	hal->band_right_normal();
	while (hal->is_puck_in_height_determination() == 0) {
	}
	while (hal->is_puck_in_height_determination() == 1) {
	}
	while(hal->is_puck_in_gate()==0){}
	hal->open_gate();

	while (hal->is_puck_running_out() == 0) {
	}
	time.getTime(&offset);
	L0toL1Fast = TIMERSTART_MS-timespecToMs(&offset);
	printf("L0toL1Fast : %d\n",L0toL1Fast);
	hal->close_gate();
	hal->band_stop();


	//LO to Height Slow
	cout << "Put puck in L0" << endl;

	while (hal->is_puck_running_in() == 0) {
	}
	time.stopTimer();
	time.setTimer(TIMERSTART, 0);
	hal->band_right_slowly();
	while (hal->is_puck_in_height_determination() == 0) {
	}
	time.getTime(&offset);
	L0toHeightSlow = TIMERSTART_MS - timespecToMs(&offset);

//	cout << "Put a puck in L0" << endl;
//	while(hal->is_puck_running_in()==0){}


	//Height to Gate slow
	time.stopTimer();
	time.setTimer(TIMERSTART,0);
	while(hal->is_puck_in_gate()==0){}
	time.getTime(&offset);
	HeighttoGateSlow = TIMERSTART_MS-timespecToMs(&offset);
	printf("HeighttoGateSlow : %d\n",HeighttoGateSlow);
	hal->open_gate();


	//Gate to Exit
	time.stopTimer();
	time.setTimer(TIMERSTART,0);
	while(hal->is_puck_running_out()==0){}
	time.getTime(&offset);
	GatetoL1Slow = TIMERSTART_MS - timespecToMs(&offset);
	printf("GatetoL1Slow : %d\n",GatetoL1Slow);
	hal->close_gate();
	hal->band_stop();

	//L0 to L1 slow
	cout << "Put a puck in L0" << endl;
	while (hal->is_puck_running_in() == 0) {
	}
	time.stopTimer();
	time.setTimer(TIMERSTART, 0);
	hal->band_right_slowly();

	while(hal->is_puck_in_gate()==0){}
	hal->open_gate();


	while (hal->is_puck_running_out() == 0) {
	}
	hal->close_gate();
	time.getTime(&offset);
	L0toL1Slow = TIMERSTART_MS - timespecToMs(&offset);
	printf("L0toL1Slow : %d\n", L0toL1Slow);
	hal->band_stop();


	/* Height measurements */

	cout << "Put a Small puck in L0" << endl;
	while(hal->is_puck_running_in()==0){}
	hal->band_right_normal();
	while(hal->is_puck_in_height_determination()==0){}
	smallPuck = getMeanValueHeight();
	printf("smallPuk : %d\n",smallPuck);

	while(hal->is_slide_full()==0){}
	hal->band_stop();

	cout << "Put a Big puck in L0" << endl;
	while(hal->is_puck_running_in()==0){}
	hal->band_right_normal();
	while(hal->is_puck_in_height_determination()==0){}
	bigPuck = getMeanValueHeight();
	printf("bigPuk : %d\n",bigPuck);

	while(hal->is_slide_full()==0){}
	hal->band_stop();


	//Hole measurement
	cout << "Put a non Metal Puck with Hole on Top" << endl;
	while(hal->is_puck_running_in()==0){}
	hal->band_right_normal();
	while(hal->is_puck_in_height_determination()==0){}
	hal->band_stop();

	holeHeight = getMeanValueHeight();
	hal->band_right_normal();

	while(hal->is_slide_full()==0){}
	hal->band_stop();

	cout << "Put a Metal Puck with Hole on Top" << endl;
	while(hal->is_puck_running_in()==0){}
	hal->band_right_normal();
	while(hal->is_puck_in_height_determination()==0){}
	hal->band_stop();

	holeHeightMetal = getMeanValueHeight();
	hal->band_right_normal();

	while(hal->is_slide_full()==0){}
	hal->band_stop();


	scaleFastToSlow = ((double)L0toL1Slow)/((double)L0toL1Fast);
	scaleSlowToFast = ((double)L0toL1Fast)/((double)L0toL1Slow);

	cout << "Push Start Button for Band1 or Stop Button for Band2" << endl;
	int run = 1;
	while(run){
		if(hal->is_startButton_pushed()==0){
			band=0;
			run=0;
			cout << "set as band 0" << endl;
		}
		if(hal->is_stopButton_pushed()==1){
			band=1;
			run=0;
			cout << "set as band 1" << endl;
		}
	}


	saveConfig();

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

void CalibrateThread::saveConfig() {
	char buf [33];

	configManager->setConfigValue("L0toHeightFast", std::string(itoa(L0toHeightFast, buf,10)));
	configManager->setConfigValue("HeighttoGateFast", std::string(itoa(HeighttoGateFast, buf,10)));
	configManager->setConfigValue("L0toL1Fast", std::string(itoa(L0toL1Fast, buf,10)));
	configManager->setConfigValue("GatetoL1Fast", std::string(itoa(GatetoL1Fast, buf,10)));
	configManager->setConfigValue("L0toHeightSlow", std::string(itoa(L0toHeightSlow, buf,10)));
	configManager->setConfigValue("HeighttoGateSlow", std::string(itoa(HeighttoGateSlow, buf,10)));
	configManager->setConfigValue("L0toL1Slow", std::string(itoa(L0toL1Slow, buf,10)));
	configManager->setConfigValue("GatetoL1Slow", std::string(itoa(GatetoL1Slow, buf,10)));
	configManager->setConfigValue("noPuckHeight", std::string(itoa(noPuckHeight, buf,10)));
	configManager->setConfigValue("band", std::string(itoa(band, buf,10)));
	configManager->setConfigValue("bigPuck", std::string(itoa(bigPuck, buf,10)));
	configManager->setConfigValue("smallPuck", std::string(itoa(smallPuck, buf,10)));
	configManager->setConfigValue("holeHeight", std::string(itoa(holeHeight, buf,10)));
	configManager->setConfigValue("holeHeightMetal", std::string(itoa(holeHeightMetal, buf,10)));
	sprintf(buf,"%.12f",scaleSlowToFast);
	configManager->setConfigValue("scaleSlowToFast", std::string(buf));
	sprintf(buf,"%.12f",scaleFastToSlow);
	configManager->setConfigValue("scaleFastToSlow", std::string(buf));
	configManager->setConfigValue("configset", "1");


	if(!configManager->writeDefaultConfig())
	{
		cout << "error writing config file!" << endl;
	}

}

int CalibrateThread::getMeanValueHeight(){

	HAL *hal = HAL::getInstance();
	int height = 0;
	for(int i = 0; i  < 5;i++){
		height += hal->get_height_measure();
	}
	height = height/5;
	return height;
}
