/*
 * TimerManagement.cpp
 *
 *  Created on: 28.05.2015
 *      Author: abn908
 */

#include "TimerManagement.h"


TimerManagement* TimerManagement::instance_ = NULL;

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
	// TODO Auto-generated constructor stub

}

TimerManagement::~TimerManagement() {
	// TODO Auto-generated destructor stub
}

