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
#include "ConfigManager.h"

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
	bigPuck = 1500;
	smallPuck = 1260;
	holeHeight = 500;

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
	

	if(keyNotFound) {
		cout << "Error! Key not found!" << endl;
	} else {
		configLoaded = true;
	}

}

CalibrateThread::~CalibrateThread() {

	// TODO Auto-generated destructor stub

	cout << "dtor Calibrate" << endl;
}

void CalibrateThread::execute(void*) {

	if(configLoaded) {
		cout << "config loaded, skipping calibration" << endl;
		return;
	}

	saveConfig();

	cout << "Calibration started" << endl;
	HAL *hal = HAL::getInstance();

	Timer time;
	time.createTimer();

	//Get Height with no Puck in Measurement
	noPuckHeight = hal->get_height_measure();

	struct timespec offset;

	cout << "Put a Puck in L0" << endl;
	while (hal->is_puck_running_in() == 0) {
	}

	//LO to Height
	time.setTimer(TIMERSTART,0);
	hal->band_right_normal();
	while (hal->is_puck_in_height_determination() == 0) {
	}
	time.getTime(&offset);
	L0toHeightFast = TIMERSTART_MS - timespecToMs(&offset);

	//Height to Gate
	time.stopTimer();
	time.setTimer(TIMERSTART,0);
	while(hal->is_puck_in_gate()==0){}
	time.getTime(&offset);
	HeighttoGateFast = TIMERSTART_MS-timespecToMs(&offset);
	printf("HeighttoGateFast : %d\n",HeighttoGateFast);
	hal->close_gate();
	while (hal->is_slide_full() == 0) {
	}
	hal->band_stop();

	//L0 to L1

	cout << "Put a puck in L0" << endl;

	while (hal->is_puck_running_in() == 0) {
	}
	time.stopTimer();
	time.setTimer(TIMERSTART, 0);

	hal->band_right_normal();
	hal->open_gate();

	while (hal->is_puck_running_out() == 0) {
	}
	time.getTime(&offset);
	L0toL1Fast = TIMERSTART_MS-timespecToMs(&offset);

	printf("L0toL1Fast : %d\n",L0toL1Fast);

	hal->band_stop();
	hal->close_gate();

	cout << "Put puck in L0" << endl;
	while (hal->is_puck_running_in() == 0) {
	}


	//LO to Height
	time.stopTimer();
	time.setTimer(TIMERSTART, 0);
	hal->band_right_slowly();
	while (hal->is_puck_in_height_determination() == 0) {
	}
	time.getTime(&offset);
	L0toHeightSlow = TIMERSTART_MS - timespecToMs(&offset);

	cout << "Put a puck in L0" << endl;
	while(hal->is_puck_running_in()==0){}

	//LO to Height
	time.stopTimer();
	time.setTimer(TIMERSTART,0);
	hal->band_right_slowly();
	while(hal->is_puck_in_height_determination()==0){}
	time.getTime(&offset);
	L0toHeightSlow = TIMERSTART_MS-timespecToMs(&offset);
	printf("L0ToHeightSlow : %d\n",L0toHeightSlow);
	hal->open_gate();

	//Height to Gate
	time.stopTimer();
	time.setTimer(TIMERSTART,0);
	while(hal->is_puck_in_gate()==0){}
	time.getTime(&offset);
	HeighttoGateSlow = TIMERSTART_MS-timespecToMs(&offset);
	printf("HeighttoGateSlow : %d\n",HeighttoGateSlow);
	hal->close_gate();
	while(hal->is_slide_full()==0){}
	hal->band_stop();


	//L0 to L1

	cout << "Put a puck in L0" << endl;
	while (hal->is_puck_running_in() == 0) {
	}
	time.stopTimer();
	time.setTimer(TIMERSTART, 0);
	hal->band_right_slowly();
	hal->open_gate();

	while (hal->is_puck_running_out() == 0) {
	}
	time.getTime(&offset);
	L0toL1Slow = TIMERSTART_MS - timespecToMs(&offset);
	printf("L0toL1Slow : %d\n", L0toL1Slow);
	hal->band_stop();
	hal->close_gate();

	/* Height measurements */

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
	hal->band_stop();

	holeHeight = hal->get_height_measure();
	hal->band_right_normal();
	hal->open_gate();
	while(hal->is_puck_in_gate()==0){}
	hal->close_gate();
	while(hal->is_slide_full()==0){}
	hal->band_stop();

	cout << "Push Start Button for Band1 or Stop Button for Band2" << endl;
	int run = 1;
	while(run){
		if(hal->is_startButton_pushed()==0){
			band=0;
			run=0;
		}
		if(hal->is_stopButton_pushed()==1){
			band=1;
			run=0;
		}
	}




		//time.deleteTimer();
	//while(hal->is_puck_in_height_determination()==0){}
	//TIME

	//TIME
	
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
	configManager->setConfigValue("configset", "1");


	if(!configManager->writeDefaultConfig())
	{
		cout << "error writing config file!" << endl;
	}

}
