/**
 * @file    Blink_ThreadGreen.h
 * @author  Lukas Wendt
 * @version 0.1
 *

 */

#ifndef BLINK_THREADSTART_H_
#define BLINK_THREADSTART_H_




#include <stdint.h>
#include <pthread.h>
#include "lib/HAWThread.h"
#include "LEDControllerThread.h"
#include "../HAL.h"

using namespace thread;

class Blink_ThreadStart: public HAWThread {
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
        virtual ~Blink_ThreadStart();      ///< Standard Dekonstruktor.
        static Blink_ThreadStart* getInstance();

    private:

        static Blink_ThreadStart* instance_;
        Blink_ThreadStart(void); ///< Standard Konstruktor. Offentlich Aufrufbar.
        Blink_ThreadStart(const Blink_ThreadStart& b);      ///< Copy-Konstruktor. Privat, deshalb kann dieses Objekt nicht als "Call-by-value" uebergeben werden.
        Blink_ThreadStart& operator=(Blink_ThreadStart& b); ///< Zuweisungskonstruktor. Objekt kann nicht an eine gleichartige Referenz zugewiesen werden da private.

        virtual void execute(void*); ///< Geerbt aus HAWThread. Muss implementiert werden.
        virtual void shutdown();     ///< Geerbt aus HAWThread. Muss implementiert werden.


};

#endif
