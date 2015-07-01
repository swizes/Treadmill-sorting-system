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
	puckStruct puck;
	puck.type = 0;
	if(ps.type == 3 || ps.type == 2){
		ser.sendPacket(&ps);
	}else{
		ser.sendPacket(&puck);
	}
	ser.recvPacket(&puck);
	ps = puck;
	switch(ps.type){
		case 0:
		case 1: pthread_cond_signal( &condSend );// 0 = NIX; 1= recPuck; 2= sendPuck 3= Error
		case 2:	pthread_cond_signal( &condRec );
		case 3: cout << "ERROR" << endl;
		default: cout << "Wrong Code" << endl;
	}
	delay(100);

}

void SerialCommunicationThread::shutdown(){

}

void SerialCommunicationThread::receivePuck(puckStruct *puck){
	pthread_cond_wait( &condRec, &mutexRec );
	copyPuck(puck);
}

void SerialCommunicationThread::sendPuck(puckStruct *puck){
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

