/*
 * State.cpp
 *
 *  Created on: 06.05.2015
 *      Author: abl441
 */

#ifndef STATE_CPP_
#define STATE_CPP_

#include "Transition.h"
#include "Context.cpp"
#include <cstdio>
#include <string>
using namespace std;

class State: public Transitions {
protected:
	Context* con_;

private:
	const string name_;

public:
	State(Context* con): con_(con){
		printf("State(Context* con)\n");
	}
	virtual ~State() {
		printf("~State()\n");
	}
	virtual void Running_In_true(void) {
		//printf("RUN");
		//printf("State=%s Method=Running_In_True\n", name_.c_str());
	}
	virtual void In_Height_true(void) {
		//printf("State=%s Method=In_Height_True\n", name_.c_str());
	}
	virtual void Height_Status_OK(void) {
		//printf("State=%s Method=Height_Status_OK\n", name_.c_str());
	}
	virtual void Puck_in_Gate_true(void) {
		//printf("State=%s Method=Puck_in_Gate_True\n", name_.c_str());
	}
	virtual void Metal_detection_true(void) {
		//printf("State=%s Method=Metal_detection_True\n", name_.c_str());
	}
	virtual void Gate_open_true(void) {
		//printf("State=%s Method=Gate_open_True\n", name_.c_str());
	}
	virtual void Slide_full_true(void) {
		//printf("State=%s Method=Slide_full_True\n", name_.c_str());
	}
	virtual void Running_out_true(void) {
		//printf("State=%s Method=Running_out_True\n", name_.c_str());
	}
	virtual void Running_In_false(void) {
		//printf("State=%s Method=Running_In_False\n", name_.c_str());
	}
	virtual void In_Height_false(void) {
		//printf("State=%s Method=In_Height_False\n", name_.c_str());
	}
	virtual void Height_Status_NOTOK(void) {
		//printf("State=%s Method=Height_Status_NOTOK\n", name_.c_str());
	}
	virtual void Puck_in_Gate_false(void) {
		//printf("State=%s Method=Puck_in_Gate_False\n", name_.c_str());
	}
	virtual void Metal_detection_false(void) {
		//printf("State=%s Method=Metal_detection_False\n", name_.c_str());
	}
	virtual void Gate_open_false(void) {
		//printf("State=%s Method=Gate_open_False\n", name_.c_str());
	}
	virtual void Slide_full_false(void) {
		//printf("State=%s Method=Slide_full_False\n", name_.c_str());
	}
	virtual void Running_out_false(void) {
		//printf("State=%s Method=Running_out_False\n", name_.c_str());
	}
};

#endif /* STATE_H_ */
