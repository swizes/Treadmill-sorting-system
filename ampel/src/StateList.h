/* Generated States File 

 * Date: 28/05/2015 02:10:46
 * 52 states
 * 114 transitions
 */

#ifndef STATELIST_H_
#define STATELIST_H_

#include "State.cpp"
#include "Context.cpp"


/* States */
class Ready: public State{
public:
	Ready(Context* con);
	virtual ~Ready();
	virtual void is_puck_running_in_(void);
	virtual void is_resetButton_pushed(void);
	virtual void is_startButton_pushed_(void);
private:
	Ready(const Ready& other);
	Ready& operator=(const Ready& other);
};


class Initialisierung: public State{
public:
	Initialisierung(Context* con);
	virtual ~Initialisierung();
	virtual void 2x_Resettaste(void);
	virtual void is_startButton_pushed_(void);
private:
	Initialisierung(const Initialisierung& other);
	Initialisierung& operator=(const Initialisierung& other);
};


class Kalibrierung: public State{
public:
	Kalibrierung(Context* con);
	virtual ~Kalibrierung();
	virtual void 2x_Resettaste(void);
	virtual void is_startButton_pushed_(void);
private:
	Kalibrierung(const Kalibrierung& other);
	Kalibrierung& operator=(const Kalibrierung& other);
};


class Puk_in_Einlauf_LS: public State{
public:
	Puk_in_Einlauf_LS(Context* con);
	virtual ~Puk_in_Einlauf_LS();
	virtual void timeout_after_X_sec(void);
	virtual void is_puck_in_height_determination__band_right_slowly(void);
private:
	Puk_in_Einlauf_LS(const Puk_in_Einlauf_LS& other);
	Puk_in_Einlauf_LS& operator=(const Puk_in_Einlauf_LS& other);
};


class ERROR: public State{
public:
	ERROR(Context* con);
	virtual ~ERROR();
	virtual void is_resetButton_pushed(void);
private:
	ERROR(const ERROR& other);
	ERROR& operator=(const ERROR& other);
};


class Hoehenmesser_LS: public State{
public:
	Hoehenmesser_LS(Context* con);
	virtual ~Hoehenmesser_LS();
	virtual void _is_height_ok_(void);
	virtual void timeout_after_X_sec(void);
	virtual void _is_height_ok_(void);
private:
	Hoehenmesser_LS(const Hoehenmesser_LS& other);
	Hoehenmesser_LS& operator=(const Hoehenmesser_LS& other);
};


class Rampe_geschlossen_halten: public State{
public:
	Rampe_geschlossen_halten(Context* con);
	virtual ~Rampe_geschlossen_halten();
	virtual void is_slide_full_(void);
	virtual void is_slide_full_(void);
private:
	Rampe_geschlossen_halten(const Rampe_geschlossen_halten& other);
	Rampe_geschlossen_halten& operator=(const Rampe_geschlossen_halten& other);
};


class EROOR__Rampe_voll: public State{
public:
	EROOR__Rampe_voll(Context* con);
	virtual ~EROOR__Rampe_voll();
	virtual void is_resetButton_pushed(void);
private:
	EROOR__Rampe_voll(const EROOR__Rampe_voll& other);
	EROOR__Rampe_voll& operator=(const EROOR__Rampe_voll& other);
};


class Hoehenmesser__Bohrung: public State{
public:
	Hoehenmesser__Bohrung(Context* con);
	virtual ~Hoehenmesser__Bohrung();
	virtual void keine_Bohrung__band_right_normal(void);
	virtual void mit_Bohrung__band_right_normal(void);
private:
	Hoehenmesser__Bohrung(const Hoehenmesser__Bohrung& other);
	Hoehenmesser__Bohrung& operator=(const Hoehenmesser__Bohrung& other);
};


