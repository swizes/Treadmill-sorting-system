/**
* HAL.cpp
*
*	Created on: 19.04.2015
*		Author: Tobias Braack
*
* todo: -shift the return values
*/


#include "HAL.h"
#include "lib/HWaccess.h"
#include "lib/Lock.h"
#include <pthread.h>
#include <iostream>
#include <time.h>
#include <unistd.h>

using namespace std;

// Implementation
HAL* HAL::instance_ = NULL;

/**
* c'tor for the Thread-safe singleton HAL implementation 
* @param none
* @return A Pointer to the Singleton HAL Object
*/
HAL* HAL::getInstance(){
	static pthread_mutex_t mtx_ = PTHREAD_MUTEX_INITIALIZER;

	if( instance_ == NULL){
		pthread_mutex_lock(&mtx_);
		if( instance_ == NULL){
		    instance_ = new HAL();
		    instance_->reset();
		}
		pthread_mutex_unlock(&mtx_);
	}
	return instance_;
}

/**
* Standard c'tor of HAL Class 
*/
HAL::HAL(){
	printf("ctor DCLP Singleton\n");
    if( ThreadCtl(_NTO_TCTL_IO_PRIV,0) == -1 ){
        cout << "Can't get Hardware access, therefore can't do anything." << endl;
    }

	out8(IO_CONTROL_ADDRESS, BM_IO_CONTROL);
}

HAL::~HAL(){
	printf("dtor DCLP Singleton\n");
}

/**
* Reset Port A 
*/
void HAL::reset_port_a(void){
	out8(PORT_A, in8(PORT_A) & RESET_PORT_A);
}

/**
* Reset Port C
*/
void HAL::reset_port_c(void){
	out8(PORT_C, in8(PORT_C) & RESET_PORT_C);
}

/**
* Reset Port A and Port C
*/
void HAL::reset(void){
	reset_port_a();
	reset_port_c();
}

//Port A Functions Aktorik

/**
* Start band running right in normal speed
*/
void HAL:: band_right_normal(void){
	//Reset Band_stop and Slowly Bit
	out8(PORT_A, in8(PORT_A) & ~BM_MOTOR_STOP & ~BM_MOTOR_SLOWLY & ~BM_MOTOR_LEFT);
	
	out8(PORT_A, in8(PORT_A) | BM_MOTOR_RIGHT);
}

/**
* Start band running right slowly 
*/
void HAL:: band_right_slowly(void){
	//Reset Band_stop Bit
	out8(PORT_A, in8(PORT_A) & ~BM_MOTOR_STOP &~BM_MOTOR_LEFT);
	
	out8(PORT_A, in8(PORT_A) | BM_MOTOR_RIGHT | BM_MOTOR_SLOWLY);
}

/**
* Starts band running left in normal speed
*/
void HAL:: band_left_normal(void){
	//Reset Band_stop and Slowly Bit
	out8(PORT_A, in8(PORT_A) & ~BM_MOTOR_STOP & ~BM_MOTOR_SLOWLY & ~BM_MOTOR_RIGHT);
	
	out8(PORT_A, in8(PORT_A) | BM_MOTOR_LEFT);
}

/**
* Starts band running left slowly 
*/
void HAL:: band_left_slowly(void){
	//Reset Band_stop Bit
	out8(PORT_A, in8(PORT_A) & ~BM_MOTOR_STOP &~BM_MOTOR_RIGHT);
	
	out8(PORT_A, in8(PORT_A) | BM_MOTOR_LEFT | BM_MOTOR_SLOWLY);
}

/**
* Stops the band
*/
void HAL:: band_stop(void){
	//out8(PORT_A, in8(PORT_A) & ~BM_MOTOR_LEFT &~BM_MOTOR_RIGHT);
	out8(PORT_A, in8(PORT_A) | BM_MOTOR_STOP);
}

/**
* Opens the gate
*/
void HAL:: open_gate(void){
	out8(PORT_A, in8(PORT_A) | BM_OPEN_GATE);
}

/**
* Closes the gate
*/
void HAL:: close_gate(void){
	out8(PORT_A, in8(PORT_A) & ~BM_OPEN_GATE);
}

/**
* turns the green light on
*/
void HAL:: turn_greenLight_on(void){
	out8(PORT_A, in8(PORT_A) | BM_GREEN);
}

/**
* turns the yellow light on
*/
void HAL:: turn_yellowLight_on(void){
	cout << "Yellow" << endl;
	out8(PORT_A, in8(PORT_A) | BM_YELLOW);
}

/**
* turns the red light on
*/
void HAL:: turn_redLight_on(void){
	out8(PORT_A, in8(PORT_A) | BM_RED);
}

/**
* turns the green light off
*/
void HAL:: turn_greenLight_off(void){
	out8(PORT_A, in8(PORT_A) & ~BM_GREEN);
}

/**
* turns the yellow light off
*/
void HAL:: turn_yellowLight_off(void){
	out8(PORT_A, in8(PORT_A) & ~BM_YELLOW);
}

