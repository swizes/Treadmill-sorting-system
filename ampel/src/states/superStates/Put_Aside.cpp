/*
 * Put_Aside.cpp
 *
 *  Created on: 02.06.2015
 *      Author: swizes
 */

#include "PuckStates.h"

Put_Aside::Put_Aside(Context* con): State::State(con){
	printf("Put Aside()\n");
	//TODO: Ask for user interaction
	//Dispatcher* dsp = Dispatcher::getInstance();
	//dsp->addListeners( this->con_, PUCK_IN_GATE_TRUE);
}

Put_Aside::~Put_Aside(){
	printf("~Put side()\n");

}

//void Put Aside::Puck_in_Gate_true(void){
//
//	//TODO:GO BACK TO NOT EXIST
//}





