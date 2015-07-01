/*
 * ESTOPTHREAD.cpp
 *
 *  Created on: 01.07.2015
 *      Author: IBOSY
 */

#include "TimeoutThread.h"
#include <exception>
#include <signal.h>

TimeoutThread::TimeoutThread() {
	// TODO Auto-generated constructor stub

}

TimeoutThread::~TimeoutThread() {
	// TODO Auto-generated destructor stub
}

void TimeoutThread::execute(void*){
	sigset_t sigset;
	siginfo_t siginfo;

	sigfillset(&sigset);
	//sigaddset(&sigset, SIGALRM);

	int sig;
	int val = 0;

	while(true) {
		cout << "TimeoutThread: wait for timeout signal" << endl;
		sig = sigwaitinfo(&sigset, &siginfo);

		if(sig == 1) {
			cout << "TimeoutThread: received signal " << sig << "with number" << siginfo.si_value.sival_int << endl;
			val = siginfo.si_value.sival_int;
		}
	}
}





void TimeoutThread::shutdown(){
    cout << "TimeoutThread shutdown" << endl;
}
