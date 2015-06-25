/*
 * PortCListenerThread.cpp
 *
 *  Created on: 25.06.2015
 *      Author: tobi
 */

#include "PortCListenerThread.h"

#define E_STOP 7

PortC_ListenerThread::PortC_ListenerThread() {
	// TODO Auto-generated constructor stub
	cout << "ctor PortC_listenerThread" << endl;


}

PortC_ListenerThread::~PortC_ListenerThread() {
	// TODO Auto-generated destructor stub
}

void PortC_ListenerThread::execute(void*){

	if (ThreadCtl(_NTO_TCTL_IO_PRIV, 0) == -1){
		exit(EXIT_FAILURE);
	}

	if (( isrChannel = ChannelCreate(0)) == -1){
		exit(EXIT_FAILURE);
	}


	if ((isrConnection = ConnectAttach(0, 0, isrChannel, 0, 0)) == -1){
		exit(EXIT_FAILURE);
	}


	registerISR_PortC();


	uint8_t oldPort = in8(PORT_C);

	HAL* hal = HAL::getInstance();

	// React on Pulsemessage
	struct _pulse pulse;
	do{
		try
		{
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

			if(val == E_STOP){
				//TODO: Sinnvollen Kram
				hal->band_stop();
			}
			//printf("Got an Interrupt, Bit: %d value: %d\n", stateChanged, val);
		} catch (exception& e) {
			cout << "exception caught: " << e.what() << endl;
		}

	}while(1);

}


void PortC_ListenerThread::shutdown(){
    cout << "PortC_ListenerThread shutdown" << endl;


}

