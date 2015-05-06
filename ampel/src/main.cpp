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
#include "Hal_Test_Thread.h"
#include "lib/HWaccess.h"
#include "Serial.h"
#include "CommunicationThread.h"
#include "Dispatcher.h"
#include "State.cpp"

using namespace std;

int main(int argc, char *argv[]) {

    // Baut Verbindung zu Simulation auf
	#ifdef SIMULATION
        IOaccess_open();
		cout << "WARNING: SYSTEM IN SIMULATION!!!" << endl;
    #endif

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


		//htt.start(NULL);

		Dispatcher disp;
		State* s1 = new State("State 1");
		State* s2 = new State("State 2");

		disp.addListeners(s1, RUNNING_IN);
		disp.addListeners(s2, IN_HEIGHT);
		disp.listenForEvents();
	
	
	#ifndef SIMULATION
		ct.join();;
    #endif



    #ifdef SIMULATION
       IOaccess_close();
    #endif

    return EXIT_SUCCESS;
}
