#ifndef PuckStates_H_
#define PuckStates_H_
#include "State.cpp"
#include "Context.cpp"
#include "../Dispatcher.h"

/*
 * PUK LIFE CYCLE:
 */

class NotExist: public State {
public:
	NotExist(Context* con);
	virtual ~NotExist();
	virtual void Running_In_true(void);
private:
	NotExist(const NotExist& other);
	NotExist& operator=(const NotExist& other);
};


class Birth: public State {
public:
	Birth(Context* con);
	virtual ~Birth();
	virtual void Running_In_false(void);
private:
	Birth(const Birth& other);
	Birth& operator=(const Birth& other);
};

class Road_to_Height: public State {
public:
	Road_to_Height(Context* con);
	virtual ~Road_to_Height();
	virtual void In_Height_true(void);
private:
	Road_to_Height(const Road_to_Height& other);
	Road_to_Height& operator=(const Road_to_Height& other);
};

class Height_Measurement: public State {
public:
	Height_Measurement(Context* con);
	virtual ~Height_Measurement();
	virtual void Height_Status_OK(void);
private:
	Height_Measurement(const Height_Measurement& other);
	Height_Measurement& operator=(const Height_Measurement& other);
};
#endif
