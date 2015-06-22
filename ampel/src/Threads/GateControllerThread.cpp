/*

 * CommunnicationThread.cpp

 *

 *  Created on: 17.04.2015

 *  Author: lukasTest, Tobi

 *

 *	

 */



#include "GateControllerThread.h"





//Only One PC can be the SENDER! 

//#define SENDER

GateControllerThread*  GateControllerThread::instance_ = NULL;

GateControllerThread* GateControllerThread::getInstance(){
	static pthread_mutex_t mtx_ = PTHREAD_MUTEX_INITIALIZER;

	if (instance_ == NULL) {
		pthread_mutex_lock(&mtx_);
		if (instance_ == NULL) {
			instance_ = new GateControllerThread();
		}
		pthread_mutex_unlock(&mtx_);
	}
	return instance_;
}



GateControllerThread::GateControllerThread(void) {
	timer = new Timer();
	cout << "ctor GateControllerThread" << endl;

}



GateControllerThread::~GateControllerThread() {

	// TODO Auto-generated destructor stub

	cout << "dtor GateControllerThread" << endl;
}



void GateControllerThread::execute(void*){
	run = 1;
	HAL *hal = HAL::getInstance();
	hal->open_gate();
	for(int i = 0; i < count; i++) {
		timer = new Timer();
		timer->waitForTimeOut(1,500000000);
	}


	hal->close_gate();
	run = 0;


}

void GateControllerThread::setTimer(void){

	if(!run){
		this->start(NULL);
		count = 1;
	}else{
		count++;
	}



}





void GateControllerThread::shutdown(){
    cout << "GateController shutdown" << endl;

}

