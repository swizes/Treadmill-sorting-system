/*

 * CommunnicationThread.cpp

 *

 *  Created on: 17.04.2015

 *  Author: lukasTest, Tobi

 *

 *	

 */



#include "CommunicationThread.h"



//Only One PC can be the SENDER! 

//#define SENDER





CommunicationThread::CommunicationThread(void) {

	cout << "ctor Communication Test" << endl;

}



CommunicationThread::~CommunicationThread() {
	cout << "dtor Communication Test" << endl;
}



void CommunicationThread::execute(void*){



	Packet p;

	

//allokieren und init

	memset(&p, 0 , sizeof(p));

	p.num = 0;



	#ifdef SENDER

		ser.sendPacket(&p);

	#endif



	while(p.num < CHECKSUM){

		ser.recvPacket(&p);

		printf("Rechner 2 received: %d\n",p.num);



		p.num += 1;



		ser.sendPacket(&p);

		printf("Rechner 2 send: %d\n",p.num);

		usleep(1000000);				//no need, recvPacket blocked?

	}

	
	if(p.num == CHECKSUM + 1){

		cout << "Serial Communication finished correct" << endl;

	}else{

		cout << "Error in Serial Communication" << endl;

	}
}

void CommunicationThread::shutdown(){
    cout << "Communication Test shutdown" << endl;
}

