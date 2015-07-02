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
#include "Threads/DispatcherThread.h"
#include "Threads/Blink_ThreadRed.h"
#include "Threads/LEDControllerThread.h"
#include "BandController.h"
#include "Tests/BlinkTest.h"
#include "Threads/E_Stop_Thread.h"
#include "Tests/Timer_Test_Thread.h"
#include "Threads/TimeoutThread.h"

using namespace std;

int main(int argc, char *argv[]) {
	LEDControllerThread *led = LEDControllerThread::getInstance();
	HAL *hal = HAL::getInstance();
	led->start(NULL);
	CalibrateThread *cal = CalibrateThread::getInstance();

	printf("Version 0.9\n");
    // Baut Verbindung zu Simulation auf
	#ifdef SIMULATION
        IOaccess_open();
		cout << "WARNING: SYSTEM IN SIMULATION!!!" << endl;
    #endif


	//RUN Calibration

		//RUN Calibration
			bool timeOut = false;
			bool startButton = false;
			int loop = 1;
			int resetCounter = 0;
			while (loop) {
				if (!(hal->is_startButton_pushed())) {
					Timer time;
					Timer timer;
					cout << "Timer started" << endl;
					timer.waitForTimeOut(2, 0);
					timer.deleteTimer();

					struct timespec result;
					cout << "Press 2 times Reset Button or Press Start again to skip Calibration" << endl;
					while (hal->is_startButton_pushed() && !timeOut) {
						time.setTimer(5, 0);
						hal->turn_yellowLight_on();

						//nicht gedrueckt
						while (!hal->is_resetButton_pushed() && !timeOut) {

							if (!(hal->is_startButton_pushed())) {
								startButton = true;
								loop = 0;
								hal->turn_yellowLight_off();
								break;
							}


							time.getTime(&result);
							if (result.tv_sec == 0) {
								hal->turn_yellowLight_off();
								hal->turn_greenLight_off();
								hal->turn_redLight_on();
								cout << "Timeout, too late" << endl;
								timeOut = true;
								loop = 0;
								break;
							}
						}

						while (hal->is_resetButton_pushed() && !timeOut && !startButton) {

						}
						if(!timeOut){
							cout << "Button gedrueckt:  " << resetCounter << endl;
						}
						delay(50);
						resetCounter++;
						if (resetCounter == 1) {
							hal->turn_greenLight_on();

						}
						if (resetCounter == 2) {
							hal->turn_yellowLight_off();
							hal->turn_greenLight_off();
							//CalibrateThread *cal1 = CalibrateThread::getInstance();
							cal->start(NULL);
							cal->join();
							cout << "cal done" << endl;
							loop = 0;
							break;
						}
						//if

					} //while start button = 0
				} //if
			} //while loop

    /*Serielle Verbindung funkitoniert nur wenn sich System nicht in der Simulation befindet
    /dev/ser1 steht nicht zur Verfuegung. 		*/

	DispatcherThread dspt;
	E_Stop_Thread estt;

	estt.start(NULL);
	dspt.start(NULL);

	TimeoutThread timeoutThread;
	timeoutThread.start(NULL);

	BandController* bc = BandController::getInstance();
	bc->refreshBand();


	cout << "Vor Start der FSM" << endl;
	cout << "-----------------------------------" << endl;
	

	if(timeOut == true) {
		new Error_Handling(NULL);
	} else if(!cal->isBand()){//is band1!<
//		State* s = new Ready(NULL);
		new Ready(NULL);
	}else{
//		State* state = new Give_New_Puck(NULL);
		new Give_New_Puck(NULL);
	}


	dspt.join();
	estt.join();
		//Hal_Test_Thread htt;
		//htt.start(NULL);
		//htt.join();



    #ifdef SIMULATION
       IOaccess_close();
    #endif

    return EXIT_SUCCESS;
}
