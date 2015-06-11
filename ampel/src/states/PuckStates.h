#ifndef PuckStates_H_
#define PuckStates_H_
#include "State.cpp"
#include "Context.cpp"
#include "../Dispatcher.h"
#include "../Timer/Timer.h"
#include "../CalibrateThread.h"
#include "../BandController.h"
#include <cstdlib>
#include <iostream>

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
	Context* con;
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


class Ready: public State {
public:
	Ready(Context* con);
	virtual ~ Ready();
	virtual void Running_In_true(void);
private:
	Ready(const Ready& other);
	Ready& operator=(const Ready& other);
};

class Calibration: public State {
public:
	Calibration(Context* con);
	virtual ~ Calibration();
private:
	Calibration(const Calibration& other);
	Calibration& operator=(const Calibration& other);
};


class Give_Band_2_Pucks: public State {
public:
	Give_Band_2_Pucks(Context* con);
	virtual ~ Give_Band_2_Pucks();
private:
	Give_Band_2_Pucks(const Give_Band_2_Pucks& other);
	Give_Band_2_Pucks& operator=(const Give_Band_2_Pucks& other);
};

class Give_New_Puck: public State {
public:
	Give_New_Puck(Context* con);
	virtual ~ Give_New_Puck();
private:
	Give_New_Puck(const Give_New_Puck& other);
	Give_New_Puck& operator=(const Give_New_Puck& other);
};

class Initialisierung: public State {
public:
	Initialisierung(Context* con);
	virtual ~ Initialisierung();
private:
	Initialisierung(const Initialisierung& other);
	Initialisierung& operator=(const Initialisierung& other);
};

class Reihenfolge: public State {
public:
	Reihenfolge(Context* con);
	virtual ~ Reihenfolge();
private:
	Reihenfolge(const Reihenfolge& other);
	Reihenfolge& operator=(const Reihenfolge& other);
};

class Sequence: public State {
public:
	Sequence(Context* con);
	virtual ~ Sequence();
private:
	Sequence(const Sequence& other);
	Sequence& operator=(const Sequence& other);
};

class User_Interaction_needed: public State {
public:
	User_Interaction_needed(Context* con);
	virtual ~ User_Interaction_needed();
private:
	User_Interaction_needed(const User_Interaction_needed& other);
	User_Interaction_needed& operator=(const User_Interaction_needed& other);
};

class Waiting_for_arriving_Puck: public State {
public:
	Waiting_for_arriving_Puck(Context* con);
	virtual ~ Waiting_for_arriving_Puck();
private:
	Waiting_for_arriving_Puck(const Waiting_for_arriving_Puck& other);
	Waiting_for_arriving_Puck& operator=(const Waiting_for_arriving_Puck& other);
};

class Put_Aside: public State {
public:
	Put_Aside(Context* con);
	virtual ~ Put_Aside();
private:
	Put_Aside(const Put_Aside& other);
	Put_Aside& operator=(const Put_Aside& other);
};

class Working_Band1: public State {
public:
	Working_Band1(Context* con);
	virtual ~ Working_Band1();
	virtual void Running_In_true(void);
	virtual void Running_out_true(void);
private:
	Working_Band1(const Working_Band1& other);
	Working_Band1& operator=(const Working_Band1& other);
};

class Working_Band2: public State {
public:
	Working_Band2(Context* con);
	virtual ~ Working_Band2();
	virtual void Running_In_true(void);
private:
	Working_Band2(const Working_Band2& other);
	Working_Band2& operator=(const Working_Band2& other);
};

//PseudoTestZustand
class SerialCommunicationBand1: public State {
public:
	SerialCommunicationBand1(Context* con);
	virtual ~ SerialCommunicationBand1();
private:
	SerialCommunicationBand1(const SerialCommunicationBand1& other);
	SerialCommunicationBand1& operator=(const SerialCommunicationBand1& other);
};


#endif
