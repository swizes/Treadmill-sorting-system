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
	//TODO: Oder virtual void Height_status_OK(void);
private:
	Height_Measurement(const Height_Measurement& other);
	Height_Measurement& operator=(const Height_Measurement& other);
};

class Search_for_Hole: public State {
public:
	Search_for_Hole(Context* con);
	virtual ~ Search_for_Hole();
	virtual void In_Height_false(void);
private:
	Search_for_Hole(const Search_for_Hole& other);
	Search_for_Hole& operator=(const Search_for_Hole& other);
};

class Road_to_Metal: public State {
public:
	Road_to_Metal(Context* con);
	virtual ~ Road_to_Metal();
	virtual void Metal_detection_true(void);
	virtual void Puck_in_Gate_true(void);
private:
	Road_to_Metal(const Road_to_Metal& other);
	Road_to_Metal& operator=(const Road_to_Metal& other);
};

class Metal_Detected: public State {
public:
	Metal_Detected(Context* con);
	virtual ~ Metal_Detected();
	virtual void Puck_in_Gate_true(void);
private:
	Metal_Detected(const Metal_Detected& other);
	Metal_Detected& operator=(const Metal_Detected& other);
};

class Is_In_Gate: public State {
public:
	Is_In_Gate(Context* con);
	virtual ~ Is_In_Gate();
	virtual void Puck_in_Gate_false(void);
private:
	Is_In_Gate(const Is_In_Gate& other);
	Is_In_Gate& operator=(const Is_In_Gate& other);
};

class Road_To_Sorting_Out: public State {
public:
	Road_To_Sorting_Out(Context* con);
	virtual ~ Road_To_Sorting_Out();
	virtual void Puck_in_Gate_true(void);
private:
	Road_To_Sorting_Out(const Road_To_Sorting_Out& other);
	Road_To_Sorting_Out& operator=(const Road_To_Sorting_Out& other);
};

class Flipping_Puck: public State {
public:
	Flipping_Puck(Context* con);
	virtual ~ Flipping_Puck();
	virtual void Slide_full_true(void);
private:
	Flipping_Puck(const Flipping_Puck& other);
	Flipping_Puck& operator=(const Flipping_Puck& other);
};

class Is_In_Slide: public State {
public:
	Is_In_Slide(Context* con);
	virtual ~ Is_In_Slide();
	virtual void Slide_full_false(void);
private:
	Is_In_Slide(const Is_In_Slide& other);
	Is_In_Slide& operator=(const Is_In_Slide& other);
};

class Road_To_Exit: public State {
public:
	Road_To_Exit(Context* con);
	virtual ~ Road_To_Exit();
	virtual void Running_out_true(void);
private:
	Road_To_Exit(const Road_To_Exit& other);
	Road_To_Exit& operator=(const Road_To_Exit& other);
};

class Timeout: public State {
public:
	Timeout(Context* con);
	virtual ~ Timeout();
	//TODO: Timeout function
private:
	Timeout(const Timeout& other);
	Timeout& operator=(const Timeout& other);
};


class Error_Handling: public State {
public:
	Error_Handling(Context* con);
	virtual ~ Error_Handling();
	//TODO: Error Handling function
private:
	Error_Handling(const Error_Handling& other);
	Error_Handling& operator=(const Error_Handling& other);
};
#endif
