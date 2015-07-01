/* 
 * @file    main.cpp
 * @author  Simon Brummer
 * @version 0.2
 * @desc    Demoprojekt fuer das erste SE2 Tutorium.
 *          Das Projekt darf gerne die Basis fuer euer eigentliches Projekt sein
 *          da, hier bereits alles Grundlegende Konfiguriert ist.
 */

//#define SIMULATION  // #define Auskommentieren falls mit der Simulation gearbeitet wird.

#include <cstdlib>
#include <iostream>
#include "./Tests/Hal_Test_Thread.h"
//#include "Hal_Test_Thread.h"
#include "lib/HWaccess.h"
#include "Serial.h"
#include "Threads/CommunicationThread.h"
#include "states/PuckStates.h"
#include "Threads/CalibrateThread.h"
#include "Dispatcher.h"
#include "State.cpp"
#include "HAL.h"
#include "states/ReadySend.h"
#include "Threads/DispatcherThread.h"
#include "Threads/Blink_ThreadRed.h"
#include "BandController.h"
#include "Tests/BlinkTest.h"
#include "Tests/Timer_Test_Thread.h"

using namespace std;

int main(int argc, char *argv[]) {
	printf("Version 0.9\n");
    // Baut Verbindung zu Simulation auf
	#ifdef SIMULATION
        IOaccess_open();
		cout << "WARNING: SYSTEM IN SIMULATION!!!" << endl;
    #endif
	//RUN Calibration

	Timer_Test_Thread ttest;
	cout << "starte Timer Test Thread" << endl;
	ttest.start(NULL);
/*
	TestClass *tc;
	ttest.getTestClass(tc);
	ttest.killTestClass(tc);
*/
	ttest.join();
	return 0;

	HAL *hal = HAL::getInstance();
	CalibrateThread *cal = CalibrateThread::getInstance();
	/*
	int resetCounter = 0;
	//EINRICHBETRIEB
	if(hal->is_startButton_pushed()) {
		cout << "Press 2 times Reset Button in 10 seconds for Calibration" << endl;
		Timer *timer = new Timer();
		timer->setTimer(10,0);
		timer->waitForTimeOut();
		if(hal->getResetCounter() == 2){
				cal->start(NULL);
				cal->join();
				cout << "Calibration is done!" << endl;
			} else {
				cout << "Timeout, switching to normal mode" << endl;
			}
		}
	*/
	//CalibrateThread *cal = CalibrateThread::getInstance();
	cal->start(NULL);
	cal->join();
	cout << "cal done" << endl;
	
    /*Serielle Verbindung funkitoniert nur wenn sich System nicht in der Simulation befindet
    /dev/ser1 steht nicht zur Verfuegung. 		*/

	DispatcherThread dspt;
	dspt.start(NULL);


	BandController* bc = BandController::getInstance();
	bc->refreshBand();


	cout << "Vor Start der FSM" << endl;
	cout << "-----------------------------------" << endl;
	
	if(!cal->isBand()){//is band1!<
//		State* s = new Ready(NULL);
		new Ready(NULL);
	}else{
//		State* state = new Give_New_Puck(NULL);
		new Give_New_Puck(NULL);
	}


	dspt.join();

		//Hal_Test_Thread htt;
		//htt.start(NULL);
		//htt.join();



    #ifdef SIMULATION
       IOaccess_close();
    #endif

    return EXIT_SUCCESS;
}
