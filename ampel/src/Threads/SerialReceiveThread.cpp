/*
 * ESTOPTHREAD.cpp
 *
 *  Created on: 30.06.2015
 *      Author: abl441
 */

#include "SerialReceiveThread.h"
#include <exception>

puckStruct tempPuck;

SerialReceiveThread::SerialReceiveThread() {
	// TODO Auto-generated constructor stub
}

SerialReceiveThread::~SerialReceiveThread() {
	// TODO Auto-generated destructor stub
}

void SerialReceiveThread::execute(void*){
	puckStruct puck;

	while(true) {
		ser.recvPacket(&puck);

		switch(puck.type) {

		}
	}
}

int SerialReceiveThread::recvPacket(puckStruct* puck) {

}



void SerialReceiveThread::shutdown(){
    cout << "E_Stop_Thread shutdown" << endl;
}
