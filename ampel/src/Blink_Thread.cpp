/**
 * @file    Blink_Thread.cpp
 * @author
 * @version 0.1
 *
 * Ampelsteurerung alle LEDs werden ein und ausgeschaltet
 */

#include <unistd.h>
#include <time.h>
#include "Blink_Thread.h"
#include "lib/Lock.h"
#include "lib/HWaccess.h"

/* Zuweisung der Klassenvariablen */
pthread_mutex_t Blink_Thread::mtx_ = PTHREAD_MUTEX_INITIALIZER;

/**
 *  Standard Konstruktor.
 *  Genauer beschreibender Text für Doxygen...
 *  @param times bestimmt wie oft das gruene Licht blinken soll. 
 */
Blink_Thread::Blink_Thread(uint16_t times, uint8_t color ): times_(times), color_ (color) {
    /* Einfacher Konstruktor, setzt die Werte der Instanzvariablen.
     * Methode bei Times ist vorzuziehen. Direktes kopieren bei 
     * Objekterzeugung, gilt nicht als Zuweisung und verstösst 
     * damit auch nicht gegen die const correctness siehe Blink_Thread.h .
     */
  
    cout << "ctor: Blink_Thread" << endl;

    ioControlAddress_ = 0x303;
    registerAddressA_  = 0x300;
    registerAddressB_  = 0x301;
    registerAddressC_  = 0x302;


    ioControlBitmask_  = 0b10001010;
    redLightBitmask_ =   0b10000000; //not set at the Moment
    yellowLightBitmask_ =0b01000000;
    greenLightBitmask_ = 0b00100000;

}


/**
 * Standard Dekonstruktor.
 * Wird aufgerufen beim loeschen des Objektes.
 * Objekte die im lokalen Kontext von Methoden allogiert wurden, werden 
 * beim Bereinigen des Stacks, bei Methodenende automatisch deallokiert.
 * --> Automatischer Dekonstruktoraufruf.  
 */
Blink_Thread::~Blink_Thread() {
    cout << "dtor: Blink_Thread" << endl;
}


/**
 * Hauptschleife des geerbten HAW-Thread.
 * Die oberklasse HAW-Thread erzwingt die Implementierung der execute Methode.  
 * Der Thread endet nach Ende dieser Methode. 
 */
void Blink_Thread::execute(void*){
    /* Klassenweiten Mutex, locken. */
    //Lock lock(&mtx_);
    cout << "Blink_Thread executing" << endl;

    /* Zugriffsrechte von QNX fuer diesen Thread, auf die Hardware erbitten. */
    if( ThreadCtl(_NTO_TCTL_IO_PRIV,0) == -1 ){
        cout << "Can't get Hardware access, therefore can't do anything." << endl;
    }
    
    /* IO Register als Eingänge bzw. Ausgänge definieren. */
    out8(ioControlAddress_, ioControlBitmask_);

    /* Gruenes Licht blinken lassen inkl. Pruefung ob der Thread extern gestoppt wurde. */
    for(int i = 0; i < times_; i++){
        /* Pruefen ob der Thread durch stop() beendet wurde. */
        if( !isStopped() ){ 
        	turnResetLedOn();
        	checkLichtschranke();
           if(color_ == GREEN){
        	   Lock lock(&mtx_);
        	   turnGreenOn();
        	   usleep(500000);
        	   turnGreenOff();
        	   usleep(500000);

           }
           if(color_ == YELLOW){
        	   Lock lock(&mtx_);
               turnYellowOn();
               usleep(500000);
               turnYellowOff();
               usleep(500000);
           }
           if(color_ == RED){
        	   Lock lock(&mtx_);
        	    turnRedOn();
        	    usleep(500000);
        	    turnRedOff();
        	    usleep(500000);

           }


            
	}
    }
}


/**
 * Shutdown Methode. 
 * Diese Methode muss beim erben von HAW-Thread implementiert werden. 
 * Sie wird nach Ende der execute-Methode aufgerufen und dient dem 
 * evtl. aufraumen das Threadablauf.
 */
void Blink_Thread::shutdown(){
    cout << "Blink_Thread shutdown" << endl;
}


/**
 *Hier kommen die Funktionen um alle 3 Leds einszuschalten
 * @return liefert immer 0 zurueck. 
 */
uint8_t Blink_Thread::turnGreenOn() const {
    cout << "Turning green light on." << endl;
    /* Bit fuer gruenes Licht setzen. */
    out8(registerAddressA_, in8(registerAddressA_) | greenLightBitmask_);
    return 0;
}

uint8_t Blink_Thread::turnRedOn() const {
    cout << "Turning red light on." << endl;
    /* Bit fuer Rotes Licht setzen. */
    out8(registerAddressA_, in8(registerAddressA_) | redLightBitmask_);
    return 0;
}
uint8_t Blink_Thread::turnYellowOn() const {
    cout << "Turning yellow light on." << endl;
    /* Bit fuer Gelbes Licht setzen. */
    out8(registerAddressA_, in8(registerAddressA_) | yellowLightBitmask_);
    return 0;
}

uint8_t Blink_Thread::turnResetLedOn() const {
    cout << "Turning yellow light on." << endl;
    /* Bit fuer Gelbes Licht setzen. */
    out8(registerAddressC_, in8(registerAddressC_) | 0b00000001);
    return 0;
}
uint8_t Blink_Thread::checkLichtschranke() const {
    cout << "Turning yellow light on." << endl;
    /* Bit fuer Gelbes Licht setzen. */
    cout << (int)in8(registerAddressB_) << endl;
    return 0;
}


/**
 * Hier kommen die Funktionen um alle 3 Leds auszuschalten
 * @return liefert immer 0 zurueck. 
 */
uint8_t Blink_Thread::turnGreenOff() const {
    cout << "Turning green light off." << endl;
    /* Bit fuer gruenes Licht loeschen. */
    out8(registerAddressA_, in8(registerAddressA_) & ~greenLightBitmask_);
    return 0;
}

uint8_t Blink_Thread::turnRedOff() const {
    cout << "Turning red light off." << endl;
    /* Bit fuer Rotes Licht loeschen. */
    out8(registerAddressA_, in8(registerAddressA_) & ~redLightBitmask_);
    return 0;
}

uint8_t Blink_Thread::turnYellowOff() const {
    cout << "Turning yellow light off." << endl;
    /* Bit fuer Gelbes Licht loeschen. */
    out8(registerAddressA_, in8(registerAddressA_) & ~yellowLightBitmask_);
    return 0;
}
