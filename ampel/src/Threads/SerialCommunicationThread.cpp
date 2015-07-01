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
	cout << "ctor SerialCommunicationThread" << endl;
	type = 1;
}

SerialCommunicationThread::~SerialCommunicationThread() {
	cout << "dtor SerialCommunicationThread" << endl;
	// TODO Auto-generated destructor stub
}



void SerialCommunicationThread::execute(void* con){
	Serial ser;
	while(1){
		puckStruct puck;
		puck.type = 0;
		if(ps.type == 3 || ps.type == 2){
			ser.sendPacket(&ps);
		}else{
			ser.sendPacket(&puck);
		}
		//cout << "Before Packet" << endl;
		ser.recvPacket(&puck);
		//cout << "Packet" << endl;
		ps = puck;
		switch(ps.type){
			case 0:
			case 1: pthread_cond_signal( &condSend ); cout << "Send Puck" << endl;// 0 = NIX; 1= recPuck; 2= sendPuck 3= Error
			case 2:	pthread_cond_signal( &condRec ); cout << "Receive Puck" << endl;
			case 3: cout << "ERROR" << endl;
			//default: cout << "Wrong Code" << (int)ps.type << endl;
		}
		delay(100);
	}

}

void SerialCommunicationThread::shutdown(){
	cout << "Shutdown SerialCommunication" << endl;
}

void SerialCommunicationThread::receivePuck(puckStruct *puck){
	cout << "Receive Puck" << endl;
	pthread_cond_wait( &condRec, &mutexRec );
	copyPuck(puck);
}

void SerialCommunicationThread::sendPuck(puckStruct *puck){
	cout << "Send Puck" << endl;
	copyPuck(puck);
	ps.type = 2;
	pthread_cond_wait( &condSend, &mutexSend );
}

void SerialCommunicationThread::sendError(){
	ps.type =3;

}

void SerialCommunicationThread::copyPuck(puckStruct *puck){
	ps.type = puck->type;
	ps.id = puck->id;
	ps.holeOnTop = puck->holeOnTop;
	ps.metal = puck->metal;
	ps.needUserInteraction = puck->needUserInteraction;
	ps.size = puck->size;
	ps.sizeBand1 = puck->size;
	ps.sizetyp = puck->sizetyp;
	ps.type = puck->type;
}

void SerialCommunicationThread::busy(){

}

