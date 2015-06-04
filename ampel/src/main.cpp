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
<<<<<<< HEAD
#include "./Tests/Hal_Test_Thread.h"
=======
//#include "Hal_Test_Thread.h"
>>>>>>> height-hole-detector
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

<<<<<<< HEAD
    // Baut Verbindung zu Simulation auf
	#ifdef SIMULATION
        IOaccess_open();
		cout << "WARNING: SYSTEM IN SIMULATION!!!" << endl;
    #endif
	//RUN Calibration
	CalibrateThread *cal = CalibrateThread::getInstance();
	cal->start(NULL);
	cal->join();

    //Hal_Test_Thread htt;
	
    /*Serielle Verbindung funkitoniert nur wenn sich System nicht in der Simulation befindet
    /dev/ser1 steht nicht zur Verfuegung. 		*/
	#ifndef SIMULATION
	CommunicationThread ct;
	ct.start(NULL);
    #endif


	HAL* hal = HAL::getInstance();
	hal->reset();
	Dispatcher* disp = Dispatcher::getInstance();

	Context* con= new Context();
	con->setState(new NotExist(con));
	disp->listenForEvents();


		
		//printf("RunIn: %d  RunOut: %d  nEvents: %d \n\n", RUNNING_IN_TRUE, RUNNING_OUT_TRUE, NEVENTS);

		//disp.listenForEvents();
	
	
	#ifndef SIMULATION
		ct.join();;
    #endif



    #ifdef SIMULATION
       IOaccess_close();
    #endif
=======

>>>>>>> height-hole-detector

    return EXIT_SUCCESS;
}
