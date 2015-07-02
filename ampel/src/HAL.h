/* Begin DCLP-Singleton */
// Declaration

#include "lib/HWaccess.h"
#include "lib/Lock.h"
#include "Timer/Timer.h"
#include <pthread.h>
#include <iostream>
#include <time.h>
#include <unistd.h>


#ifndef HAL_H
#define HAL_H


#include <stdint.h>

#define IO_CONTROL_ADDRESS 0x303
#define PORT_A 0x300
#define PORT_B 0x301
#define PORT_C 0x302
#define PORT_ADC_LOW 0x322
#define PORT_ADC_HIGH 0x323

#define BM_IO_CONTROL 0b10001010

//defines Port A
#define BM_MOTOR_RIGHT 0x01
#define BM_MOTOR_LEFT 0x02
#define BM_MOTOR_SLOWLY 0x04
#define BM_MOTOR_STOP 0x08
#define BM_OPEN_GATE 0x10
#define BM_GREEN 0x20
#define BM_YELLOW 0x40
#define BM_RED 0x80

//defines Sensorik Port B
#define BM_RUNNING_IN 0x01
#define BM_HEIGHT_DETERM 0x02
#define BM_HEIGHT_OK 0x04
#define BM_PUCK_IN_GATE 0x08
#define BM_METAL_DETECTOR 0x10
#define BM_GATE_STATUS 0x20
#define BM_SLIDE_STATUS 0x40
#define BM_RUNNING_OUT 0x80

//Port C
#define BM_START_LED 0x01
#define BM_RESET_LED 0x02
#define BM_Q1_LED 0x04
#define BM_Q2_LED 0x08
#define BM_START_BUTTON_STATUS 0x10
#define BM_STOP_BUTTON_STATUS 0x20
#define BM_RESET_BUTTON_STATUS 0x40
#define BM_ESTOP_BUTTON_STATUS 0x80

// ADC
#define BM_START_MEASURE 0x10

//Reset
#define RESET_PORT_A 0x0
#define RESET_PORT_C 0xF0

 

class HAL {
private:
    static HAL* instance_;

private:
    HAL();
    HAL(const HAL& other);
    HAL& operator=(const HAL& other);
    virtual ~HAL();
    Timer *timer;

public:
    static HAL* getInstance();
	
    void reset_port_a(void);
    void reset_port_c(void);
    void reset(void);

	void band_right_normal(void);
	void band_right_slowly(void);
	void band_left_normal(void);
	void band_left_slowly(void);
	void band_stop(void);
	
    void open_gate(void);
	void close_gate(void);
	
	void turn_greenLight_on(void);
	void turn_yellowLight_on(void);
	void turn_redLight_on(void);
	void turn_greenLight_off(void);
	void turn_yellowLight_off(void);
	void turn_redLight_off(void);
	
	void turn_startLED_on(void);
	void turn_resetLED_on(void);
	void turn_startLED_off(void);
	void turn_resetLED_off(void);
	void turn_Q1_LED_on(void);
	void turn_Q2_LED_on(void);
	void turn_Q1_LED_off(void);
	void turn_Q2_LED_off(void);

	int is_puck_running_in(void);
	int is_puck_in_height_determination(void);
	int is_height_ok(void);
	int is_puck_in_gate(void);
	int is_metal_detected(void);
	int is_gate_open(void);
	int is_slide_full(void);
	int is_puck_running_out(void);
	
	int is_startButton_pushed(void);
	int is_stopButton_pushed(void);
	int is_resetButton_pushed(void);
	int is_eStopButton_pushed(void);
	uint16_t get_height_measure(void);
};



#endif
