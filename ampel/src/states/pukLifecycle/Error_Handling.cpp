/*
 * Error_Handling.cpp
 *
 *  Created on: 31.05.2015
 *      Author: swizes
 */


#include "PuckStates.h"


Error_Handling::Error_Handling(Context* con): State::State(con){
	printf("Error Handling()\n");
}

Error_Handling::~Error_Handling(){
	printf("~Error Handling()\n");
}

//TODO: Error Handling function

