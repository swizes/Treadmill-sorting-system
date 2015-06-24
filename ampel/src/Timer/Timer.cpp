/*
 * Timer.cpp
 *
 *  Created on: 17.05.2015
 *      Author: lukasTest
 */

#include "Timer.h"

TimerManagement *timeM;
int channel;
int connection;


Timer::Timer() {
	//std::cout << "ctor Timer" << std::endl;
	TimerManagement *time = TimerManagement::getInstance();
	timeM = time;
	timerid = -1;


}

Timer::~Timer() {
	this->deleteTimer();
	//std::cout << "dtor Timer" << std::endl;
	// TODO Auto-generated destructor stub
}

void Timer::createTimer(){

	if((timer_create(CLOCK_REALTIME, &timerEvent, &timerid))==-1){
		std::cout << "Timer not created" << std::endl;
		exit(1);
	}else{
		 timeM->addTimer(*this);
		 stop = 1;
	}
}

int Timer::createTimerPulse(){
    if( (channel  = ChannelCreate(0)) == -1){
        exit(EXIT_FAILURE);
    }
    if( (connection = ConnectAttach(0, 0, channel, 0, 0)) == -1){
        exit(EXIT_FAILURE);
    }

    SIGEV_PULSE_INIT (&timerEvent, connection, SIGEV_PULSE_PRIO_INHERIT, 0, 0);

    createTimer();
    return channel;

}

void Timer::setTimer(int s, int ns){
	if(timerid == -1){
		createTimer();
	}
	if(timerid != -1 && stop){
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

}

void Timer::deleteTimer(){
	timer_delete(timerid);
	timeM->deleteTimer(*this);
	stop = 1;
	timerid = -1;

}

void Timer::stopTimer(){
	if(timerid != -1 && !stop){
		getTime(&stopval);
		setTimer(0,0);
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
void Timer::waitForTimeOut(int s, int ns){

	struct _pulse pulse;
	int channel = createTimerPulse();
	setTimer(s,ns);
	//Timer timer;
	MsgReceivePulse(channel, &pulse, sizeof(pulse), NULL);


}

void Timer::waitForTimeOut(){
	struct _pulse pulse;
	int channel = createTimerPulse();
	//Timer timer;
	MsgReceivePulse(channel, &pulse, sizeof(pulse), NULL);

}



