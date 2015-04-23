/*

 * CommunnicationThread.cpp

 *

 *  Created on: 17.04.2015

 *  Author: lukasTest, Tobi

 *

 *	

 */



#include "CommunnicationThread.h"



//Only One PC can be the SENDER! 

//#define SENDER





CommunnicationThread::CommunnicationThread(void) {

	cout << "ctor Communication Test" << endl;

}



CommunnicationThread::~CommunnicationThread() {

	// TODO Auto-generated destructor stub

	cout << "dtor Communication Test" << endl;
}



void CommunnicationThread::execute(void*){



	Packet p;

	

//allokieren und init

	memset(&p, 0 , sizeof(p));

	p.num = 0;



	#ifdef SENDER

		ser->sendPacket(&p);

	#endif



	while(p.num < CHECKSUM){

		ser.recvPacket(&p);

		//printf("Pong: %d\n",p.data);



		p.num += 1;



		ser.sendPacket(&p);

		//printf("Ping: %d\n",p.data);

		//usleep(1000000);				//no need, recvPacket blocked?

	}

	
	if(p.num == CHECKSUM){

		cout << "Serial Communication finished correct" << endl;

	}else{

		cout << "Error in Serial Communication" << endl;

	}



}





void CommunnicationThread::shutdown(){
    cout << "Communication Test shutdown" << endl;

}