class Metalldetektor: public State{
public:
	Metalldetektor(Context* con);
	virtual ~Metalldetektor();
	virtual void is_metal_detected_(void);
	virtual void is_metal_detected_(void);
	virtual void is_metal_detected_(void);
	virtual void is_metal_detected_(void);
private:
	Metalldetektor(const Metalldetektor& other);
	Metalldetektor& operator=(const Metalldetektor& other);
};


class ERROR: public State{
public:
	ERROR(Context* con);
	virtual ~ERROR();
	virtual void is_resetButton_pushed(void);
private:
	ERROR(const ERROR& other);
	ERROR& operator=(const ERROR& other);
};


class Reihenfolgen_check: public State{
public:
	Reihenfolgen_check(Context* con);
	virtual ~Reihenfolgen_check();
	virtual void Reihenfolge_passt_nicht(void);
	virtual void Reihenfolge_passt_nicht(void);
	virtual void aktueller_Puk_passt_zur_Reihenfolge(void);
	virtual void Reihenfolge_passt__band_right_normal(void);
	virtual void timeout_after_X_sec(void);
private:
	Reihenfolgen_check(const Reihenfolgen_check& other);
	Reihenfolgen_check& operator=(const Reihenfolgen_check& other);
};


class Warte_auf_Puk_Request_Band2_after_User: public State{
public:
	Warte_auf_Puk_Request_Band2_after_User(Context* con);
	virtual ~Warte_auf_Puk_Request_Band2_after_User();
	virtual void requestNextPuk_(void);
	virtual void requestNextPuk_(void);
	virtual void timeout_after_X_sec(void);
private:
	Warte_auf_Puk_Request_Band2_after_User(const Warte_auf_Puk_Request_Band2_after_User& other);
	Warte_auf_Puk_Request_Band2_after_User& operator=(const Warte_auf_Puk_Request_Band2_after_User& other);
};


class Beiseite_legen: public State{
public:
	Beiseite_legen(Context* con);
	virtual ~Beiseite_legen();
	virtual void last_SavedPuk_passt_zur_Reihenfolge__UEberschreibe_aktuelle_Puk_ID_mit_last_SavedPuk(void);
	virtual void kein_passender_Puk__is_startButton_pushed_(void);
private:
	Beiseite_legen(const Beiseite_legen& other);
	Beiseite_legen& operator=(const Beiseite_legen& other);
};


class User_Interaction___SavedPuk: public State{
public:
	User_Interaction___SavedPuk(Context* con);
	virtual ~User_Interaction___SavedPuk();
	virtual void is_startButton_pushed_(void);
	virtual void timeout_after_X_sec(void);
private:
	User_Interaction___SavedPuk(const User_Interaction___SavedPuk& other);
	User_Interaction___SavedPuk& operator=(const User_Interaction___SavedPuk& other);
};


class User_Interaction__Drehe_Puk: public State{
public:
	User_Interaction__Drehe_Puk(Context* con);
	virtual ~User_Interaction__Drehe_Puk();
	virtual void is_startButton_pushed_(void);
	virtual void timeout_after_X_sec(void);
private:
	User_Interaction__Drehe_Puk(const User_Interaction__Drehe_Puk& other);
	User_Interaction__Drehe_Puk& operator=(const User_Interaction__Drehe_Puk& other);
};


class ERROR__User: public State{
public:
	ERROR__User(Context* con);
	virtual ~ERROR__User();
private:
	ERROR__User(const ERROR__User& other);
	ERROR__User& operator=(const ERROR__User& other);
};


class Band2_Lichtschranke2: public State{
public:
	Band2_Lichtschranke2(Context* con);
	virtual ~Band2_Lichtschranke2();
private:
	Band2_Lichtschranke2(const Band2_Lichtschranke2& other);
	Band2_Lichtschranke2& operator=(const Band2_Lichtschranke2& other);
};


class ERROR_B1toB2: public State{
public:
	ERROR_B1toB2(Context* con);
	virtual ~ERROR_B1toB2();
private:
	ERROR_B1toB2(const ERROR_B1toB2& other);
	ERROR_B1toB2& operator=(const ERROR_B1toB2& other);
};


