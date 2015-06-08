/*
 * Height_Measurement.cpp
 *
 *  Created on: 28.05.2015
 *      Author: Roland
 */
#include "PuckStates.h"


Height_Measurement::Height_Measurement(Context* con): State::State(con){
	printf("Height_Measurement()\n");
	//TODO: Kill TIMER! von Road_to_Height
	HAL *hal = HAL::getInstance();
	hal->band_right_slowly();
	//TODO: HÖHENMESSUNG + SAVE DATA
	//TODO: PRECONDITION is_height_ok return true

	new (this) Search_for_Hole(this->con_);
}

Height_Measurement::~Height_Measurement(){
	printf("~Road_to_Height()\n");

}
