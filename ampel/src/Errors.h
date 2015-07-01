/*
 * Errors.h
 *
 *  Created on: 24.06.2015
 *      Author: Roland M
 */
 

 // TimeOuts
 #define ERROR_TIMOUT_Birth2RtoH    100 /* timeout from <Birth> to <Road to Height> */
 #define ERROR_TIMOUT_RtoH2HM       101 /* timeout from <Road to Height> to <Height Measurement> */
 #define ERROR_TIMOUT_HM2SfH        102 /* timeout from <Height Measurement> to <Search for Hole> */
 #define ERROR_TIMOUT_SfH2RtoM      103 /* timeout from <Search for Hole> to <Road to Metal> */
 #define ERROR_TIMOUT_RtoM2IiG      104 /* timeout from <Road to Metal> to <Is in Gate> */
 #define ERROR_TIMOUT_IiG2RtoE      105 /* timeout from <Is in Gate> to <Road to Exit> */
 #define ERROR_TIMOUT_SfH2RtoSO     106 /* timeout from <Search for Hole> to <Road to Sorting Out> */
 #define ERROR_TIMOUT_RtoSO2FP      107 /* timeout from <Road to Sorting Out> to <Flipping Puck> */
 #define ERROR_TIMOUT_FP2IiS        108 /* timeout from <Flipping Puck> to <Is In Slide> */
 #define ERROR_TIMOUT_RtoE			109 /*  timeout in <Road to Exit> */
 
 // TooSoon
 #define ERROR_2SOON_Birth2RtoH    200 /* too soon from <Birth> to <Road to Height> */
 #define ERROR_2SOON_RtoH2HM       201 /* too soon from <Road to Height> to <Height Measurement> */
 #define ERROR_2SOON_HM2SfH        202 /* too soon from <Height Measurement> to <Search for Hole> */
 #define ERROR_2SOON_SfH2RtoM      203 /* too soon from <Search for Hole> to <Road to Metal> */
 #define ERROR_2SOON_RtoM2IiG      204 /* too soon from <Road to Metal> to <Is in Gate> */
 #define ERROR_2SOON_IiG2RtoE      205 /* too soon from <Is in Gate> to <Road to Exit> */
 #define ERROR_2SOON_SfH2RtoSO     206 /* too soon from <Search for Hole> to <Road to Sorting Out> */
 #define ERROR_2SOON_RtoSO2FP      207 /* too soon from <Road to Sorting Out> to <Flipping Puck> */
 #define ERROR_2SOON_FP2IiS        208 /* too soon from <Flipping Puck> to <Is In Slide> */
 #define ERROR_2SOON_RtoE          209 /* too soon in <Road to Exit> */
 //
#define ERROR_SLIDEFULL            300 /* slide is full */
#define ERROR_MAX_PUCKS            301 /* maximum pucks on band reached */
#define ERROR_2BIG4PUCK            302 /* object on line is too big */

int errors_print(int errcode);
