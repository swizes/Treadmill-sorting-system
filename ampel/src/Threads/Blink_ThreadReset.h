/**
 * @file    Blink_ThreadGreen.h
 * @author  Lukas Wendt
 * @version 0.1
 *

 */

#ifndef BLINK_THREADRESET_H_
#define BLINK_THREADRESET_H_




#include <stdint.h>
#include <pthread.h>
#include "lib/HAWThread.h"
#include "LEDControllerThread.h"
#include "../HAL.h"

using namespace thread;

class Blink_ThreadReset: public HAWThread {
    /* Variablen deklarationen */
    private:
		bool off;
		int time;
		int countBlink;
		LEDControllerThread *led;

        static pthread_mutex_t mtx_; ///< Synchronisationsmutex.

    /* Methoden deklarationen */
    public:

        void setLED(int, int);
        virtual ~Blink_ThreadReset();      ///< Standard Dekonstruktor.
        static Blink_ThreadReset* getInstance();

    private:

        static Blink_ThreadReset* instance_;
        Blink_ThreadReset(void); ///< Standard Konstruktor. Offentlich Aufrufbar.
        Blink_ThreadReset(const Blink_ThreadReset& b);      ///< Copy-Konstruktor. Privat, deshalb kann dieses Objekt nicht als "Call-by-value" uebergeben werden.
        Blink_ThreadReset& operator=(Blink_ThreadReset& b); ///< Zuweisungskonstruktor. Objekt kann nicht an eine gleichartige Referenz zugewiesen werden da private.

        virtual void execute(void*); ///< Geerbt aus HAWThread. Muss implementiert werden.
        virtual void shutdown();     ///< Geerbt aus HAWThread. Muss implementiert werden.


};

#endif
