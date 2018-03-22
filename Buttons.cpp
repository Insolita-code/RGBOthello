/*
*File: Buttons.cpp
*Author: Olavi Viitanen, Rauno Vesti, Mikko Uutela
*Description: Button handling for an othello game.
*/

#include <Arduino.h>
#include "Buttons.h"


#define BUTTON_LEFT A0
#define BUTTON_DOWN A1
#define BUTTON_RIGHT A2
#define BUTTON_UP A3
#define BUTTON_SELECT A4
#define BUTTON_START A5

#define KEY_RELEASED 0
#define KEY_POSSIBLY_RELEASED 1
#define KEY_PRESSED 2
#define KEY_POSSIBLY_PRESSED 3

#define DEBOUNCE_GUARD_TIME 10

int DetectLeftButtonPress()
{
	static int state = KEY_RELEASED;
	static long timeOfPreviousStateTrans = 0;
	switch(state)
	{
		case KEY_RELEASED:
			if(digitalRead(BUTTON_LEFT) == HIGH)
			{
				state = KEY_POSSIBLY_PRESSED;
				timeOfPreviousStateTrans = millis();
			}
			break;
		case KEY_POSSIBLY_PRESSED:
			if(digitalRead(BUTTON_LEFT) != HIGH)
			{
				state = KEY_RELEASED;
			}
			else if(millis() - timeOfPreviousStateTrans > DEBOUNCE_GUARD_TIME)
			{
				state = KEY_PRESSED;
				return 1;
			}
			break;
		case KEY_PRESSED:
			if(digitalRead(BUTTON_LEFT) == LOW)
			{
				state = KEY_POSSIBLY_RELEASED;
				timeOfPreviousStateTrans = millis();
			}
			break;
		case KEY_POSSIBLY_RELEASED:
			if(digitalRead(BUTTON_LEFT) != LOW)
			{
				state = KEY_PRESSED;
			}
			else if(millis() - timeOfPreviousStateTrans > DEBOUNCE_GUARD_TIME)
			{
				state = KEY_RELEASED;
			}
			break;
	}
	return 0;
}

int DetectDownButtonPress()
{
	static int state = KEY_RELEASED;
	static long timeOfPreviousStateTrans = 0;
	switch(state)
	{
		case KEY_RELEASED:
			if(digitalRead(BUTTON_DOWN) == HIGH)
			{
				state = KEY_POSSIBLY_PRESSED;
				timeOfPreviousStateTrans = millis();
			}
			break;
		case KEY_POSSIBLY_PRESSED:
			if(digitalRead(BUTTON_DOWN) != HIGH)
			{
				state = KEY_RELEASED;
			}
			else if(millis() - timeOfPreviousStateTrans > DEBOUNCE_GUARD_TIME)
			{
				state = KEY_PRESSED;
				return 1;
			}
			break;
		case KEY_PRESSED:
			if(digitalRead(BUTTON_DOWN) == LOW)
			{
				state = KEY_POSSIBLY_RELEASED;
				timeOfPreviousStateTrans = millis();
			}
			break;
		case KEY_POSSIBLY_RELEASED:
			if(digitalRead(BUTTON_DOWN) != LOW)
			{
				state = KEY_PRESSED;
			}
			else if(millis() - timeOfPreviousStateTrans > DEBOUNCE_GUARD_TIME)
			{
				state = KEY_RELEASED;
			}
			break;
	}
	return 0;
}

int DetectRightButtonPress()
{
	static int state = KEY_RELEASED;
	static long timeOfPreviousStateTrans = 0;
	switch(state)
	{
		case KEY_RELEASED:
			if(digitalRead(BUTTON_RIGHT) == HIGH)
			{
				state = KEY_POSSIBLY_PRESSED;
				timeOfPreviousStateTrans = millis();
			}
			break;
		case KEY_POSSIBLY_PRESSED:
			if(digitalRead(BUTTON_RIGHT) != HIGH)
			{
				state=KEY_RELEASED;
			}
			else if(millis() - timeOfPreviousStateTrans > DEBOUNCE_GUARD_TIME)
			{
				state = KEY_PRESSED;
				return 1;
			}
			break;
		case KEY_PRESSED:
			if(digitalRead(BUTTON_RIGHT) == LOW)
			{
				state = KEY_POSSIBLY_RELEASED;
				timeOfPreviousStateTrans = millis();
			}
			break;
		case KEY_POSSIBLY_RELEASED:
			if(digitalRead(BUTTON_RIGHT) != LOW)
			{
				state = KEY_PRESSED;
			}
			else if(millis() - timeOfPreviousStateTrans > DEBOUNCE_GUARD_TIME)
			{
				state = KEY_RELEASED;
			}
			break;
	}
	return 0;
}

