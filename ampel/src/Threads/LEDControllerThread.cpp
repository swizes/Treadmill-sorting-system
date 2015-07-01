/**
 * @file    LEDControllerThread.cpp
 * @author
 * @version 0.1
 *
 * Ampelsteurerung alle LEDs werden ein und ausgeschaltet
 */

#include <unistd.h>
#include <time.h>
#include "LEDControllerThread.h"
#include "lib/Lock.h"
#include "lib/HWaccess.h"





LEDControllerThread* LEDControllerThread::instance_ = NULL;

/**
 * c'tor for the Thread-safe singleton Calibration implementation
 * @param none
 * @return A Pointer to the Singleton Calibration Object
 */
LEDControllerThread* LEDControllerThread::getInstance() {
	static pthread_mutex_t mtx_ = PTHREAD_MUTEX_INITIALIZER;

	if (instance_ == NULL) {
		pthread_mutex_lock(&mtx_);
		if (instance_ == NULL) {
			instance_ = new LEDControllerThread();
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
LEDControllerThread::LEDControllerThread(void ) {
	hal = HAL::getInstance();

}


/**
 * Standard Dekonstruktor.
 * Wird aufgerufen beim loeschen des Objektes.
 * Objekte die im lokalen Kontext von Methoden allogiert wurden, werden 
 * beim Bereinigen des Stacks, bei Methodenende automatisch deallokiert.
 * --> Automatischer Dekonstruktoraufruf.  
 */
LEDControllerThread::~LEDControllerThread() {
    cout << "dtor: Blink_Thread" << endl;
}


/**
 * Hauptschleife des geerbten HAW-Thread.
 * Die oberklasse HAW-Thread erzwingt die Implementierung der execute Methode.  
 * Der Thread endet nach Ende dieser Methode. 
 */
void LEDControllerThread::execute(void*){
	pthread_mutex_lock( &mutex );
	while(1){
		if(green == 1){
			hal->turn_greenLight_on();
		}else{
			hal->turn_greenLight_off();
		}
		if(yellow == 1){
			hal->turn_yellowLight_on();
		}else{
			hal->turn_yellowLight_off();
		}
		if(red == 1){
			hal->turn_redLight_on();
		}else{
			hal->turn_redLight_off();
		}
		if(reset == 1){
			hal->turn_resetLED_on();
		}else{
			hal->turn_resetLED_off();
		}
		if(startLED == 1){
			hal->turn_startLED_on();
		}else{
			hal->turn_startLED_off();
		}
		cout << "Refresh" << endl;
		pthread_cond_wait( &cond, &mutex );
	}
}


/**
 * Shutdown Methode. 
 * Diese Methode muss beim erben von HAW-Thread implementiert werden. 
 * Sie wird nach Ende der execute-Methode aufgerufen und dient dem 
 * evtl. aufraumen das Threadablauf.
 */
void LEDControllerThread::shutdown(){
    cout << "Blink_Thread shutdown" << endl;
}




