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
#include "lib/HWaccess.h"
#include "Serial.h"
#include "CommunicationThread.h"
#include "states/PuckStates.h"
#include "CalibrateThread.h"
#include "Dispatcher.h"
#include "State.cpp"

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

    //Hal_Test_Thread htt;
	
    /*Serielle Verbindung funkitoniert nur wenn sich System nicht in der Simulation befindet
    /dev/ser1 steht nicht zur Verfuegung. 		*/
	#ifndef SIMULATION
	CommunicationThread ct;
	ct.start(NULL);
    #endif
		//Hal_Test_Thread htt;
		//htt.start(NULL);
		//htt.join();
//		CalibrateThread cal;
//		cal.start(NULL);
//		cal.join();


		//htt.start(NULL);

		/*Dispatcher disp;
		State* s1 = new State("New Puck");
		State* s2 = new State("In height measure");
		State* s3 = new State("height ok");
		State* s4 = new State("in gate");
		State* s5 = new State("in metal detection");
		State* s6 = new State("gate open?");
		State* s7 = new State("is slide full?");
		State* s8 = new State("running out?");

		disp.addListeners(s1, RUNNING_IN_TRUE);
		disp.addListeners(s2, IN_HEIGHT_TRUE);
		disp.addListeners(s3, HEIGHT_STATUS_OK);
		disp.addListeners(s4, PUCK_IN_GATE_TRUE);
		disp.addListeners(s5, METAL_DETECTION_TRUE);
		disp.addListeners(s6, GATE_OPEN_TRUE);
		disp.addListeners(s7, SLIDE_FULL_TRUE);
		disp.addListeners(s8, RUNNING_OUT_TRUE);*/

		HAL* hal = HAL::getInstance();
		hal->reset();
		Dispatcher* disp = Dispatcher::getInstance();

		Context* con= new Context();
		con->setState(new NotExist(con));
		disp->listenForEvents();


		
		printf("RunIn: %d  RunOut: %d  nEvents: %d \n\n", RUNNING_IN_TRUE, RUNNING_OUT_TRUE, NEVENTS);

		//disp.listenForEvents();
	
	
	#ifndef SIMULATION
		ct.join();;
    #endif



    #ifdef SIMULATION
       IOaccess_close();
    #endif

    return EXIT_SUCCESS;
}
