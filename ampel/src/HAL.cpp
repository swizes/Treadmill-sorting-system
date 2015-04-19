#include "HAL.h"


// Implementation
HAL* HAL::instance_ = NULL;

HAL* HAL::getInstance(){
	static pthread_mutex_t mtx_ = PTHREAD_MUTEX_INITIALIZER;

	if( instance_ == NULL){
		pthread_mutex_lock(&mtx_);
		if( instance_ == NULL){
		    instance_ = new HAL();
		}
		pthread_mutex_unlock(&mtx_);
	}
	return instance_;
}

HAL::HAL(){
	printf("ctor DCLP Singleton\n");
}

HAL::~HAL(){
	printf("dtor DCLP Singleton\n");
}

//Port A Functions Aktorik
void HAL:: band_right_normal(void){
	//Reset Band_stop and Slowly Bit
	out8(PORT_A, in8(PORT_A) & ~BM_MOTOR_STOP & ~BM_MOTOR_SLOWLY);
	
	out8(PORT_A, in8(PORT_A) | BM_MOTOR_RIGHT);
}

void HAL:: band_right_slowly(void){
	//Reset Band_stop Bit
	out8(PORT_A, in8(PORT_A) & ~BM_MOTOR_STOP);
	
	out8(PORT_A, in8(PORT_A) | BM_MOTOR_RIGHT | BM_MOTOR_SLOWLY);
}

void HAL:: band_left_normal(void){
	//Reset Band_stop and Slowly Bit
	out8(PORT_A, in8(PORT_A) & ~BM_MOTOR_STOP & ~BM_MOTOR_SLOWLY);
	
	out8(PORT_A, in8(PORT_A) | BM_MOTOR_LEFT);
}

void HAL:: band_left_slowly(void){
	//Reset Band_stop Bit
	out8(PORT_A, in8(PORT_A) & ~BM_MOTOR_STOP);
	
	out8(PORT_A, in8(PORT_A) | BM_MOTOR_LEFT | BM_MOTOR_SLOWLY);
}

void HAL:: band_stop(void){
	out8(PORT_A, in8(PORT_A) | BM_MOTOR_STOP);
}

void HAL:: open_gate(void){
	out8(PORT_A, in8(PORT_A) | BM_OPEN_GATE);
}

void HAL:: close_gate(void){
	out8(PORT_A, in8(PORT_A) & ~BM_OPEN_GATE);
}

void HAL:: turn_greenLight_on(void){
	out8(PORT_A, in8(PORT_A) | BM_GREEN);
}

void HAL:: turn_yellowLight_on(void){
	out8(PORT_A, in8(PORT_A) | BM_YELLOW);
}

void HAL:: turn_redLight_on(void){
	out8(PORT_A, in8(PORT_A) | BM_RED);
}

void HAL:: turn_greenLight_off(void){
	out8(PORT_A, in8(PORT_A) & ~BM_GREEN);
}

void HAL:: turn_yellowLight_off(void){
	out8(PORT_A, in8(PORT_A) & ~BM_YELLOW);
}

void HAL:: turn_redLight_off(void){
	out8(PORT_A, in8(PORT_A) & ~BM_RED);
}

//Port C Functions Aktorik
void HAL:: turn_startLED_on(void){
	out8(PORT_C, in8(PORT_C) | BM_START_LED);
}

void HAL:: turn_resetLED_on(void){
	out8(PORT_C, in8(PORT_C) | BM_RESET_LED);
}

void HAL:: turn_startLED_off(void){
	out8(PORT_C, in8(PORT_C) & ~BM_START_LED);
}

void HAL:: turn_resetLED_off(void){
	out8(PORT_C, in8(PORT_C) & ~BM_RESET_LED);
}

//Port B Functions Sensorik
int HAL:: is_puck_running_in(void){
	return (in8(PORT_B) & BM_RUNNING_IN);
}

int HAL:: is_puck_in_height_determination(void){
	return (in8(PORT_B) & BM_HEIGHT_DETERM);
}

int HAL:: is_height_ok(void){
	return (in8(PORT_B) & BM_HEIGHT_OK);
}

int HAL:: is_puck_in_gate(void){
	return (in8(PORT_B) & BM_PUCK_IN_GATE);
}

int HAL:: is_metal_detected(void){
	return (in8(PORT_B) & BM_METAL_DETECTOR);
}

int HAL:: is_gate_open(void){
	return (in8(PORT_B) & BM_GATE_STATUS);
}

int HAL:: is_slide_full(void){
	return (in8(PORT_B) & BM_SLIDE_STATUS);
}

int HAL:: is_puck_running_out(void){
	return (in8(PORT_B) & BM_RUNNING_OUT);
}

//Port C Functions Sensorik
int HAL:: is_startButton_pushed(void){
	return (in8(PORT_C) & BM_START_BUTTON_STATUS);
}

int HAL:: is_stopButton_pushed(void){
	return (in8(PORT_C) & BM_STOP_BUTTON_STATUS);
}

int HAL:: is_resetButton_pushed(void){
	return (in8(PORT_C) & BM_RESET_BUTTON_STATUS);
}

int HAL:: is_eStopButton_pushed(void){
	return (in8(PORT_C) & BM_ESTOP_BUTTON_STATUS);
}