class Auslauf_LS: public State{
public:
	Auslauf_LS(Context* con);
	virtual ~Auslauf_LS();
	virtual void requestNextPuk_(void);
	virtual void requestNextPuk_(void);
	virtual void timeout_after_X_sec(void);
private:
	Auslauf_LS(const Auslauf_LS& other);
	Auslauf_LS& operator=(const Auslauf_LS& other);
};


class ERROR_Auslauf: public State{
public:
	ERROR_Auslauf(Context* con);
	virtual ~ERROR_Auslauf();
private:
	ERROR_Auslauf(const ERROR_Auslauf& other);
	ERROR_Auslauf& operator=(const ERROR_Auslauf& other);
};


class Default_Initialisierung: public State{
public:
	Default_Initialisierung(Context* con);
	virtual ~Default_Initialisierung();
	virtual void (void);
private:
	Default_Initialisierung(const Default_Initialisierung& other);
	Default_Initialisierung& operator=(const Default_Initialisierung& other);
};


class Ready: public State{
public:
	Ready(Context* con);
	virtual ~Ready();
	virtual void is_resetButton_pushed_(void);
	virtual void is_puck_running_in_(void);
	virtual void is_startButton_pushed_(void);
private:
	Ready(const Ready& other);
	Ready& operator=(const Ready& other);
};


class Kalibirierung: public State{
public:
	Kalibirierung(Context* con);
	virtual ~Kalibirierung();
	virtual void (void);
private:
	Kalibirierung(const Kalibirierung& other);
	Kalibirierung& operator=(const Kalibirierung& other);
};


class Band1: public State{
public:
	Band1(Context* con);
	virtual ~Band1();
	virtual void _Puk_IDs_existing_on_FiFo(void);
	virtual void ERROR(void);
private:
	Band1(const Band1& other);
	Band1& operator=(const Band1& other);
};


class Working_Band1: public State{
public:
	Working_Band1(Context* con);
	virtual ~Working_Band1();
	virtual void No_more_living_Puks__band_stop(void);
	virtual void is_puck_running_out_(void);
private:
	Working_Band1(const Working_Band1& other);
	Working_Band1& operator=(const Working_Band1& other);
};


class Is_Band2_free: public State{
public:
	Is_Band2_free(Context* con);
	virtual ~Is_Band2_free();
	virtual void (void);
private:
	Is_Band2_free(const Is_Band2_free& other);
	Is_Band2_free& operator=(const Is_Band2_free& other);
};


class Road_to_Exit: public State{
public:
	Road_to_Exit(Context* con);
	virtual ~Road_to_Exit();
	virtual void is_puck_running_out_(void);
	virtual void timer1__timeout_after_X_sec(void);
	virtual void after_X_secs__close_gate(void);
private:
	Road_to_Exit(const Road_to_Exit& other);
	Road_to_Exit& operator=(const Road_to_Exit& other);
};


class TIMEOUT: public State{
public:
	TIMEOUT(Context* con);
	virtual ~TIMEOUT();
	virtual void (void);
	virtual void (void);
private:
	TIMEOUT(const TIMEOUT& other);
	TIMEOUT& operator=(const TIMEOUT& other);
};


class Metall_detected: public State{
public:
	Metall_detected(Context* con);
	virtual ~Metall_detected();
	virtual void after_X_secs(void);
	virtual void is_puck_in_gate_(void);
private:
	Metall_detected(const Metall_detected& other);
	Metall_detected& operator=(const Metall_detected& other);
};


class Road_to_Metal: public State{
public:
	Road_to_Metal(Context* con);
	virtual ~Road_to_Metal();
	virtual void is_metal_detected(void);
	virtual void is_puck_in_gate_(void);
private:
	Road_to_Metal(const Road_to_Metal& other);
	Road_to_Metal& operator=(const Road_to_Metal& other);
};


