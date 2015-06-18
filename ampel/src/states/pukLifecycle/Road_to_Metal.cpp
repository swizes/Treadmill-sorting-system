/*
 * Road_to_Metal.cpp
 *
 *  Created on: 28.05.2015
 *      Author: swizes
 */

#include "PuckStates.h"
//TODO: Class name should be changed to Metal Detection
Road_to_Metal::Road_to_Metal(Context* con): State::State(con){
	printf("Road_to_Metal()\n");
	Dispatcher* dsp = Dispatcher::getInstance();


//	BandController* bc = BandController::getInstance();
//	con->getPuck()->runBandFast();
//	bc->refreshBand();


	//TODO: Start timer
	//TODO: Is this necessary? The gate was already opened. Check the state in diagram (do / open_gate())
	//HAL *hal = HAL::getInstance();
	//hal->open_gate();

	  //dsp->addListeners( this->con_, METAL_DETECTION_TRUE);
	  //dsp->addListeners( this->con_, METAL_DETECTION_FALSE);

	  dsp->addListeners( this->con_, PUCK_IN_GATE_TRUE);


}

Road_to_Metal::~Road_to_Metal(){
	printf("~Road_to_Metal()\n");

}
//If the puck has metal
//void Road_to_Metal::Metal_detection_true(void){
//
//	cout<<"metal found"<<endl;
//	// Stop listen to Event Transmission1
//	Dispatcher* dsp = Dispatcher::getInstance();
//
//	con_->getPuck()->setMetal(true);
//
//	//dsp->remListeners( this->con_, METAL_DETECTION_TRUE);
//	//dsp->remListeners( this->con_, METAL_DETECTION_FALSE);
//	dsp->remListeners( this->con_, PUCK_IN_GATE_TRUE);
//
//	// Move to State Metal_Detected
//	new (this) Metal_Detected(this->con_);
//}
//
//void Road_to_Metal::Metal_detection_false(void){
//
//	cout<<"NO metal found"<<endl;
//	// Stop listen to Event Transmission1
//	Dispatcher* dsp = Dispatcher::getInstance();
//
//	con_->getPuck()->setMetal(false);
//
//	dsp->remListeners( this->con_, METAL_DETECTION_TRUE);
//	dsp->remListeners( this->con_, METAL_DETECTION_FALSE);
//
//	// Move to State Metal_Detected
//	new (this) Metal_Detected(this->con_);
//}
//
//
////SHOULD NOT BE REACHED
void Road_to_Metal::Puck_in_Gate_true(void){


	// Stop listen to Event Transmission2
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners( this->con_, PUCK_IN_GATE_TRUE);
	//dsp->remListeners( this->con_, METAL_DETECTION_TRUE);

	// Move to  Is In Gate
	new (this) Is_In_Gate(this->con_);

}



