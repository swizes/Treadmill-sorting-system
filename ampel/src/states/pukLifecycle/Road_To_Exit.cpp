/*
 * Road_To_Exit.cpp
 *
 *  Created on: 30.05.2015
 *      Author: Cumhur
 */
#include "PuckStates.h"


Road_To_Exit::Road_To_Exit(Context* con): State::State(con){
	HAL *hal= HAL::getInstance();

	BandController* bc = BandController::getInstance();

	this->con_->getPuck()->runBandFast();
	bc->refreshBand();


	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->addListeners( this->con_, RUNNING_OUT_TRUE);

	delay(600);
	hal->close_gate();

	cout << "Road To Exit ----- PuckId: " << this->con_->getPuck()->getId() << endl;
	cout << "TYPE IS : " << this->con_->getPuck()->isMetal() << endl;
	cout << "HOLE IS : " << this->con_->getPuck()->isHoleOnTop() << endl;

}

Road_To_Exit::~Road_To_Exit(){
	printf("~Road_to_Exit()\n");

}

void Road_To_Exit::Running_out_true(void){

	// Stop listen to Event Transmission1
	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->remListeners( this->con_, RUNNING_OUT_TRUE);

	CalibrateThread* ct = CalibrateThread::getInstance();



	//Band2
	if(ct->isBand() == 1){
		BandController* bc = BandController::getInstance();

		bc->delPuck(this->con_->getPuck());
		bc->refreshBand();


		//TODO: ENDE VOM BAND 2 DATEN AUSGEBEN
		//cout << "PUCK ID: " << this->con_->getPuck()->getId() << endl;
		//cout << "PUCK TYP: " << this->con_->getPuck()->getSizeTyp() << endl;
		//TODO: getHeightBand1
		//cout << "HÖHEN-MESSWERT VON BAND 1" << this->con_->getPuck()->getHeightBand1
		//cout << "HÖHEN-MESSWERT VON BAND 2" << this->con_->getPuck()->getHeightBand2

		new (this) Give_New_Puck(NULL);
	}else{
		new (this) User_Interaction_needed(this->con_);
	}

}