class Search_for_Hole: public State{
public:
	Search_for_Hole(Context* con);
	virtual ~Search_for_Hole();
	virtual void is_puck_in_height_determination_(void);
	virtual void Height_was_ok__open_gate(void);
	virtual void is_puck_in_height_determination_(void);
private:
	Search_for_Hole(const Search_for_Hole& other);
	Search_for_Hole& operator=(const Search_for_Hole& other);
};


class Height_Measurement: public State{
public:
	Height_Measurement(Context* con);
	virtual ~Height_Measurement();
	virtual void open_gate(void);
	virtual void open_gate(void);
private:
	Height_Measurement(const Height_Measurement& other);
	Height_Measurement& operator=(const Height_Measurement& other);
};


class Road_to_Height: public State{
public:
	Road_to_Height(Context* con);
	virtual ~Road_to_Height();
	virtual void is_puck_in_height_determination__band_right_slowly_and_delete_timer0(void);
	virtual void is_puck_in_height_determination__band_right_slowly_and_delete_timer0(void);
	virtual void timer0__timeout_after_X_sec(void);
private:
	Road_to_Height(const Road_to_Height& other);
	Road_to_Height& operator=(const Road_to_Height& other);
};


class Birth: public State{
public:
	Birth(Context* con);
	virtual ~Birth();
	virtual void is_puck_running_in_(void);
private:
	Birth(const Birth& other);
	Birth& operator=(const Birth& other);
};


class Road_to_Sorting_Out: public State{
public:
	Road_to_Sorting_Out(Context* con);
	virtual ~Road_to_Sorting_Out();
	virtual void is_puck_in_gate_(void);
private:
	Road_to_Sorting_Out(const Road_to_Sorting_Out& other);
	Road_to_Sorting_Out& operator=(const Road_to_Sorting_Out& other);
};


class Flipping_Puck: public State{
public:
	Flipping_Puck(Context* con);
	virtual ~Flipping_Puck();
	virtual void is_slide_full_(void);
private:
	Flipping_Puck(const Flipping_Puck& other);
	Flipping_Puck& operator=(const Flipping_Puck& other);
};


class Is_In_Slide: public State{
public:
	Is_In_Slide(Context* con);
	virtual ~Is_In_Slide();
	virtual void after_X_secs_is_slide_full_(void);
	virtual void is_slide_full_(void);
private:
	Is_In_Slide(const Is_In_Slide& other);
	Is_In_Slide& operator=(const Is_In_Slide& other);
};


class Is_in_Gate: public State{
public:
	Is_in_Gate(Context* con);
	virtual ~Is_in_Gate();
	virtual void is_puck_in_gate_(void);
	virtual void is_puck_in_gate_(void);
private:
	Is_in_Gate(const Is_in_Gate& other);
	Is_in_Gate& operator=(const Is_in_Gate& other);
};


class Give_Band_2_Pucks: public State{
public:
	Give_Band_2_Pucks(Context* con);
	virtual ~Give_Band_2_Pucks();
	virtual void get_Pucks_from_Band1_FiFo(void);
	virtual void is_puck_running_out_(void);
private:
	Give_Band_2_Pucks(const Give_Band_2_Pucks& other);
	Give_Band_2_Pucks& operator=(const Give_Band_2_Pucks& other);
};


class Band2: public State{
public:
	Band2(Context* con);
	virtual ~Band2();
	virtual void (void);
	virtual void ERROR(void);
private:
	Band2(const Band2& other);
	Band2& operator=(const Band2& other);
};


class Give_New_Puk: public State{
public:
	Give_New_Puk(Context* con);
	virtual ~Give_New_Puk();
	virtual void is_resetButton_pushed_(void);
	virtual void Band1__is_puck_running_out_(void);
	virtual void is_startButton_pushed_(void);
private:
	Give_New_Puk(const Give_New_Puk& other);
	Give_New_Puk& operator=(const Give_New_Puk& other);
};


