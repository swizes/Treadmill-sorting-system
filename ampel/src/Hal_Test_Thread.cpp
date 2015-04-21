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
    startPressed();
    hal->turn_yellowLight_off();

    cout << "Der Test wird nun die Gruene Lampe einschalten Bestaetigen bitte mit Start" << endl;
    hal->turn_greenLight_on();
    startPressed();
    hal->turn_greenLight_off();

    cout << "Der Test wird nun die Rote Lampe einschalten Bestaetigen bitte mit Start" << endl;
    hal->turn_redLight_on();
    startPressed();
    hal->turn_redLight_off();

    cout << "Der Test wird nun die Start Lampe einschalten Bestaetigen bitte mit Start" << endl;
    hal->turn_startLED_on();
    startPressed();
    hal->turn_startLED_off();

    cout << "Der Test wird nun die Reset Lampe einschalten Bestaetigen bitte mit Start" << endl;
    hal->turn_resetLED_on();
    startPressed();
    hal->turn_resetLED_off();

    cout << "Der Test wird nun das Band nach Rechts fahren Bestaetigen bitte mit Start" << endl;
    hal->band_right_normal();
    startPressed();
    hal->band_stop();

    cout << "Der Test wird nun das Band langsam nach Rechts fahren Bestaetigen bitte mit Start" << endl;
    hal->band_right_slowly();
    startPressed();
    hal->band_stop();

    cout << "Der Test wird nun das Band nach Links fahren Bestaetigen bitte mit Start" << endl;
    hal->band_left_normal();
    startPressed();
    hal->band_stop();

    cout << "Der Test wird nun das Band langsam nach Links fahren Bestaetigen bitte mit Start" << endl;
    hal->band_left_slowly();
    startPressed();
    hal->band_stop();

    cout << "Der Test wird nun die Weiche oeffnen Bestaetigen bitte mit Start" << endl;
    hal->open_gate();
    startPressed();
    cout << "Gate open: " << hal->is_gate_open();

    cout << "Der Test wird nun die Weiche oeffnen Bestaetigen bitte mit Start" << endl;
    hal->close_gate();
    startPressed();
    cout << "Gate open: " << hal->is_gate_open();

    cout << "Puk in Eingangs Lichschranke legen";
    while(hal->is_puck_running_in()==0);
    usleep(500);

    cout << "Puk wieder runter nehmen";
    while(hal->is_puck_running_in()!=0);
    usleep(500);

    cout << "Puk in Ausgangs Lichschranke legen";
    while(hal->is_puck_running_out()==0);
    usleep(500);

    cout << "Puk wieder runter nehmen";
    while(hal->is_puck_running_out()!=0);
    usleep(500);

    cout << "Rutsche voll packen";
    while(hal->is_slide_full()==0){}

    cout << "Puk in Metalldetektor";
    while(hal->is_metal_detected()==0){}

    cout << "Puk in Gate legen";
    while(hal->is_puck_in_gate()==0){}





    cout << "Test erfolgreich" << endl;

}


void Hal_Test_Thread::shutdown(){
    cout << "Hal Test shutdown" << endl;
}

void Hal_Test_Thread::startPressed(){
	HAL *hal = HAL::getInstance();
    while(hal->is_startButton_pushed()==0) {}
    usleep(500);
    while(hal->is_startButton_pushed()!=0){}
}


