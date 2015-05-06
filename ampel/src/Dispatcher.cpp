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
	methods[0] = &Transitions::Transition1;
	methods[1] = &Transitions::Transition2;
	methods[2] = &Transitions::Transition3;


}

Dispatcher::  ~Dispatcher(){

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
	for(int i=0; i<MAXLISTENERS; i++){
		if( listeners_[event][i] == listener){
			listeners_[event][i] = NULL;
			return;
		}
	}
	printf("Sorry, couldn't find Listener at requested Event\n");
}

void Dispatcher:: callListeners(EVENTS event){
	// Call for every registered Listener
	// the Method that corresponds with event.
	for(int i=0; i<MAXLISTENERS; i++){
		if( listeners_[event][i] != NULL){
			(listeners_[event][i]->*methods[event])();
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
		cout << "Wait for Interrupt" << endl;
		MsgReceivePulse(isrChannel,&pulse,sizeof(pulse),NULL);

		// old XOR new
		uint8_t stateChanged = oldPort ^ pulse.value.sival_int;

		//old = new
		oldPort = pulse.value.sival_int;

		//log2 for changed bit
		stateChanged = log(stateChanged) / log(2);

		printf("Got an Interrupt, Bit: %d\n", stateChanged);
		callListeners((EVENTS)stateChanged);

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