class User_Interaction_needed: public State{
public:
	User_Interaction_needed(Context* con);
	virtual ~User_Interaction_needed();
	virtual void UserInteraktion(void);
private:
	User_Interaction_needed(const User_Interaction_needed& other);
	User_Interaction_needed& operator=(const User_Interaction_needed& other);
};


class Waiting_for_arriving_Puk: public State{
public:
	Waiting_for_arriving_Puk(Context* con);
	virtual ~Waiting_for_arriving_Puk();
	virtual void is_startButton_pushed_(void);
private:
	Waiting_for_arriving_Puk(const Waiting_for_arriving_Puk& other);
	Waiting_for_arriving_Puk& operator=(const Waiting_for_arriving_Puk& other);
};


class Working_Band2: public State{
public:
	Working_Band2(Context* con);
	virtual ~Working_Band2();
	virtual void is_puck_running_out_(void);
private:
	Working_Band2(const Working_Band2& other);
	Working_Band2& operator=(const Working_Band2& other);
};


class Arriving_Puk_ID: public State{
public:
	Arriving_Puk_ID(Context* con);
	virtual ~Arriving_Puk_ID();
	virtual void is_puck_running_in_(void);
private:
	Arriving_Puk_ID(const Arriving_Puk_ID& other);
	Arriving_Puk_ID& operator=(const Arriving_Puk_ID& other);
};


class Reihenfolge_Beiseitelegen: public State{
public:
	Reihenfolge_Beiseitelegen(Context* con);
	virtual ~Reihenfolge_Beiseitelegen();
	virtual void Beiseitelegen(void);
	virtual void Beiseitelegen__No(void);
	virtual void Beiseitelegen__Yes(void);
	virtual void (void);
private:
	Reihenfolge_Beiseitelegen(const Reihenfolge_Beiseitelegen& other);
	Reihenfolge_Beiseitelegen& operator=(const Reihenfolge_Beiseitelegen& other);
};


class Last_Puk_ID_with_Metal: public State{
public:
	Last_Puk_ID_with_Metal(Context* con);
	virtual ~Last_Puk_ID_with_Metal();
	virtual void Yes(void);
	virtual void No(void);
private:
	Last_Puk_ID_with_Metal(const Last_Puk_ID_with_Metal& other);
	Last_Puk_ID_with_Metal& operator=(const Last_Puk_ID_with_Metal& other);
};


class This_Puk_got_Metal: public State{
public:
	This_Puk_got_Metal(Context* con);
	virtual ~This_Puk_got_Metal();
	virtual void Yes(void);
	virtual void No(void);
	virtual void Yes(void);
	virtual void No(void);
private:
	This_Puk_got_Metal(const This_Puk_got_Metal& other);
	This_Puk_got_Metal& operator=(const This_Puk_got_Metal& other);
};


class Reserved_Puk_Got_Metal: public State{
public:
	Reserved_Puk_Got_Metal(Context* con);
	virtual ~Reserved_Puk_Got_Metal();
	virtual void (void);
	virtual void Yes(void);
	virtual void No(void);
	virtual void Yes(void);
private:
	Reserved_Puk_Got_Metal(const Reserved_Puk_Got_Metal& other);
	Reserved_Puk_Got_Metal& operator=(const Reserved_Puk_Got_Metal& other);
};


class Beiseitelegen: public State{
public:
	Beiseitelegen(Context* con);
	virtual ~Beiseitelegen();
	virtual void is_startButton_pushed_(void);
private:
	Beiseitelegen(const Beiseitelegen& other);
	Beiseitelegen& operator=(const Beiseitelegen& other);
};


class ERROR_Handling: public State{
public:
	ERROR_Handling(Context* con);
	virtual ~ERROR_Handling();
	virtual void is_resetButton_pushed_(void);
private:
	ERROR_Handling(const ERROR_Handling& other);
	ERROR_Handling& operator=(const ERROR_Handling& other);
};



#endif // STATELIST_H_
