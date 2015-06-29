/*
 * @file Context.cpp
 * @author Simon Brummer
 * @desc Tutorium 6. Context Klasse fuer Statemaschines.
 * Delegiert Methodenaufrufe an den aktuellen State
 * und haelt die Daten die von den States
 * manipuliert werden.
 */
#ifndef CONTEXT_CPP_
#define CONTEXT_CPP_
#include "Transition.h"
#include "Dispatcher.h"
#include "Puck.h"

class Context: public Transitions {
private:
	Transitions* state_;

	Puck* puck;
	int errCode;
public:
	Timer* timer;
	Context() :
		state_(NULL) {
//		printf("Context()\n");
		puck = new Puck();
		timer = new Timer();
		errCode = -1;
	}

	virtual ~Context() {
		printf("~Context()\n");
		// On cleanup: Remove yourself from all Events
		Dispatcher* dsp = Dispatcher::getInstance();
		for(int i = 0; i < NEVENTS;i++){
			dsp->remListeners(this,(EVENTS)i);
		}
		// Delete Inner Object too!
		if (state_ != NULL) {
			delete state_;
			delete timer;
			state_ = NULL;
		}
		delete puck;
	}

	Context(Puck* p) :
		state_(NULL) {
		this->puck = p;
		errCode = this->errCode;//???

	}


	virtual void setState(Transitions* state) {
		state_ = state;
	}

	virtual void Running_In_true(void) {
		state_->Running_In_true();
	}
	virtual void In_Height_true(void) {
		state_->In_Height_true();
	}
	virtual void Height_Status_OK(void) {
		state_->Height_Status_OK();
	}
	virtual void Puck_in_Gate_true(void) {
		state_->Puck_in_Gate_true();
	}
	virtual void Metal_detection_true(void) {
		state_->Metal_detection_true();
	}
	virtual void Gate_open_true(void) {
		state_->Gate_open_true();
	}
	virtual void Slide_full_true(void) {
		state_->Slide_full_true();
	}
	virtual void Running_out_true(void) {
		state_->Running_out_true();
	}
	virtual void Running_In_false(void) {
		state_->Running_In_false();
	}
	virtual void In_Height_false(void) {
		state_->In_Height_false();
	}
	virtual void Height_Status_NOTOK(void) {
		state_->Height_Status_NOTOK();
	}
	virtual void Puck_in_Gate_false(void) {
		state_->Puck_in_Gate_false();
	}
	virtual void Metal_detection_false(void) {
		state_->Metal_detection_false();
	}
	virtual void Gate_open_false(void) {
		state_->Gate_open_false();
	}
	virtual void Slide_full_false(void) {
		state_->Slide_full_false();
	}
	virtual void Running_out_false(void) {
		state_->Running_out_false();
	}

	Puck* getPuck(void){
		return puck;
	}

	int getErrcode(void){
		return errCode;
	}

	void setErrcode(int errCode){
		this->errCode=errCode;
	}



private:
	Context(const Context& other);
	Context& operator=(const Context& other);
};
#endif
