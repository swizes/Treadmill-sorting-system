/*
 * Timer.cpp
 *
 *  Created on: 17.05.2015
 *      Author: lukasTest
 */

#include "Timer.h"



Timer::Timer() {
	std::cout << "ctor Timer" << std::endl;
	timerid = -1;


}

Timer::~Timer() {
	std::cout << "dtor Timer" << std::endl;
	// TODO Auto-generated destructor stub
}

void Timer::createTimer(){

	if((timer_create(CLOCK_REALTIME, &timerEvent, &timerid))==-1){
		std::cout << "Timer not created" << std::endl;
		exit(1);
	}
}

void Timer::setTimer(int s, int ns){
	val.it_value.tv_sec = s;
	val.it_value.tv_nsec= ns;
	if(timerid != -1){
		timer_settime(timerid, NULL, &val,NULL);

	}else{
		std::cout << "Timer not set" << std::endl;
		exit(1);
	}
}

void Timer::deleteTimer(){

	timer_delete(timerid);

}

void Timer::getTime(struct timespec *offset){

		timer_gettime(timerid,&result);

		offset->tv_nsec = result.it_value.tv_nsec;
		offset->tv_sec = result.it_value.tv_sec;


}



