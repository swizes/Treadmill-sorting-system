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
#include "CommunnicationThread.h"
#include "FileHelper.h"
#include "ConfigManager.h"

using namespace std;

int main(int argc, char *argv[]) {

	ConfigManager *cf = new ConfigManager();
	string val1 = "ha";
	string val2;

	/*
	cf->setConfigValue("test1", "value1");
	cf->setConfigValue("test2", "value2");


	cf->getConfigValue("test1", &val1);
	cf->getConfigValue("test2", &val2);

	cout << "val1:" << val1 << endl;
	cout << "val2:" << val2 << endl;

	cf->writeDefaultConfig();
*/
	cf->readDefaultConfig();

	cf->getConfigValue("test1", &val1);
	cf->getConfigValue("test2", &val2);

	cout << "val1:" << val1 << endl;
	cout << "val2:" << val2 << endl;

	//cout << "check file system";
	//FileHelper fhelper;// = new FileHelper();
	//fhelper.test1();


    #ifdef SIMULATION
       IOaccess_close();
    #endif

    return EXIT_SUCCESS;
}
