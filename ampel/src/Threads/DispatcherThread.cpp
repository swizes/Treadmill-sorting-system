/*

 * CommunnicationThread.cpp

 *

 *  Created on: 17.04.2015

 *  Author: lukasTest, Tobi

 *

 *	

 */



#include "DispatcherThread.h"



//Only One PC can be the SENDER! 

//#define SENDER





DispatcherThread::DispatcherThread(void) {

	cout << "ctor Dispatcher" << endl;

}



DispatcherThread::~DispatcherThread() {

	// TODO Auto-generated destructor stub

	cout << "dtor Dispatcher" << endl;
}



void DispatcherThread::execute(void*){

	Dispatcher *dsp = Dispatcher::getInstance();
	dsp->listenForEvents();

	cout << "EndListenForEvents" << endl;

}





void DispatcherThread::shutdown(){
    cout << "Dispatcher shutdown" << endl;

}

