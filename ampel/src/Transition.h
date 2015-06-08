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
	  virtual void Running_In_true(void) = 0;
	  virtual void In_Height_true(void) = 0;
	  virtual void Height_Status_OK(void) = 0;
	  virtual void Puck_in_Gate_true(void) = 0;
	  virtual void Metal_detection_true(void) = 0;
	  virtual void Gate_open_true(void) = 0;
	  virtual void Slide_full_true(void) = 0;
	  virtual void Running_out_true(void) = 0;

	  virtual void Running_In_false(void) = 0;
	  virtual void In_Height_false(void) = 0;
	  virtual void Height_Status_NOTOK(void) = 0;
	  virtual void Puck_in_Gate_false(void) = 0;
	  virtual void Metal_detection_false(void) = 0;
	  virtual void Gate_open_false(void) = 0;
	  virtual void Slide_full_false(void) = 0;
	  virtual void Running_out_false(void) = 0;

};

#endif
