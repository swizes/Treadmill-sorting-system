/*
 * Serial.cpp
 *
 *  Created on: 17.04.2015
 *      Author: Lukas Wendt
 */

#include <stdint.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Serial.h"

Serial::Serial() {
	this->dev_ = "/dev/ser1";
		this->fdesc_ = open(this->dev_, O_RDWR);
		if(this->fdesc_ == -1){
			exit(-1);
	}
}

Serial::~Serial(){
	// Close File descriptor
	if( close(this->fdesc_) < 0 ){
		exit(-1);
	}
}

