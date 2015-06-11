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
#include "Blink_Thread.h"
#include "./Tests/Hal_Test_Thread.h"
//#include "Hal_Test_Thread.h"
#include "lib/HWaccess.h"
#include "Serial.h"
#include "CommunicationThread.h"
#include "states/PuckStates.h"
#include "CalibrateThread.h"
#include "Dispatcher.h"
#include "State.cpp"
#include "HAL.h"
#include "HoleDetector.h"

using namespace std;

int main(int argc, char *argv[]) {




    // Baut Verbindung zu Simulation auf
	#ifdef SIMULATION
        IOaccess_open();
		cout << "WARNING: SYSTEM IN SIMULATION!!!" << endl;
    #endif
	//RUN Calibration
	CalibrateThread *cal = CalibrateThread::getInstance();
	cal->start(NULL);
	cal->join();
	cout << "cal done" << endl;


    //Hal_Test_Thread htt;
	
    /*Serielle Verbindung funkitoniert nur wenn sich System nicht in der Simulation befindet
    /dev/ser1 steht nicht zur Verfuegung. 		*/
	#ifndef SIMULATION
	//CommunicationThread ct;
	//ct.start(NULL);
    #endif
	cout << "instance" << endl;
//	HAL* hal = HAL::getInstance();
//	hal->reset();
	cout << "reset" << endl;
	Dispatcher* disp = Dispatcher::getInstance();
	cout << "disp" << endl;

	cout << "Vor Start der FSM" << endl;

	Context* con= new Context();
	cout << "context" << endl;
	State* s = new Ready(NULL);
	con->setState(new Ready(NULL));
	cout << "setState" << endl;
	disp->listenForEvents();
	cout << "listenForEvents" << endl;


		//Hal_Test_Thread htt;
		//htt.start(NULL);
		//htt.join();


	#ifndef SIMULATION
		//ct.join();;
    #endif



    #ifdef SIMULATION
       IOaccess_close();
    #endif

    return EXIT_SUCCESS;
}
