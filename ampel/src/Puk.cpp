/*
 * Puk.cpp
 *
 *  Created on: 27.05.2015
 *      Author: abn908
 */

#include "Puk.h"


int Puk::idCount = 0;
Puk::Puk() {
	metal = false;
	holeOnTop = false;
	size = 0;
	sizeTyp = UNKNOWN;
	id = idCount++;



}

Puk::~Puk() {

	// TODO Auto-generated destructor stub
}

