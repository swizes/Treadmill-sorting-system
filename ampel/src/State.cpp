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
    virtual void Transition1(void){
    	printf("State=%s Method=Transition1\n", name_.c_str());
    }
    virtual void Transition2(void){
    	printf("State=%s Method=Transition2\n", name_.c_str());
    }
    virtual void Transition3(void){
    	printf("State=%s Method=Transition3\n", name_.c_str());
    }
};

#endif /* STATE_H_ */
