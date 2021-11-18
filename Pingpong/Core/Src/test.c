/*
@brief	Pingpong, test functions for Pingpong-program
@file	test.c
@date	5 nov. 2021
@author	Elzbieta Rakoczy
@brief	Testing pingpong_functions.c functions
 */
#include "Pingpong.h"
#include "Test.h"
#include "stm32l4xx_hal.h"


/*Running the tests for each pingpong_function.c function*/
void Test_program(void){
	//Test_Led();
	Test_showPoints();
	//Test_buttons();
	//Test_Blink();
}

void Test_Led(void){
	int8_t Lednr;
	/* Loop checking that all leds can be turned on*/
	for(Lednr=1; Lednr<=8; Lednr++){
		Led_on(Lednr);
		HAL_Delay(500);
	}
	Led_on(9); //Turn off led 8
	HAL_Delay(1000); // 1000 ms
	return;
}
void Test_Blink(void){
	Blinking(3);
}

void Test_showPoints(void){
	int8_t L_points; //points for left player
	int8_t R_points; //points for right player
	for(L_points = 0; L_points <= 4; L_points++){
		for(R_points = 0; R_points <= 4; R_points++){
			Show_points(0,1);	// right player scores a point
			HAL_Delay(1000);
			Show_points(0,2);	// right player scores a second point
			HAL_Delay(1000);
			Show_points(1,2);	// left player scores a point
			HAL_Delay(1000);
			Show_points(1,3);	// right player scores a third points
			HAL_Delay(1000);
			Show_points(2,3);	// left player scores a second point
			HAL_Delay(1000);
			Show_points(4,2);
			HAL_Delay(1000);
			Show_points(2,4);
			HAL_Delay(1000);
		}

	}
	return;
}

void Test_buttons(void)
{
	int8_t j;
 /* Checking buttons */
	j=4;	// Led4
	Led_on(j); // Light on
	while (j<9 && j>0)
	{
		if ( L_hit() == true ) // Wait for left button hit
		{
			j++; // next led to the right
			Led_on(j); // Light on
			HAL_Delay(100); // 100 ms
			while ( L_hit() == true ); // Wait for button release
			HAL_Delay(100); // 100 ms
		}
		if ( R_hit() == true ) // Wait for right button hit
		{
			j--; // next led to the left
			Led_on(j); // Light on
			HAL_Delay(100); // 100 ms
			while ( R_hit() == true ); // Wait for button release
			HAL_Delay(100); // 100 ms
			if (j<1) j=0; // Start again from left
		}
	}
	return;
 }
