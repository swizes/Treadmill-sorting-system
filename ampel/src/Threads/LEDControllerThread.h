/**
 * @file    LEDControllerThread.h
 * @author  Lukas Wendt
 * @version 0.1
 *

 */

#ifndef LEDCONTROLLERTHREAD_H_
#define LEDCONTROLLERTHREAD_H_




#include <stdint.h>
#include <pthread.h>
#include "lib/HAWThread.h"
#include "../HAL.h"

using namespace thread;

class LEDControllerThread: public HAWThread {
    /* Variablen deklarationen */
    private:
		bool red;
		bool green;
		bool yellow;
		bool reset;
		bool startLED;
		HAL *hal;
		pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
		pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

        static pthread_mutex_t mtx_; ///< Synchronisationsmutex.

    /* Methoden deklarationen */
    public:

        virtual ~LEDControllerThread();      ///< Standard Dekonstruktor.
        static LEDControllerThread* getInstance();

	bool isGreen() const {
		return green;
	}

	void setGreen(bool green) {
		pthread_cond_signal( &cond );
		this->green = green;
	}

	bool isRed() const {
		return red;
	}

	void setRed(bool red) {
		pthread_cond_signal( &cond );
		this->red = red;
	}

	bool isReset() const {
		return reset;
	}

	void setReset(bool reset) {
		pthread_cond_signal( &cond );
		this->reset = reset;
	}

	bool isStart() const {
		return startLED;
	}

	void setStart(bool start) {
		pthread_cond_signal( &cond );
		this->startLED = start;
	}

	bool isYellow() const {
		return yellow;
	}

	void setYellow(bool yellow) {
		pthread_cond_signal( &cond );
		this->yellow = yellow;
	}

    private:

        static LEDControllerThread* instance_;
        LEDControllerThread(void); ///< Standard Konstruktor. Offentlich Aufrufbar.
        LEDControllerThread(const LEDControllerThread& b);      ///< Copy-Konstruktor. Privat, deshalb kann dieses Objekt nicht als "Call-by-value" uebergeben werden.
        LEDControllerThread& operator=(LEDControllerThread& b); ///< Zuweisungskonstruktor. Objekt kann nicht an eine gleichartige Referenz zugewiesen werden da private.

        virtual void execute(void*); ///< Geerbt aus HAWThread. Muss implementiert werden.
        virtual void shutdown();     ///< Geerbt aus HAWThread. Muss implementiert werden.


};

#endif
