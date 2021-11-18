/*
 * @brief	Pingpong, source code for Pingpong-program
 * @file	pingpong.c
 * @date	5 nov. 2021
 * @author	Elzbieta Rakoczy
 * @brief	States for the Pingpong game:
 * 			Start: The very beginning of the game. Players choose themselves who serves first.
 * 			Start2: After the first serve, only the player who hasn't served in the last round
 * 			can serve.
 * 			MoveRight: The ball moves towards the right player
 * 			LeftRight: The ball moves towards the left player
 * 			Points: Shows the points and goes to Start or Start2 dependently on the score
 */
#include "Pingpong.h"
#include "Test.h"
/* Define states for state machine*/
typedef enum
{ 	Start,
	Start2,
	MoveRight,
	MoveLeft,
	Points
} states;

static states State, NextState;

void Pingpong(void)
{
	bool ButtonPressed = false; // To remember that button is pressed
	uint32_t Varv, MinSpeed, MaxSpeed; // Ball speed
	uint8_t Led; // LED nr
	uint8_t L_points = 0; // To initialize amount of points for left player
	uint8_t R_points = 0; // To initialize amount of points for right player
	bool L_serve;	// Left player turn to serve (true/false)
	bool R_serve;	// Right player turn to serve (true/false)
	State= Start; // Initiate State to Start
	NextState= Start;
	MinSpeed= 500000;	// Number of loops (speed at the beginning of each serve)
	MaxSpeed = 100000;	// Number of loops (the maximal speed after increasing the speed)
	/* Infinite loop */
	while (1)
	{
		State = NextState;
		switch (State) // State machine
		{
		case Start:
			Led_on(0); // Turn off all LEDs
			MinSpeed = 500000;
			if ( L_hit() == true) // L serve
			{
				L_serve = false; //if L_hit the first time, it can't start next time
				R_serve = true;	//if L_hit the first time, right player serves next time
				Led = 1;
				NextState= MoveRight;
				while ( L_hit() == true ); // wait until button is released
			}
			else if ( R_hit() == true) // R serve
			{
				L_serve = true; //if R_hit the first time it can't start next time
				R_serve = false;	//if R_hit the first time, left player serves next time
				Led = 8;
				NextState= MoveLeft;
				while ( R_hit() == true ); // wait until button is released
			}
			else
				NextState = Start; // Stay in Start state
			break;

		case Start2:
		{
			Led_on(0);
			MinSpeed = 500000;
			if(L_hit() == true && L_serve == true){
				L_serve = false;
				R_serve = true;
				Led = 1;
				NextState = MoveRight;
				while(L_hit() == true);
			}
			else if(R_hit() == true && R_serve == true){
				L_serve = true;
				R_serve = false;
				Led = 8;
				NextState = MoveLeft;
				while(R_hit() == true);
			}
			else
				NextState = Start2;
			break;
		}
		case MoveRight:
		{
			Led_on(Led);
			Varv = MinSpeed;
			while( Varv != 0 )
			{
				if ( R_hit() ) ButtonPressed = true; // R hit
				Varv--;
			}
			if ( ButtonPressed ) // R pressed
			{
				if ( Led == 8 ) // and LED8 active
				{
					if(MaxSpeed < MinSpeed){
						MinSpeed -= 50000;
					}
					else{
						MinSpeed = MaxSpeed;
					}
					NextState=MoveLeft; // return ball
					Led=7;
				}
				else{
					L_points++;
					NextState = Points; // hit to early
				}
			}
			else
			{
				if ( Led == 9 ) // no hit or to late
				{
					L_points++;
					NextState = Points;
				}
				else
					NextState = MoveRight; // ball continues to move right
			}
			if ( !ButtonPressed ) Led++; // prepare to turn next LED on
			ButtonPressed=false;
		}
		break;
		case MoveLeft:
		{
			Led_on(Led);
			Varv = MinSpeed;
			while(Varv != 0)
			{
				if ( L_hit() ) ButtonPressed = true; // L hit
				Varv--;
			}
			if ( ButtonPressed ) // L pressed
			{
				if ( Led == 1 ) // and LED1 active
				{
					if(MaxSpeed < MinSpeed){
						MinSpeed -= 50000;
					}
					else{
						MinSpeed = MaxSpeed;
					}
					NextState=MoveRight; // return ball
					Led=2;
				}
				else{
					R_points++;
					NextState = Points; // hit to early
				}
			}
			else
			{
				if ( Led == 0 ) // no hit or to late
				{
					R_points++;
					NextState = Points;
				}
				else
					NextState = MoveLeft; // ball continues to move left
			}
			if ( !ButtonPressed ) Led--; // prepare to turn next LED on
			ButtonPressed=false;
		}
		break;

		case Points:
		{
			Led_on(0);
			Blinking(3);
			Show_points(L_points, R_points);
			if(L_points < 4 && R_points < 4){
				NextState = Start2;
			}
			else{
				L_points = 0;
				R_points = 0;
				NextState = Start;
			}
			//NextState = Start;
			break;
		}
		default:
			break;
		}
	}
} // End of function Pingpong
