/*
 * PuckLifcycleFSM.cpp
 *
 *  Created on: 10.06.2015
 *      Author: abn908
 */

#include "SerialCommunicationThread.h"


SerialCommunicationThread* SerialCommunicationThread::instance_ = NULL;

SerialCommunicationThread* SerialCommunicationThread::getInstance() {
	static pthread_mutex_t mtx_ = PTHREAD_MUTEX_INITIALIZER;

	if (instance_ == NULL) {
		pthread_mutex_lock(&mtx_);
		if (instance_ == NULL) {
			instance_ = new SerialCommunicationThread();
		}
		pthread_mutex_unlock(&mtx_);
	}
	return instance_;
}

SerialCommunicationThread::SerialCommunicationThread() {
	cout << "ReadySend" << endl;
	type = 1;
}

SerialCommunicationThread::~SerialCommunicationThread() {
	// TODO Auto-generated destructor stub
}



void SerialCommunicationThread::execute(void* con){
	Serial ser;
	Packet p;
	while(1){
		p.num = this->type;
		ser.sendPacket(&p);
		ser.recvPacket(&p);
		/*nothing = 0;
		  error = 1;
		  receivePuck = 2;
		  sendPuck = 3;
		 */
		switch(p.num){
			case 0:
			case 1:
				cout << "Error Handling"  << endl;
			case 2:
				cout << "Send Request" << endl;
				if (type == 3){
					ser.sendPacket(&ps);
					received = 1;
					ser.recvPacket(&p);
					type = 0;
				}
			case 3:
				cout << "Receive Request"  << endl;
				if (type == 2){
					ser.sendPacket(&p);
					ser.recvPacket(&ps);
					type = 0;
				}
			default: cout <<"error Wrong Code" << endl;
		}
		//Timer time;
		//time.waitForTimeOut(0,100000000);
		delay(100);
		//cout << "Ready" << endl;
	}

}

void SerialCommunicationThread::shutdown(){

}

void SerialCommunicationThread::receivePuck(Puck *puck){
	type = 2;
	int i = 1;
	while(i){
			delay(100);
			if(received ==1){
				puck->setPuckFromStruct(ps);
				i = 0;
				received = 0;
			}
	}
}

void SerialCommunicationThread::sendPuck(Puck *puck){
	ps = puck->getPuckStruct();
	type = 3;
}

void SerialCommunicationThread::sendError(){
	type = 1;
}

void SerialCommunicationThread::busy(){
	type = 0;
}

/*void ReadSend::rdy(){
	stop();
	type = 1;
	start();
}*/
