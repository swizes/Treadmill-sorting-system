/**
 * @file    Blink_Thread.cpp
 * @author
 * @version 0.1
 *
 * Ampelsteurerung alle LEDs werden ein und ausgeschaltet
 */

#include <unistd.h>
#include <time.h>
#include "Blink_ThreadRed.h"
#include "lib/Lock.h"
#include "lib/HWaccess.h"



/**
 *  Standard Konstruktor.
 *  Genauer beschreibender Text für Doxygen...
 *  @param times bestimmt wie oft das gruene Licht blinken soll. 
 */
Blink_ThreadRed::Blink_ThreadRed(void ) {
	hal = HAL::getInstance();

}


/**
 * Standard Dekonstruktor.
 * Wird aufgerufen beim loeschen des Objektes.
 * Objekte die im lokalen Kontext von Methoden allogiert wurden, werden 
 * beim Bereinigen des Stacks, bei Methodenende automatisch deallokiert.
 * --> Automatischer Dekonstruktoraufruf.  
 */
Blink_ThreadRed::~Blink_ThreadRed() {
    cout << "dtor: Blink_Thread" << endl;
}


/**
 * Hauptschleife des geerbten HAW-Thread.
 * Die oberklasse HAW-Thread erzwingt die Implementierung der execute Methode.  
 * Der Thread endet nach Ende dieser Methode. 
 */
void Blink_ThreadRed::execute(void*){
	while(1){
		if(countBlink < 0){
			hal->turn_redLight_on();
			this->stop();
		}
		while(countBlink > 0){
			hal->turn_redLight_on();
			usleep(time);
			hal->turn_redLight_off();
			usleep(time);
			countBlink--;
		}
		if(countBlink == 0){
			hal->turn_redLight_off();
			this->stop();
		}
	}
}


/**
 * Shutdown Methode. 
 * Diese Methode muss beim erben von HAW-Thread implementiert werden. 
 * Sie wird nach Ende der execute-Methode aufgerufen und dient dem 
 * evtl. aufraumen das Threadablauf.
 */
void Blink_ThreadRed::shutdown(){
    cout << "Blink_Thread shutdown" << endl;
}

void Blink_ThreadRed::setLED(int countBlink, int time){
	//Negative countBlink werte bewirken Dauerleuchten 0 bedeutet aus und Positive Werte die anzahl
	//time ist Zeit in Microsekunden zwischen dem ein und ausschalten
	this->stop();
	this->countBlink = countBlink;
	this->time = time;
	this->start(NULL);
}



