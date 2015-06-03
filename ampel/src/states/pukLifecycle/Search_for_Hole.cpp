/*
 * Search_For_Hole.cpp
 *
 *  Created on: 28.05.2015
 *      Author: swizes
 */

#include "PuckStates.h"
int alternate = 0;

Search_for_Hole::Search_for_Hole(Context* con): State::State(con){
	printf("SearchSearch_for_Hole for Hole\n");
	//TODO: Set the type of Puck and save it
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->addListeners( this->con_, IN_HEIGHT_FALSE);
}

Search_for_Hole::~Search_for_Hole(){
	printf("~Search for Hole()\n");

}

void Search_for_Hole::In_Height_false(void){


	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners( this->con_, IN_HEIGHT_FALSE);


//	if(type==ok){
//	  if(!loch){
//		  Mark the puck for userinteraction
//	  }
//	  //Move to State Road_to_Metal
//	  new (this) Road_to_Metal(this->con_);
//	}
//
//	If(type==trash){
//	 Move to State Road to Sorting Out
//	new (this) Road_to_Sorting_Out(this->con_);
//	}

	//abwechselnd aussortieren oder durchlassen
	if(alternate == 1){
		new(this) Road_to_Sorting_Out(this->con_);
		alternate = 0;
	}else{
		new (this) Road_to_Metal(this->con_);
		alternate = 1;
	}
}