/**
* turns the red light off
*/
void HAL:: turn_redLight_off(void){
	out8(PORT_A, in8(PORT_A) & ~BM_RED);
}

//Port C Functions Aktorik

/**
* turns the start LED on
*/
void HAL:: turn_startLED_on(void){
	out8(PORT_C, in8(PORT_C) | BM_START_LED);
}

/**
* turns the reset LED on
*/
void HAL:: turn_resetLED_on(void){
	out8(PORT_C, in8(PORT_C) | BM_RESET_LED);
}

/**
* turns the start LED off
*/
void HAL:: turn_startLED_off(void){
	out8(PORT_C, in8(PORT_C) & ~BM_START_LED);
}

/**
* turns the reset LED off
*/
void HAL:: turn_resetLED_off(void){
	out8(PORT_C, in8(PORT_C) & ~BM_RESET_LED);
}

/**
* turns the Q1 LED on
*/
void HAL:: turn_Q1_LED_on(void){
	out8(PORT_C, in8(PORT_C) | BM_Q1_LED);
}

/**
* turns the Q2 LED on
*/
void HAL:: turn_Q2_LED_on(void){
	out8(PORT_C, in8(PORT_C) | BM_Q2_LED);
}

/**
* turns the Q1 LED off
*/
void HAL:: turn_Q1_LED_off(void){
	out8(PORT_C, in8(PORT_C) & ~BM_Q1_LED);
}

/**
* turns the Q2 LED off
*/
void HAL:: turn_Q2_LED_off(void){
	out8(PORT_C, in8(PORT_C) & ~BM_Q2_LED);
}

//Port B Functions Sensorik

/**
* Shows if a Puck is running in
* @return 0 = false, 1 = true
*/
int HAL:: is_puck_running_in(void){
	return !(in8(PORT_B) & BM_RUNNING_IN);
}

/**
* Shows if a puck is in height determination
* @return 0 = false, 1 = true
*/
int HAL:: is_puck_in_height_determination(void){
	return !(in8(PORT_B) & BM_HEIGHT_DETERM);
}

/**
* Shows if the height is ok
* @return 0 = false, 1 = true
*/
int HAL:: is_height_ok(void){
	return !(in8(PORT_B) & BM_HEIGHT_OK);
}

/** 
* Shows if the puck is in gate
* @return 0 = false, 1 = true
*/
int HAL:: is_puck_in_gate(void){
	return !(in8(PORT_B) & BM_PUCK_IN_GATE);
}

/**
* Shows if the puck has a metal inner life
* @return 0 = false, 1 = true
*/
int HAL:: is_metal_detected(void){
	return (in8(PORT_B) & BM_METAL_DETECTOR);
}

/**
* Shows if the gate is open
* @return 0 = false, 1 = true
*/
int HAL:: is_gate_open(void){
	return (in8(PORT_B) & BM_GATE_STATUS);
}

/**
* Shows if the slide is full
* @return 0 = false, 1 = true
*/
int HAL:: is_slide_full(void){
	return !(in8(PORT_B) & BM_SLIDE_STATUS);
}

/**
* Shows if the puck is running out
* @return 0 = false, 1 = true
*/
int HAL:: is_puck_running_out(void){
	return !(in8(PORT_B) & BM_RUNNING_OUT);
}

//Port C Functions Sensorik

/**
* Shows if the start button is pushed
* @return 0 = false, 1 = true
*/
int HAL:: is_startButton_pushed(void){
	return !(in8(PORT_C) & BM_START_BUTTON_STATUS);
}

/**
* Shows if the stop button is pushed
* @return 1 = true, 0 = false
*/
int HAL:: is_stopButton_pushed(void){
	return !(in8(PORT_C) & BM_STOP_BUTTON_STATUS);
}

/**
* Shows if the reset button is pushed
* @return 0 = false, 1 = true
*/
int HAL:: is_resetButton_pushed(void){
	return (in8(PORT_C) & BM_RESET_BUTTON_STATUS);
}

/**
* Shows if the e-stopp button is pushed
* @return 0 = true, 1 = false
*/
int HAL:: is_eStopButton_pushed(void){
	return (in8(PORT_C) & BM_ESTOP_BUTTON_STATUS);
}

/**
 * Get the height from the height measure sensor.
 * This functions blocks for 5ms
 * @return converted value between 4090 and 0 (~4050 = empty, 0 = ~800 = max allowed height)
 */
uint16_t HAL:: get_height_measure(void) {
	uint8_t v_low = in8(PORT_ADC_LOW);
	uint8_t v_high;

	//cout << "in get_height_measure" << endl;
	out8(PORT_ADC_LOW, BM_START_MEASURE);
	delay(1);

	v_high = in8(PORT_ADC_HIGH);

	//printf("h: %x l: %x ", v_high, v_low);

	uint16_t retVal = v_high << 8;
	retVal |= v_low;

	return retVal;
	//return 476;
	//return 4096-in16(PORT_ADC_LOW);
}
