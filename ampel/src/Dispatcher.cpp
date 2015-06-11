/*
 * Dispatcher.cpp
 *
 *  Created on: 06.05.2015
 *      Author: abl441
 */


#include "Dispatcher.h"
using namespace std;

int isrChannel = 0;
int isrConnection = 0;
struct sigevent isrEvent;

Dispatcher:: Dispatcher(){
	// Clear Listener Pointer 2Dim Array
	for(int i=0; i<NEVENTS; i++){
		for(int j=0; j<MAXLISTENERS; j++){
			listeners_[i][j] = NULL;
		}
	}

	// Add Method pointer to Call Method Array
	methods[0] = &Transitions::Running_In_true;
	methods[1] = &Transitions::In_Height_true;
	methods[2] = &Transitions::Height_Status_OK;
	methods[3] = &Transitions::Puck_in_Gate_true;
	methods[4] = &Transitions::Metal_detection_true;
	methods[5] = &Transitions::Gate_open_true;
	methods[6] = &Transitions::Slide_full_true;
	methods[7] = &Transitions::Running_out_true;
	methods[8] = &Transitions::Running_In_false;
	methods[9] = &Transitions::In_Height_false;
	methods[10] = &Transitions::Height_Status_NOTOK;
	methods[11] = &Transitions::Puck_in_Gate_false;
	methods[12] = &Transitions::Metal_detection_false;
	methods[13] = &Transitions::Gate_open_false;
	methods[14] = &Transitions::Slide_full_false;
	methods[15] = &Transitions::Running_out_false;


	


}

Dispatcher::  ~Dispatcher(){

}

Dispatcher* Dispatcher::getInstance(void){
	static Dispatcher instance_;
	return &instance_;
}

void Dispatcher:: addListeners(Transitions* listener, EVENTS event){
	// Add Listener to be called on a specific Event
	for(int i=0; i<MAXLISTENERS; i++){
		if( listeners_[event][i] == NULL || listeners_[event][i] == listener){
			listeners_[event][i] = listener;
			return;
		}
	}
	printf("Sorry, no Space for Listener at requested Event left\n");
}

void Dispatcher:: remListeners(Transitions* listener, EVENTS event){
	// Remove Listener from a specific Event
	int res = 0;
	int j = -1;

	for(int i=0; i<MAXLISTENERS; i++){

		//Liste von hinten nach vorne kopieren
		if(j >= 0 && listeners_[event][i] != NULL){
			listeners_[event][j] = listeners_[event][i];
		}

		if( listeners_[event][i] == listener){
			listeners_[event][i] = NULL;
			res = 1;
			j = i;
		}
	}

	if(res){return;}

	printf("Sorry, couldn't find Listener at requested Event\n");
}

void Dispatcher:: callListeners(EVENTS event){
	// Call for every registered Listener
	// the Method that corresponds with event.
	for(int i=0; i<MAXLISTENERS; i++){
		if( listeners_[event][i] != NULL){
			(listeners_[event][i]->*methods[event])();
			break; //call only the first
		}
	}
}




void Dispatcher:: listenForEvents(){

	if (ThreadCtl(_NTO_TCTL_IO_PRIV, 0) == -1){
			exit(EXIT_FAILURE);
	}

	if (( isrChannel = ChannelCreate(0)) == -1){
		exit(EXIT_FAILURE);
	}


	if ((isrConnection = ConnectAttach(0, 0, isrChannel, 0, 0)) == -1){
		exit(EXIT_FAILURE);
	}


	registerISR();

	uint8_t oldPort = in8(PORT_B);

	// React on Pulsemessage
	struct _pulse pulse;
	do{
		//cout << "Wait for Interrupt" << endl;
		MsgReceivePulse(isrChannel,&pulse,sizeof(pulse),NULL);

		uint8_t sival = pulse.value.sival_int;

		// old XOR new = stateChanged
		uint8_t stateChanged = oldPort ^ sival;
		//printf("oldPort: %x     %d\n", pulse.value.sival_int, stateChanged);

		//old = new
		oldPort = sival;

		//Register Value
		uint8_t val = oldPort & stateChanged;

		//log2 for changed registerbit
		stateChanged = (float) log(stateChanged) / (float) log(2);

		//Shift -> 0 or 1
		val = !(val << stateChanged);

		if (val == 1){
			//printf("Got an Interrupt, Bit: %d value: %d\n", stateChanged, val);
			callListeners((EVENTS)stateChanged);
		} else {
			//printf("Got an Interrupt, Bit: %d value: %d\n", stateChanged+EVENT_OFFSET, val);
			callListeners((EVENTS)(stateChanged+EVENT_OFFSET));
		}
		//printf("Got an Interrupt, Bit: %d value: %d\n", stateChanged, val);

		cout << endl;
	}while(1);

	// Cleanup
	unregisterISR();
    if( ConnectDetach(isrConnection) == -1){
        exit(EXIT_FAILURE);
    }

    if( ChannelDestroy(isrChannel) == -1 ){
        exit(EXIT_FAILURE);
    }
}
