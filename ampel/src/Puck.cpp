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
	stopBand_ = false;
	runBandSlowly_ = false;
	runBandFast_ = false;

	std::cout << "Puck is created" << std::endl;
}

Puck::~Puck() {

	// TODO Auto-generated destructor stub
}

void Puck::setPuckFromStruct(puckStruct puckS) {
	this->metal = puckS.metal;
	this->holeOnTop = puckS.holeOnTop;
	this->size = puckS.size;
	this->sizeTyp = puckS.sizetyp;
	this->id = puckS.id;
	this->needUserInteraction = puckS.needUserInteraction;
}

puckStruct Puck::getPuckStruct(void){
	puckStruct puckS;
	puckS.metal = this->metal;
	puckS.holeOnTop = this->holeOnTop;
	puckS.size = this->size;
	puckS.sizetyp = this->sizeTyp;
	puckS.id = this->id;
	puckS.needUserInteraction = this->needUserInteraction;
	return puckS;

}
