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
#include "../Threads/Blink_ThreadRed.h"
#include "../Threads/Blink_ThreadGreen.h"
#include "../Threads/Blink_ThreadYellow.h"


using namespace std;

int main(int argc, char *argv[]) {
	printf("Version 0.9\n");
	// Baut Verbindung zu Simulation auf
#ifdef SIMULATION
	IOaccess_open();
	cout << "WARNING: SYSTEM IN SIMULATION!!!" << endl;
#endif
	//RUN Calibration

	//EINRICHBETRIEB
	HAL *hal = HAL::getInstance();
//	Blink_ThreadRed* red = Blink_ThreadRed::getInstance();
//	Blink_ThreadYellow* yel = Blink_ThreadYellow::getInstance();
//	Blink_ThreadGreen* gre = Blink_ThreadGreen::getInstance();

	int loop = 1;
	int resetCounter = 0;
	while (loop) {
		if (!hal->is_startButton_pushed()) {
			Timer time;
			Timer timer;
			cout << "Timer started" << endl;
			timer.waitForTimeOut(1, 0);
			timer.deleteTimer();


			struct timespec result;
			cout << "Press 2 times Reset Button or Press Start again to skip Calibration" << endl;
			while (hal->is_startButton_pushed()) {
				time.setTimer(10, 0);
				hal->turn_yellowLight_on();

				//nicht gedrückt
				while (hal->is_resetButton_pushed()) {
					time.getTime(&result);
					if (result.tv_sec == 0) {
						hal->turn_yellowLight_off();
						hal->turn_redLight_on();
						cout << "Timeout, too late" << endl;
					}
				}

				while (!hal->is_resetButton_pushed()) {
				}
				cout << "Button gedrückt" << resetCounter << endl;

				delay(50);
				resetCounter++;
				if (resetCounter == 1) {
					hal->turn_greenLight_on();

				}
				if (resetCounter == 2) {
					hal->turn_yellowLight_off();
					hal->turn_greenLight_off();
					CalibrateThread *cal1 = CalibrateThread::getInstance();
					//start blink
//					red->setLED(5000,1000000);
//					yel->setLED(5000,1000000);
//					gre->setLED(5000,1000000);
					cal1->start(NULL);
					cal1->join();
					cout << "cal done" << endl;
					loop = 0;
					//stop blink
//					red->setLED(1,0);
//					yel->setLED(1,0);
//					gre->setLED(1,0);
					break;
				}
				//if

			} //while start button = 0
		} //if
	} //while loop

	/*Serielle Verbindung funkitoniert nur wenn sich System nicht in der Simulation befindet
	 /dev/ser1 steht nicht zur Verfuegung. 		*/

	DispatcherThread dspt;
	dspt.start(NULL);

	BandController* bc = BandController::getInstance();
	bc->refreshBand();

	cout << "Vor Start der FSM" << endl;
	cout << "-----------------------------------" << endl;
	CalibrateThread *cal = CalibrateThread::getInstance();
	if (!cal->isBand()) { //is band1!<
//		State* s = new Ready(NULL);
		new Ready(NULL);
	} else {
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
