/*
 * Timer.cpp
 *
 *  Created on: 17.05.2015
 *      Author: lukasTest
 */

#include "Timer.h"
#include <sys/siginfo.h>

TimerManagement *timeM;
int channel = -1;
int connection = -1;


Timer::Timer() {
	//std::cout << "ctor Timer" << std::endl;
	TimerManagement *time = TimerManagement::getInstance();
	timeM = time;
	timerid = -1;
	stop = false;
	currentScale = 1;
	shouldContinue = false;
}

Timer::~Timer() {
	//std::cout << "dtor Timer" << std::endl;
	this->deleteTimer();
}

void Timer::createTimer(){
	if((timer_create(CLOCK_REALTIME, &timerEvent, &timerid))==-1){
		std::cout << "Timer not created" << std::endl;
		exit(1);
	}else{
		 timeM->addTimer(this);
		 stop = 1;
	}
}

void Timer::createSignalTimer(int s, int ns, int errorcode) {
	struct sigevent event;

	cout << "create signal timer..";

	//SIGEV_SIGNAL_INIT (&event, 200);
	//SIGEV_SIGNAL_CODE_INIT (&event, 1, 1, 1);
	SIGEV_SIGNAL_VALUE_INIT(&event, 1, errorcode);
	//&event

	if((timer_create (CLOCK_REALTIME, &event, &timerid))==-1){
		std::cout << "Timer not created" << std::endl;
		exit(1);
	}else{
		 timeM->addTimer(this);
		 stop = 1;
	}

	itimerspec nval;
	nval.it_value.tv_sec = s;
	nval.it_value.tv_nsec= ns;
	nval.it_interval.tv_sec = 0;
	nval.it_interval.tv_nsec = 0;
	if(timerid != -1){
		timer_settime(timerid, 0, &nval,NULL);
		cout << "done" << endl;
		stop = 0;
	} else {
		cout << "error" << endl;
	}


}

int Timer::createTimerPulse(){
    if( (channel  = ChannelCreate(0)) == -1){
    	cout << "exit in timer 1" << endl;
        //exit(EXIT_FAILURE);
    	return 0;
    }
    if( (connection = ConnectAttach(0, 0, channel, 0, 0)) == -1){
    	cout << "exit in timer 2" << endl;
        //exit(EXIT_FAILURE);
    	return 0;
    }

    SIGEV_PULSE_INIT (&timerEvent, connection, SIGEV_PULSE_PRIO_INHERIT, 0, 0);

    createTimer();
    return channel;

}

void Timer::setTimer(int s, int ns, bool scaleTime, bool shouldUpdate){
	if(timerid == -1){
		createTimer();
	}

	if(timerid != -1 ){
		this->scaleTime = scaleTime;
		val.it_value.tv_sec = s;
		val.it_value.tv_nsec= ns;
		val.it_interval.tv_sec = 0;
		val.it_interval.tv_nsec = 0;
		if(timerid != -1){
			timer_settime(timerid, 0, &val,NULL);
			stop = 0;
		}else{
			std::cout << "Timer not set" << std::endl;
			exit(1);
		}
	}

	if(shouldUpdate) timeM->updateTimer(this);
}

void Timer::setTimer(int s, int ns, bool scaleTime){
	setTimer(s, ns, scaleTime, true);
}

void Timer::setTimer(int s, int ns) {
	setTimer(s, ns, scaleTime);
}

void Timer::deleteTimer(){
	timer_delete(timerid);
	timeM->deleteTimer(this);
	stop = 1;
	timerid = -1;

}

void Timer::stopTimer(){
	if(timerid != -1 && !stop){
		getTime(&stopval);
		setTimer(900000,0, scaleTime, false);
		stop = 1;
	}

}

void Timer::continueTimer(){
	if(timerid != -1 && stop){
		setTimer(stopval.tv_sec,stopval.tv_nsec);
		stop = 0;
	}

}

void Timer::getTime(struct timespec *offset){
	if(timerid!=-1){
		if(!stop){
			timer_gettime(timerid,&result);
			offset->tv_nsec = result.it_value.tv_nsec;
			offset->tv_sec = result.it_value.tv_sec;
		}else{
			offset->tv_nsec = stopval.tv_nsec;
			offset->tv_sec = stopval.tv_sec;
		}
	}else{
		offset->tv_nsec = -1;
		offset->tv_sec = -1;
	}

}

void Timer::waitForTimeOut(int s, int ns, bool scaleTime){
	struct _pulse pulse;
	this->scaleTime = scaleTime;
	int channel = createTimerPulse();
	setTimer(s,ns);
	//Timer timer;
	MsgReceivePulse(channel, &pulse, sizeof(pulse), NULL);
	ConnectDetach(connection);
}

void Timer::waitForTimeOut(int s, int ns){
	waitForTimeOut(s, ns, false);
}

void Timer::waitForTimeOut(){
	struct _pulse pulse;
	int channel = createTimerPulse();
	//Timer timer;
	MsgReceivePulse(channel, &pulse, sizeof(pulse), NULL);
	ConnectDetach(connection);

}

bool Timer::isStopped() {
	return stop;
}


