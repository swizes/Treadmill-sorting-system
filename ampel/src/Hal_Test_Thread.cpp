/*
 * Hal_Test_Thread.cpp
 *
 *  Created on: 20.04.2015
 *      Author: abn908
 */

#include <unistd.h>
#include <time.h>
#include "Hal_Test_Thread.h"
#include "lib/Lock.h"
#include "lib/HWaccess.h"
#include "Hal.h"


Hal_Test_Thread::Hal_Test_Thread() {
	cout << "ctor Hal Test" << endl;
}

Hal_Test_Thread::~Hal_Test_Thread() {
	cout << "dtor Hal Test" << endl;
}

void Hal_Test_Thread::execute(void*){
    cout << "Der Test wir nun die Gelbe Lampe einschalten Bestaetigen bitte mit Start" << endl;
    cout << "1" << endl;

    HAL *hal = HAL::getInstance();

    cout << "2" << endl;
    //hal->band_right_normal();
    //hal->turn_yellowLight_on();
    cout << "3" << endl;
    while(1){
    	//cout << "Button : " << hal->is_startButton_pushed();
    }
    while(/*hal->is_startButton_pushed()*/1){

    }
    cout << "Test erfolgreich" << endl;
}


void Hal_Test_Thread::shutdown(){
    cout << "Hal Test shutdown" << endl;
}


