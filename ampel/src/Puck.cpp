/*
 * Puk.cpp
 *
 *  Created on: 27.05.2015
 *      Author: abn908
 */

#include "Puck.h"

#include <iostream>

int Puck::idCount = 0;
Puck::Puck() {
	metal = false;
	holeOnTop = false;
	size = 0;
	//sizeTyp = UNKNOWN;
	sizeTyp = NOT_OK;	//Default sortingPuck out
	id = idCount++;
	needUserInteraction = false;

	std::cout << "Puck is created" << std::endl;
}

Puck::~Puck() {

	// TODO Auto-generated destructor stub
}

