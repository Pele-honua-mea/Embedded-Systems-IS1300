/*
@brief	Pingpong, header file for Pingpong-program
@file	Test.h
@date	5 nov. 2021
@author	Elzbieta Rakoczy
@brief	Header file holding declarations of functions in test.c
 */

#ifndef INC_TEST_H_
#define INC_TEST_H_

#include "gpio.h"
#include "stdint.h"
#include "stdbool.h"

void Test_program(void);
void Test_Led(void);
void Test_showPoints(void);
bool L_hit(void);
bool R_hit(void);
void Test_buttons(void);
void Test_Blink(void);

#endif /* INC_TEST_H_ */
