/*

 *  CalibrateThread.cpp

 *

 *  Created on: 17.04.2015

 *  Author: Lukas Wendt

 *

 *	

 */
#include "CalibrateThread.h"

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
	configManager->getConfigValue("HeightToGateFast", &outVal) ? HeightToGateFast = atoi(outVal.c_str()) : keyNotFound = true;
	configManager->getConfigValue("L0toL1Fast", &outVal) ? L0toL1Fast = atoi(outVal.c_str()) : keyNotFound = true;
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
	configManager->getConfigValue("scaleSlowToFast", &outVal) ? scaleSlowToFast = atof(outVal.c_str()) : keyNotFound = true;
	configManager->getConfigValue("scaleFastToSlow", &outVal) ?	scaleFastToSlow = atof(outVal.c_str()) : keyNotFound = true;
	configManager->getConfigValue("L0toHeightFast", &outVal) ? L0toHeightFast = atoi(outVal.c_str()) : keyNotFound = true;
	configManager->getConfigValue("HeightToMetalFast", &outVal) ? HeightToMetalFast = atoi(outVal.c_str()) : keyNotFound = true;
	configManager->getConfigValue("MetalToIsInGateFast", &outVal) ? MetalToIsInGateFast = atoi(outVal.c_str()) : keyNotFound = true;
	configManager->getConfigValue("InGateToSlideFast", &outVal) ? InGateToSlideFast = atoi(outVal.c_str()) : keyNotFound = true;
	configManager->getConfigValue("OutGateToL1Fast", &outVal) ? OutGateToL1Fast = atoi(outVal.c_str()) : keyNotFound = true;
	configManager->getConfigValue("OutGateToL1Fast2SD", &outVal) ? OutGateToL1Fast2SD = atoi(outVal.c_str()) : keyNotFound = true;
	configManager->getConfigValue("HeightToGateFast", &outVal) ?	HeightToGateFast = atoi(outVal.c_str()) : keyNotFound = true;
	configManager->getConfigValue("L0toHeightFast2SD", &outVal) ? L0toHeightFast2SD = atoi(outVal.c_str()) : keyNotFound = true;
	configManager->getConfigValue("HeightToMetalFast2SD", &outVal) ? HeightToMetalFast2SD = atoi(outVal.c_str()) : keyNotFound = true;
	configManager->getConfigValue("MetalToIsInGateFast2SD", &outVal) ? MetalToIsInGateFast2SD = atoi(outVal.c_str()) : keyNotFound = true;
	configManager->getConfigValue("InGateToSlideFast2SD", &outVal) ?	InGateToSlideFast2SD = atoi(outVal.c_str()) : keyNotFound = true;
	configManager->getConfigValue("OutGateToL1Fast2SD", &outVal) ? OutGateToL1Fast2SD = atoi(outVal.c_str()) : keyNotFound = true;
	configManager->getConfigValue("HeightToGateFast2SD", &outVal) ? HeightToGateFast2SD = atoi(outVal.c_str()) : keyNotFound = true;
	configManager->getConfigValue("L0toL1Fast2SD", &outVal) ? L0toL1Fast2SD = atoi(outVal.c_str()) : keyNotFound = true;
	
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


	cout << "Calibration started" << endl;
	LEDControllerThread *led = LEDControllerThread::getInstance();
	Blink_ThreadGreen *gre = Blink_ThreadGreen::getInstance();
	Blink_ThreadYellow *yel = Blink_ThreadYellow::getInstance();
	Blink_ThreadRed *red = Blink_ThreadRed::getInstance();
	Blink_ThreadReset *res = Blink_ThreadReset::getInstance();
	Blink_ThreadStart *start = Blink_ThreadStart::getInstance();
	HAL *hal = HAL::getInstance();
	red->setLED(50,200000);
	delay(200);
	yel->setLED(50,200000);
	delay(200);
	gre->setLED(50,200000);
	delay(200);
	start->setLED(50,200000);
	delay(200);
	res->setLED(50,200000);

	Timer time;
	Timer time2;
	time.createTimer();

	//Get Height with no Puck in Measurement
	noPuckHeight = hal->get_height_measure();

	struct timespec offset;

	//L0 to L1
	for (int i = 0; i < 3;i++){
		cout << "Put a Metall puck in L0" << endl;

		while (hal->is_puck_running_in() == 0) {}
		time.stopTimer();
		time.setTimer(TIMERSTART, 0);
		time2.stopTimer();
		time2.setTimer(TIMERSTART, 0);

		hal->band_right_normal();

		while (hal->is_puck_in_height_determination() == 0){}
		time.getTime(&offset);
		L0toHeightFastAr[i] = TIMERSTART_MS-timespecToMs(&offset);
		time.stopTimer();
		time.setTimer(TIMERSTART, 0);
		hal->open_gate();
		while(hal->is_metal_detected()==0){}
		time.getTime(&offset);
		HeightToMetalFastAr[i] = TIMERSTART_MS-timespecToMs(&offset);
		time.stopTimer();
		time.setTimer(TIMERSTART, 0);
		while(hal->is_puck_in_gate()==0){}
		time.getTime(&offset);
		MetalToIsInGateFastAr[i] = TIMERSTART_MS-timespecToMs(&offset);
		time.stopTimer();
		time.setTimer(TIMERSTART, 0);

		while(hal->is_puck_in_gate()==1){}
		delay(300);
		hal->close_gate();

		while (hal->is_puck_running_out() == 0) {}
		time2.getTime(&offset);
		L0toL1FastAr[i] = TIMERSTART_MS-timespecToMs(&offset);
		time.getTime(&offset);
		OutGateToL1FastAr[i] = TIMERSTART_MS-timespecToMs(&offset);
		//time.setTimer(TIMERSTART, 0);

		printf("L0toL1Fast : %d\n",L0toL1FastAr[i]);

		hal->band_stop();

		HeightToGateFastAr[i] = HeightToMetalFastAr[i] + MetalToIsInGateFastAr[i] ;
	}


	cout << "Put a puck in L0" << endl;
	while(hal->is_puck_running_in()==0){}

	//LO to Height Slow
	time.stopTimer();
	time.setTimer(TIMERSTART,0);
	hal->band_right_slowly();
	while(hal->is_puck_in_height_determination()==0){}
	time.getTime(&offset);
	L0toHeightSlow = TIMERSTART_MS-timespecToMs(&offset);
	printf("L0ToHeightSlow : %d\n",L0toHeightSlow);

	//Height to Gate
	time.stopTimer();
	time.setTimer(TIMERSTART,0);
	while(hal->is_puck_in_gate()==0){}
	time.getTime(&offset);
	HeighttoGateSlow = TIMERSTART_MS-timespecToMs(&offset);
	hal->open_gate();
	printf("HeighttoGateSlow : %d\n",HeighttoGateSlow);


	//Gate to RunningOut Slow
	while(hal->is_puck_in_gate() == 1){}
	time.stopTimer();
	time.setTimer(TIMERSTART,0);
	delay(600);
	hal->close_gate();

	while (hal->is_puck_running_out() == 0) {}

	time.getTime(&offset);
	GatetoL1Slow = TIMERSTART_MS-timespecToMs(&offset);
	printf("GateToL1Slow : %d\n",GatetoL1Slow);
	hal->band_stop();


	//L0 to L1

	cout << "Put a puck in L0" << endl;
	while (hal->is_puck_running_in() == 0) {
	}
	time.stopTimer();
	time.setTimer(TIMERSTART, 0);
	hal->band_right_slowly();

	while(hal->is_puck_in_gate()==0){}
	hal->open_gate();
	while(hal->is_puck_in_gate()==1){}
	delay(600);
	hal->close_gate();

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


	//Locherkennung
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


	
	saveCalcMean();
	scaleFastToSlow = ((double)L0toL1Slow)/((double)L0toL1Fast);
	scaleSlowToFast = ((double)L0toL1Fast)/((double)L0toL1Slow);
	HeightToGateFast2SD = HeightToMetalFast2SD + MetalToIsInGateFast2SD;
	InGateToSlideFast  = -1;
	InGateToSlideFast2SD  = -1;
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

