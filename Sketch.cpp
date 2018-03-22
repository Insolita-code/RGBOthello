/*
*File: Sketch.cpp
*Author: Olavi Viitanen, Rauno Vesti, Mikko Uutela
*Description: The main file for an othello game on a 8x8 rgb matrix
*/
#include <Arduino.h>

/*Include project files*/
#include "Buttons.h"
#include "LedMatrix.h"
#include "GameOthello.h"
#include "Speaker.h"

#define OTHELLO_START_SCREEN 0
#define INIT_OTHELLO 1
#define OTHELLO_TURN 2
#define OTHELLO_END_ANNOUNCEMENT 3
#define OTHELLO_END_SCORES 4
#define OTHELLO_END_BOARD 5

void setup() {

}

void loop() {
	static int programPhase = 0;
	static int currentPlayerTurn = 1;
	static int previousPlayerTurn = 0;

	static int player1Score = 0;
	static int player2Score = 0;

	static long int gameStartTime = 0;

	/*Detect button presses*/
	int leftButtonPressed = DetectLeftButtonPress();
	int downButtonPressed = DetectDownButtonPress();
	int rightButtonPressed = DetectRightButtonPress();
	int upButtonPressed = DetectUpButtonPress();
	int selectButtonPressed = DetectSelectButtonPress();
	int startButtonPressed = DetectStartButtonPress();
	int startButtonHeld = DetectStartButtonHold();

	/*Act based on the button presses and game state*/
	switch (programPhase)
	{
		case OTHELLO_START_SCREEN: /*Starting screen*/
			if (startButtonPressed)
			{
				programPhase = INIT_OTHELLO;	/*Move to game initiation*/
			}
		break;
		case INIT_OTHELLO: /*Start a new game*/
			initOthelloBoard();
			cursorToDefaultPosition();
			currentPlayerTurn = 1;
			previousPlayerTurn = 0;
			player1Score = 0;
			player2Score = 0;
			gameStartTime = millis();
			programPhase = OTHELLO_TURN; /*Move to player turn*/
		break;
		case OTHELLO_TURN: /*Player turn*/

			/*Check if the player can't play their turn*/
			if (checkIfAnyValidPlacements(currentPlayerTurn) == 0)
			{
				if (currentPlayerTurn == previousPlayerTurn)
				{
					/*There are no valid moves left for neither player.*/
					programPhase = OTHELLO_END_ANNOUNCEMENT; /*Move to the ending announcement*/
					break;
				}
				else
				{
					/*Go back to previous player*/
					if (currentPlayerTurn == 1)
					{
						currentPlayerTurn = 2;
					}
					else
					{
						currentPlayerTurn = 1;
					}
					break;
				}
			}

			/*Check for button presses*/
			if (leftButtonPressed)
			{
				moveCursorLeft();
			}
			if (rightButtonPressed)
			{
				moveCursorRight();
			}
			if (upButtonPressed)
			{
				moveCursorUp();
			}
			if (downButtonPressed)
			{
				moveCursorDown();
			}
			/*Check for START button press and hold*/
			if (startButtonHeld && (millis() - gameStartTime > 3000))
			{
				programPhase = OTHELLO_START_SCREEN; /*End game and return to start screen*/
				break;
			}

			if (selectButtonPressed) /*Try to place a disk in current cursor position*/
			{
				if (placeDisk(getCursorX(), getCursorY(), currentPlayerTurn))
				{
					/*Valid move*/
					if (currentPlayerTurn == 1)
					{
						currentPlayerTurn = 2;
						previousPlayerTurn = 1;
					}
					else
					{
						currentPlayerTurn = 1;
						previousPlayerTurn = 2;
					}
					cursorToDefaultPosition();
				}
				else
				{
					/*Invalid move*/
				}
			}
		break;
		case OTHELLO_END_ANNOUNCEMENT: /*Ending announcement*/
			player1Score = countPlayer1Score();
			player2Score = countPlayer2Score();			
			/*Briefly show the winner here*/
			programPhase = OTHELLO_END_SCORES;
		break;
		case OTHELLO_END_SCORES: /*Show player scores*/
			if (leftButtonPressed || downButtonPressed || rightButtonPressed || upButtonPressed)
			{
				programPhase = OTHELLO_END_BOARD; /*Swap to showing game board*/
				break;
			}
			if (startButtonPressed)
			{
				programPhase = OTHELLO_START_SCREEN;/*Go back to the starting screen*/
				break;
			}
			/*Show the scores*/

		break;
		case OTHELLO_END_BOARD: /*Ending game board*/
			if (leftButtonPressed || downButtonPressed || rightButtonPressed || upButtonPressed)
			{
				programPhase = OTHELLO_END_SCORES; /*Swap to showing player scores*/
				break;
			}
			if (startButtonPressed)
			{
				programPhase = OTHELLO_START_SCREEN;/*Go back to the starting screen*/
				break;
			}
			/*Show the othello game board at the end of the game*/
		break;
		default:
		/* Your code here */
		break;
	}
}
