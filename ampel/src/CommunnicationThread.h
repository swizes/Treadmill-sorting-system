/*
 * CommunnicationThread.h
 *
 *  Created on: 17.04.2015
 *      Author: lukasTest
 */

#ifndef COMMUNNICATIONTHREAD_H_
#define COMMUNNICATIONTHREAD_H_

class Communnication_Thread {
public:
	Communnication_Thread();
	virtual ~Communnication_Thread();
private:
	Serial ser();
};

#endif /* COMMUNNICATIONTHREAD_H_ */
