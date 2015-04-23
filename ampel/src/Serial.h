/*
 * Serial.h
 *
 *  Created on: 17.04.2015
 *      Author: lukasTest
 */

#ifndef SERIAL_H_
#define SERIAL_H_

typedef struct {
		uint8_t num;
}Packet;

class Serial {

public:
	Serial();
	~Serial();
	void config(void);
	int sendPacket(Packet* p);
	int recvPacket(Packet* p);
	int startreq();
	int startresp();

private:
	const char* dev_;
	int fdesc_;
};


#endif /* SERIAL_H_ */
