/*

 *  CalibrateThread.cpp

 *

 *  Created on: 17.04.2015

 *  Author: lukasTest, Tobi

 *

 *	

 */



#include "CalibrateThread.h"



//Only One PC can be the SENDER! 

#define SENDER





CalibrateThread::CalibrateThread(void) {

	cout << "ctor Calibrate" << endl;

}



CalibrateThread::~CalibrateThread() {

	// TODO Auto-generated destructor stub

	cout << "dtor Calibrate" << endl;
}



void CalibrateThread::execute(void*){


	cout << "Calibration started" << endl;


}





void CalibrateThread::shutdown(){
    cout << "Communication Test shutdown" << endl;

}

