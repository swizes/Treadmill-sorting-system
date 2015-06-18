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
#include "states/ReadySend.h"
#include "DispatcherThread.h"
#include "BandController.h"

using namespace std;

int main(int argc, char *argv[]) {
	printf("Version 0.9\n");
    // Baut Verbindung zu Simulation auf
	#ifdef SIMULATION
        IOaccess_open();
		cout << "WARNING: SYSTEM IN SIMULATION!!!" << endl;
    #endif
	//RUN Calibration


	/*HAL *hal = HAL::getInstance();
	hal->open_gate();
	hal->band_left_normal();
	delay(100);
	hal->band_left_slowly();
	delay(100);
	hal->band_right_normal();
	delay(100);
	hal->band_right_slowly();
	delay(100);
	hal->band_stop();
	delay(100);
	hal->get_height_measure();
	delay(100);
	hal->is_puck_running_in();
	delay(100);
	cout << "End Test" << endl;*/

	CalibrateThread *cal = CalibrateThread::getInstance();
	//cal->start(NULL);
	//cal->join();
	cout << "cal done" << endl;


    //Hal_Test_Thread htt;
	
    /*Serielle Verbindung funkitoniert nur wenn sich System nicht in der Simulation befindet
    /dev/ser1 steht nicht zur Verfuegung. 		*/


	#ifndef SIMULATION
	//CommunicationThread ct;
	//ct.start(NULL);
    #endif


	DispatcherThread dspt;
	dspt.start(NULL);
	//BandController* bd = BandController::getInstance();
	//bd->refreshBand();
	//bd->refreshGate();
	//Dispatcher* disp = Dispatcher::getInstance();

	cout << "Vor Start der FSM" << endl;
	cout << "-----------------------------------" << endl;
	if(1){//is band1!<
		//Context* con= new Context();
		State* s = new Ready(NULL);
		//con->setState(new Ready(NULL));
		//disp->listenForEvents();
//		dspt.start(NULL);

	}else{
		ReadySend rdy;
		rdy.setBusy(1);
		rdy.start(NULL);
		while(1){
			Context* con = new Context();
			con->setState(new Give_New_Puck(con));
			Serial ser;
			puckStruct puck;
//			dspt.start(NULL);
			//disp->listenForEvents();
			ser.recvPacket(&puck);
		}
	}

	dspt.join();

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
