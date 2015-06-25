/*
 * ISRPortC.cpp
 *
 *  Created on: 25.06.2015
 *      Author: tobi
 */

#include "ISRPortC.h"

int isrId = 0;

const struct sigevent* ISR_DIO(void* arg, int id) {
    struct sigevent* event = (struct sigevent*) arg;
    out8(0x30F, 0);

    event->sigev_notify = SIGEV_PULSE ;
    event->__sigev_un1.__sigev_coid = isrConnection;
    event->__sigev_un2.__st.__sigev_code = 0;
    event->sigev_value.sival_int = in8(PORT_C);
    return event;
}


void registerISR_PortC(void){
	out8(0x30F, 0);
	out8(0x30B, 0b11111101);

	SIGEV_PULSE_INIT(&isrEvent, isrConnection, SIGEV_PULSE_PRIO_INHERIT, 0, 0);
	isrId = InterruptAttach(11, ISR_DIO, &isrEvent, sizeof(isrEvent), 0);
	if (isrId == -1) {
	    exit(EXIT_FAILURE);
	}
}


void unregisterISR_PortC(void){
    if( InterruptDetach(isrId) == -1 ){
        exit(EXIT_FAILURE);
    }
    out8(0x30B, 0b11111111);
    out8(0x30F,0);
}



