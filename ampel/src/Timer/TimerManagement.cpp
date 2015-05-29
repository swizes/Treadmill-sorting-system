/*
 * TimerManagement.cpp
 *
 *  Created on: 28.05.2015
 *      Author: abn908
 */

#include "TimerManagement.h"


TimerManagement* TimerManagement::instance_ = NULL;

vector<class Timer> data;

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
	}

}

TimerManagement::TimerManagement() {
	std::cout << "ctor TimerManagement" << std::endl;
}

TimerManagement::~TimerManagement() {
	std::cout << "dtor TimerManagement"<< std::endl;
}

void TimerManagement::addTimer(Timer timer){
	data.push_back(timer);
}

void TimerManagement::deleteTimer(Timer timer){
	for(uint8_t i = 0;i < data.size();i++){
		/*if(data.at(i) == timer){
			data.erase(data.begin()+i,data.begin()+i);
		}*/
	}

}
void TimerManagement::deleteTimer(){
	for(uint8_t i = 0; i < data.size();i++){
		data.erase(data.begin()+i,data.begin()+i);
	}

}

void TimerManagement::stopTimer(){
	int length = data.size();
	for(int i = 0; i < length;i++){
		data.at(i).stopTimer();
	}
}
void TimerManagement::continueTimer(){
	int length = data.size();
	for(int i = 0; i < length;i++){
		data.at(i).continueTimer();
	}
}

