/**
 * @file    Blink_ThreadRed.h
 * @author  Lukas Wendt
 * @version 0.1
 *

 */

#ifndef BLINK_THREADRED_H_
#define BLINK_THREADRED_H_




#include <stdint.h>
#include <pthread.h>
#include "lib/HAWThread.h"
#include "../HAL.h"

using namespace thread;

class Blink_ThreadRed: public HAWThread {
    /* Variablen deklarationen */
    private:
		bool off;
		int time;
		int countBlink;
		HAL *hal;

        static pthread_mutex_t mtx_; ///< Synchronisationsmutex.

    /* Methoden deklarationen */
    public:

        void setLED(int, int);
        virtual ~Blink_ThreadRed();      ///< Standard Dekonstruktor.
        static Blink_ThreadRed* getInstance();

    private:

        static Blink_ThreadRed* instance_;
        Blink_ThreadRed(void); ///< Standard Konstruktor. Offentlich Aufrufbar.
        Blink_ThreadRed(const Blink_ThreadRed& b);      ///< Copy-Konstruktor. Privat, deshalb kann dieses Objekt nicht als "Call-by-value" uebergeben werden.
        Blink_ThreadRed& operator=(Blink_ThreadRed& b); ///< Zuweisungskonstruktor. Objekt kann nicht an eine gleichartige Referenz zugewiesen werden da private.

        virtual void execute(void*); ///< Geerbt aus HAWThread. Muss implementiert werden.
        virtual void shutdown();     ///< Geerbt aus HAWThread. Muss implementiert werden.


};

#endif
