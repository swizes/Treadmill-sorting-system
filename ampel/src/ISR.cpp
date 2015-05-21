/*
 * ISR.cpp
 *
 *  Created on: 06.05.2015
 *      Author: abl441
 */


#include "ISR.h"


int isrId = 0;

const struct sigevent* ISR_DIO(void* arg, int id) {
    struct sigevent* event = (struct sigevent*) arg;
    out8(0x30F, 0);

    event->sigev_notify = SIGEV_PULSE ;
    event->__sigev_un1.__sigev_coid = isrConnection;
    event->__sigev_un2.__st.__sigev_code = 0;
    event->sigev_value.sival_int = in8(PORT_B);
    return event;
}


void registerISR(void){
	out8(0x30F, 0);
	out8(0x30B, 0b11111101);

	SIGEV_PULSE_INIT(&isrEvent, isrConnection, SIGEV_PULSE_PRIO_INHERIT, 0, 0);
	isrId = InterruptAttach(11, ISR_DIO, &isrEvent, sizeof(isrEvent), 0);
	if (isrId == -1) {
	    exit(EXIT_FAILURE);
	}
}


void unregisterISR(void){
    if( InterruptDetach(isrId) == -1 ){
        exit(EXIT_FAILURE);
    }
    out8(0x30B, 0b11111111);
    out8(0x30F,0);
}



