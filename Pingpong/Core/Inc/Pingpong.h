/*
@brief	Pingpong, header file for Pingpong-program
@file	Pingpong.h
@date	5 nov. 2021
@author	Elzbieta Rakoczy
@brief	Header file holding declarations of functions in pingpong_functions.c
 */

#ifndef INC_PINGPONG_H_
#define INC_PINGPONG_H_
#include "stdint.h"

void Pingpong(void);
void Led_on(uint8_t Lednr);
void Show_points(uint8_t L_points, uint8_t R_points);
void Blinking(uint8_t blinkNumber);


#endif /* INC_PINGPONG_H_ */
