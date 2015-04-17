/*
 * Serial.h
 *
 *  Created on: 17.04.2015
 *      Author: lukasTest
 */

#ifndef SERIAL_H_
#define SERIAL_H_

class Serial {

typedef struct {
		uint8_t num;
}Packet;
public:
	Serial();
	virtual ~Serial();
	int sendPacket(Packet* p);
	int recvPacket(Packet* p);

private:
	const char* dev_;
	int fdesc_;
	void config(void);
};


#endif /* SERIAL_H_ */
