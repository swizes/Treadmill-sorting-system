/*
 * Road_to_Height.cpp
 *
 *  Created on: 28.05.2015
 *      Author: Roland
 */
#include "PuckStates.h"


Road_to_Height::Road_to_Height(Context* con): State::State(con){


	Dispatcher* dsp = Dispatcher::getInstance();
	dsp->addListeners( this->con_, IN_HEIGHT_TRUE);

	cout << "Road To Height ----- PuckId: " << this->con_->getPuck()->getId() << endl;

		Timer time;
		struct timespec result;
		time.getTime(&result);



	//TODO: how to check if puck is in height
	///// ********** ///////
	/*
	 * bool timeout = false;
	 * while(!timeout) {
	 *    if(!(result.tv_sec <= 0) && IN_HEIGHT_TRUE){
	 *      timeout = true;
	 *      dsp->addListeners( this->con_, IN_HEIGHT_TRUE);
	 *    } else {
	 *    	cout << "Waited too much, puck betrayed us" << endl;
	 *    	new (this) Error_Handling(this->con_);
	 *    }
	 * }
	 */
}

Road_to_Height::~Road_to_Height(){
	printf("~Road to Height()\n");

}

void Road_to_Height::In_Height_true (void){
	Timer time;
	struct timespec result;
	time.getTime(&result);

	//To soon >> less than 1,5 sec a puck has arrived
	if (result.tv_sec > 1 && result.tv_nsec > 5) {
		cout << "Too soon... There is an extra puck" << endl;
		new (this) Error_Handling(this->con_);
	}
	else {
			// Stop listen to Event Transmission1
			Dispatcher* dsp = Dispatcher::getInstance();
			BandController* bc = BandController::getInstance();

			//TODO: Check, da eig nicht ueber HAL auf Band zugegriffen werden soll
			this->con_->getPuck()->runBandSlowly();
			bc->refreshBand();

			dsp->remListeners( this->con_, IN_HEIGHT_TRUE);

			// Move to State Height Measurement.
			new (this) Height_Measurement(this->con_);
	}



}
