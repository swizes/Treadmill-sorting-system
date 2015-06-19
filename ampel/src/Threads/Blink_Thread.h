/**
 * @file    Blink_Thread.h
 * @author  Simon Brummer
 * @version 0.1
 *
 * Headerfile zur Demoklasse fuer das SEP2 Tutorium. Es wird folgendes gezeigt:
 * - Ableiten von Klassen
 * - Sichtbarkeitsregeln fuer Variablen und Methoden
 * - Konstruktorenarten
 * - Doxygenkompatible Kommentare.
 */

#ifndef BLINK_THREAD_H_
#define BLINK_THREAD_H_

#define RED 2
#define YELLOW 1
#define GREEN 0

#define IO_CONTROL_ADDRESS 0x303
#define PORT_A 0x300
#define PORT_B 0x301
#define PORT_C 0x302
#define BM_IO_CONTROL 0b10001010
#define BM_GREEN 0b00100000
#define BM_YELLOW 0b01000000
#define BM_RED 0b10000000
#define BM_MOTOR_RIGHT 0b00000001
#define BM_MOTOR_LEFT 0b00000010


#include <stdint.h>
#include <pthread.h>
#include "lib/HAWThread.h"

using namespace thread;

class Blink_Thread: public HAWThread {
    /* Variablen deklarationen */
    private:
        uint16_t const times_ ;      ///< Anzahl der Blinkvorgaenge.

        uint16_t ioControlAddress_;  ///< Registeradresse IO Controlregister.
        uint16_t registerAddressA_ ;  ///< Registeradresse Port A
        uint16_t registerAddressB_ ;  ///< Registeradresse Port B
        uint16_t registerAddressC_ ;  ///< Registeradresse Port C

        uint8_t ioControlBitmask_ ;  ///< Setzen der Richtungsbits.
        uint8_t greenLightBitmask_;  ///< Bitmaske zum Ansteuern der gruenen Lampe.
        uint8_t yellowLightBitmask_;  ///< Bitmaske zum Ansteuern der orangenen Lampe.
        uint8_t redLightBitmask_;  ///< Bitmaske zum Ansteuern der roten Lampe.
        uint8_t motorRightRunBitmask_;
        uint8_t motorLeftRunBitmask_;
        uint8_t color_;

        static pthread_mutex_t mtx_; ///< Synchronisationsmutex.

    /* Methoden deklarationen */
    public:
        Blink_Thread(uint16_t times, uint8_t color); ///< Standard Konstruktor. Offentlich Aufrufbar.
        virtual ~Blink_Thread();      ///< Standard Dekonstruktor.

    private:
        Blink_Thread(const Blink_Thread& b);      ///< Copy-Konstruktor. Privat, deshalb kann dieses Objekt nicht als "Call-by-value" uebergeben werden.
        Blink_Thread& operator=(Blink_Thread& b); ///< Zuweisungskonstruktor. Objekt kann nicht an eine gleichartige Referenz zugewiesen werden da private.

        virtual void execute(void*); ///< Geerbt aus HAWThread. Muss implementiert werden.
        virtual void shutdown();     ///< Geerbt aus HAWThread. Muss implementiert werden.

        uint8_t turnGreenOn() const;    ///< Einfache Methode, const versichert das diese Methode keine Instanzvariable veraendert.
        uint8_t turnGreenOff() const;  
        uint8_t turnYellowOn() const;
        uint8_t turnYellowOff() const;
        uint8_t turnRedOn() const;   
        uint8_t turnRedOff() const;  
        uint8_t turnResetLedOn() const;
        uint8_t checkLichtschranke() const;
};

#endif
