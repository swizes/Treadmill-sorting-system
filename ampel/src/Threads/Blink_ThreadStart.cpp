/**
 * @file    Blink_Thread.cpp
 * @author
 * @version 0.1
 *
 * Ampelsteurerung alle LEDs werden ein und ausgeschaltet
 */

#include <unistd.h>
#include <time.h>
#include "Blink_ThreadStart.h"
#include "lib/Lock.h"
#include "lib/HWaccess.h"





Blink_ThreadStart* Blink_ThreadStart::instance_ = NULL;

/**
 * c'tor for the Thread-safe singleton Calibration implementation
 * @param none
 * @return A Pointer to the Singleton Calibration Object
 */
Blink_ThreadStart* Blink_ThreadStart::getInstance() {
	static pthread_mutex_t mtx_ = PTHREAD_MUTEX_INITIALIZER;

	if (instance_ == NULL) {
		pthread_mutex_lock(&mtx_);
		if (instance_ == NULL) {
			instance_ = new Blink_ThreadStart();
		}
		pthread_mutex_unlock(&mtx_);
	}
	return instance_;
}


/**
 *  Standard Konstruktor.
 *  Genauer beschreibender Text für Doxygen...
 *  @param times bestimmt wie oft das gruene Licht blinken soll. 
 */
Blink_ThreadStart::Blink_ThreadStart(void ) {
	led = LEDControllerThread::getInstance();

	time = 0;
	off = true;
	countBlink = 0;
}


/**
 * Standard Dekonstruktor.
 * Wird aufgerufen beim loeschen des Objektes.
 * Objekte die im lokalen Kontext von Methoden allogiert wurden, werden 
 * beim Bereinigen des Stacks, bei Methodenende automatisch deallokiert.
 * --> Automatischer Dekonstruktoraufruf.  
 */
Blink_ThreadStart::~Blink_ThreadStart() {
    cout << "dtor: Blink_Thread" << endl;
}


/**
 * Hauptschleife des geerbten HAW-Thread.
 * Die oberklasse HAW-Thread erzwingt die Implementierung der execute Methode.  
 * Der Thread endet nach Ende dieser Methode. 
 */
void Blink_ThreadStart::execute(void*){
	int run = 1;
	while(run){
		if(countBlink < 0){
			led->setStart(1);
			run = 0;
		}
		while(countBlink > 0){
			led->setStart(1);
			usleep(time);
			led->setStart(0);
			usleep(time);
			countBlink--;
		}
		if(countBlink == 0){
			led->setStart(0);
			run = 0;
		}
	}
}


/**
 * Shutdown Methode. 
 * Diese Methode muss beim erben von HAW-Thread implementiert werden. 
 * Sie wird nach Ende der execute-Methode aufgerufen und dient dem 
 * evtl. aufraumen das Threadablauf.
 */
void Blink_ThreadStart::shutdown(){
    cout << "Blink_Thread shutdown" << endl;
}

void Blink_ThreadStart::setLED(int countBlink, int time){
	//Negative countBlink werte bewirken Dauerleuchten 0 bedeutet aus und Positive Werte die anzahl
	//time ist Zeit in Microsekunden zwischen dem ein und ausschalten
	this->stop();
	this->countBlink = countBlink;
	this->time = time;
	this->start(NULL);
}



