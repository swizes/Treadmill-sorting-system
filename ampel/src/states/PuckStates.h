#ifndef PuckStates_H_
#define PuckStates_H_
#include "../State.cpp"
#include "../Context.cpp"
#include "../Dispatcher.h"


class Birth: public State {
public:
	Birth(Context* con);
	virtual ~Birth();
	virtual void Running_In_false(void);
private:
	Birth(const Birth& other);
	Birth& operator=(const Birth& other);
};

class NotExist: public State {
public:
	NotExist(Context* con);
	virtual ~NotExist();
	virtual void Running_In_true(void);
private:
	NotExist(const NotExist& other);
	NotExist& operator=(const NotExist& other);
};
#endif
