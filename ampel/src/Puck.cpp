/*
 * Puk.cpp
 *
 *  Created on: 27.05.2015
 *      Author: abn908
 */

#include "Puck.h"


int Puck::idCount = 0;
Puck::Puck() {
	metal = false;
	holeOnTop = false;
	size = 0;
	//sizeTyp = UNKNOWN;
	sizeTyp = NOT_OK;	//Default sortingPuck out
	id = idCount++;
	needUserInteraction = false;


}

Puck::~Puck() {

	// TODO Auto-generated destructor stub
}

