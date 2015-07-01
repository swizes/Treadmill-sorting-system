/**
 * @file    Blink_ThreadYellow.h
 * @author  Lukas Wendt
 * @version 0.1
 *

 */

#ifndef BLINK_THREADYELLOW_H_
#define BLINK_THREADYELLOW_H_




#include <stdint.h>
#include <pthread.h>
#include "lib/HAWThread.h"
#include "LEDControllerThread.h"
#include "../HAL.h"

using namespace thread;

class Blink_ThreadYellow: public HAWThread {
    /* Variablen deklarationen */
    private:
		bool off;
		int time;
		int countBlink;

		LEDControllerThread *lct;

        static pthread_mutex_t mtx_; ///< Synchronisationsmutex.

    /* Methoden deklarationen */
    public:

        void setLED(int, int);
        virtual ~Blink_ThreadYellow();      ///< Standard Dekonstruktor.
        static Blink_ThreadYellow* getInstance();

    private:

        static Blink_ThreadYellow* instance_;
        Blink_ThreadYellow(void); ///< Standard Konstruktor. Offentlich Aufrufbar.
        Blink_ThreadYellow(const Blink_ThreadYellow& b);      ///< Copy-Konstruktor. Privat, deshalb kann dieses Objekt nicht als "Call-by-value" uebergeben werden.
        Blink_ThreadYellow& operator=(Blink_ThreadYellow& b); ///< Zuweisungskonstruktor. Objekt kann nicht an eine gleichartige Referenz zugewiesen werden da private.

        virtual void execute(void*); ///< Geerbt aus HAWThread. Muss implementiert werden.
        virtual void shutdown();     ///< Geerbt aus HAWThread. Muss implementiert werden.


};

#endif
