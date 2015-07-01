/*
 * Errors.c
 *
 *  Created on: 24.06.2015
 *      Author: Roland M
 */
 
#include "Errors.h"
#include <stdio.h>

using namespace std;

int  errors_print(int errcode){
    printf("[ERROR %3d]: ", errcode);
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
    case ERROR_TIMOUT_RtoE:
		printf(" timeout in <Road to Exit>");
		break;
        
    // TooSoon
    case ERROR_2SOON_Birth2RtoH:
        printf("too soon from <Birth> to <Road to Height>\n");
        printf("Please remove the two last pucks");
        break;        
    case ERROR_2SOON_RtoH2HM:
        printf("too soon from <Road to Height> to <Height Measurement>\n");
        printf("Please remove the two last pucks");
        break;
    case ERROR_2SOON_HM2SfH:
        printf("too soon from <Height Measurement> to <Search for Hole>\n");
        printf("Please remove the two last pucks");
        break;
    case ERROR_2SOON_SfH2RtoM:
        printf("too soon from <Search for Hole> to <Road to Metal>\n");
        printf("Please remove the two last pucks");
        break;
    case ERROR_2SOON_RtoM2IiG:
        printf("too soon from <Road to Metal> to <Is in Gate>\n");
        printf("Please remove the two last pucks");
        break;
    case ERROR_2SOON_IiG2RtoE:
        printf("too soon from <Is in Gate> to <Road to Exit>\n");
        printf("Please remove the two last pucks");
        break;
    case ERROR_2SOON_SfH2RtoSO:
        printf("too soon from <Search for Hole> to <Road to Sorting Out>\n");
        printf("Please remove the two last pucks");
        break;
    case ERROR_2SOON_RtoSO2FP:
        printf("too soon from <Road to Sorting Out> to <Flipping Puck>\n");
        printf("Please remove the two last pucks");
        break;
    case ERROR_2SOON_FP2IiS:
        printf("too soon from <Flipping Puck> to <Is In Slide>\n");
        printf("Please remove the two last pucks");
        break;
    case ERROR_2SOON_RtoE:
    	printf(" too soon in <Road to Exit>\n");
    	printf("Please remove the two last pucks");
    	break;

        
    //Other
    case ERROR_SLIDEFULL:
        printf("slide is full\n");
        printf("Please clear slide");
        break;
    case ERROR_MAX_PUCKS:
    	printf("maximum pucks on band reached");
		break;
    case ERROR_2BIG4PUCK:
    	printf("object on line is too big\n");
    	printf( "Please remove Object");
		break;
    
 
    //
    default:
        printf("Unknown Error!");
        break;
    }
    
    printf("\n");

 return errcode;
}
 
 
