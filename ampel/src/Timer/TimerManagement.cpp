/*
 * TimerManagement.cpp
 *
 *  Created on: 28.05.2015
 *      Author: abn908
 */

#include "TimerManagement.h"


TimerManagement* TimerManagement::instance_ = NULL;

vector<Timer*> data;
TIMESCALE currentTimeScale = FAST;

/**
* c'tor for the Thread-safe singleton HAL implementation
* @param none
* @return A Pointer to the Singleton HAL Object
*/
TimerManagement* TimerManagement::getInstance(){
	if (instance_ != NULL){
			return instance_;
	}else{
		instance_ = new TimerManagement();
		return instance_;
	}

}

TimerManagement::TimerManagement() {
	std::cout << "ctor TimerManagement" << std::endl;
}

TimerManagement::~TimerManagement() {
	std::cout << "dtor TimerManagement"<< std::endl;
}

void TimerManagement::addTimer(Timer *timer){
	data.push_back(timer);
}

void TimerManagement::updateTimer(Timer *timer) {
	if(timeScaleFactor == 0) {
		cout << "Error! timeScaleFactor not set / = 0" << endl;
		return;
	}

	if(!timer->scaleTime) {
		cout << "timer should not scale." << endl;
		return;
	}

	timespec t_spec;

	if(timer->currentScale == 1 && this->currentTimeScale == SLOW)
	{
		cout << "scale up new timer" << endl;

		timer->getTime(&t_spec);
		timer->currentScale = timeScaleFactor;
		cout << "spec sec:" << t_spec.tv_sec << "nsec:" << t_spec.tv_nsec << endl;
		if(timer->isStopped() && timer->shouldContinue) timer->continueTimer();

		timer->setTimer(t_spec.tv_sec*timeScaleFactor, t_spec.tv_nsec*timeScaleFactor);
	} else if (timer->currentScale != 1 && this->currentTimeScale == FAST) {
		timer->getTime(&t_spec);
		timer->currentScale = 1;
		cout << "spec sec:" << t_spec.tv_sec << "nsec:" << t_spec.tv_nsec << endl;
		if(timer->isStopped() && timer->shouldContinue) timer->continueTimer();

		timer->setTimer(t_spec.tv_sec/timeScaleFactor, t_spec.tv_nsec/timeScaleFactor);
	} else if (this->currentTimeScale == STOPPED) {
		timer->stopTimer();
		timer->shouldContinue = true;
	}
}

void TimerManagement::deleteTimer(Timer *timer){
	for(uint8_t i = 0;i < data.size();i++){
		if(data.at(i) == timer){
			data.erase(data.begin()+i,data.begin()+i);
		}
	}
}
void TimerManagement::deleteTimer(){
	data.clear();
}

void TimerManagement::stopTimer(){
	int length = data.size();
	for(int i = 0; i < length;i++){
		data.at(i)->stopTimer();
	}
}

void TimerManagement::continueTimer(){
	int length = data.size();
	for(int i = 0; i < length;i++){
		data.at(i)->continueTimer();
	}
}

void TimerManagement::setTimeScaleFactor(double timeScaleFactor){
	this->timeScaleFactor = timeScaleFactor;
}

void TimerManagement::setScaleTime(TIMESCALE scaleTime) {
	if(scaleTime == this->currentTimeScale) return;
	if(timeScaleFactor == 0) {
		cout << "Error! timeScaleFactor not set / = 0" << endl;
	}

	this->currentTimeScale = scaleTime;
	timespec t_spec;

	cout << "set TimerManagement scaleTime" << endl;
	if(scaleTime == SLOW) {
		//upscale time
		for(int i = 0; i < data.size(); i++){
			if (data.at(i)->scaleTime && data.at(i)->currentScale == 1) {
				cout << "upscale timer " << i << endl;
				if(data.at(i)->isStopped() && data.at(i)->shouldContinue) data.at(i)->continueTimer();
				data.at(i)->getTime(&t_spec);
				data.at(i)->setTimer(t_spec.tv_sec*timeScaleFactor, t_spec.tv_nsec*timeScaleFactor, true, false);
				data.at(i)->currentScale = timeScaleFactor;
			}
		}
	} else if(scaleTime == FAST) {
		//downscale
		for(int i = 0; i < data.size(); i++){
			if (data.at(i)->scaleTime && data.at(i)->currentScale != 1) {
				cout << "upscale timer " << i << endl;
				if(data.at(i)->isStopped() && data.at(i)->shouldContinue) data.at(i)->continueTimer();
				data.at(i)->getTime(&t_spec);
				data.at(i)->setTimer(t_spec.tv_sec/timeScaleFactor, t_spec.tv_nsec/timeScaleFactor, true, false);
				data.at(i)->currentScale = 1;
			}
		}
	} else if(scaleTime == STOPPED) {
		for(int i = 0; i < data.size(); i++){
			if (data.at(i)->scaleTime) {
				cout << "stop timer " << i << endl;
				if(!data.at(i)->isStopped()) data.at(i)->shouldContinue = true;
				data.at(i)->stopTimer();
			}
		}
	}
}
