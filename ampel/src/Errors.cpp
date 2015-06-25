/*
 * Errors.c
 *
 *  Created on: 24.06.2015
 *      Author: Roland M
 */
 
#include "Errors.h"
#include <stdio.h>


void errors_print(int errcode){
    printf("[ERROR]: ");
    switch(errcode){
        
    // TimeOuts
    case ERROR_TIMOUT_Birth2RtoH:
        printf("timeout from <Birth> to <Road to Height>");
        break;        
    case ERROR_TIMOUT_RtoH2HM:
        printf("timeout from <Road to Height> to <Height Measurement>");
        break;
    case ERROR_TIMOUT_HM2SfH:
        printf("timeout from <Height Measurement> to <Search for Hole>");
        break;
    case ERROR_TIMOUT_SfH2RtoM:
        printf("timeout from <Search for Hole> to <Road to Metal>");
        break;
    case ERROR_TIMOUT_RtoM2IiG:
        printf("timeout from <Road to Metal> to <Is in Gate>");
        break;
    case ERROR_TIMOUT_IiG2RtoE:
        printf("timeout from <Is in Gate> to <Road to Exit>");
        break;
    case ERROR_TIMOUT_SfH2RtoSO:
        printf("timeout from <Search for Hole> to <Road to Sorting Out>");
        break;
    case ERROR_TIMOUT_RtoSO2FP:
        printf("timeout from <Road to Sorting Out> to <Flipping Puck>");
        break;
    case ERROR_TIMOUT_FP2IiS:
        printf("timeout from <Flipping Puck> to <Is In Slide>");
        break;
        
    // TooSoon
    case ERROR_2SOON_Birth2RtoH:
        printf("too soon from <Birth> to <Road to Height>");
        break;        
    case ERROR_2SOON_RtoH2HM:
        printf("too soon from <Road to Height> to <Height Measurement>");
        break;
    case ERROR_2SOON_HM2SfH:
        printf("too soon from <Height Measurement> to <Search for Hole>");
        break;
    case ERROR_2SOON_SfH2RtoM:
        printf("too soon from <Search for Hole> to <Road to Metal>");
        break;
    case ERROR_2SOON_RtoM2IiG:
        printf("too soon from <Road to Metal> to <Is in Gate>");
        break;
    case ERROR_2SOON_IiG2RtoE:
        printf("too soon from <Is in Gate> to <Road to Exit>");
        break;
    case ERROR_2SOON_SfH2RtoSO:
        printf("too soon from <Search for Hole> to <Road to Sorting Out>");
        break;
    case ERROR_2SOON_RtoSO2FP:
        printf("too soon from <Road to Sorting Out> to <Flipping Puck>");
        break;
    case ERROR_2SOON_FP2IiS:
        printf("too soon from <Flipping Puck> to <Is In Slide>");
        break;

        
    //Other
    case ERROR_SLIDEFULL:
        printf("slide is full");
        break;
    case ERROR_MAX_PUCKS:
    	printf("maximum pucks on band reached");
		break;
    
 
    //
    default:
        printf("Unknown Error!");
        break;
    }
    
    printf("\n");

 //return errcode;
}
 
 
