/*
 * Metal_Detected.cpp
 *
 *  Created on: 30.05.2015
 *      Author: swizes
 */


//#include "PuckStates.h"
//
//Metal_Detected::Metal_Detected(Context* con): State::State(con){
////entry:
//	printf("Metal Detected()\n");
////do:
//
//	Dispatcher* dsp = Dispatcher::getInstance();
//	dsp->remListeners( this->con_, METAL_DETECTION_TRUE);
//	dsp->addListeners( this->con_, PUCK_IN_GATE_FALSE);
//}
//
//Metal_Detected::~Metal_Detected(){
//	printf("~Metal Detected()\n");
//
//}
//
//void Metal_Detected::Puck_in_Gate_false(void){
//
//
//	// Stop listen to Event Transmission1
//	Dispatcher* dsp = Dispatcher::getInstance();
//	dsp->remListeners( this->con_, PUCK_IN_GATE_FALSE);
//
//	// Move to State Is in Gate
//	new (this) Is_In_Gate(this->con_);
//}
//
//
