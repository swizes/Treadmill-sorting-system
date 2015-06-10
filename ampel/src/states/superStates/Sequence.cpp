/*
 * Sequence.cpp
 *
 *  Created on: 02.06.2015
 *      Author: swizes
 */

#include "PuckStates.h"

Sequence::Sequence(Context* con): State::State(con){
	printf("Sequence()\n");
	HAL *hal = HAL::getInstance();
	hal->band_stop();

	/*
	if(last_puck->metal == true){
		if(this.puck->metal == true){
			if(reserved_puck->metal == true){
				new (this) Transfer(this->con);
			} else {
				//TODO: let last puk id overwrite Reserved puk
				new (this) Put_Aside(this->con);
			}
		} else {
			new (this) Transfer(this->con);
		}
	} else {
		if(this.puck->metal == true) {
			new (this) Transfer(this->con);
		} else {
			if(reserved_puck->metal == true){
				//TODO: let last puk id overwrite Reserved puk
				new (this) Put_Aside(this->con);
			} else {
				new (this) Transfer(this->con);
			}
		}
	}
	*/


	//Dispatcher* dsp = Dispatcher::getInstance();
	//dsp->addListeners( this->con_, PUCK_IN_GATE_TRUE);
}

Sequence::~Sequence(){
	printf("~Sequence()\n");

}

//void Sequence::Puck_in_Gate_true(void){
//
//
//	// Stop listen to Event Transmission1
//	Dispatcher* dsp = Dispatcher::getInstance();
//	dsp->remListeners( this->con_, PUCK_IN_GATE_TRUE);
//
//	// Move to State Is in Gate
//	new (this) Is_in_Gate(this->con_);
//}
//



