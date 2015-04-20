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
    HAL *hal = HAL::getInstance();

    hal->reset();

    cout << "Der Test wird nun die Gelbe Lampe einschalten Bestaetigen bitte mit Start" << endl;
    hal->turn_yellowLight_on();
    while(hal->is_startButton_pushed()==0) {}
    usleep(500);
    while(hal->is_startButton_pushed()!=0){}


    hal->turn_yellowLight_off();
    cout << "Der Test wird nun die Gruene Lampe einschalten Bestaetigen bitte mit Start" << endl;
    hal->turn_greenLight_on();
    while(hal->is_startButton_pushed()==0){}
    usleep(500);
    while(hal->is_startButton_pushed()!=0){}


    hal->turn_greenLight_off();
    cout << "Der Test wird nun die Rote Lampe einschalten Bestaetigen bitte mit Start" << endl;
    hal->turn_redLight_on();
    while(hal->is_startButton_pushed()==0){}
    usleep(500);
    while(hal->is_startButton_pushed()!=0){}


    hal->turn_redLight_off();

    cout << "Der Test wird nun die Start Lampe einschalten Bestaetigen bitte mit Start" << endl;
    hal->turn_startLED_on();
    while(hal->is_startButton_pushed()==0){}
    usleep(500);
    while(hal->is_startButton_pushed()!=0){}


    hal->turn_startLED_off();

    cout << "Der Test wird nun die Reset Lampe einschalten Bestaetigen bitte mit Start" << endl;
    hal->turn_resetLED_on();
    while(hal->is_startButton_pushed()==0){}
    usleep(500);
    while(hal->is_startButton_pushed()!=0){}


    hal->turn_resetLED_off();

    cout << "Der Test wird nun das Band nach Rechts fahren Bestaetigen bitte mit Start" << endl;
    hal->band_right_normal();
    while(hal->is_startButton_pushed()==0){}
    usleep(500);
    while(hal->is_startButton_pushed()!=0){}

    hal->band_right_slowly();
    while(hal->is_startButton_pushed()==0){}
    usleep(500);
    while(hal->is_startButton_pushed()!=0){}



    hal->band_stop();




    cout << "Test erfolgreich" << endl;

}


void Hal_Test_Thread::shutdown(){
    cout << "Hal Test shutdown" << endl;
}


