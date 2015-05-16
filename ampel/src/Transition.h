/*
 * Transition.h
 *
 *  Created on: 06.05.2015
 *      Author: abl441
 */

#ifndef TRANSITIONS_H_
#define TRANSITIONS_H_

class Transitions{
	public:
	  virtual void Running_In(void) = 0;
	  virtual void In_Height(void) = 0;
	  virtual void Height_Status(void) = 0;
	  virtual void Puck_in_Gate(void) = 0;
	  virtual void Metal_detection(void) = 0;
	  virtual void Gate_open(void) = 0;
	  virtual void Slide_full(void) = 0;
	  virtual void Running_out(void) = 0;
};

#endif
