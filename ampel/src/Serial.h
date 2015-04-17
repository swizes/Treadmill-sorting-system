/*
 * Serial.h
 *
 *  Created on: 17.04.2015
 *      Author: lukasTest
 */

#ifndef SERIAL_H_
#define SERIAL_H_

class Serial {
public:
	Serial();
	virtual ~Serial();

private:
	const char* dev_;
	int fdesc_;
};


#endif /* SERIAL_H_ */