int DetectUpButtonPress()
{
	static int state = KEY_RELEASED;
	static long timeOfPreviousStateTrans = 0;
	switch(state)
	{
		case KEY_RELEASED:
			if(digitalRead(BUTTON_UP) == HIGH)
			{
				state = KEY_POSSIBLY_PRESSED;
				timeOfPreviousStateTrans = millis();
			}
			break;
		case KEY_POSSIBLY_PRESSED:
			if(digitalRead(BUTTON_UP) != HIGH)
			{
				state = KEY_RELEASED;
			}
			else if(millis() - timeOfPreviousStateTrans > DEBOUNCE_GUARD_TIME)
			{
				state = KEY_PRESSED;
				return 1;
			}
			break;
		case KEY_PRESSED:
			if(digitalRead(BUTTON_UP) == LOW)
			{
				state = KEY_POSSIBLY_RELEASED;
				timeOfPreviousStateTrans = millis();
			}
			break;
		case KEY_POSSIBLY_RELEASED:
			if(digitalRead(BUTTON_UP) != LOW)
			{
				state = KEY_PRESSED;
			}
			else if(millis() - timeOfPreviousStateTrans > DEBOUNCE_GUARD_TIME)
			{
				state = KEY_RELEASED;
			}
			break;
	}
	return 0;
}

int DetectSelectButtonPress()
{
	static int state = KEY_RELEASED;
	static long timeOfPreviousStateTrans = 0;
	switch(state)
	{
		case KEY_RELEASED:
			if(digitalRead(BUTTON_SELECT) == HIGH)
			{
				state = KEY_POSSIBLY_PRESSED;
				timeOfPreviousStateTrans = millis();
			}
			break;
		case KEY_POSSIBLY_PRESSED:
			if(digitalRead(BUTTON_SELECT) != HIGH)
			{
				state = KEY_RELEASED;
			}
			else if(millis() - timeOfPreviousStateTrans > DEBOUNCE_GUARD_TIME)
			{
				state = KEY_PRESSED;
				return 1;
			}
			break;
		case KEY_PRESSED:
			if(digitalRead(BUTTON_SELECT) == LOW)
			{
				state = KEY_POSSIBLY_RELEASED;
				timeOfPreviousStateTrans = millis();
			}
			break;
		case KEY_POSSIBLY_RELEASED:
			if(digitalRead(BUTTON_SELECT) != LOW)
			{
				state = KEY_PRESSED;
			}
			else if(millis() - timeOfPreviousStateTrans > DEBOUNCE_GUARD_TIME)
			{
				state = KEY_RELEASED;
			}
			break;
	}
	return 0;

}

int DetectStartButtonPress()
{
	static int state = KEY_RELEASED;
	static long timeOfPreviousStateTrans = 0;
	switch(state)
	{
		case KEY_RELEASED:
			if(digitalRead(BUTTON_START) == HIGH)
			{
				state = KEY_POSSIBLY_PRESSED;
				timeOfPreviousStateTrans = millis();
			}
			break;
		case KEY_POSSIBLY_PRESSED:
			if(digitalRead(BUTTON_START) != HIGH)
			{
				state = KEY_RELEASED;
			}
			else if(millis() - timeOfPreviousStateTrans > DEBOUNCE_GUARD_TIME)
			{
				state = KEY_PRESSED;
				return 1;
			}
			break;
		case KEY_PRESSED:
			if(digitalRead(BUTTON_START) == LOW)
			{
				state = KEY_POSSIBLY_RELEASED;
				timeOfPreviousStateTrans = millis();
			}
			break;
		case KEY_POSSIBLY_RELEASED:
			if(digitalRead(BUTTON_START) != LOW)
			{
				state = KEY_PRESSED;
			}
			else if(millis() - timeOfPreviousStateTrans > DEBOUNCE_GUARD_TIME)
			{
				state = KEY_RELEASED;
			}
			break;
	}
	return 0;

}

int DetectStartButtonHold()
{
	static int state = KEY_RELEASED;
	static long timeOfPreviousStateTrans = 0;
	switch(state)
	{
		case KEY_RELEASED:
			if(digitalRead(BUTTON_START) == HIGH)
			{
				state = KEY_POSSIBLY_PRESSED;
				timeOfPreviousStateTrans = millis();
			}
			break;
		case KEY_POSSIBLY_PRESSED:
			if(digitalRead(BUTTON_START) != HIGH)
			{
				state = KEY_RELEASED;
			}
			else if(millis() - timeOfPreviousStateTrans > 3000)
			{
				state = KEY_PRESSED;
				return 1;
			}
			break;
		case KEY_PRESSED:
			if(digitalRead(BUTTON_START) == LOW)
			{
				state = KEY_POSSIBLY_RELEASED;
				timeOfPreviousStateTrans = millis();
			}
			break;
		case KEY_POSSIBLY_RELEASED:
			if(digitalRead(BUTTON_START) != LOW)
			{
				state = KEY_PRESSED;
			}
			else if(millis() - timeOfPreviousStateTrans > DEBOUNCE_GUARD_TIME)
			{
				state = KEY_RELEASED;
			}
			break;
	}
	return 0;
}