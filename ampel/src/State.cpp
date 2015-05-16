/*
 * State.cpp
 *
 *  Created on: 06.05.2015
 *      Author: abl441
 */


#ifndef STATE_CPP_
#define STATE_CPP_

#include "Transition.h"
#include <cstdio>
#include <string>
using namespace std;

class State: public Transitions {
private:
	const string name_;

public:
	State(string name): name_(name){
		printf("State(string name)\n");
	}
	virtual ~State(){
		printf("~State()\n");
	}
    virtual void Running_In(void){
    	printf("State=%s Method=Running_In\n", name_.c_str());
    }
    virtual void In_Height(void){
    	printf("State=%s Method=In_Height\n", name_.c_str());
    }
    virtual void Height_Status(void){
    	printf("State=%s Method=Height_Status\n", name_.c_str());
    }
	virtual void Puck_in_Gate(void){
    	printf("State=%s Method=Puck_in_Gate\n", name_.c_str());
    }
    virtual void Metal_detection(void){
    	printf("State=%s Method=Metal_detection\n", name_.c_str());
    }
    virtual void Gate_open(void){
    	printf("State=%s Method=Gate_open\n", name_.c_str());
    }
    virtual void Slide_full(void){
    	printf("State=%s Method=Slide_full\n", name_.c_str());
    }
    virtual void Running_out(void){
    	printf("State=%s Method=Running_out\n", name_.c_str());
    }
};

#endif /* STATE_H_ */
