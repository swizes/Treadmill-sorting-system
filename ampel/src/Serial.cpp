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
	#ifdef SIMULATION
		this->dev_ = "/dev/serusb1";
    #endif
	#ifndef SIMULATION
	this->dev_ = "/dev/ser1";
    #endif
	this->fdesc_ = open(this->dev_, O_RDWR);
	if(this->fdesc_ == -1){
			exit(-1);
	}

	this->config();
}

Serial::~Serial(){
	// Close File descriptor
	if( close(this->fdesc_) < 0 ){
		exit(-1);
	}
}

void Serial::config(void){
    struct termios ts;
    tcflush(this->fdesc_, TCIOFLUSH);
    tcgetattr(this->fdesc_, &ts);
    cfsetispeed(&ts, B19200);
    cfsetospeed(&ts, B19200);
    ts.c_cflag &= ~CSIZE;
    ts.c_cflag &= ~CSTOPB;
    ts.c_cflag &= ~PARENB;
    ts.c_cflag |= CS8;
    ts.c_cflag |= CREAD;
    ts.c_cflag |= CLOCAL;
    tcsetattr(this->fdesc_, TCSANOW, &ts);
}

int Serial::sendPacket(Packet* p){
	write(this->fdesc_, p, sizeof(Packet));
	return 0;
}

int Serial::recvPacket(Packet* p){
	if( readcond(this->fdesc_, p, sizeof(Packet), sizeof(Packet), 0, 0) > 0) {
		return 0;
	}
	return -1;
}

int Serial::sendPacket(puckStruct* puck){
	write(this->fdesc_, puck, sizeof(puckStruct));
		return 0;
}

int Serial::recvPacket(puckStruct* puck){
	if( readcond(this->fdesc_, puck, sizeof(puckStruct), sizeof(puckStruct), 0, 0) > 0) {
		return 0;
	}
	return -1;
}

int Serial::startreq(){
	Packet p;
	memset(&p, 0 , sizeof(p));
	p.num = 0;
	sendPacket(&p);
	return -1;
}

int Serial::startresp(){
	Packet p;
	memset(&p, 0 , sizeof(p));
	p.num = 0;
	recvPacket(&p);
	return -1;
}

