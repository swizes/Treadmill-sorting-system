/*
 * Timer.cpp
 *
 *  Created on: 17.05.2015
 *      Author: lukasTest
 */

#include "Timer.h"
#include <stdint.h> // Integer Typen
#include <stdlib.h> // Speicherverwaltung
#include <stdio.h> // Ein- Ausgabe
#include <unistd.h> // Symbolische POSIX Konstanten
#include <time.h> // Timer Spezifikation
#include <pthread.h>
#include <sys/neutrino.h> // ThreadCtl u. message passing
#include <hw/inout.h> // in#(), out#() Befehle
//#include "geme.h"
//#include "error_check_vxx.h"


Timer::Timer() {
	// TODO Auto-generated constructor stub
	uint8_t new_stat; // new counter state
	uint8_t old_stat; // old counter state
	uint8_t lsb, msb; // LSByte, MSByte
	uint16_t fac; // factor for timing
	uint32_t i; // just an integer
	time_t cur_time; // current time
	// achieve system rights
	ThreadCtl( _NTO_TCTL_IO, 0 );
	printf("clock1 is fixed to 1MHz\n"); fflush(stdout);
	printf("connect out1 to clk2\n\n"); fflush(stdout);
	// configure count1 for 1ms
	// 1000 μs =1 ms => "factor"=1000
	fac = 1000; // 1000μs=1ms: 0x3E8
	lsb = fac & 0xFF; // --XX low
	msb = (fac>>8) & 0xFF; // XX-- high
	//out8(pit8254_cswr, 0x74); // Count1 in Mode2
	//out8(pit8254_cnt1, lsb); // Count1CR:low
	//out8(pit8254_cnt1, msb); // Count1CR:high

	// configure count2 for 10s
	// 10.000ms=10s => "factor"=10.000
	fac = 10000; // 10000ms=10s; 0x2710
	lsb = fac & 0xFF; // --XX low
	msb = (fac>>8) & 0xFF; // XX-- high
	//out8(pit8254_cswr, 0xB4); // Count2:Mode2
	//out8(pit8254_cnt2, lsb); // Count2:low
	//out8(pit8254_cnt2, msb); // Count2:high
}

Timer::~Timer() {
	// TODO Auto-generated destructor stub
}

