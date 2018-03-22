/*
*File: GameOthello.cpp
*Author: Olavi Viitanen, Rauno Vesti, Mikko Uutela
*Description: Othello game functions
*/
#include "GameOthello.h"

#define PLAYER1_COLOR 1
#define PLAYER2_COLOR 2

#define UP 1
#define DOWN 2
#define RIGHT 4
#define LEFT 8
#define UP_RIGHT 16
#define UP_LEFT 32
#define DOWN_RIGHT 64
#define DOWN_LEFT 128

int othelloBoard[8][8] ={{0,0,0,0,0,0,0,0}
						,{0,0,0,0,0,0,0,0}
						,{0,0,0,0,0,0,0,0}
						,{0,0,0,PLAYER2_COLOR,PLAYER1_COLOR,0,0,0}
						,{0,0,0,PLAYER1_COLOR,PLAYER2_COLOR,0,0,0}
						,{0,0,0,0,0,0,0,0}
						,{0,0,0,0,0,0,0,0}
						,{0,0,0,0,0,0,0,0}};


static int cursorPosition[2] = {3,3}; /*{x,y}*/
/*Player turn: 1 for player1, 2 for player2* /*/

void initOthelloBoard() 
{
	int startingOthelloBoard[8][8] = {{0,0,0,0,0,0,0,0}
					,{0,0,0,0,0,0,0,0}
					,{0,0,0,0,0,0,0,0}
					,{0,0,0,PLAYER2_COLOR,PLAYER1_COLOR,0,0,0}
					,{0,0,0,PLAYER1_COLOR,PLAYER2_COLOR,0,0,0}
					,{0,0,0,0,0,0,0,0}
					,{0,0,0,0,0,0,0,0}
					,{0,0,0,0,0,0,0,0}};

	for (int yAxis = 0; yAxis <= 7; yAxis++)
	{
		for (int xAxis = 0; xAxis <= 7; xAxis++)
		{
			othelloBoard[yAxis][xAxis] = startingOthelloBoard[yAxis][xAxis];
		}
	}
}

void cursorToDefaultPosition() 
{
	cursorPosition[0] = 3;
	cursorPosition[1] = 3;
}

void moveCursorUp()
{
	if(cursorPosition[1] == 0) // Stop movement off the edge
	{
		return;
	}
	cursorPosition[1] -= 1;
}

void moveCursorDown()
{
	if (cursorPosition[1] == 7)
	{
		return;
	}
	cursorPosition[1] += 1;
}

void moveCursorRight()
{
	if (cursorPosition[0] == 7)
	{
		return;
	}
	cursorPosition[0] += 1;
}

void moveCursorLeft()
{
	if (cursorPosition[0] == 0)
	{
		return;
	}
	cursorPosition[0] -= 1;
}

int getCursorX()
{
	return cursorPosition[0];
}

int getCursorY()
{
	return cursorPosition[1];
}