void CalibrateThread::msToTimespec(int ms, struct timespec * time) {
	uint64_t sec = ms/1000;
	uint64_t nsec = (ms-sec*1000)*1000000;
	time->tv_sec = sec;
	time->tv_nsec = nsec;
}

void CalibrateThread::saveConfig() {
	char buf [33];

	configManager->setConfigValue("L0toHeightFast", std::string(itoa(L0toHeightFast, buf,10)));
	configManager->setConfigValue("HeightToGateFast", std::string(itoa(HeightToGateFast, buf,10)));
	configManager->setConfigValue("L0toL1Fast", std::string(itoa(L0toL1Fast, buf,10)));
	//configManager->setConfigValue("GatetoL1Fast", std::string(itoa(GatetoL1Fast, buf,10)));
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
	sprintf(buf,"%.12f",scaleSlowToFast);configManager->setConfigValue("scaleSlowToFast", std::string(buf));
	sprintf(buf,"%.12f",scaleFastToSlow);configManager->setConfigValue("scaleFastToSlow", std::string(buf));
	configManager->setConfigValue("configset", "1");
	configManager->setConfigValue("L0toHeightFast", std::string(itoa(L0toHeightFast, buf,10)));
	configManager->setConfigValue("HeightToMetalFast", std::string(itoa(HeightToMetalFast, buf,10)));
	configManager->setConfigValue("MetalToIsInGateFast", std::string(itoa(MetalToIsInGateFast, buf,10)));
	configManager->setConfigValue("InGateToSlideFast", std::string(itoa(InGateToSlideFast, buf,10)));
	configManager->setConfigValue("OutGateToL1Fast", std::string(itoa(OutGateToL1Fast, buf,10)));
	configManager->setConfigValue("HeightToGateFast", std::string(itoa(HeightToGateFast, buf,10)));
//	configManager->setConfigValue("GatetoL1Fast", std::string(itoa(GatetoL1Fast, buf,10)));
	configManager->setConfigValue("L0toHeightFast2SD", std::string(itoa(L0toHeightFast2SD, buf,10)));
	configManager->setConfigValue("HeightToMetalFast2SD", std::string(itoa(HeightToMetalFast2SD, buf,10)));
	configManager->setConfigValue("MetalToIsInGateFast2SD", std::string(itoa(MetalToIsInGateFast2SD, buf,10)));
	configManager->setConfigValue("InGateToSlideFast2SD", std::string(itoa(InGateToSlideFast2SD, buf,10)));
	configManager->setConfigValue("OutGateToL1Fast2SD", std::string(itoa(OutGateToL1Fast2SD, buf,10)));
	configManager->setConfigValue("HeightToGateFast2SD", std::string(itoa(HeightToGateFast2SD, buf,10)));
	configManager->setConfigValue("L0toL1Fast2SD", std::string(itoa(L0toL1Fast2SD, buf,10)));
	//configManager->setConfigValue("GatetoL1Fast2SD", std::string(itoa(GatetoL1Fast2SD, buf,10)));



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


int CalibrateThread::mean(int *ar, int length){
	int sum = 0;
	for(int i = 0; i < length;i++){
		sum += ar[i];
	}
	return sum/length;

}

void CalibrateThread::saveCalcMean(){

	L0toHeightFast = mean(L0toHeightFastAr,3);
	L0toHeightFast2SD = 2*calcStandardDeviation(L0toHeightFast,L0toHeightFastAr,3);
	HeightToMetalFast = mean(HeightToMetalFastAr,3);
	HeightToMetalFast2SD = 2*calcStandardDeviation(HeightToMetalFast,HeightToMetalFastAr,3);
	MetalToIsInGateFast= mean(MetalToIsInGateFastAr,3);
	MetalToIsInGateFast2SD = 2*calcStandardDeviation(MetalToIsInGateFast,MetalToIsInGateFastAr,3);
	InGateToSlideFast= mean(InGateToSlideFastAr,3);
	InGateToSlideFast2SD = 2*calcStandardDeviation(InGateToSlideFast,InGateToSlideFastAr,3);
	OutGateToL1Fast= mean(OutGateToL1FastAr,3);
	OutGateToL1Fast2SD = 2*calcStandardDeviation(OutGateToL1Fast,OutGateToL1FastAr,3);
	HeightToGateFast= mean(HeightToGateFastAr,3);
	HeightToGateFast2SD = 2*calcStandardDeviation(HeightToGateFast,HeightToGateFastAr,3);
	L0toL1Fast= mean(L0toL1FastAr,3);
	L0toL1Fast2SD = 2*calcStandardDeviation(L0toL1Fast,L0toL1FastAr,3);

}

int CalibrateThread::calcStandardDeviation(int mean, int *ar, int length){
	int abw = 0;
	for(int i = 0; i < length;i++){
		abw += abs(mean-ar[i]);
	}
	abw /= length;
	abw = sqrt(abw);
	return abw;
}
// Help Function for State to Set Timeout to Next Sensor
int CalibrateThread::setTimeout(Timer *timer,int timeout, int sd2){
	timer->createTimer();
	timeout = timeout+sd2; // Timeout + 2Standard Deviation
	struct timespec *t;
	msToTimespec(timeout,t);
	//timer->waitForTimeout(t->tv_sec,t->tv_nsec);
	cout << "Puck missing" << endl;
}

//CheckTimeout
int CalibrateThread::checkTimeout(Timer *timer, int sd2){
	struct timespec *t;
	timer->getTime(t);
	int ms = timespecToMs(t);
	if(ms > sd2){
		cout << "Puck too early" << endl;
	}
}

