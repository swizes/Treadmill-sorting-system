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
//#include "Hal_Test_Thread.h"
#include "lib/HWaccess.h"
#include "Serial.h"
#include "CommunicationThread.h"
#include "states/PuckStates.h"
//#include "CalibrateThread.h"
#include "Dispatcher.h"
#include "State.cpp"
#include "HAL.h"
#include "HoleDetector.h"

using namespace std;

int main(int argc, char *argv[]) {

	HAL* hal = HAL::getInstance();

	cout << "start hole detection" << endl;
	hal->band_right_normal();
	bool x = HoleDetector::detectHole(hal, false);

	if(x) {
		cout << "has hole!" << endl;
	} else {
		cout << "no hole" << endl;
	}
	hal->band_stop();
	/*
	int i = 1000000;
	while (true) {
		if(i<0)
		{
			cout << "val:" << hal->get_height_measure() << endl;
			i = 1000000;
		}
		i--;
	}
	*/

    return EXIT_SUCCESS;
}