/*Return 1 if empty*/
int checkIfEmptySquare(int xAxis, int yAxis)
{
	if (othelloBoard[yAxis][xAxis] == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*Return value based on the valid directions*/
/*	Up:			1
	down:		2
	right:		4
	left:		8
	UpRight:	16
	UpLeft:		32
	DownRight:	64
	DownLeft	128
	*/
int checkIfPlacementValid(int xAxis, int yAxis, int playerTurn)
{
	if (checkIfEmptySquare(xAxis, yAxis) == 0)
	{
		return 0;
	}
	int player = 0;
	int opponent = 0;
	int isValid = 0;
	int opponentPiecesBetween = 0;
	/*Determine friendly and enemy pieces*/
	if (playerTurn == 1)
	{
		player = PLAYER1_COLOR;
		opponent = PLAYER2_COLOR;
	} 
	else
	{
		player = PLAYER2_COLOR;
		opponent = PLAYER1_COLOR;
	}
	/*Check if there are pieces to capture*/
	/*A number is added to isValid based on the valid direction*/
	/*Up:		1
	  down:		2
	  right:	4
	  left:		8
	  UpRight:	16
	  UpLeft:	32
	  DownRight:64
	  DownLeft	128
	 */
	/*Up*/
	opponentPiecesBetween = 0;
	for (int i = yAxis -1; i >= 0; i--)
	{
		if (othelloBoard[i][xAxis] == 0)
		{
			break;
		}
		if (othelloBoard[i][xAxis] == opponent)
		{
			opponentPiecesBetween += 1;
		}
		else if ((othelloBoard[i][xAxis] == player) && (opponentPiecesBetween > 0))
		{
			isValid += UP;
			break;
		}
	}
	/*Down*/
	opponentPiecesBetween = 0;
	for (int i = yAxis +1; i <= 7; i++)
	{
		if (othelloBoard[i][xAxis] == 0)
		{
			break;
		}
		if (othelloBoard[i][xAxis] == opponent)
		{
			opponentPiecesBetween += 1;
		}
		else if ((othelloBoard[i][xAxis] == player) && (opponentPiecesBetween > 0))
		{
			isValid += DOWN;
			break;
		}
	}
	/*Right*/
	opponentPiecesBetween = 0;
	for (int i = xAxis +1; i <= 7; i++)
	{
		if (othelloBoard[yAxis][i] == 0)
		{
			break;
		}
		if (othelloBoard[yAxis][i] == opponent)
		{
			opponentPiecesBetween += 1;
		}
		else if ((othelloBoard[yAxis][i] == player) && (opponentPiecesBetween > 0))
		{
			isValid += RIGHT;
			break;
		}
	}
	/*Left*/
	opponentPiecesBetween = 0;
	for (int i = xAxis -1; i >= 0; i--)
	{
		if (othelloBoard[yAxis][i] == 0)
		{
			break;
		}
		if (othelloBoard[yAxis][i] == opponent)
		{
			opponentPiecesBetween += 1;
		}
		else if ((othelloBoard[yAxis][i] == player) && (opponentPiecesBetween > 0))
		{
			isValid += LEFT;
			break;
		}
	}
	/*Up and right diagonal*/
	opponentPiecesBetween = 0;
	for (int i = 1; i <= 7; i++)
	{
		if ((yAxis - i < 0) || (xAxis + i > 7))
		{
			/*Out of bounds*/
			break;
		}
		if (othelloBoard[yAxis - i][xAxis + i] == 0)
		{
			break;
		}
		if (othelloBoard[yAxis - i][xAxis + i] == opponent)
		{
			opponentPiecesBetween += 1;
		}
		else if ((othelloBoard[yAxis - i][xAxis + i] == player) && (opponentPiecesBetween > 0))
		{
			isValid += UP_RIGHT;
			break;
		}
	}
	/*Up and left diagonal*/
	opponentPiecesBetween = 0;
	for (int i = 1; i <= 7; i++)
	{
		if ((yAxis - i < 0) || (xAxis - i < 0))
		{
			/*Out of bounds*/
			break;
		}
		if (othelloBoard[yAxis - i][xAxis - i] == 0)
		{
			break;
		}
		if (othelloBoard[yAxis - i][xAxis - i] == opponent)
		{
			opponentPiecesBetween += 1;
		}
		else if ((othelloBoard[yAxis - i][xAxis - i] == player) && (opponentPiecesBetween > 0))
		{
			isValid += UP_LEFT;
			break;
		}
	}
	/*Down and right diagonal*/
	opponentPiecesBetween = 0;
	for (int i = 1; i <= 7; i++)
	{
		if ((yAxis + i > 7) || (xAxis + i > 7))
		{
			/*Out of bounds*/
			break;
		}
		if (othelloBoard[yAxis + i][xAxis + i] == 0)
		{
			break;
		}
		if (othelloBoard[yAxis + i][xAxis + i] == opponent)
		{
			opponentPiecesBetween += 1;
		}
		else if ((othelloBoard[yAxis + i][xAxis + i] == player) && (opponentPiecesBetween > 0))
		{
			isValid += DOWN_RIGHT;
			break;
		}
	}
	/*Down and left diagonal*/
	opponentPiecesBetween = 0;
	for (int i = 1; i <= 7; i++)
	{
		if ((yAxis + i > 7) || (xAxis - i < 0))
		{
			/*Out of bounds*/
			break;
		}
		if (othelloBoard[yAxis + i][xAxis - i] == 0)
		{
			break;
		}
		if (othelloBoard[yAxis + i][xAxis - i] == opponent)
		{
			opponentPiecesBetween += 1;
		}
		else if ((othelloBoard[yAxis + i][xAxis - i] == player) && (opponentPiecesBetween > 0))
		{
			isValid += DOWN_LEFT;
			break;
		}
	}

	return isValid;
}

/*Check all squares one by one.*/
int checkIfAnyValidPlacements(int playerTurn)
{
	int validPlacementFound = 0;
	for (int yAxis = 0; yAxis <= 7; yAxis++)	/*Loop through columns*/
	{
		for (int xAxis = 0; xAxis <= 7; xAxis++)	/*Loop through rows*/
		{
			if (checkIfPlacementValid(xAxis, yAxis, playerTurn))
			{
				validPlacementFound = 1;
			}
		}
	}
	return validPlacementFound;
}

/*Change disk colors to their new owner*/
void captureDisks(int xAxis, int yAxis, int playerTurn, int validDirections)
{
	int player = 0;
	int opponent = 0;
	/*Determine friendly and enemy pieces*/
	if (playerTurn == 1)
	{
		player = PLAYER1_COLOR;
		opponent = PLAYER2_COLOR;
	}
	else
	{
		player = PLAYER2_COLOR;
		opponent = PLAYER1_COLOR;
	}

	/*Change opponent disks to player's disks*/
	/*Up:		1
	  down:		2
	  right:	4
	  left:		8
	  UpRight:	16
	  UpLeft:	32
	  DownRight:64
	  DownLeft	128
	 */
	/*Up*/
	if (validDirections & UP)
	{
		for (int i = yAxis -1; i >= 0; i--)	/*Start looping one square from the placement.*/
		{
			if (othelloBoard[i][xAxis] == opponent)	/*Change opponents color to player's*/
			{
				(othelloBoard[i][xAxis] = player);
			}
			else if ((othelloBoard[i][xAxis] == player)) /*End when player's own piece is seen*/
			{
				break;
			}
		}
	}
	/*Down*/
	if (validDirections & DOWN)
	{
		for (int i = yAxis +1; i <= 7; i++)
		{
			if (othelloBoard[i][xAxis] == opponent)
			{
				(othelloBoard[i][xAxis] = player);
			}
			else if ((othelloBoard[i][xAxis] == player))
			{
				break;
			}
		}
	}
	/*Right*/
	if (validDirections & RIGHT)
	{
		for (int i = xAxis +1; i <= 7; i++)
		{
			if (othelloBoard[yAxis][i] == opponent)
			{
				(othelloBoard[yAxis][i] = player);
			}
			else if ((othelloBoard[yAxis][i] == player))
			{
				break;
			}
		}
	}
	/*Left*/
	if (validDirections & LEFT)
	{
		for (int i = xAxis -1; i >= 0; i--)
		{
			if (othelloBoard[yAxis][i] == opponent)
			{
				(othelloBoard[yAxis][i] = player);
			}
			else if ((othelloBoard[yAxis][i] == player))
			{
				break;
			}
		}
	}
	/*Up and right diagonal*/
	if (validDirections & UP_RIGHT)
	{
		for (int i = 1; i <= 7; i++)
		{
			if (othelloBoard[yAxis - i][xAxis + i] == opponent)
			{
				othelloBoard[yAxis - i][xAxis + i] = player;
			}
			else if (othelloBoard[yAxis - i][xAxis + i] == player)
			{
				break;
			}
		}
	}
	/*Up and left diagonal*/
	if (validDirections & UP_LEFT)
	{
		for (int i = 1; i <= 7; i++)
		{
			if (othelloBoard[yAxis - i][xAxis - i] == opponent)
			{
				othelloBoard[yAxis - i][xAxis - i] = player;
			}
			else if (othelloBoard[yAxis - i][xAxis - i] == player)
			{
				break;
			}
		}
	}
	/*Down and right diagonal*/
	if (validDirections & DOWN_RIGHT)
	{
		for (int i = 1; i <= 7; i++)
		{
			if (othelloBoard[yAxis + i][xAxis + i] == opponent)
			{
				othelloBoard[yAxis + i][xAxis + i] = player;
			}
			else if (othelloBoard[yAxis + i][xAxis + i] == player)
			{
				break;
			}
		}
	}
	/*Down and left diagonal*/
	if (validDirections & DOWN_LEFT)
	{
		for (int i = 1; i <= 7; i++)
		{
			if (othelloBoard[yAxis + i][xAxis - i] == opponent)
			{
				othelloBoard[yAxis + i][xAxis - i] = player;
			}
			else if (othelloBoard[yAxis + i][xAxis - i] == player)
			{
				break;
			}
		}
	}
}

/*Place a disk and do the required checks for it*/
int placeDisk(int xAxis, int yAxis, int playerTurn)
{
	if (checkIfEmptySquare(xAxis, yAxis))
	{
		int validDirections = checkIfPlacementValid(xAxis, yAxis, playerTurn);
		if (validDirections > 0)
		{
			/*Place marker*/
			int player = 0;
			int opponent = 0;
			/*Determine friendly and enemy pieces*/
			if (playerTurn == 1)
			{
				player = PLAYER1_COLOR;
			}
			else
			{
				player = PLAYER2_COLOR;
			}
			othelloBoard[yAxis][xAxis] = player;
			captureDisks(xAxis, yAxis, playerTurn, validDirections);
			return 1;
		}
	}
}

/*Count the amount of player 1's disks*/
int countPlayer1Score()
{
	int score = 0;
	for (int row = 0; row <= 7; row++)
	{
		for (int column = 0; column <= 7; column++)
		{
			if (othelloBoard[row][column] == PLAYER1_COLOR)
			{
				score += 1;
			}
		}
	}

	return score;
}

/*Count the amount of player 1's disks*/
int countPlayer2Score()
{
	int score = 0;
	for (int row = 0; row <= 7; row++)
	{
		for (int column = 0; column <= 7; column++)
		{
			if (othelloBoard[row][column] == PLAYER2_COLOR)
			{
				score += 1;
			}
		}
	}

	return score;
}