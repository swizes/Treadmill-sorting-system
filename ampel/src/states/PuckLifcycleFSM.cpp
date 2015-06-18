/*
 * PuckLifcycleFSM.cpp
 *
 *  Created on: 10.06.2015
 *      Author: abn908
 */

#include "PuckLifcycleFSM.h"


PuckLifcycleFSM::PuckLifcycleFSM() {
	// TODO Auto-generated constructor stub
    if( ThreadCtl(_NTO_TCTL_IO_PRIV,0) == -1 ){
        cout << "Can't get Hardware access, therefore can't do anything." << endl;
    }

	out8(IO_CONTROL_ADDRESS, BM_IO_CONTROL);

}

PuckLifcycleFSM::~PuckLifcycleFSM() {
	// TODO Auto-generated destructor stub
}



void PuckLifcycleFSM::execute(void* con){

	Context* c = (Context*) con;
	c->setState(new Birth(c));
}

void PuckLifcycleFSM::shutdown(){

}
