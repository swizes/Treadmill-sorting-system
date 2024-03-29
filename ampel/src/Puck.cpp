/*
 * Puk.cpp
 *
 *  Created on: 27.05.2015
 *      Author: abn908
 */

#include "Puck.h"

#include <iostream>

int Puck::idCount = -2;
Puck::Puck() {
	metal = false;
	holeOnTop = false;
	size = 0;
	sizeBand1 = 0;
	//sizeTyp = UNKNOWN;
	sizeTyp = NOT_OK;	//Default sortingPuck out
	id = idCount++;
	needUserInteraction = false;
	stopBand_ = 0;
	runBandSlowly_ = 0;
	runBandFast_ = 0;

//	std::cout << "ID: " << id << "  idCount: " << idCount << std::endl;

//	std::cout << "Puck is created" << std::endl;
}


//Copy Constructor
Puck::Puck(const Puck &obj){
	metal = obj.metal;
	holeOnTop = obj.holeOnTop;
	size = obj.size;
	sizeBand1 = obj.sizeBand1;
	sizeTyp = obj.sizeTyp;
	id = obj.id;
	needUserInteraction = obj.needUserInteraction;
	stopBand_ = obj.stopBand_;
	runBandSlowly_ = obj.runBandSlowly_;
	runBandFast_ = obj.runBandFast_;
}

Puck::~Puck() {

	// TODO Auto-generated destructor stub
}

void Puck::setPuckFromStruct(puckStruct puckS) {
	this->metal = puckS.metal;
	this->holeOnTop = puckS.holeOnTop;
	this->size = puckS.size;
	this->sizeBand1 = puckS.sizeBand1;
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
	puckS.sizeBand1 = this->sizeBand1;
	return puckS;

}
